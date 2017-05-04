## Overview
Sketches used to test how much time elapsed between sending data from one Arduino unit to another, for the second unit to parse the data,
then send that pased data back to the first Arduino unit.

The first Arduino unit would start a clock once it sent the data to the second, then it would stop the clock once the data had been received
back.

A number of techniques were used, such as sending strings through "Serial.print(....)", which sends data over the Xbee radio modules. The strings would need to be parsed into the needed data types (floats, doubles, etc.).
The EasyTransfer Library was also used to send data back and forth between two Arduino modules.
