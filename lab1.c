#include "utils.h"
#include <msp430.h>

int main(void) {
  WDTCTL = WDPPW | WDTHOLD;

  configure(P1, BIT7, INPUT);
  configure(P2, BIT2, INPUT);
  configure(P1, BIT0, OUTPUT);

  bool s2Prev = 0;

  while (1) {
    bool s1;
    do {
      s2 = s2();
    } while(s1 = s1());

    delay(TRANSITION_DELAY);

    if (s1() != s1 || s2() != s2) {
      continue;
    }

    if (s2Prev == 1 && s2 == 0) {
      setD1(!getD1());
    }

    s2Prev = s2;
  }

  return 0;
}
