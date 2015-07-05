#include "basic.hpp"


int main()
{
  _10: LET A=3;
  _20: LET B=2;
  _30: DIM F(A,B);
  _40: F(1,1)=" "; F(1,2)=" ";
  _50: F(2,1)="x"; F(2,2)="!";
  _60: F(3,1)=" "; F(3,2)="-";
  _70: LET LINE$="";
  _80: LET I = 0;
  _90: LET J = 0;
 _100: FOR I = 1 TO A;
 _110: FOR J = 1 TO B;
 _120: LINE$=LINE$+F(I,J);
 _130: NEXT;
 _140: PRINT LINE$;
 _150: LINE$="";
 _160: NEXT;
}

