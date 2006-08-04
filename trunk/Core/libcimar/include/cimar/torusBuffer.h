// File Name: torusBuffer.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a torusBuffer datastructure

#ifndef TORUS_BUFFER_H
#define TORUS_BUFFER_H

#define TORUS_BUFFER_CHAR		0
#define TORUS_BUFFER_SHORT		1
#define TORUS_BUFFER_INT		2
#define TORUS_BUFFER_LONG		3
#define TORUS_BUFFER_UCHAR		4
#define TORUS_BUFFER_USHORT		5
#define TORUS_BUFFER_UINT		6
#define TORUS_BUFFER_ULONG		7
#define TORUS_BUFFER_FLOAT		8
#define TORUS_BUFFER_DOUBLE		9
#define TORUS_BUFFER_POINTER	10

#define TORUS_BUFFER_ERROR		-1

// TorusBufferCell is a union of possible cell types
typedef union
{
	char charValue;
	short shortValue;
	int integerValue;
	long long longValue;
	unsigned char uCharValue;
	unsigned int uShortValue;
	unsigned int uIntegerValue;
	unsigned long long uLongValue;
	float floatValue;
	double doubleValue;
	void *pointer;	
}TorusBufferCell;

typedef struct
{
	int rows;
	int columns;
	
	int beginRow;
	int beginColumn;
	
	unsigned int cellCount;
	
	char dataType;
	
	TorusBufferCell (*createCell)(void);
	void (*destroyCell)(void *);
	double (*getCellValue)(void *);
	
	TorusBufferCell defaultCell;
	TorusBufferCell *data;
}TorusBufferStruct;

typedef TorusBufferStruct* TorusBuffer;

TorusBuffer torusBufferCreate(int rows, int columns, char dataType, TorusBufferCell defaultCell, TorusBufferCell createCell(void), void destroyCell(void *), double getCellValue(void *));
void torusBufferDestroy(TorusBuffer buffer);
int torusBufferClone(TorusBuffer output, TorusBuffer input);

void torusBufferAdjustCenter(TorusBuffer buffer, int deltaRow, int deltaCol);
double torusBufferGetDoubleInterpretation(TorusBuffer buffer, int row, int column, int *success);

TorusBufferCell *torusBufferGetCellPointer(TorusBuffer buffer, int row, int column, int *success);
TorusBufferCell torusBufferGetCell(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetCell(TorusBuffer buffer, int row, int column, TorusBufferCell cell);

// ******************************************************************************************
// Primitive Data Type Accessors
// ******************************************************************************************

// Char
char torusBufferGetCharValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetCharValue(TorusBuffer buffer, int row, int column, char value);

// Short
short torusBufferGetShortValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetShortValue(TorusBuffer buffer, int row, int column, short value);

// Int
int torusBufferGetIntValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetIntValue(TorusBuffer buffer, int row, int column, int value);

// Long
long long torusBufferGetLongValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetLongValue(TorusBuffer buffer, int row, int column, long long value);

// UChar
unsigned char torusBufferGetUCharValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetUCharValue(TorusBuffer buffer, int row, int column, unsigned char value);

// UShort
unsigned short torusBufferGetUShortValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetUShortValue(TorusBuffer buffer, int row, int column, unsigned short value);

// UInt
unsigned int torusBufferGetUIntValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetUIntValue(TorusBuffer buffer, int row, int column, unsigned int value);

// ULong
unsigned long long torusBufferGetULongValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetULongValue(TorusBuffer buffer, int row, int column, unsigned long long value);

// Float
float torusBufferGetFloatValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetFloatValue(TorusBuffer buffer, int row, int column, float value);

// Double
double torusBufferGetDoubleValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetDoubleValue(TorusBuffer buffer, int row, int column, double value);

// Pointer
void *torusBufferGetPointerValue(TorusBuffer buffer, int row, int column, int *success);
void torusBufferSetPointerValue(TorusBuffer buffer, int row, int column, void *value);

#endif
