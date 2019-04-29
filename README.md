# adept-fc

This repository has the code that will run onboard the ADEPT-FC aircraft, to test flight control with distributed electric propulsion.

# Running the autopilot
1. build the software `make all` 
2. type `sudo ./bin/adept_fc >&1 | tee outlog.dat` 

This will print outputs to the terminal and to the file `outlog.dat` (usefull for flights when the terminal isn't attached). 



# VN-200 Module with ZCM Integration

Compile with this command in folder `/vnins`:
```
make all
```

Run publisher with this command in folder `/bin`:
```
./vnins
```

Run example subscriber with this command in folder `/bin`:
```
./vnins_subber
```

# Python demo

Run as:
```
python3 demo.py
```

It will read lines for 10 seconds and will compute how many lines / second were read.

# Notes

* Why is the python rate almost exactly 40 Hz (as it should be) and the C rate more like 41.5 Hz? You should check that the INS time differen
ce matches the CPU time difference.
* Should we be concerned about %CPU? It's high, peaking at about 50% for both processes. Consider testing with `nice` or `cpulimit`. Consider
 using the `python3` version, since it's simpler, more robust, easier to parse, etc., and since it seems to be taking no more %CPU than the `
C` version.

