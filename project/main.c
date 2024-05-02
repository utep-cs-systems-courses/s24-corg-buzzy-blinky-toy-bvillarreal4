#include <msp430.h>
#include "./timerLib/libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)

#define switches (SW1 | SW2 | SW3 | SW4)
int main(void){

  configureClocks();
  enableWDTInterrupts();
  buzzer_init();

  P1DIR |= LEDS;

  P2REN |= switches;
  P2IE |= switches;
  P2OUT |= switches;
  // P2DIR &= ~SW1;

  or_sr(0x18);

  
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){

  if(P2IFG & SW1){
    P2IFG &= ~SW1;
    switch_interrupt_handler_SW1();
  }
  if(P2IFG & SW2){
    P2IFG &= ~SW2;
    switch_interrupt_handler_SW2();
  }
  if(P2IFG & SW3){
    P2IFG &= ~SW3;
    switch_interrupt_handler_SW3();
  }
 

}

void switch_interrupt_handler_SW1(){
  char p1 = P1IN;

  P1IES |= (p1 & switches);
  P1IES &= (p1 | ~switches);

  if(p1 & SW1){
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
  else{
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  }
}


void switch_interrupt_handler_SW2(){
  char p2 = P2IN;

  P2IES |= (p2 & SW2);
  P2IES &= (p2 | ~SW2);

  if(p2 & SW2){
    buzzer_set_period(0);
  }
  else{
    buzzer_set_period(554);
  }
}

void switch_interrupt_handler_SW3(){
  char p2 = P2IN;

  P2IES |= (p2 & SW3);
  P2IES &= (p2 | ~SW3);

  const int E = 632;
  const int D = 55;
  const int A = 440;

  int song[] = {E,D,A,E,D,A,E,D,A,E,D,A,E,D,E,D,E,D,A,E,D,A,E,D,A,E,E,E,E,D,A,D};
  int count = 0;
  int limit = sizeof(song)/sizeof(song[0]);
  int interruptCount = 0;

  if(p2 & SW3){
    buzzer_set_period(0);
  }
  else{
    buzzer_set_period(632);
    __delay_cycles(1000000);
    buzzer_set_period(550);
    __delay_cycles(1000000);
    buzzer_set_period(440);
    __delay_cycles(1000000);

    buzzer_set_period(632);
    __delay_cycles(1000000);
    buzzer_set_period(550);
    __delay_cycles(1000000);
    buzzer_set_period(440);
    __delay_cycles(1000000);
  }

 
}


 

