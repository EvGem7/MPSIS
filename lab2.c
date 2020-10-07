#include "utils.h"
#include <msp430.h>

void onS1Pressed(void);
void onS2Pressed(void);

#pragma vector = PORT1_VECTOR
__interrupt void isrS1(void) {
	bool s1State;
	if (!read(P1IFG, BIT7)) {
		return;
	}
	if (!(s1State = s1())) {
		turn(P1IFG, BIT7, 0);
		return;
	}
	delay(TRANSITION_DELAY);
	if (s1State == s1()) {
		onS1Pressed();
	}
	turn(P1IFG, BIT7, 0);
}

#pragma vector = PORT2_VECTOR
__interrupt void isrS2(void) {
	bool s2State;
	if (!read(P2IFG, BIT2)) {
		return;
	}
	if (!(s2State = s2())) {
		turn(P2IFG, BIT2, 0);
		return;
	}
	delay(TRANSITION_DELAY);
	if (s2State == s2()) {
		onS2Pressed();
	}
	turn(P2IFG, BIT2, 0);
}

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;

  configure(P1, BIT7, INPUT);
  configure(P2, BIT2, INPUT);
  configure(P1, BIT0, OUTPUT);

  __bis_SR_register(GIE); // Enable global interrupts

  turn(P1IE, BIT7, 1); 	// enable interrupt s1
  turn(P1IES, BIT7, 1); // back front

  turn(P2IE, BIT2, 1); 	// enable interrupt s2
  turn(P2IES, BIT2, 1); // back front

  P1IFG = 0x00;			// Clear all interrupt flags

  UCSCTL1 |= DCORSEL_2; // 0,32 MHz — 7,38 MHz
  UCSCTL2 |= FLLD__16; // FLLD  = 16
  UCSCTL3 |= SELREF__XT1CLK;

  UCSCTL4 |= SELM__DCOCLK; // MCLK source is DCOCLK


  __no_operation();
}

void onS1Pressed(void) {

}

void onS2Pressed(void) {
  if (UCSCTL4 & SELM__DCOCLK) {
    UCSCTL4 |= SELM__VLOCLK;
  } else {
    UCSCTL4 |= SELM__DCOCLK;
  }
}
