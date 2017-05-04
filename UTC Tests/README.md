## Overview
Execute the Python script to characterize the clocks of the Arduino microcontrollers. You will need two Arduino microcontrollers:
1.) To send data over Serial1, with the Tx pin connceted to the Rx pin of the second Arduino and the Rx pin connected to the Tx pin on the second
2.) This one reads the character from the first Arduino controller and starts a timer once the '$' character is recieved. After the Python scripts wakes up from sleep after a set amount of time, it will send another '$' character to stop the timer on this Arduino unit
You will need to configure the Python script for the right COM port on your computer, and also adjust the time that you want the script to sleep.
