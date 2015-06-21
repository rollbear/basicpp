## **`C++`** today is as simple as **`BASIC`** was in the 80s

Single header **`BASIC`** emulation in **`C++`**. This is based on my
(flawed) memory of the **`BASIC`** dialect in the
[EACA](https://en.wikipedia.org/wiki/EACA)
[Colour Genie](https://en.wikipedia.org/wiki/Colour_Genie) computer I
got on my 15th birthday.

## Versions

* [Original BASIC](#basic) - AKA Dartmouth BASIC
* [Structured BASIC] (#sbasic)



## Basic
*Original BASIC - AKA Dartmouth BASIC*

Header file: [basic.hpp](./basic.hpp) 

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

## SBASIC
*Structured BASIC - AKA SBASIC*

Header file: [structured_basic.hpp](./structured_basic.hpp)

### Example program:
```Cpp
#include "structured_basic.hpp"

int main()
{
	_10: LET X = 1;
	_20: INPUT "enter a positive number: " , X;
	_30: IF X > 0 THEN GOTO _60; 
	_40: PRINT "Positive means greater than 0";
	_50: GOTO _20;
	_60: LET i = 0;
	_70: DO ;
	_80: PRINT i+1, " Basic is awesome";
	_90: i = i + 1 ;
	_100: ;LOOP WHILE ( i < X );

}
```

## Limitations
* C++11 or later (easy to back-port, but why?)
* Those pesky semicolons...
* Variables must be defined prior to use
* Can't be used in kernel modules ;-)
* Many language features missing, e.g. PRINT USING and Most I/O

PR's for fixes and added functionality are most welcome.
