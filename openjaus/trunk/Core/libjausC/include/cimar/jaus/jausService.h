// File Name: jausService.h
//
// Written By: Bob Touchton (btouch AT comcast DOT net), inspired by Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// This file defines the attributes of a ReportServicesMessage support functions

#ifndef JAUS_SERVICE_H
#define JAUS_SERVICE_H

#include "cimar/jaus.h"

#define CORE_MESSAGE_SUPPORT	0
#define NO_PRESENCE_VECTOR 		0
#define JAUS_SERVICE_INPUT_COMMAND 0
#define JAUS_SERVICE_OUTPUT_COMMAND 1

// ************************************************************************************************************************************
//			Report Services Support
// ************************************************************************************************************************************

typedef struct
{
	JausUnsignedShort type;				// Enumeration, same as Component ID from RA 3.2
	Vector inputJausCommands;			// Dynamic Array of input messages 
	Vector outputJausCommands;			// Dynamic Array of output messages
}JausServiceStruct;

typedef JausServiceStruct *JausService;

typedef struct
{
	JausUnsignedShort commandCode;		
	JausIntegerPresenceVector presenceVector;			
}JausCommandStruct;

typedef JausCommandStruct *JausCommand;

// Services Vector Constructor
Vector jausServicesCreate(void);

// Services Vector Destructor
void jausServicesDestroy(Vector jausServices);

// Services Duplication
Vector jausServicesDuplicate(Vector sourceServices);

// Service Constructor
JausService jausServiceCreate(JausByte type);

// Command Constructor
JausCommand jausCommandCreate(void);

// Service Destructor
void jausServiceDestroy(JausService service);

// Command Destructor
void jausCommandDestroy(JausCommand command);

// ************************************************************************************************************************************
//			Report Services End User Functions
// ************************************************************************************************************************************

JausBoolean jausServiceAddCoreServices(Vector jausServices);

JausService jausServiceCreateService(JausUnsignedShort serviceType);

JausBoolean jausServiceAddInputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector);

JausBoolean jausServiceAddOutputCommand(JausService service, JausUnsignedShort commandCode, JausIntegerPresenceVector presenceVector);

JausBoolean jausServiceAddService(Vector jausServices, JausService service);

JausService jausServiceRetrieveService(Vector jausServices, JausUnsignedShort serviceType);

#endif

