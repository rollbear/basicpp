/*
 *by @MCSH
 */

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
	_100:  LOOP WHILE ( i < X );

}
