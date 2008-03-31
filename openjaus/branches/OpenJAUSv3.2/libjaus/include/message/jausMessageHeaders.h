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
#ifndef JAUS_MESSAGE_HEADERS_H
#define JAUS_MESSAGE_HEADERS_H

#include "jausMessage.h"

// Command Class
#include "command/core/setComponentAuthorityMessage.h"
#include "command/core/shutdownMessage.h"
#include "command/core/standbyMessage.h"
#include "command/core/resumeMessage.h"
#include "command/core/resetMessage.h"
#include "command/core/setEmergencyMessage.h"
#include "command/core/clearEmergencyMessage.h"
#include "command/core/createServiceConnectionMessage.h"
#include "command/core/confirmServiceConnectionMessage.h"
#include "command/core/activateServiceConnectionMessage.h"
#include "command/core/suspendServiceConnectionMessage.h"
#include "command/core/terminateServiceConnectionMessage.h"
#include "command/core/requestComponentControlMessage.h"
#include "command/core/releaseComponentControlMessage.h"
#include "command/core/confirmComponentControlMessage.h"
#include "command/core/rejectComponentControlMessage.h"
#include "command/core/setTimeMessage.h"
#include "command/communications/setDataLinkStatusMessage.h"
#include "command/communications/setDataLinkSelectMessage.h"
#include "command/environment/selectCameraMessage.h"
#include "command/environment/setCameraPoseMessage.h"
#include "command/environment/setCameraCapabilitiesMessage.h"
#include "command/environment/setCameraFormatOptionsMessage.h"
#include "command/manipulator/setJointEffortsMessage.h"
#include "command/manipulator/setJointPositionsMessage.h"
#include "command/manipulator/setJointVelocitiesMessage.h"
#include "command/manipulator/setToolPointMessage.h"
#include "command/manipulator/setEndEffectorPoseMessage.h"
#include "command/manipulator/setEndEffectorVelocityStateMessage.h"
#include "command/manipulator/setJointMotionMessage.h"
#include "command/manipulator/setEndEffectorPathMotionMessage.h"
#include "command/platform/setWrenchEffortMessage.h"
#include "command/platform/setDiscreteDevicesMessage.h"
#include "command/platform/setGlobalVectorMessage.h"
#include "command/platform/setLocalVectorMessage.h"
#include "command/platform/setTravelSpeedMessage.h"
#include "command/platform/setGlobalWaypointMessage.h"
#include "command/platform/setLocalWaypointMessage.h"
#include "command/platform/setVelocityStateMessage.h"
#include "command/platform/setGlobalPathSegmentMessage.h"
#include "command/platform/setLocalPathSegmentMessage.h"

// Inform Class
#include "inform/core/reportComponentAuthorityMessage.h"
#include "inform/core/reportComponentStatusMessage.h"
#include "inform/core/reportTimeMessage.h"
#include "inform/communications/reportDataLinkStatusMessage.h"
#include "inform/communications/reportSelectedDataLinkStatusMessage.h"
#include "inform/communications/reportHeartbeatPulseMessage.h"
#include "inform/environment/reportVideoFrameMessage.h"
#include "inform/environment/reportCameraPoseMessage.h"
#include "inform/environment/reportCameraCountMessage.h"
#include "inform/environment/reportCameraCapabilitiesMessage.h"
#include "inform/environment/reportCameraFormatOptionsMessage.h"
#include "inform/environment/reportRelativeObjectPositionMessage.h"
#include "inform/environment/reportSelectedCameraMessage.h"
#include "inform/manipulator/reportManipulatorSpecificationsMessage.h"
#include "inform/manipulator/reportJointEffortsMessage.h"
#include "inform/manipulator/reportJointPositionsMessage.h"
#include "inform/manipulator/reportJointVelocitiesMessage.h"
#include "inform/manipulator/reportJointForceTorquesMessage.h"
#include "inform/manipulator/reportToolPointMessage.h"
#include "inform/platform/reportPlatformSpecificationsMessage.h"
#include "inform/platform/reportPlatformOperationalDataMessage.h"
#include "inform/platform/reportGlobalPoseMessage.h"
#include "inform/platform/reportVelocityStateMessage.h"
#include "inform/platform/reportWrenchEffortMessage.h"
#include "inform/platform/reportDiscreteDevicesMessage.h"
#include "inform/platform/reportGlobalVectorMessage.h"
#include "inform/platform/reportTravelSpeedMessage.h"
#include "inform/platform/reportWaypointCountMessage.h"
#include "inform/platform/reportGlobalWaypointMessage.h"

// Query Class
#include "query/core/queryComponentAuthorityMessage.h"
#include "query/core/queryComponentStatusMessage.h"
#include "query/core/queryTimeMessage.h"
#include "query/communications/queryDataLinkStatusMessage.h"
#include "query/communications/querySelectedDataLinkStatusMessage.h"
#include "query/environment/queryVideoFrameMessage.h"
#include "query/environment/queryCameraPoseMessage.h"
#include "query/environment/queryCameraCountMessage.h"
#include "query/environment/queryCameraCapabilitiesMessage.h"
#include "query/environment/queryCameraFormatOptionsMessage.h"
#include "query/environment/queryRelativeObjectPositionMessage.h"
#include "query/environment/querySelectedCameraMessage.h"
#include "query/manipulator/queryManipulatorSpecificationsMessage.h"
#include "query/manipulator/queryJointEffortsMessage.h"
#include "query/manipulator/queryJointPositionsMessage.h"
#include "query/manipulator/queryJointVelocitiesMessage.h"
#include "query/manipulator/queryToolPointMessage.h"
#include "query/manipulator/queryJointForceTorquesMessage.h"
#include "query/platform/queryPlatformSpecificationsMessage.h"
#include "query/platform/queryPlatformOperationalDataMessage.h"
#include "query/platform/queryGlobalPoseMessage.h"
#include "query/platform/queryLocalPoseMessage.h"
#include "query/platform/queryVelocityStateMessage.h"
#include "query/platform/queryWrenchEffortMessage.h"
#include "query/platform/queryDiscreteDevicesMessage.h"
#include "query/platform/queryGlobalVectorMessage.h"
#include "query/platform/queryLocalVectorMessage.h"
#include "query/platform/queryTravelSpeedMessage.h"
#include "query/platform/queryWaypointCountMessage.h"
#include "query/platform/queryGlobalWaypointMessage.h"
#include "query/platform/queryLocalWaypointMessage.h"
#include "query/platform/queryPathSegmentCountMessage.h"
#include "query/platform/queryGlobalPathSegmentMessage.h"
#include "query/platform/queryLocalPathSegmentMessage.h"
#include "query/communications/queryHeartbeatPulseMessage.h"

// Experimental
#include "experimental/queryIdentificationMessage.h"
#include "experimental/reportIdentificationMessage.h"
#include "experimental/queryConfigurationMessage.h"
#include "experimental/reportConfigurationMessage.h"
#include "experimental/configurationChangedEventSetupMessage.h"
#include "experimental/configurationChangedEventNotificationMessage.h"
#include "experimental/queryServicesMessage.h"
#include "experimental/reportServicesMessage.h"
#include "experimental/queryPayloadDataElementMessage.h"
#include "experimental/queryPayloadInterfaceMessage.h"
#include "experimental/reportPayloadDataElementMessage.h"
#include "experimental/reportPayloadInterfaceMessage.h"
#include "experimental/setPayloadDataElementMessage.h"

// Experimental/WorldModel
#include "experimental/worldModel/createVksObjectsMessage.h"
#include "experimental/worldModel/deleteVksObjectsMessage.h"
#include "experimental/worldModel/queryVksBoundsMessage.h"
#include "experimental/worldModel/queryVksFeatureClassMetadataMessage.h"
#include "experimental/worldModel/queryVksObjectsMessage.h"
#include "experimental/worldModel/reportVksBoundsMessage.h"
#include "experimental/worldModel/reportVksFeatureClassMetadataMessage.h"
#include "experimental/worldModel/reportVksObjectsCreationMessage.h"
#include "experimental/worldModel/reportVksObjectsMessage.h"

// Experimental/Events
#include "experimental/events/cancelEventMessage.h"
#include "experimental/events/confirmEventMessage.h"
#include "experimental/events/createEventMessage.h"

#endif //JAUS_MESSAGE_HEADERS_H
