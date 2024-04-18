#include <msp430.h>
#include "./timerLib/libTimer.h"
#include "led.h"
#include "buzzer.h"

#define SW1 BIT0

int main(void){

  configureClocks();
  buzzer_init();

  P2REN |= SW1;
  P2IE |= SW1;
  P2OUT |= SW1;
  P2DIR &= ~SW1;

  or_sr(0x18);

  
}

void __interrupt_vec(PORT2_VECTOR) Port_2(){

  if(P2IFG & SW1){
    P2IFG &= ~SW1;
    switch_interrupt_handler();
  }

}

void switch_interrupt_handler(){
  char p2 = P2IN;

  P2IES |= (p2 & SW1);
  P2IES &= (p2 | ~SW1);

  if(p2 & SW1){
    buzzer_set_period(0);
  }
  else{
    buzzer_set_period(1000);
  }

  

}
