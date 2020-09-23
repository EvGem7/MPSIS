#ifndef UTILS
#define UTILS

#include <msp430.h>

#define TRANSITION_DELAY 400

#define int16 int
#define u_int16 unsigned int

#define bool char

#define turn(port, bit, enabled)  \
  if (enabled) {                  \
    port |= bit;                  \
  } else {                        \
    port &= ~bit;                 \
  }

#define INPUT 0
#define OUTPUT 1

#define configure(port, bit, state) \
  switch (state) {                  \
    case INPUT:                     \
      turn(port##DIR, bit, 0);      \
      turn(port##OUT, bit, 1);      \
      turn(port##REN, bit, 1);      \
      break;                        \
    case OUTPUT:                    \
      turn(port##DIR, bit, 1);      \
      break;                        \
  }

void delay(u_int16 cycles) {
  u_int16 i;
  for (i = 0; i < cycles; ++i);
}

void setD1(bool enabled) {
  turn(P1OUT, BIT0, enabled);
}

bool getD1(void) {
  return P1OUT & BIT0;
}

bool s1(void) {
	if (P1IN & BIT7) {
		return 0;
	} else {
		return 1;
	}
}

bool s2(void) {
  if (P2IN & BIT2) {
  		return 0;
  	} else {
  		return 1;
  	}
}

#endif
