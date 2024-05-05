##Description

Button 1: If green light is on, when pressed, the green light will turn off
and turn on the red light. If the red light is on and the button is pressed,
the red light will turn off and the green light will turn on.

Button 2: Makes a buzzing sound when pressed.

Button 3: Plays a ring when pressed.

Sometimes project will not run when the command "make load" is ran. It might
be needed to run the following command then try to load it again. If an error
occurs, retype the command and then load it again.
Command: msp430-elf-gcc -mmcu=msp430g2553 -I../h -L/opt/ti/msp430_gcc/include
-o led.elf main.o buzzer.o ./lib/libTimer.a

