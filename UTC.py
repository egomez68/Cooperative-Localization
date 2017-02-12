import serial #You must install pyserial for this to work
import time
import datetime
ser = serial.Serial("/dev/cu.usbmodem1411", 9600) #make sure to configure which COM port the Arduino is in
time.sleep(7)
ser.flushOutput()
message = datetime.datetime.utcnow()
print '$' + message.isoformat()
ser.write('$' + message.isoformat())
time.sleep(1200)
message2 = datetime.datetime.utcnow()
print '$' + message2.isoformat()
ser.write('$' + message2.isoformat())
time.sleep(1)
ser.close()
