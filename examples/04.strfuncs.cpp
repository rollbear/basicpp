#include "basic.hpp"

int main()
{
  _10: LET A$ = "The quick brown fox jumped over the lazy dog...";
  _15: LET X = 0;
  _20: FOR X = 0 TO LEN(A$) - 1;
  _30: PRINT RIGHT$(A$, X) + LEFT$(A$, LEN(A$) - X);
  _40: NEXT;
}
