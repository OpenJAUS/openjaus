// File Name: bres.h
//
// Written By: Bob Touchton (btouch AT comcast DOT net)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Header for Bresenham Line utility. Derived from implementations by Heinz W. Werntges and D. F. Rogers.

#ifndef BRES_H
#define BRES_H

#define	 BRES_LINE_EOL	0
#define	 BRES_LINE_ERR	-1

typedef struct 
{
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	int currentRow;
	int currentCol;
	int deltaRow;
	int deltaCol;
	int sign1;
	int sign2;
	int count;
	int err;
	int swapDirection;
		
} BresLineStruct;

typedef BresLineStruct *BresLine;

BresLine bresLineCreate(void);
void bresLineDestroy(BresLine);

int bresLineInit(BresLine, int, int, int, int);
int	bresLineNext(BresLine);

#endif // BRES_H
