#include "basic.hpp"


int main()
{
  LET A=3;
  LET B=2;
  DIM F(A,B);
  LET I = 0;
  LET J = 0;
  LET MUL=5;
  FOR I = 1 TO A;
  FOR J = 1 TO B;
  F(I,J)=CHR$(I+MUL*J+ASC("A"));
  NEXT;
  NEXT;
  LET LINE$="";
  FOR I = 1 TO A;
  FOR J = 1 TO B;
  LINE$=LINE$+F(I,J);
  NEXT;
  PRINT LINE$;
  LINE$="";
  NEXT;
}

