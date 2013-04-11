use: make clean
to remove exe and obj files

use: make
to compile

use: ./dvsim
to run exe

You will then be prompted by the program for the file name to be used.
topology1.txt: will run for 15 seconds, sends a data packet and drops a link at 10 sec
topology2.txt: will run for 30 seconde, sends a data packet and drops a link at 20 sec
topology3.txt: will run for 60 seconds, sends a data packet and drops a link at 30 sec
any other file: will run for 60 seconds, sends no data and drops no link