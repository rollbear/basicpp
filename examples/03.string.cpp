#include "basic.hpp"

int main()
{
  _10: LET A$ = "";
  _40: LET B = 12;
  _20: INPUT "What is your name? ", A$;
  _50: INPUT "How old are you? ", B;
  _60: PRINT "Hello ", A$, " who is ", B, " years old";
  _70: LET C$ = STR(B);
  _80: LET D = VAL(C$);
  _90: PRINT "C$ = ", C$, " D = ", D;
}
