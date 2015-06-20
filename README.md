## **`C++`** today is as simple as **`BASIC`** was in the 80s

Single header **`BASIC`** emulation in **`C++`**. This is based on my
(flawed) memory of the **`BASIC`** dialect in the
[EACA](https://en.wikipedia.org/wiki/EACA)
[Colour Genie](https://en.wikipedia.org/wiki/Colour_Genie) computer I
got on my 15th birthday.

### Example program:
```Cpp
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
```

### Limitations
* Only numeric variables are supported (no strings, no matrices)
* C++11 or later (easy to back-port, but why?)
* Those pesky semicolons...
* Variables must be defined prior to use
* Can't be used in kernel modules ;-)
* Many language features missing, e.g. PRINT USING and Most I/O

PR's for fixes and added functionality are most welcome.
