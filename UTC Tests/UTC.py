import serial #You must install pyserial for this to work
import time
import datetime
ser = serial.Serial("/dev/cu.usbmodem1411", 9600) #make sure to configure which COM port the Arduino is in
time.sleep(7) # Sleep to set up the connection with the Arduino unit
ser.flushOutput() # Flush the outputs
message = datetime.datetime.utcnow() # Get the current UTC time - this is the starting time 
print '$' + message.isoformat() # Prints '$' plus the current UTC date/time to the console screen
ser.write('$' + message.isoformat()) # Sends the start character to start the Arduino timer. Print a '$' with the current date/time - You do not need to include the 'message.isoformat()', you just need to send '$' since the Arduino unit is only listening for '$'
time.sleep(1200) # Time the program will sleep (in seconds)
message2 = datetime.datetime.utcnow() # Get the current UTC time - this is the ending time
print '$' + message2.isoformat() # Prints ending time to console screen
ser.write('$' + message2.isoformat()) # Sends the stop character - Again you do not need to include the isoformat(), just the '$'
time.sleep(1)
ser.close() # Close the serial connection
