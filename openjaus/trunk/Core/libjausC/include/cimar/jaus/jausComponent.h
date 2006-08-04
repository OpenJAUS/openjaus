// File Name: jausComponent.h
//
// Written By: Danny Kent (jaus AT dannykent DOT com)
//
// Version: 3.2
//
// Date: 08/04/06
//
// Description: This file defines all the attributes of a JausComponent and defines all 
// pre-defined Jaus Component Ids according to RA 3.2

#ifndef JAUS_COMPONENT_H
#define JAUS_COMPONENT_H

#include "cimar/jaus.h"

#define JAUS_DEFAULT_AUTHORITY		0

// Jaus-Defined Component Ids:
#define JAUS_NODE_MANAGER 									 1
#define JAUS_SYSTEM_COMMANDER 								40
#define JAUS_SUBSYSTEM_COMMANDER 							32
#define JAUS_COMMUNICATOR 									35
#define JAUS_GLOBAL_POSE_SENSOR 							38
#define JAUS_LOCAL_POSE_SENSOR 								41
#define JAUS_VELOCITY_STATE_SENSOR 							42
#define JAUS_PRIMITIVE_DRIVER 								33
#define JAUS_REFLEXIVE_DRIVER 								43
#define JAUS_GLOBAL_VECTOR_DRIVER 							34
#define JAUS_LOCAL_VECTOR_DRIVER 							44
#define JAUS_GLOBAL_WAYPOINT_DRIVER 						45
#define JAUS_LOCAL_WAYPOINT_DRIVER 							46
#define JAUS_GLOBAL_PATH_SEGMENT_DRIVER 					47
#define JAUS_LOCAL_PATH_SEGMENT_DRIVER 						48
#define JAUS_PRIMATIVE_MANIPULATOR 							49
#define JAUS_MANIPULATOR_JOINT_POSITION_SENSOR 				51
#define JAUS_MANIPULATOR_JOINT_VELOCITY_SENSOR 				52
#define JAUS_MANIPULATOR_JOINT_FORCE_TORQUE_SENSOR 			53
#define JAUS_MANIPULATOR_JOINT_POSITIONS_DRIVER 			54
#define JAUS_MANIPULATOR_END_EFFECTOR_DRIVER 				55
#define JAUS_MANIPULATOR_JOINT_VELOCITIES_DRIVER 			56
#define JAUS_MANIPULATOR_END_EFFECTOR_VELOCITY_STATE_DRIVER 57
#define JAUS_MANIPULATOR_JOINT_MOVE_DRIVER 					58
#define JAUS_MANIPULATOR_END_EFFECTOR_DISCRETE_POSE_DRIVER 	59
#define JAUS_VISUAL_SENSOR 									37
#define JAUS_RANGE_SENSOR 									50

#define JAUS_COMPONENT_TIMEOUT_SEC 3.0

typedef struct
{
	char *identification;
	JausAddress address;
	JausState state;
	JausByte authority;
	JausNode node;
	Vector services;
	
	struct
	{
		JausAddress address;
		JausState state;
		JausByte authority;
		JausBoolean active;
	}controller;
	
	unsigned short port;
	double timestamp;
}JausComponentStruct;

typedef JausComponentStruct *JausComponent;

JausComponent jausComponentCreate(void);
void jausComponentDestroy(JausComponent);
JausComponent jausComponentClone(JausComponent);

char *jausComponentGetTypeString(JausComponent);

void jausComponentUpdateTimestamp(JausComponent);
JausBoolean jausComponentIsTimedOut(JausComponent);

int jausComponentToString(JausComponent, char *);

#endif // JAUS_COMPONENT_H
