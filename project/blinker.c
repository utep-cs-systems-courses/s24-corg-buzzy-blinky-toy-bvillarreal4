#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include <stdlib.h>

static int oneCycle = 0;

int blinker(void){
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();
  enableWDTInterrupts();

  if(oneCycle){
    P1OUT &= ~LED_RED;
    WDTCTL = WDTPW | WDTHOLD;
    oneCycle = 0;
  }

  os_rs(0x18);
}

static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle

void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit

{

  static int blinkCount = 0; // state var representing blink state

  blinkCount ++;

  if (blinkCount >= blinkLimit) {

    blinkCount = 0;
    greenControl(1);

  } else

    greenControl(0);

}



void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec

{

  blinkLimit ++;  // reduce duty cycle

  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7.

    blinkLimit = 0;
}
