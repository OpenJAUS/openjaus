/*****************************************************************************
 *  Copyright (c) 2008, University of Florida
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
// File Name: JausMissionTask.h
//
// Written By: Luke Roseberry (MountainTop Technology, Inc)
//
// Version: 3.3.0b
//
// Date: 09/08/09
//
// Description: This file describes all the functionality associated with a JausMissionTask.
//                JausMissionTasks are used to support the storage and transfer of mission through the planning message set.
//
// Modified by: Luke Roseberry (MountainTop Technology, Inc) to add Planner
//              messages to OpenJAUS.

#ifndef JAUS_MISSION_TASK_H
#define JAUS_MISSION_TASK_H

#include "jaus.h"
#include "string.h"

#include "type/jausMissionCommand.h"

// ************************************************************************************************************************************
//			JausMissionTask
// ************************************************************************************************************************************
typedef struct
{
  JausUnsignedShort taskId;		// Unique Id for this task
  JausArray commands; //List of JausMissionCommand structures for messages
  JausArray children; //List of JausMissionTask structures signifying the children tasks of this task

  JausInteger bufferOffset; //Internal variable used for ToBuffer processing
}JausMissionTaskStruct;
typedef JausMissionTaskStruct *JausMissionTask;

// JausMissionTask Constructor
JAUS_EXPORT JausMissionTask missionTaskCreate(void);

// JausMissionTask Constructor (from Buffer)
JAUS_EXPORT JausBoolean missionTaskFromBuffer(JausMissionTask *messagePointer, unsigned char *buffer, unsigned int bufferSizeBytes);

// JausMissionTask To Buffer
JAUS_EXPORT JausBoolean missionTaskToBuffer(JausMissionTask task, unsigned char *buffer, unsigned int bufferSizeBytes);

// JausMissionTask Destructor
JAUS_EXPORT void missionTaskDestroy(JausMissionTask object);

// JausMissionTask Buffer Size
JAUS_EXPORT unsigned int missionTaskSize(JausMissionTask object);

JAUS_EXPORT char* missionTaskToString(JausMissionTask value);
#endif // JAUSMISSIONTASK_H
