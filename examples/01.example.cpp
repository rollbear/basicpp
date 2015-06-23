#include "basic.hpp"

int main()
{
  _10: LET X = 1;
  _20: LET SUM = 0;
  _30: LET DEPTH$ = "";
  _40: INPUT "Enter a positive number: ", X;
  _50: IF X > 0 THEN GOTO _80;
  _60: PRINT "By positive, I mean greater than zero. You entered ", X, " which isn't";
  _70: GOTO _40;
  _80: GOSUB _110;
  _90: PRINT "SUM=", SUM, " DEPTH=", DEPTH$;
 _100: END;
 _110: SUM = SUM + X;
 _120: X = X - 1;
 _130: IF X > 0 THEN GOSUB _110;
 _140: DEPTH$ = DEPTH$ + ".";
 _150: RETURN;
}
