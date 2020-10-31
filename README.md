## **`C++`**is as simple as **`BASIC`** was in the 80s 

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
 _100: LOOP WHILE ( i < X );
}
```

## Limitations
* C++11 or later (easy to back-port, but why?)
* Those pesky semicolons...
* Variables must be defined prior to use
* Can't be used in kernel modules ;-)
* Many language features missing, e.g. PRINT USING and Most I/O

PR's for fixes and added functionality are most welcome.
