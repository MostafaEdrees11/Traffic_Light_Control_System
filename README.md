# Traffic Light Control System 🚥🚥

## Description
Traffic Light Control System which will include two traffic lights one for cars🚙, 
the other for pedestrian🚶 and will have two modes:
### Normal Mode
Car traffic leds will be changed every 5 seconds starting from green 
then yellow then red then yellow then green.

### Pedestrian Mode

the switch from Normal mode will happen when pedestrian presses the 
pedestrain button.
#### 1st state
if pressed when the Cars' Red LED is on, the pedestrian's Green LED and the
cars' Red LEDs will be on for 5 seconds, this means that pedestrians can 
cross the street while the pedestrian's Green LED is on.
#### 2nd state
if pressed when the cars' Green LED is on or the cars' Yellow LED is on,
the pedestrian Red LED will be on then both Yellow LEDs start to on for 5
seconds, then the cars' Red LEDs and the pedestrian's Green LED are on for
5 seconds, this means that pedestrian must wait until the Green LED is on.

At the end of the two states, the cars Red LED will be off and Yellow LED 
will be on for 5 seconds and the pedestrian's Green LED is still on.

___
## Simulation On Proteus:
![gitHub]()

## Run on Hardware 
[Video](https://drive.google.com/file/d/1BRXUtF_cBBFVytFZ_16nYZREgBYJc_ae/view?usp=drive_link)
___

## Analysis
![gitHub]()
![gitHub]()
![gitHub]()