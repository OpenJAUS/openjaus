// File Name: createEventMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 11/2/05
//
// This file defines the attributes of a CreateEventMessage

#ifndef CREATE_EVENT_MESSAGE_H
#define CREATE_EVENT_MESSAGE_H

#include <cimar/jaus.h>

#define JAUS_CREATE_EVENT	0xF0A1

// PV as defined in Events Document v1.8
#ifndef CREATE_EVENT_PV
#define CREATE_EVENT_PV_BOUNDARY_BIT		0	// Field 4
#define CREATE_EVENT_PV_DATA_TYPE_BIT		1	// Field 5
#define CREATE_EVENT_PV_DATA_FIELD_BIT		2	// Field 6
#define CREATE_EVENT_PV_LOWER_LIMIT_BIT		3	// Field 7
#define CREATE_EVENT_PV_UPPER_LIMIT_BIT		4	// Field 8
#define CREATE_EVENT_PV_STATE_LIMIT_BIT		5	// Field 9
#define CREATE_EVENT_PV_MINIMUM_RATE_BIT	6	// Field 10
#define CREATE_EVENT_PV_REQUESTED_RATE_BIT	7	// Field 11
#endif

// Event Types as defined in Events Document v1.8
#ifndef EVENT_TYPES
#define EVENT_TYPES
#define EVENT_PERIODIC_TYPE						0
#define EVENT_EVERY_CHANGE_TYPE					1
#define EVENT_FIRST_CHANGE_TYPE					2
#define EVENT_FIRST_CHANGE_IN_AND_OUT_TYPE		3
#define EVENT_PERIODIC_NO_REPEAT_TYPE			4
#endif

// Event Boundaries as defined in Events Document v1.8
#ifndef EVENT_BOUNDARIES
#define EVENT_BOUNDARIES
#define EQUAL_BOUNDARY							0
#define NOT_EQUAL_BOUNDARY						1
#define INSIDE_INCLUSIVE_BOUNDARY				2
#define INSIDE_EXCLUSIVE_BOUNDARY				3
#define OUTSIDE_INCLUSIVE_BOUNDARY				4
#define OUTSIDE_EXCLUSIVE_BOUNDARY				5
#define GREATER_THAN_OR_EQUAL_BOUNDARY			6
#define GREATER_THAN_BOUNDARY					7
#define LESS_THAN_OR_EQUAL_BOUNDARY				8
#define LESS_THAN_BOUNDARY						9
#endif

typedef struct
{
	// Include all parameters from a JausMessage structure:
	// Header Properties
	union
	{
		struct
		{
			// Properties by bit fields
			#ifdef JAUS_BIG_ENDIAN
				JausUnsignedShort reserved:2;
				JausUnsignedShort version:6;
				JausUnsignedShort expFlag:1;
				JausUnsignedShort scFlag:1;
				JausUnsignedShort ackNak:2;
				JausUnsignedShort priority:4; 
			#elif JAUS_LITTLE_ENDIAN
				JausUnsignedShort priority:4; 
				JausUnsignedShort ackNak:2;
				JausUnsignedShort scFlag:1; 
				JausUnsignedShort expFlag:1;
				JausUnsignedShort version:6; 
				JausUnsignedShort reserved:2;
			#else
				#error "Please define system endianess (see jaus.h)"
			#endif
		};
		JausUnsignedShort properties;		
	};

	JausUnsignedShort commandCode; 

	JausAddress destination;

	JausAddress source;

	union
	{
		struct
		{
			JausUnsignedInteger dataSize;
			JausUnsignedInteger dataFlag;
		};
		JausUnsignedLong dataControl;		
	};
	
	JausUnsignedShort sequenceNumber;

	// MESSAGE DATA MEMBERS GO HERE
	JausBytePresenceVector presenceVector;	// 1: Presence Vector
	JausUnsignedShort messageCode;			// 2: Command Code of the resulting query
	JausByte eventType;						// 3: Enumeration of Event types
	JausByte eventBoundary;					// 4: Enumeration of Event Boundary Conditions
	JausByte limitDataType;					// 5: Enumeration of data types for fields 7 & 8
	JausByte limitDataField;				// 6: Field from Report for Limit Trigger
	JausEventLimit lowerLimit;				// 7: Lower Event Limit
	JausEventLimit upperLimit;				// 8: Upper Event Limit
	JausEventLimit stateLimit;				// 9: State Event Limit used for Equal Boundary
	JausDouble requestedMinimumRate;		// 10: For Periodic Events for unchanging value, Scaled UnsignedShort (0, 1092)
	JausDouble requestedUpdateRate;			// 11: For Periodic Events, Scaled UnsignedShort (0, 1092)
	JausMessage queryMessage;				// 12: Query Message (including header) to use for response
}CreateEventMessageStruct;

typedef CreateEventMessageStruct* CreateEventMessage;

CreateEventMessage createEventMessageCreate(void);
void createEventMessageDestroy(CreateEventMessage);

JausBoolean createEventMessageFromBuffer(CreateEventMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean createEventMessageToBuffer(CreateEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean createEventMessageToUdpBuffer(CreateEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

CreateEventMessage createEventMessageFromJausMessage(JausMessage jausMessage);
JausMessage createEventMessageToJausMessage(CreateEventMessage message);

unsigned int createEventMessageUdpSize(CreateEventMessage message);
unsigned int createEventMessageSize(CreateEventMessage message);


#endif // CREATE_EVENT_MESSAGE_H
