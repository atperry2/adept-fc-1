CXX = g++
CXXFLAGS = -Wall -g
NAVIO = ../Navio2/C++/Navio
INCS = -I./message_types -I$(NAVIO) -L$(NAVIO)  
LIBS = -lzcm -lnavio 
BIN = ./bin
SRC = ./src

all: vnins subber demo pwm_out scribe rc_in adept_fc autopilot interface monitor 

vnins: $(SRC)/vnins.cpp
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/vnins.cpp $(SRC)/rs232.c -o $(BIN)/vnins

subber: $(SRC)/subber.cpp
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/subber.cpp -o $(BIN)/vnins_subber

demo: $(SRC)/demo.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/demo.cpp $(SRC)/rs232.c -o $(BIN)/demo

pwm_out: $(SRC)/PWM_out_main.cpp 
	$(CXX) $(CXXFLAGS) $(SRC)/PWM_out_main.cpp $(LIBS) $(INCS) -o $(BIN)/pwm_out

scribe: $(SRC)/scribe_main.cpp
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/scribe_main.cpp -o $(BIN)/scribe 

rc_in: $(SRC)/RC_in_main.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/RC_in_main.cpp $(LIBS) $(INCS) -o $(BIN)/rc_in 

adept_fc: $(SRC)/adept_fc_main.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/adept_fc_main.cpp -o $(BIN)/adept_fc 

autopilot: $(SRC)/autopilot_main.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/autopilot_main.cpp -o $(BIN)/autopilot 

interface: $(SRC)/interface.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/interface.cpp -o $(BIN)/interface 

monitor: $(SRC)/monitor.cpp 
	$(CXX) $(CXXFLAGS) $(INCS) $(LIBS) $(SRC)/monitor.cpp -o $(BIN)/monitor 

clean:
	rm -f $(BIN)/vnins
	rm -f $(BIN)/vnins_subber
	rm -f $(BIN)/demo
	rm -f $(BIN)/pwm_out
	rm -f $(BIN)/scribe
	rm -f $(BIN)/rc_in
	rm -f $(BIN)/adept_fc 
	rm -f $(BIN)/autopilot
	rm -f $(BIN)/interface 
	rm -f $(BIN)/monitor
