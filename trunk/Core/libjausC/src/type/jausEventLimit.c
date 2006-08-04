// File Name: jausEventLimit.c
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo (galluzzo AT gmail DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description:

#include <malloc.h>
#include <string.h>

#include <cimar.h>
#include "cimar/jaus.h"

// JausEventLimit Constructor
JausEventLimit jausEventLimitCreate()
{
	JausEventLimit limit;
	limit = (JausEventLimit) malloc(sizeof(JausEventLimitStruct));
	if(limit)
	{
		memset(limit, 0, sizeof(JausEventLimitStruct));
		return limit;
	}
	else
	{
		return NULL;
	}	
}

// JausEventLimit Destructor
void jausEventLimitDestroy(JausEventLimit limit)
{
	if(limit)
	{
		free(limit);
		limit = NULL;
	}		
}

// JausEventLimit Constructor (from Buffer)
JausEventLimit jausEventLimitFromBuffer(unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType)
{
	JausEventLimit limit;
	int index = 0;

	limit = (JausEventLimit) malloc(sizeof(JausEventLimitStruct));
	if(limit)
	{
		memset(limit, 0, sizeof(JausEventLimitStruct));
		switch(dataType)
		{
			case EVENT_LIMIT_BYTE_DATA:
				if(!jausByteFromBuffer(&limit->byteValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
				
			case EVENT_LIMIT_SHORT_DATA:
				if(!jausShortFromBuffer(&limit->shortValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_INTEGER_DATA:
				if(!jausIntegerFromBuffer(&limit->integerValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_LONG_DATA:
				if(!jausLongFromBuffer(&limit->longValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_UNSIGNED_SHORT_DATA:
				if(!jausUnsignedShortFromBuffer(&limit->unsignedShortValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_UNSIGNED_INTEGER_DATA:
				if(!jausUnsignedIntegerFromBuffer(&limit->unsignedIntegerValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_UNSIGNED_LONG_DATA:
				if(!jausUnsignedLongFromBuffer(&limit->unsignedLongValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_FLOAT_DATA:
				if(!jausFloatFromBuffer(&limit->floatValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
			case EVENT_LIMIT_DOUBLE_DATA:
				if(!jausDoubleFromBuffer(&limit->doubleValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				return limit;
	
				break;
	
			case EVENT_LIMIT_RGB_DATA:
				if(!jausByteFromBuffer(&limit->redValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				index += JAUS_BYTE_SIZE_BYTES;
	
				if(!jausByteFromBuffer(&limit->greenValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				index += JAUS_BYTE_SIZE_BYTES;
	
				if(!jausByteFromBuffer(&limit->blueValue, buffer+index, bufferSizeBytes-index))
				{
					free(limit);
					return NULL;
				}
				index += JAUS_BYTE_SIZE_BYTES;
				return limit;
	
			default:
				free(limit);
				return NULL;
		}	
	}
	else
	{
		return NULL;
	}
}

// JausEventLimit To Buffer
JausBoolean jausEventLimitToBuffer(JausEventLimit limit, unsigned char *buffer, unsigned int bufferSizeBytes, JausByte dataType)
{
	unsigned int index = 0;
	if(limit)
	{
		// Value
		switch(dataType)
		{
			case EVENT_LIMIT_BYTE_DATA:
				if(!jausByteToBuffer(limit->byteValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;
								
			case EVENT_LIMIT_SHORT_DATA:
				if(!jausShortToBuffer(limit->shortValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_INTEGER_DATA:
				if(!jausIntegerToBuffer(limit->integerValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_LONG_DATA:
				if(!jausLongToBuffer(limit->longValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_UNSIGNED_SHORT_DATA:
				if(!jausUnsignedShortToBuffer(limit->unsignedShortValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_UNSIGNED_INTEGER_DATA:
				if(!jausUnsignedIntegerToBuffer(limit->unsignedIntegerValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_UNSIGNED_LONG_DATA:
				if(!jausUnsignedLongToBuffer(limit->unsignedLongValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_FLOAT_DATA:
				if(!jausFloatToBuffer(limit->floatValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_DOUBLE_DATA:
				if(!jausDoubleToBuffer(limit->doubleValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			case EVENT_LIMIT_RGB_DATA:
				if(!jausByteToBuffer(limit->redValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;

				if(!jausByteToBuffer(limit->greenValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				index += JAUS_BYTE_SIZE_BYTES;

				if(!jausByteToBuffer(limit->blueValue, buffer+index, bufferSizeBytes-index)) return JAUS_FALSE;
				return JAUS_TRUE;

			default:
				return JAUS_TRUE;
		}
	}
	return JAUS_FALSE;	
}

unsigned int jausEventLimitByteSize(JausByte dataType)
{
	unsigned int size = 0;

	switch(dataType)
	{
		case EVENT_LIMIT_BYTE_DATA:
			size += JAUS_BYTE_SIZE_BYTES;
			return size;
			break;
			
		case EVENT_LIMIT_SHORT_DATA:
			size += JAUS_SHORT_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_INTEGER_DATA:
			size += JAUS_INTEGER_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_LONG_DATA:
			size += JAUS_LONG_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_UNSIGNED_SHORT_DATA:
			size += JAUS_UNSIGNED_SHORT_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_UNSIGNED_INTEGER_DATA:
			size += JAUS_UNSIGNED_INTEGER_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_UNSIGNED_LONG_DATA:
			size += JAUS_UNSIGNED_LONG_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_FLOAT_DATA:
			size += JAUS_FLOAT_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_DOUBLE_DATA:
			size += JAUS_DOUBLE_SIZE_BYTES;
			return size;
			break;

		case EVENT_LIMIT_RGB_DATA:
			size += JAUS_BYTE_SIZE_BYTES;	// Red
			size += JAUS_BYTE_SIZE_BYTES;	// Green
			size += JAUS_BYTE_SIZE_BYTES;	// Blue
			return size;
			break;

		default:
			return 0;			
	}
	return size;
}

JausEvent jausEventCreate()
{
	JausEvent event;
	event = (JausEvent) malloc(sizeof(JausEventStruct));
	
	event->eventMessage = NULL;
	event->eventId = 0;
	event->previousLimitValue = jausEventLimitCreate();
	
	return event;
}

void jausEventDestroy(JausEvent event)
{
	// Note event->eventMessage needs to be freed
	/*if(event->eventMessage)*/ createEventMessageDestroy(event->eventMessage);
	
	jausEventLimitDestroy(event->previousLimitValue);	
	free(event);	
}
