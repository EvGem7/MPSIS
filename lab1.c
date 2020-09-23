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
      setD1(!getD1());
    }

    s2Prev = s2Val;
  }

  return 0;
}
