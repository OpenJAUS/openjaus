// File Name: confirmEventMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a ConfirmEventMessage

#ifndef CONFIRM_EVENT_MESSAGE_H
#define CONFIRM_EVENT_MESSAGE_H

#include <cimar/jaus.h>

#define JAUS_CONFIRM_EVENT	0xF009

// PV as defined in Events Document v1.8
#ifndef CONFIRM_EVENT_PV
#define CONFIRM_EVENT_PV
#define CONFIRM_EVENT_PV_PERIODIC_RATE_BIT	0
#endif

// Response Codes as defined in Events Document v1.8
#ifndef CONFIRM_EVENT_RESPONSE_CODES
#define CONFIRM_EVENT_RESPONSE_CODES
#define SUCCESSFUL_RESPONSE					0
#define PERIODIC_UNSUPPORTED_RESPONSE		1
#define CHANGE_BASED_UNSUPPORTED_RESPONSE	2
#define CONNECTION_REFUSED_RESPONSE			3
#define INVALID_EVENT_RESPONSE				4
#define MESSAGE_UNSUPPORTED_RESPONSE		5
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
	JausUnsignedShort messageCode;			// 2: Command Code of message sent in case of event occurance
	JausByte eventId;						// 3: Event Id
	JausDouble confirmedUpdateRate;			// 4: For Periodic Events, Scaled UnsignedShort (0, 1092)
	JausByte responseCode;					// 5: Enumeration of Response Types (see above)
	
}ConfirmEventMessageStruct;

typedef ConfirmEventMessageStruct* ConfirmEventMessage;

ConfirmEventMessage confirmEventMessageCreate(void);
void confirmEventMessageDestroy(ConfirmEventMessage);

JausBoolean confirmEventMessageFromBuffer(ConfirmEventMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean confirmEventMessageToBuffer(ConfirmEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean confirmEventMessageToUdpBuffer(ConfirmEventMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

ConfirmEventMessage confirmEventMessageFromJausMessage(JausMessage jausMessage);
JausMessage confirmEventMessageToJausMessage(ConfirmEventMessage message);

unsigned int confirmEventMessageUdpSize(ConfirmEventMessage message);
unsigned int confirmEventMessageSize(ConfirmEventMessage message);


#endif // CONFIRM_EVENT_MESSAGE_H
