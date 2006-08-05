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
// File Name: torusBuffer.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the functions of a torusBuffer datastructure

#include <stdlib.h>
#include <string.h>
#include "cimar.h"

#define ROTATE(x, offset, max)  \
			x += offset; 		\
			while (x >= max) 	\
				x -= max;    	\
			while (x < 0)		\
				x += max;		\

// Private Function prototype
void torusBufferCleanCell(TorusBuffer buffer, int rowValue, int colValue);

TorusBuffer torusBufferCreate(int rows, int columns, char dataType, TorusBufferCell defaultCell, TorusBufferCell createCell(void), void destroyCell(void *), double getCellValue(void *))
{
	int i, j;
		
	// Test rows and columns non-zero
	if(rows == 0 || columns == 0)
	{
		return NULL;
	}
	
	// Test function pointers
	if(createCell != NULL)
	{
		if(destroyCell == NULL || getCellValue == NULL)
		{
			return NULL;
		}
	}

	// Malloc the TorusBufferStruct
	TorusBuffer buffer = (TorusBuffer)malloc(sizeof(TorusBufferStruct));
	if(buffer == NULL)
	{
		return NULL;
	}
	
	buffer->rows = rows;
	buffer->columns = columns;
	buffer->cellCount = rows * columns;
	buffer->dataType = dataType;
	
	buffer->data = (TorusBufferCell *)malloc(buffer->cellCount * sizeof(TorusBufferCell));
	if(buffer->data == NULL)
	{
		// Malloc Failed
		free(buffer);
		return NULL;
	}
	
	buffer->defaultCell = defaultCell;
	buffer->createCell = createCell;
	buffer->destroyCell = destroyCell;
	buffer->getCellValue = getCellValue;
	
	for(i = 0; i < buffer->rows; i++)
	{
		for(j = 0; j < buffer->columns; j++)
		{
			if(buffer->createCell == NULL)
			{
				buffer->data[i*buffer->columns + j] = buffer->defaultCell;
			}
			else
			{
				buffer->data[i*buffer->columns + j] = buffer->createCell();
			}
		}
	}
	
	buffer->beginRow = 0;
	buffer->beginColumn = 0;
	
	return buffer;
}

void torusBufferDestroy(TorusBuffer buffer)
{
	// Destroy TorusBuffer
	// Destroy Cells
	int i, j;
	if(buffer->destroyCell != NULL)
	{
		for(i = 0; i < buffer->rows; i++)
		{
			for(j = 0; j < buffer->columns; j++)
			{
				buffer->destroyCell(&buffer->data[i*buffer->columns + j]);
			}
		}
	}

	// Free Cell Memory
	free(buffer->data);

	// Free TorusBuffer
	free(buffer);
}

int torusBufferClone(TorusBuffer output, TorusBuffer input)
{
	if(input == NULL || output == NULL) return CIMAR_FALSE;

	output->rows = input->rows;
	output->columns = input->columns;
	output->beginRow = input->beginRow;
	output->beginColumn = input->beginColumn;
	
	output->cellCount = input->cellCount;
	output->dataType = input->dataType;
	
	output->createCell = input->createCell;
	output->destroyCell = input->destroyCell;
	output->getCellValue = input->getCellValue;
	
	output->defaultCell = input->defaultCell;
	memcpy(output->data, input->data, input->cellCount*sizeof(TorusBufferCell));
	
	return CIMAR_TRUE;
}


void torusBufferAdjustCenter(TorusBuffer buffer, int deltaRow, int deltaCol)
{
	/*when we move the center we need to reupdate the cells that rotate back to DEFAULTVALUE*/
	long i, j, oldColumn, oldRow;

	oldColumn = buffer->beginColumn;
	oldRow = buffer->beginRow;

	ROTATE(buffer->beginRow, deltaRow, buffer->rows);
	ROTATE(buffer->beginColumn, deltaCol, buffer->columns);
	
	if(deltaRow != 0)
	{
		if(abs(deltaRow) >= buffer->rows)
		{
			// In this case we spun the torus buffer all the way around
			// Re-initialize all cells
			for(i = 0; i < buffer->rows; i++)
			{
				for(j = 0; j < buffer->columns; j++)
				{
					torusBufferCleanCell(buffer, i, j);
				}
			}
		}

		//can't just memset this part cause we need to ensure that any dirty data is taken care of.
		if(oldRow < buffer->beginRow)
		{
			if(deltaRow > 0)
			{
				for(i = oldRow; i < buffer->beginRow; i++)
				{
					for(j = 0; j < buffer->columns; j++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
			else
			{
				for(j = 0; j < buffer->columns; j++)
				{
					for(i = buffer->rows-1; i >= buffer->beginRow; i--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
					for(i = oldRow-1; i >= 0; i--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
		}
		else
		{
			if(deltaRow > 0)
			{
				for(j = 0; j < buffer->columns; j++)
				{
					for(i = 0; i < buffer->beginRow; i++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
					for(i = oldRow; i < buffer->rows; i++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
			else
			{
				for(j = 0; j < buffer->columns; j++)
				{
					for(i = oldRow-1; i >= buffer->beginRow; i--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
		}
	}

	if(deltaCol != 0)
	{
		if(abs(deltaCol) >= buffer->columns)
		{
			// In this case we spun the torus buffer all the way around
			// Re-initialize all cells
			for(i = 0; i < buffer->rows; i++)
			{
				for(j = 0; j < buffer->columns; j++)
				{
					torusBufferCleanCell(buffer, i, j);
				}
			}
		}

		if(oldColumn < buffer->beginColumn)
		{
			if(deltaCol > 0)
			{
				//on every row
				for(i = 0; i < buffer->rows; i++)
				{
					for(j = oldColumn; j < buffer->beginColumn; j++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
			else
			{
				for(i = 0; i < buffer->rows; i++)
				{
					for(j = buffer->columns-1; j >= buffer->beginColumn; j--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
					for(j = oldColumn-1; j >= 0; j--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
		}
		else
		{
			if(deltaCol > 0)
			{
				for(i = 0; i < buffer->rows; i++)
				{
					for (j = 0; j < buffer->beginColumn; j++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
					for (j = oldColumn; j < buffer->columns; j++)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
			else
			{
				for(i = 0; i < buffer->rows; i++)
				{
					for (j = oldColumn-1; j >= buffer->beginColumn; j--)
					{
						torusBufferCleanCell(buffer, i, j);
					}
				}
			}
		}
	}
}

void torusBufferSetCell(TorusBuffer buffer, int row, int column, TorusBufferCell cell)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column] = cell;
	}
}

TorusBufferCell torusBufferGetCell(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column];
}

TorusBufferCell *torusBufferGetCellPointer(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return &buffer->defaultCell;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return &buffer->data[row*buffer->columns + column];
}

double torusBufferGetDoubleInterpretation(TorusBuffer buffer, int row, int column, int *success)
{
	TorusBufferCell cell;
	
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return 0.0;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		cell = buffer->data[row*buffer->columns + column];
	}
	
	if(buffer->getCellValue != NULL)
	{
		return buffer->getCellValue(&cell);
	}
	else
	{
		switch(buffer->dataType)
		{
			case TORUS_BUFFER_CHAR:
				return (double)cell.charValue;
	
			case TORUS_BUFFER_SHORT:
				return (double)cell.shortValue;
	
			case TORUS_BUFFER_INT:
				return (double)cell.integerValue;
	
			case TORUS_BUFFER_LONG:
				return (double)cell.longValue;
				
			case TORUS_BUFFER_UCHAR:
				return (double)cell.uCharValue;
	
			case TORUS_BUFFER_USHORT:
				return (double)cell.uShortValue;

			case TORUS_BUFFER_UINT:
				return (double)cell.uIntegerValue;
				
			case TORUS_BUFFER_ULONG:
				return (double)cell.uLongValue;
				
			case TORUS_BUFFER_FLOAT:
				return (double)cell.floatValue;
				
			case TORUS_BUFFER_DOUBLE:
				return cell.doubleValue;

			case TORUS_BUFFER_POINTER:
				// This is undefined!
				// You should not be requesting an interpretation of a pointer, it should have a getCellValue function associated with it
				cError("%s:%d: Requesting interpretation of pointer value. Undefined!\n", __FILE__, __LINE__);
				if(success) *success = TORUS_BUFFER_ERROR;
				return 0.0;
				
			default:
				cError("%s:%d: If you got here, you are in big trouble!\n", __FILE__, __LINE__);
				if(success) *success = TORUS_BUFFER_ERROR;
				return 0.0;
		}
	}

	cError("%s:%d: If you got here, you are in big trouble!\n", __FILE__, __LINE__);
	if(success) *success = TORUS_BUFFER_ERROR;
	return 0.0;
}
void torusBufferCleanCell(TorusBuffer buffer, int rowValue, int colValue)
{
	unsigned int position; // Index to proper cell in linear array
	position = (rowValue * buffer->columns) +  colValue;
	
	if(buffer->createCell == NULL)
	{
		buffer->data[position] = buffer->defaultCell;
	}
	else
	{
		buffer->destroyCell(&buffer->data[position]);
		buffer->data[position] = buffer->createCell();
	}	
}

// ******************************************************************************************
// Primitive Data Type Accessors
// ******************************************************************************************

// Char
char torusBufferGetCharValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.charValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].charValue;
}

void torusBufferSetCharValue(TorusBuffer buffer, int row, int column, char value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].charValue = value;
	}
}

// Short
short torusBufferGetShortValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.shortValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].shortValue;
}

void torusBufferSetShortValue(TorusBuffer buffer, int row, int column, short value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].shortValue = value;
	}
}

// Int
int torusBufferGetIntValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.integerValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].integerValue;	
}

void torusBufferSetIntValue(TorusBuffer buffer, int row, int column, int value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].integerValue = value;
	}
}

// Long
long long torusBufferGetLongValue(TorusBuffer buffer, int row, int column, int *success)
{	
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.longValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].longValue;	
}

void torusBufferSetLongValue(TorusBuffer buffer, int row, int column, long long value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].longValue = value;
	}
}

// UChar
unsigned char torusBufferGetUCharValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.uCharValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].uCharValue;	
}

void torusBufferSetUCharValue(TorusBuffer buffer, int row, int column, unsigned char value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].uCharValue = value;
	}
}

// UShort
unsigned short torusBufferGetUShortValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.uShortValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].uShortValue;	
}

void torusBufferSetUShortValue(TorusBuffer buffer, int row, int column, unsigned short value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].uShortValue = value;
	}
}

// UInt
unsigned int torusBufferGetUIntValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.uIntegerValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].uIntegerValue;	
}

void torusBufferSetUIntValue(TorusBuffer buffer, int row, int column, unsigned int value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].uIntegerValue = value;
	}
}

// ULong
unsigned long long torusBufferGetULongValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.uLongValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].uLongValue;	
}

void torusBufferSetULongValue(TorusBuffer buffer, int row, int column, unsigned long long value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].uLongValue = value;
	}
}

// Float
float torusBufferGetFloatValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.floatValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].floatValue;	
}

void torusBufferSetFloatValue(TorusBuffer buffer, int row, int column, float value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].floatValue = value;
	}
}

// Double
double torusBufferGetDoubleValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.doubleValue;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].doubleValue;	
}

void torusBufferSetDoubleValue(TorusBuffer buffer, int row, int column, double value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].doubleValue = value;
	}
}

// Pointer
void *torusBufferGetPointerValue(TorusBuffer buffer, int row, int column, int *success)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		if(success) *success = TORUS_BUFFER_ERROR;
		return buffer->defaultCell.pointer;
	}

	ROTATE(column, buffer->beginColumn, buffer->columns);
	ROTATE(row, buffer->beginRow, buffer->rows);

	return buffer->data[row*buffer->columns + column].pointer;	
}

void torusBufferSetPointerValue(TorusBuffer buffer, int row, int column, void *value)
{
	if (row < 0 || row >= buffer->rows || column < 0 || column >= buffer->columns)
	{
		cError("%s:%d: Try to access row/column out of range\n", __FILE__, __LINE__);
		return;
	}
	else
	{
		ROTATE(column, buffer->beginColumn, buffer->columns);
		ROTATE(row, buffer->beginRow, buffer->rows);
	
		buffer->data[row*buffer->columns + column].pointer = value;
	}
}

