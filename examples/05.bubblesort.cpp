#include "basic.hpp"


int main()
{
  _10: DIM F(10);
  _11: LET I = 0;
  _12: LET J = 0;
  _13: LET TMP = 0;
  _20: FOR I = 1 TO 10;
  _30: F(I) = RND();
  _35: PRINT F(I);
  _40: NEXT
  _50: FOR I = 1 TO 9;
  _60: FOR J = I + 1 TO 10;
  _70: IF F(J) > F(I) THEN GOTO _110;
  _80: TMP = F(I);
  _90: F(I) = F(J);
  _100: F(J) = TMP;
  _110: NEXT;
  _120: NEXT;
  _130: PRINT "reordered";
  _140: FOR I = 1 TO 10;
  _150: PRINT F(I);
  _160: NEXT
}

