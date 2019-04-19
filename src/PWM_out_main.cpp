//Reads in actuator commands and sends PWM commands out
//Aaron Perry, 4/15/2019
#include <zcm/zcm-cpp.hpp>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "Navio2/PWM.h"
#include "Navio2/RCOutput_Navio2.h"
#include "Common/Util.h"
#include <memory>
//message types:
#include "../message_types/pwm_t.hpp"
#include "../message_types/rc_t.hpp"
#include "../message_types/actuators_t.hpp"
#include "../message_types/status_t.hpp"

using std::string;

class Handler
{
    public:
        ~Handler() = default;

        rc_t rc_in = {};
        status_t stat;

        Handler()
        {
            stat.should_exit = 0;
        }


        void read_rc(const zcm::ReceiveBuffer* rbuf,const string& chan,const rc_t *msg)
        {
            rc_in = *msg;
        }

        void read_stat(const zcm::ReceiveBuffer* rbuf,const string& chan,const status_t *msg)
        {
            stat = *msg;
        }
};

std::unique_ptr <RCOutput> get_rcout()
{
        auto ptr = std::unique_ptr <RCOutput>{ new RCOutput_Navio2() };
        return ptr;
}

int main(int argc, char *argv[])
{
    //load configuration variables
    int num_outputs = 11; //read in from config file
    int pwm_freq = 50; //read in from config file -potentially different per channel
    int disarm_pwm_all = 1500; //read from config file
    int servo_min = 1100; //read from config file
    int servo_max = 1900; //read from config file

    //initialize zcm
    zcm::ZCM zcm {"ipc"};

    //structures to publish
    pwm_t pwm_comm;

    //subscribe to incoming channels:
    Handler handlerObject;
    zcm.subscribe("RC_IN",&Handler::read_rc,&handlerObject);
    zcm.subscribe("STATUS",&Handler::read_stat,&handlerObject);

    //initialize PWM outputs
    //************************************************************
    auto pwm = get_rcout();

    if (check_apm()) {
        return 1;
    }

    if (getuid()) {
        std::cout << "Not root. Please launch with Sudo." << std::endl;
    }

    for (int i=0;i<=num_outputs; i++){

        if( !(pwm->initialize(i)) ) {
            return 1;
        }

        pwm->set_frequency(i, pwm_freq); //want to include pwm rate as a config variable

        if ( !(pwm->enable(i)) ) {
            return 1;
        }

        //printf("Initialized channel %i\n",i+1);
        usleep(1000000); //without this, initialization of multiple channels fails
    }

    //set disarm pwm values - need to include disarm logic
    for (int i = 0; i<=num_outputs; i++){
       pwm_comm.pwm_out[i] = disarm_pwm_all;
    }

	//done initilizing PWM outputs
    //************************************************************

    zcm.start();

    while (!handlerObject.stat.should_exit) {

        //mixing logic here - manual scaling of rc_in vs. scaling of autopilot actuators depending on operating state
        pwm_comm.pwm_out[1] = handlerObject.rc_in.rc_chan[1]; //for testing purposes
        pwm_comm.pwm_out[0] = handlerObject.rc_in.rc_chan[0]; //for testing purposes

        //command pwm values
        for (int i=0; i<=num_outputs; i++){
            pwm->set_duty_cycle(i, pwm_comm.pwm_out[i]);
        };

        //publish pwm values for logging
        zcm.publish("PWM_OUT", &pwm_comm);
    }

    std::cout << "pwm_out module exiting..." << std::endl;
    //pass a message back to monitor as well (feature to add)

    zcm.stop();

    return 0;
}