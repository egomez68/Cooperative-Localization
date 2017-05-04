## Overview
The code to be used for each of the RSUs, which have their known latitude and longitude values hard-coded in, given to the team by the surveyors.
The RSUs broadcast the known error in the GPS messages to the other vehicles in the network.

### Deprecated
The RSUs no longer use interrupts to get their GPS measurements, so the interrupt function has been commented out in all of the RSU sketches
The RSUs just get their new GPS measurements in the main loop.
