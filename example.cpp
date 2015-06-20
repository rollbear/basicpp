#include "basic.hpp"

int main()
{
  _10: LET X = 1;
  _20: LET SUM = 0;
  _30: LET DEPTH = 1;
  _40: INPUT "Enter a positive number: ", X;
  _50: IF X > 0 THEN GOTO _130;
  _60: PRINT "By positive, I mean greater than zero. You entered ", X, " which isn't";
  _70: GOTO _40;
  _80: SUM = SUM + X;
  _90: X = X - 1;
 _100: IF X > 0 THEN GOSUB _80;
 _110: DEPTH = DEPTH * 2;
 _120: RETURN;
 _130: GOSUB _80;
 _140: PRINT "SUM=", SUM, " DEPTH=", DEPTH;
}
