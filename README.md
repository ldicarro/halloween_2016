This project is an Arduino implementation of the "screaming pumpkins" that are found around Halloween time. It incorporates a PIR sensor as an input and uses LEDs, a buzzer, and a motor as an output. When the PIR sensor goes high (senses movement), the outputs animate for 10 seconds. Animation means turning the outputs on and off in a pattern. 

The code is written in a "state machine" pattern. This means that the loop() function is not blocked when the outputs are turned off and on. Flags are set to HIGH or LOW to detemine if the animation should be running as well as whether the output should be high or low. All timing is based on milliseconds except a counter used to stagger the motor animation.

Materials needed:
1	Arduino (Uno or higher)
1	PIR sensor
3	LEDs
1 	Piezo Buzzer
1	Small DC Hobby Motor
2	NPN transistors
1	9V Battery and connector
*	Hookup Wire

All of these are stuffed into a Halloween prop.

You view the wiring and component mock up here: https://circuits.io/circuits/2951213-pumpkin/embed#breadboard
