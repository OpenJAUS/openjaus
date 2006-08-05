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
// File:		defaultJausMessageProcessor.c
// Version:		3.2
// Written by:	Tom Galluzzo (galluzzo AT gmail DOT com) and Danny Kent (jaus AT dannykent DOT com)
// Date:		08/04/06
// Description:	Processes a given JAUS message with the expected JAUS defined behavior

#include <stdio.h>
#include <string.h>
#include <cimar/jaus.h>

#include "nodeManager.h"

void defaultJausMessageProcessor(JausMessage message, NodeManagerInterface nmi, JausComponent cmpt)
{
	JausMessage txMessage;
	SetComponentAuthorityMessage setComponentAuthority;
	RequestComponentControlMessage requestComponentControl;
	ReleaseComponentControlMessage releaseComponentControl;
	RejectComponentControlMessage rejectComponentControl;
	ConfirmComponentControlMessage confirmComponentControl;
	ReportComponentAuthorityMessage reportComponentAuthority;
	ReportComponentStatusMessage reportComponentStatus;
	ReportIdentificationMessage reportIdentification;
	QueryConfigurationMessage queryConfMsg;
	ReportConfigurationMessage reportConfMsg;
	ConfigurationChangedEventSetupMessage confChangeSetupMsg;
	ConfirmServiceConnectionMessage confScMsg;
	CreateServiceConnectionMessage createScMsg;
	ActivateServiceConnectionMessage activateServiceConnection;
	SuspendServiceConnectionMessage suspendServiceConnection;
	TerminateServiceConnectionMessage terminateServiceConnection;
	ConfirmEventMessage confirmEvent;
	CreateEventMessage createEvent;
	CancelEventMessage cancelEvent;
	QueryServicesMessage queryServices;
	ReportServicesMessage reportServices;
	
	char string[128] = {0};
	
	if(message == NULL)
	{
		return;
	}
	
	if(nmi == NULL)
	{
		jausMessageDestroy(message);
		return;
	}
	
	if(nmi->scm == NULL) 
	{
		jausMessageDestroy(message);
		return;
	}
	
	if(cmpt->controller.active && message->source->id != cmpt->controller.address->id && jausMessageIsRejectableCommand(message) )
	{
		jausAddressToString(message->source, string);
		cError("DefaultMessageProcessor: Command %s, from non-controlling source: %s\n", jausMessageCommandCodeString(message));
		jausMessageDestroy(message);
		return;		
	}	

	switch(message->commandCode) // Switch the processing algorithm according to the JAUS message type
	{
		// Set the component authority according to the incoming authority code
		case JAUS_SET_COMPONENT_AUTHORITY: 
			setComponentAuthority = setComponentAuthorityMessageFromJausMessage(message);
			if(setComponentAuthority)
			{
				cmpt->authority = setComponentAuthority->authorityCode;				
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
		
		case JAUS_SHUTDOWN:
			cmpt->state = JAUS_SHUTDOWN_STATE; 
			jausMessageDestroy(message);
			break;
			
		case JAUS_STANDBY:
			if(cmpt->state == JAUS_READY_STATE)
			{
				cmpt->state = JAUS_STANDBY_STATE;
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_RESUME:
			if(cmpt->state == JAUS_STANDBY_STATE)
			{
				cmpt->state = JAUS_READY_STATE;
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_RESET:
			cmpt->state = JAUS_INITIALIZE_STATE;
			jausMessageDestroy(message);
			break;
			
		case JAUS_SET_EMERGENCY:
			cmpt->state = JAUS_EMERGENCY_STATE; 
			jausMessageDestroy(message);
			break;
			
		case JAUS_CLEAR_EMERGENCY:
			cmpt->state = JAUS_STANDBY_STATE;
			jausMessageDestroy(message);
			break;
			
		case JAUS_REQUEST_COMPONENT_CONTROL:
			requestComponentControl = requestComponentControlMessageFromJausMessage(message);
			if(requestComponentControl)
			{
				if(cmpt->controller.active)
				{
					if(requestComponentControl->authorityCode > cmpt->controller.authority) // Test for higher authority
					{	
						// Terminate control of current component
						rejectComponentControl = rejectComponentControlMessageCreate();
						rejectComponentControl->source->id = cmpt->address->id;
						rejectComponentControl->destination->id = cmpt->controller.address->id;
						txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl); 
						nodeManagerSend(nmi, txMessage);
						jausMessageDestroy(txMessage);
						
						// Accept control of new component
						confirmComponentControl = confirmComponentControlMessageCreate();
						confirmComponentControl->source->id = cmpt->address->id;
						confirmComponentControl->destination->id = message->source->id;
						confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
						txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
						nodeManagerSend(nmi, txMessage);
						jausMessageDestroy(txMessage);
						
						// Update cmpt controller information
						cmpt->controller.address->id = message->source->id;
						cmpt->controller.authority = requestComponentControl->authorityCode;
					
						rejectComponentControlMessageDestroy(rejectComponentControl);
						confirmComponentControlMessageDestroy(confirmComponentControl);						
					}	
					else
					{
						if(	message->source->id != cmpt->controller.address->id)
						{
							rejectComponentControl = rejectComponentControlMessageCreate();
							rejectComponentControl->source->id = cmpt->address->id;
							rejectComponentControl->destination->id = message->source->id;
							txMessage = rejectComponentControlMessageToJausMessage(rejectComponentControl); 
							nodeManagerSend(nmi, txMessage);
							jausMessageDestroy(txMessage);

							rejectComponentControlMessageDestroy(rejectComponentControl);
						}
						else
						{
							// Reaccept control of new component
							confirmComponentControl = confirmComponentControlMessageCreate();
							confirmComponentControl->source->id = cmpt->address->id;
							confirmComponentControl->destination->id = message->source->id;
							confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
							txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
							nodeManagerSend(nmi, txMessage);
							jausMessageDestroy(txMessage);
							
							confirmComponentControlMessageDestroy(confirmComponentControl);						
						}
					}
				}					
				else // Not currently under component control, so give control
				{
					confirmComponentControl = confirmComponentControlMessageCreate();
					confirmComponentControl->source->id = cmpt->address->id;
					confirmComponentControl->destination->id = message->source->id;
					confirmComponentControl->responseCode = JAUS_RESPONSE_CODE_CONTROL_ACCEPTED;
					txMessage = confirmComponentControlMessageToJausMessage(confirmComponentControl); 
					nodeManagerSend(nmi, txMessage);
					jausMessageDestroy(txMessage);
	
					cmpt->controller.address->id = message->source->id;
					cmpt->controller.authority = requestComponentControl->authorityCode;
					cmpt->controller.active = JAUS_TRUE;

					confirmComponentControlMessageDestroy(confirmComponentControl);						
				}

				requestComponentControlMessageDestroy(requestComponentControl);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_RELEASE_COMPONENT_CONTROL:
			releaseComponentControl = releaseComponentControlMessageFromJausMessage(message);
			if(releaseComponentControl)
			{
				cmpt->controller.active = JAUS_FALSE;
				cmpt->controller.address->id = 0;
				cmpt->controller.authority = 0;
				cmpt->controller.state = JAUS_UNDEFINED_STATE;
				releaseComponentControlMessageDestroy(releaseComponentControl);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CONFIRM_SERVICE_CONNECTION:
			confScMsg = confirmServiceConnectionMessageFromJausMessage(message);
			if(confScMsg)
			{
				scManagerProcessConfirmScMessage(nmi, confScMsg);
				confirmServiceConnectionMessageDestroy(confScMsg);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CREATE_SERVICE_CONNECTION:
			createScMsg = createServiceConnectionMessageFromJausMessage(message);
			if(createScMsg)
			{
				scManagerProcessCreateScMessage(nmi, createScMsg);
				createServiceConnectionMessageDestroy(createScMsg);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_ACTIVATE_SERVICE_CONNECTION:
			activateServiceConnection = activateServiceConnectionMessageFromJausMessage(message);
			if(activateServiceConnection)
			{
				scManagerProcessActivateScMessage(nmi, activateServiceConnection);
				activateServiceConnectionMessageDestroy(activateServiceConnection);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
			
		case JAUS_SUSPEND_SERVICE_CONNECTION:
			suspendServiceConnection = suspendServiceConnectionMessageFromJausMessage(message);
			if(suspendServiceConnection)
			{
				scManagerProcessSuspendScMessage(nmi, suspendServiceConnection);
				suspendServiceConnectionMessageDestroy(suspendServiceConnection);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_TERMINATE_SERVICE_CONNECTION:
			terminateServiceConnection = terminateServiceConnectionMessageFromJausMessage(message);
			if(terminateServiceConnection)
			{
				scManagerProcessTerminateScMessage(nmi, terminateServiceConnection);
				terminateServiceConnectionMessageDestroy(terminateServiceConnection);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;
					
		case JAUS_QUERY_COMPONENT_AUTHORITY:
			reportComponentAuthority = reportComponentAuthorityMessageCreate();
			reportComponentAuthority->source->id = cmpt->address->id;
			reportComponentAuthority->destination->id = message->source->id;
			reportComponentAuthority->authorityCode = cmpt->authority;
			txMessage = reportComponentAuthorityMessageToJausMessage(reportComponentAuthority);	
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
			
			reportComponentAuthorityMessageDestroy(reportComponentAuthority);
			jausMessageDestroy(message);
			break;
			
		case JAUS_QUERY_COMPONENT_STATUS:
			reportComponentStatus = reportComponentStatusMessageCreate();
			reportComponentStatus->source->id = cmpt->address->id;
			reportComponentStatus->destination->id = message->source->id;
			reportComponentStatus->primaryStatusCode = cmpt->state;
			
			txMessage = reportComponentStatusMessageToJausMessage(reportComponentStatus);	
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);

			reportComponentStatusMessageDestroy(reportComponentStatus);
			jausMessageDestroy(message);
			break;

		case JAUS_REPORT_HEARTBEAT_PULSE:
			if(	message->source->subsystem == cmpt->address->subsystem &&
				message->source->node == cmpt->address->node &&
				message->source->component == JAUS_NODE_MANAGER)
			{
				nmi->timestamp = getTimeSeconds();
			}
			
			jausMessageDestroy(message);
			break;
					
		case JAUS_QUERY_IDENTIFICATION:
			reportIdentification = reportIdentificationMessageCreate();
			reportIdentification->source->id = cmpt->address->id;
			reportIdentification->destination->id = message->source->id;
			sprintf(reportIdentification->identification, "%s", cmpt->identification);
			reportIdentification->queryType = JAUS_QUERY_FIELD_COMPONENT_IDENTITY; // A component can only respond with its identification
			txMessage = reportIdentificationMessageToJausMessage(reportIdentification);	
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);

			reportIdentificationMessageDestroy(reportIdentification);
			
			//TODO: Change the way the interface between the Cmpt and NM works for subsystem tables
			
		    switch(message->source->component)
		    {
		        case JAUS_NODE_MANAGER:
		        	if(message->source->subsystem == cmpt->address->subsystem && message->source->node == cmpt->address->node)
		        	{
		        		// Only query config from local node manager
						queryConfMsg = queryConfigurationMessageCreate();
						queryConfMsg->source->id = cmpt->address->id;
						queryConfMsg->destination->id = message->source->id;
		        		queryConfMsg->queryField = JAUS_SUBSYSTEM_CONFIGURATION;		        	    
		        	}
		        	else
		        	{
						return;
		        	}
		            break;
		            
		        default: 
		        	return; // Do not bother to query any other component for its config
		    }
			txMessage = queryConfigurationMessageToJausMessage(queryConfMsg);	
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);
			
			queryConfigurationMessageDestroy(queryConfMsg);
			jausMessageDestroy(message);
			break;
			
		case JAUS_REPORT_CONFIGURATION:
			reportConfMsg = reportConfigurationMessageFromJausMessage(message);
			if(reportConfMsg)
			{
				jausSubsystemDestroy(cmpt->node->subsystem);
				cmpt->node->subsystem = jausSubsystemClone(reportConfMsg->subsystem);
				//jausSubsystemTableToString(cmpt->node->subsystem, string);
			    //printf("%s", string);
			    
				confChangeSetupMsg = configurationChangedEventSetupMessageCreate();
				confChangeSetupMsg->source->id = cmpt->address->id;
				confChangeSetupMsg->destination->id = message->source->id;
				confChangeSetupMsg->notificationType = JAUS_NOTIFICATION_ALWAYS;
				// The node manager is designed to send us a notification whenever the subsystem changes
				txMessage = configurationChangedEventSetupMessageToJausMessage(confChangeSetupMsg);	
				nodeManagerSend(nmi, txMessage);
				jausMessageDestroy(txMessage);

				configurationChangedEventSetupMessageDestroy(confChangeSetupMsg);
				reportConfigurationMessageDestroy(reportConfMsg);
				
				scManagerProcessUpdatedSubystem(nmi, cmpt->node->subsystem);
				
				// Check for Controlleer
				if(	cmpt->controller.active == JAUS_TRUE && !nodeManagerVerifyAddress(nmi, cmpt->controller.address) )
				{
					cError("Active Component Controller (%d.%d.%d.%d) lost.\n", 
						cmpt->controller.address->subsystem, cmpt->controller.address->node, cmpt->controller.address->component, cmpt->controller.address->instance);

					// Disable Controller
					cmpt->controller.active = JAUS_FALSE;
					cmpt->controller.address->id = 0;
					cmpt->controller.state = JAUS_UNDEFINED_STATE;
					cmpt->controller.authority = 0;
				}
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CONFIGURATION_CHANGED_EVENT_NOTIFICATION:
			queryConfMsg = queryConfigurationMessageCreate();
			queryConfMsg->source->id = cmpt->address->id;
			queryConfMsg->destination->id = message->source->id;
			
		    switch(message->source->component)
		    {
		        case JAUS_NODE_MANAGER:
		        	queryConfMsg->queryField = JAUS_SUBSYSTEM_CONFIGURATION;		        	    
		            break;
		            
		        default: 
					queryConfigurationMessageDestroy(queryConfMsg);
					jausMessageDestroy(message);
		        	return; // Do not bother to query any other component for its config
		    }
			txMessage = queryConfigurationMessageToJausMessage(queryConfMsg);	
			nodeManagerSend(nmi, txMessage);
			jausMessageDestroy(txMessage);

			queryConfigurationMessageDestroy(queryConfMsg);
			jausMessageDestroy(message);
			break;

		// *************************************************************************************************************************
		// 		Experimental Use of Event Messages for OPC 2.75
		//		Danny Kent (jaus AT dannykent DOT com)
		//		11/07/05
		// *************************************************************************************************************************
		case JAUS_CREATE_EVENT:
			createEvent = createEventMessageFromJausMessage(message);
			if(createEvent)
			{
				if(createEvent->eventType == EVENT_PERIODIC_TYPE || createEvent->eventType == EVENT_PERIODIC_NO_REPEAT_TYPE)
				{
					// Create Service Connection
					scManagerProccessCreateEvent(nmi, createEvent);
				}
				else
				{
					// Don't handle other Event Types Here
					// Error and send a refusal back
					cError("DefaultMessageProcessor: Warning! Received Event Message not of Periodic Type\n");
					confirmEvent = confirmEventMessageCreate();
					if(confirmEvent)
					{
						confirmEvent->source->id = cmpt->address->id;
						confirmEvent->destination->id = message->source->id;
						
						confirmEvent->messageCode = createEvent->messageCode;
						confirmEvent->eventId = 0;
						confirmEvent->responseCode = CONNECTION_REFUSED_RESPONSE;
						
						txMessage = confirmEventMessageToJausMessage(confirmEvent);
						confirmEventMessageDestroy(confirmEvent);
						
						nodeManagerSend(nmi, txMessage);
						jausMessageDestroy(txMessage);
					}
					else
					{
						cError("DefaultMessageProcessor: Cannot create confirmEvent\n");
					}
				}
				createEventMessageDestroy(createEvent);				
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CONFIRM_EVENT:
			confirmEvent = confirmEventMessageFromJausMessage(message);
			if(confirmEvent)
			{
				scManagerProcessConfirmEvent(nmi, confirmEvent);
				confirmEventMessageDestroy(confirmEvent);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		case JAUS_CANCEL_EVENT:
			cancelEvent = cancelEventMessageFromJausMessage(message);
			if(cancelEvent)
			{
				scManagerProcessCancelEvent(nmi, cancelEvent);
				cancelEventMessageDestroy(cancelEvent);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;


		case JAUS_QUERY_SERVICES:
			queryServices = queryServicesMessageFromJausMessage(message);
			if(queryServices)
			{
				// Respond with our services
				reportServices = reportServicesMessageCreate();

				reportServices->destination->id = message->source->id;
				reportServices->source->id = nmi->cmpt->address->id;
				reportServices->jausServices = jausServicesDuplicate(nmi->cmpt->services);

				txMessage = reportServicesMessageToJausMessage(reportServices);
				reportServicesMessageDestroy(reportServices);

				nodeManagerSend(nmi, txMessage);
				jausMessageDestroy(txMessage);
				queryServicesMessageDestroy(queryServices);
			}
			else
			{
				cError("DefaultMessageProcessor: Error unpacking %s message.\n", jausMessageCommandCodeString(message));
			}
			jausMessageDestroy(message);
			break;

		default:
			// Destroy the rxMessage
			jausAddressToString(message->source, string);
			cError("DefaultMessageProcessor: Unhandled code: %s, from: %s\n", jausMessageCommandCodeString(message), string);
			jausMessageDestroy(message);
			break;
	}
}

