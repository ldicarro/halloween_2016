This project is an Arduino implementation of the "screaming pumpkins" that are found around Halloween time. It incorporates a PIR sensor as an input and uses LEDs, a buzzer, and a motor as an output. When the PIR sensor goes high (senses movement), the outputs animate for 10 seconds. Animation means turning the outputs on and off in a pattern. 

The code is written in a "state machine" pattern. This means that the loop() function is not blocked when the outputs are turned off and on. Flags are set to HIGH or LOW to detemine if the animation should be running as well as whether the output should be high or low. All timing is based on milliseconds except a counter used to stagger the motor animation.

Materials needed:
<table cellspacing='0' border='1'>
	<tr><td>1</td><td>Arduino (Uno or higher)</td></tr>
	<tr><td>1</td><td>PIR sensor</td></tr>
	<tr><td>3</td><td>LEDs</td></tr>
	<tr><td>1</td><td>	Piezo Buzzer</td></tr>
	<tr><td>1</td><td>Small DC Hobby Motor</td></tr>
	<tr><td>2</td><td>NPN transistors</td></tr>
	<tr><td>1</td><td>9V Battery and connector</td></tr>
	<tr><td>*</td><td>Hookup Wire</td></tr>
</table>

All of these are stuffed into a Halloween prop.

You view the wiring and component mock up here: https://circuits.io/circuits/2951213-pumpkin/embed#breadboard
