#include "basic.hpp"


int main()
{
  _10: LET A=3;
  _20: LET B=2;
  _30: DIM F(A,B);
  _40: LET I = 0;
  _50: LET J = 0;
  _60: FOR I = 1 TO A;
  _70: FOR J = 1 TO B;
  _80: F(I,J)=CHR$(I+5*J+ASC("A"));
  _90: NEXT;
 _100: NEXT;
 _110: LET LINE$="";
 _120: FOR I = 1 TO A;
 _130: FOR J = 1 TO B;
 _140: LINE$=LINE$+F(I,J);
 _150: NEXT;
 _160: PRINT LINE$;
 _170: LINE$="";
 _180: NEXT;
}

