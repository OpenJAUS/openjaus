// File Name: setDiscreteDevicesMessage.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com), Tom Galluzzo 
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines the attributes of a SetDiscreteDevicesMessage

#ifndef SET_DISCRETE_DEVICES_MESSAGE_H
#define SET_DISCRETE_DEVICES_MESSAGE_H

#include "cimar/jaus.h"

#ifndef JAUS_DEVICES_PV
#define JAUS_DEVICES_PV
#define JAUS_DEVICES_PV_PROPULSION_BIT	0
#define JAUS_DEVICES_PV_PARKING_BIT		1
#define JAUS_DEVICES_PV_GEAR_BIT		2
#define JAUS_DEVICES_PV_TRANSFER_BIT	3
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

	JausBytePresenceVector presenceVector;
	JausByte mainPropulsion;
	JausByte parkingBrakeHorn;
	JausByte gear;
	JausByte transferCase;
	
}SetDiscreteDevicesMessageStruct;

typedef SetDiscreteDevicesMessageStruct* SetDiscreteDevicesMessage;

SetDiscreteDevicesMessage setDiscreteDevicesMessageCreate(void);
void setDiscreteDevicesMessageDestroy(SetDiscreteDevicesMessage);

JausBoolean setDiscreteDevicesMessageFromBuffer(SetDiscreteDevicesMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JausBoolean setDiscreteDevicesMessageToBuffer(SetDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);
JausBoolean setDiscreteDevicesMessageToUdpBuffer(SetDiscreteDevicesMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

SetDiscreteDevicesMessage setDiscreteDevicesMessageFromJausMessage(JausMessage jausMessage);
JausMessage setDiscreteDevicesMessageToJausMessage(SetDiscreteDevicesMessage message);

unsigned int setDiscreteDevicesMessageUdpSize(SetDiscreteDevicesMessage message);
unsigned int setDiscreteDevicesMessageSize(SetDiscreteDevicesMessage message);


#endif // SET_DISCRETE_DEVICES_MESSAGE_H
