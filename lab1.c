#include "utils.h"
#include <msp430.h>

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;

  configure(P1, BIT7, INPUT);
  configure(P2, BIT2, INPUT);
  configure(P1, BIT0, OUTPUT);

  bool s2Prev = 0;

  while (1) {
    bool s1Val, s2Val;
    do {
      s2Val = s2();
    } while(s1Val = s1());

    delay(TRANSITION_DELAY);

    if (s1() != s1Val || s2() != s2Val) {
      continue;
    }

    if (s2Prev == 1 && s2Val == 0) {
    	if (!s1()) {
    		setD1(!getD1());
    	}
    }

    s2Prev = s2Val;
  }
}

/////////////////////////////////////////////

#include "utils.h"
#include <msp430.h>

#pragma vector = PORT2_VECTOR
__interrupt void isr(void) {
	if (!read(P2IFG, BIT2)) {
		return;
	}

	delay(TRANSITION_DELAY);
	if (!s2() && !s1()) {
		setD1(!getD1());
	}

	turn(P2IFG, BIT2, 0);
}

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;

  configure(P1, BIT7, INPUT);
  configure(P2, BIT2, INPUT);
  configure(P1, BIT0, OUTPUT);

  __bis_SR_register(GIE); // Enable global interrupts

  turn(P2IE, BIT2, 1); 	// enable interrupt s2
  turn(P2IES, BIT2, 0); // back front
  P1IFG = 0x00;			// Clear all interrupt flags

  __no_operation();
}
