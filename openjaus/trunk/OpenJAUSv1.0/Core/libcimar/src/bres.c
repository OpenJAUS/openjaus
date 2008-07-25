/*****************************************************************************
 *  Copyright (c) 2006, University of Florida.
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: bres.c
//
// Written By: Bob Touchton (btouch AT comcast DOT net)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: Source for Bresenham Line utility. 
// Derived from implementations by Heinz W. Werntges and D. F. Rogers.

// USAGE: 
//
//	First, Create the stucture to be used by the function
// 		bresLine = bresLineCreate();
//
//	Then, initialize the stucture as follows:
//		bresLineInit(bresLine, startRow, startCol, endRow, endCol);
//
//	Next, walk through the cells from startCell to endCell as follows:
//		do	
//		{
//			row = bresLine->currentRow;
//			column = bresLine->currentCol;
//		} while (bresLineNext(bresLine) != BRES_LINE_ERR);	
//
// 	The Init and walk through procedures can be repeated for any number of lines
//
//  Finally, destroy the data structure
// 		bresLineDestroy(bresLine);

#include <stdlib.h>
#include "cimar.h"

BresLine bresLineCreate(void)
{
	BresLine bresLine = NULL;
	
	bresLine = (BresLine) malloc(sizeof (BresLineStruct));
	if(bresLine == NULL)
	{
		return NULL;
	}
	
	bresLine->startRow = 0;
	bresLine->startCol = 0;
	bresLine->endRow = 0;
	bresLine->endCol = 0;
	bresLine->currentRow = 0;
	bresLine->currentCol = 0;
	bresLine->deltaRow = 0;
	bresLine->deltaCol = 0;
	bresLine->sign1 = 0;
	bresLine->sign2 = 0;
	bresLine->count = 0;
	bresLine->err = 0;
	bresLine->swapDirection = 0;
	
	return bresLine;
}

void bresLineDestroy(BresLine bresLine)
{
	if(bresLine == NULL)
	{
		return;
	}

	free(bresLine);
}

int bresLineInit(BresLine bresLine, int startRow, int startCol, int endRow, int endCol)
{
	bresLine->startRow = startRow;
	bresLine->startCol = startCol;
	bresLine->startRow = endRow;
	bresLine->startCol = endCol;
	bresLine->currentRow = startRow;
	bresLine->currentCol = startCol;

	if((bresLine->deltaCol = endCol - startCol) != 0)
	{
		if(bresLine->deltaCol < 0)
		{
			bresLine->deltaCol = -bresLine->deltaCol;
			bresLine->sign1 = -1;
		}
		else
		{
			bresLine->sign1 = 1;
		}
	}
	else
	{
		bresLine->sign1 = 0;	/* deltaCol = abs(col2-col1), sign1 = sign(col2-col1)	*/
	}
	
	if((bresLine->deltaRow = endRow - startRow) != 0)
	{
		if (bresLine->deltaRow < 0)
		{
			bresLine->deltaRow = -bresLine->deltaRow;
			bresLine->sign2 = -1;
		}
		else
		{
			bresLine->sign2 = 1;
		}
	}
	else
	{
		bresLine->sign2 = 0;	/* deltaRow = abs(row2-row1), sign2 = sign(row2-row1)	*/
	}
	
	if (bresLine->deltaRow > bresLine->deltaCol)
	{
		bresLine->swapDirection = bresLine->deltaCol;	/* use swapDirection as temp. var.	*/
		bresLine->deltaCol = bresLine->deltaRow;
		bresLine->deltaRow = bresLine->swapDirection;
		bresLine->swapDirection = 1;
	}
	else
	{
		bresLine->swapDirection = 0;
	}
	
	bresLine->count = bresLine->deltaCol;		/* Init. of loop cnt	*/
	bresLine->deltaRow <<= 1;
	bresLine->err = bresLine->deltaRow - bresLine->deltaCol;	/* Init. of error term	*/
	bresLine->deltaCol <<= 1;
	
	return bresLine->count + 1;
}

// Function: bresLineNext
// Move current cell to next position (if possible)
// 
// Returns 0 if ok,
// BRES_LINE_EOL if last point reached (cellPtr == *endCell),
// BRES_LINE_ERR else (e.g. if moving past EOL attempted)
int	bresLineNext (BresLine bresLine)
{
	if(bresLine->count < BRES_LINE_EOL)
	{
		return BRES_LINE_ERR;	// Beyond last point!
	}
	
	while (bresLine->err > 0)
	{
		if (bresLine->swapDirection)
		{	
			bresLine->currentCol += bresLine->sign1;
		}	
		else
		{
			bresLine->currentRow += bresLine->sign2;
		}
		bresLine->err -=bresLine->deltaCol;
	}
	if (bresLine->swapDirection)
	{
		bresLine->currentRow += bresLine->sign2;
	}
	else
	{
		bresLine->currentCol += bresLine->sign1;
	}
	bresLine->err += bresLine->deltaRow;
	
	bresLine->count--;
	
	return bresLine->count;
}
