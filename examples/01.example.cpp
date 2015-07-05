#include "basic.hpp"

int main()
{
  _10: LET COUNT = 1;
  _20: LET SUM = 0;
  _30: LET STACK$ = ".";
  _40: LET TRY = 0;
  _50: FOR TRY = 3 TO 1 STEP -1;
  _60: PRINT "You have ", TRY, " chances to get this right: ";
  _70: INPUT "Enter a positive number ", COUNT;
  _80: IF COUNT > 0 THEN GOTO _130;
  _90: PRINT "I said positive. ", COUNT, " isn't";
 _100: NEXT;
 _110: PRINT "I give up on you!";
 _120: END;
 _130: GOSUB _160;
 _140: PRINT "SUM=", SUM, " STACK=", STACK$;
 _150: END;
 _160: SUM = SUM + COUNT;
 _170: COUNT = COUNT - 1;
 _180: IF COUNT > 0 THEN GOSUB _160;
 _190: STACK$ = STACK$ + STACK$;
 _200: RETURN;
}
