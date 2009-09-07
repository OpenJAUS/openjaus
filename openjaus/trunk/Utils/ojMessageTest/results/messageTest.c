#include <stdio.h>
#include <jaus.h>
#include <malloc.h>

int main(void)
{
	char *msgStr = NULL;
	SetCameraCapabilitiesMessage setCameraCapabilitiesMessage;
	SetCameraPoseMessage setCameraPoseMessage;
	SelectCameraMessage selectCameraMessage;
	SetCameraFormatOptionsMessage setCameraFormatOptionsMessage;
	SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessage;
	SetJointVelocitiesMessage setJointVelocitiesMessage;
	SetJointMotionMessage setJointMotionMessage;
	SetJointEffortsMessage setJointEffortsMessage;
	SetJointPositionsMessage setJointPositionsMessage;
	SetToolPointMessage setToolPointMessage;
	SetEndEffectorPathMotionMessage setEndEffectorPathMotionMessage;
	SetEndEffectorPoseMessage setEndEffectorPoseMessage;
	CreateVksObjectsMessage createVksObjectsMessage;
	DeleteVksObjectsMessage deleteVksObjectsMessage;
	SetVksFeatureClassMetadataMessage setVksFeatureClassMetadataMessage;
	TerminateVksDataTransferMessage terminateVksDataTransferMessage;
	PauseMissionMessage pauseMissionMessage;
	ReplaceMessagesMessage replaceMessagesMessage;
	SpoolMissionMessage spoolMissionMessage;
	RemoveMessagesMessage removeMessagesMessage;
	AbortMissionMessage abortMissionMessage;
	RunMissionMessage runMissionMessage;
	ResumeMissionMessage resumeMissionMessage;
	StandbyMessage standbyMessage;
	ShutdownMessage shutdownMessage;
	ConfirmServiceConnectionMessage confirmServiceConnectionMessage;
	SetEmergencyMessage setEmergencyMessage;
	ActivateServiceConnectionMessage activateServiceConnectionMessage;
	SetComponentAuthorityMessage setComponentAuthorityMessage;
	RejectComponentControlMessage rejectComponentControlMessage;
	TerminateServiceConnectionMessage terminateServiceConnectionMessage;
	RequestComponentControlMessage requestComponentControlMessage;
	SetTimeMessage setTimeMessage;
	ResumeMessage resumeMessage;
	SuspendServiceConnectionMessage suspendServiceConnectionMessage;
	ResetMessage resetMessage;
	CreateServiceConnectionMessage createServiceConnectionMessage;
	ReleaseComponentControlMessage releaseComponentControlMessage;
	ClearEmergencyMessage clearEmergencyMessage;
	ConfirmComponentControlMessage confirmComponentControlMessage;
	RejectEventRequestMessage rejectEventRequestMessage;
	UpdateEventMessage updateEventMessage;
	CreateEventMessage createEventMessage;
	CancelEventMessage cancelEventMessage;
	ConfirmEventRequestMessage confirmEventRequestMessage;
	SetSelectedDataLinkStateMessage setSelectedDataLinkStateMessage;
	SetDataLinkStatusMessage setDataLinkStatusMessage;
	SetDataLinkSelectMessage setDataLinkSelectMessage;
	SetLocalWaypointMessage setLocalWaypointMessage;
	SetLocalVectorMessage setLocalVectorMessage;
	SetVelocityStateMessage setVelocityStateMessage;
	SetGlobalPathSegmentMessage setGlobalPathSegmentMessage;
	SetGlobalWaypointMessage setGlobalWaypointMessage;
	SetDiscreteDevicesMessage setDiscreteDevicesMessage;
	SetWrenchEffortMessage setWrenchEffortMessage;
	SetLocalPathSegmentMessage setLocalPathSegmentMessage;
	SetTravelSpeedMessage setTravelSpeedMessage;
	SetGlobalVectorMessage setGlobalVectorMessage;
	QueryImageMessage queryImageMessage;
	QuerySelectedCameraMessage querySelectedCameraMessage;
	QueryCameraFormatOptionsMessage queryCameraFormatOptionsMessage;
	QueryCameraCountMessage queryCameraCountMessage;
	QueryCameraPoseMessage queryCameraPoseMessage;
	QueryCameraCapabilitiesMessage queryCameraCapabilitiesMessage;
	QueryRelativeObjectPositionMessage queryRelativeObjectPositionMessage;
	QueryJointForceTorquesMessage queryJointForceTorquesMessage;
	QueryManipulatorSpecificationsMessage queryManipulatorSpecificationsMessage;
	QueryToolPointMessage queryToolPointMessage;
	QueryJointEffortsMessage queryJointEffortsMessage;
	QueryJointVelocitiesMessage queryJointVelocitiesMessage;
	QueryJointPositionsMessage queryJointPositionsMessage;
	QueryVksObjectsMessage queryVksObjectsMessage;
	QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessage;
	QueryVksBoundsMessage queryVksBoundsMessage;
	QuerySubsystemListMessage querySubsystemListMessage;
	QueryIdentificationMessage queryIdentificationMessage;
	QueryServicesMessage queryServicesMessage;
	QueryConfigurationMessage queryConfigurationMessage;
	QueryMissionStatusMessage queryMissionStatusMessage;
	QuerySpoolingPreferenceMessage querySpoolingPreferenceMessage;
	QueryComponentStatusMessage queryComponentStatusMessage;
	QueryTimeMessage queryTimeMessage;
	QueryComponentControlMessage queryComponentControlMessage;
	QueryComponentAuthorityMessage queryComponentAuthorityMessage;
	QueryEventsMessage queryEventsMessage;
	QueryHeartbeatPulseMessage queryHeartbeatPulseMessage;
	QuerySelectedDataLinkStatusMessage querySelectedDataLinkStatusMessage;
	QueryDataLinkStatusMessage queryDataLinkStatusMessage;
	QueryWaypointCountMessage queryWaypointCountMessage;
	QueryLocalWaypointMessage queryLocalWaypointMessage;
	QueryLocalPoseMessage queryLocalPoseMessage;
	QueryLocalPathSegmentMessage queryLocalPathSegmentMessage;
	QueryGlobalPoseMessage queryGlobalPoseMessage;
	QueryGlobalVectorMessage queryGlobalVectorMessage;
	QueryGlobalPathSegmentMessage queryGlobalPathSegmentMessage;
	QueryDiscreteDevicesMessage queryDiscreteDevicesMessage;
	QueryPathSegmentCountMessage queryPathSegmentCountMessage;
	QueryTravelSpeedMessage queryTravelSpeedMessage;
	QueryPlatformOperationalDataMessage queryPlatformOperationalDataMessage;
	QueryWrenchEffortMessage queryWrenchEffortMessage;
	QueryVelocityStateMessage queryVelocityStateMessage;
	QueryGlobalWaypointMessage queryGlobalWaypointMessage;
	QueryLocalVectorMessage queryLocalVectorMessage;
	QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessage;
	JausMessage jausMessage;
	ReportRelativeObjectPositionMessage reportRelativeObjectPositionMessage;
	ReportImageMessage reportImageMessage;
	ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessage;
	ReportSelectedCameraMessage reportSelectedCameraMessage;
	ReportCameraCountMessage reportCameraCountMessage;
	ReportCameraFormatOptionsMessage reportCameraFormatOptionsMessage;
	ReportCameraPoseMessage reportCameraPoseMessage;
	ReportJointPositionsMessage reportJointPositionsMessage;
	ReportJointVelocitiesMessage reportJointVelocitiesMessage;
	ReportManipulatorSpecificationsMessage reportManipulatorSpecificationsMessage;
	ReportJointEffortsMessage reportJointEffortsMessage;
	ReportToolPointMessage reportToolPointMessage;
	ReportJointForceTorquesMessage reportJointForceTorquesMessage;
	ReportVksBoundsMessage reportVksBoundsMessage;
	ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessage;
	ReportVksDataTransferTerminationMessage reportVksDataTransferTerminationMessage;
	ReportVksObjectsCreationMessage reportVksObjectsCreationMessage;
	ReportVksObjectsMessage reportVksObjectsMessage;
	ReportServicesMessage reportServicesMessage;
	ReportIdentificationMessage reportIdentificationMessage;
	ReportConfigurationMessage reportConfigurationMessage;
	ReportSubsystemListMessage reportSubsystemListMessage;
	ReportMissionStatusMessage reportMissionStatusMessage;
	ReportSpoolingPreferenceMessage reportSpoolingPreferenceMessage;
	ReportTimeMessage reportTimeMessage;
	ReportComponentAuthorityMessage reportComponentAuthorityMessage;
	ReportComponentStatusMessage reportComponentStatusMessage;
	ReportComponentControlMessage reportComponentControlMessage;
	ReportEventsMessage reportEventsMessage;
	EventMessage eventMessage;
	ReportDataLinkStatusMessage reportDataLinkStatusMessage;
	ReportHeartbeatPulseMessage reportHeartbeatPulseMessage;
	ReportSelectedDataLinkStatusMessage reportSelectedDataLinkStatusMessage;
	ReportVelocityStateMessage reportVelocityStateMessage;
	ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessage;
	ReportWrenchEffortMessage reportWrenchEffortMessage;
	ReportLocalPathSegmentMessage reportLocalPathSegmentMessage;
	ReportWaypointCountMessage reportWaypointCountMessage;
	ReportLocalPoseMessage reportLocalPoseMessage;
	ReportLocalWaypointMessage reportLocalWaypointMessage;
	ReportPathSegmentCountMessage reportPathSegmentCountMessage;
	ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessage;
	ReportGlobalPoseMessage reportGlobalPoseMessage;
	ReportLocalVectorMessage reportLocalVectorMessage;
	ReportDiscreteDevicesMessage reportDiscreteDevicesMessage;
	ReportGlobalPathSegmentMessage reportGlobalPathSegmentMessage;
	ReportTravelSpeedMessage reportTravelSpeedMessage;
	ReportGlobalWaypointMessage reportGlobalWaypointMessage;
	ReportGlobalVectorMessage reportGlobalVectorMessage;


	printf("Testing setCameraCapabilitiesMessage:\n");
	setCameraCapabilitiesMessage = setCameraCapabilitiesMessageCreate();
	if(setCameraCapabilitiesMessage == NULL)
	{
		printf("setCameraCapabilitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = setCameraCapabilitiesMessageToString(setCameraCapabilitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setCameraCapabilitiesMessageToJausMessage(setCameraCapabilitiesMessage);
		setCameraCapabilitiesMessageDestroy(setCameraCapabilitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setCameraCapabilitiesMessageToJausMessage failed\n");
		}
		else
		{
			setCameraCapabilitiesMessage = setCameraCapabilitiesMessageFromJausMessage(jausMessage);
			if(setCameraCapabilitiesMessage == NULL)
			{
				printf("setCameraCapabilitiesMessageFromJausMessage failed\n");
			}
			else
			{
				setCameraCapabilitiesMessageDestroy(setCameraCapabilitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setCameraPoseMessage:\n");
	setCameraPoseMessage = setCameraPoseMessageCreate();
	if(setCameraPoseMessage == NULL)
	{
		printf("setCameraPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = setCameraPoseMessageToString(setCameraPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setCameraPoseMessageToJausMessage(setCameraPoseMessage);
		setCameraPoseMessageDestroy(setCameraPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setCameraPoseMessageToJausMessage failed\n");
		}
		else
		{
			setCameraPoseMessage = setCameraPoseMessageFromJausMessage(jausMessage);
			if(setCameraPoseMessage == NULL)
			{
				printf("setCameraPoseMessageFromJausMessage failed\n");
			}
			else
			{
				setCameraPoseMessageDestroy(setCameraPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing selectCameraMessage:\n");
	selectCameraMessage = selectCameraMessageCreate();
	if(selectCameraMessage == NULL)
	{
		printf("selectCameraMessageCreate failed\n");
	}
	else
	{
		msgStr = selectCameraMessageToString(selectCameraMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = selectCameraMessageToJausMessage(selectCameraMessage);
		selectCameraMessageDestroy(selectCameraMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("selectCameraMessageToJausMessage failed\n");
		}
		else
		{
			selectCameraMessage = selectCameraMessageFromJausMessage(jausMessage);
			if(selectCameraMessage == NULL)
			{
				printf("selectCameraMessageFromJausMessage failed\n");
			}
			else
			{
				selectCameraMessageDestroy(selectCameraMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setCameraFormatOptionsMessage:\n");
	setCameraFormatOptionsMessage = setCameraFormatOptionsMessageCreate();
	if(setCameraFormatOptionsMessage == NULL)
	{
		printf("setCameraFormatOptionsMessageCreate failed\n");
	}
	else
	{
		msgStr = setCameraFormatOptionsMessageToString(setCameraFormatOptionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setCameraFormatOptionsMessageToJausMessage(setCameraFormatOptionsMessage);
		setCameraFormatOptionsMessageDestroy(setCameraFormatOptionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setCameraFormatOptionsMessageToJausMessage failed\n");
		}
		else
		{
			setCameraFormatOptionsMessage = setCameraFormatOptionsMessageFromJausMessage(jausMessage);
			if(setCameraFormatOptionsMessage == NULL)
			{
				printf("setCameraFormatOptionsMessageFromJausMessage failed\n");
			}
			else
			{
				setCameraFormatOptionsMessageDestroy(setCameraFormatOptionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setEndEffectorVelocityStateMessage:\n");
	setEndEffectorVelocityStateMessage = setEndEffectorVelocityStateMessageCreate();
	if(setEndEffectorVelocityStateMessage == NULL)
	{
		printf("setEndEffectorVelocityStateMessageCreate failed\n");
	}
	else
	{
		msgStr = setEndEffectorVelocityStateMessageToString(setEndEffectorVelocityStateMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setEndEffectorVelocityStateMessageToJausMessage(setEndEffectorVelocityStateMessage);
		setEndEffectorVelocityStateMessageDestroy(setEndEffectorVelocityStateMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setEndEffectorVelocityStateMessageToJausMessage failed\n");
		}
		else
		{
			setEndEffectorVelocityStateMessage = setEndEffectorVelocityStateMessageFromJausMessage(jausMessage);
			if(setEndEffectorVelocityStateMessage == NULL)
			{
				printf("setEndEffectorVelocityStateMessageFromJausMessage failed\n");
			}
			else
			{
				setEndEffectorVelocityStateMessageDestroy(setEndEffectorVelocityStateMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setJointVelocitiesMessage:\n");
	setJointVelocitiesMessage = setJointVelocitiesMessageCreate();
	if(setJointVelocitiesMessage == NULL)
	{
		printf("setJointVelocitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = setJointVelocitiesMessageToString(setJointVelocitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setJointVelocitiesMessageToJausMessage(setJointVelocitiesMessage);
		setJointVelocitiesMessageDestroy(setJointVelocitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setJointVelocitiesMessageToJausMessage failed\n");
		}
		else
		{
			setJointVelocitiesMessage = setJointVelocitiesMessageFromJausMessage(jausMessage);
			if(setJointVelocitiesMessage == NULL)
			{
				printf("setJointVelocitiesMessageFromJausMessage failed\n");
			}
			else
			{
				setJointVelocitiesMessageDestroy(setJointVelocitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setJointMotionMessage:\n");
	setJointMotionMessage = setJointMotionMessageCreate();
	if(setJointMotionMessage == NULL)
	{
		printf("setJointMotionMessageCreate failed\n");
	}
	else
	{
		msgStr = setJointMotionMessageToString(setJointMotionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setJointMotionMessageToJausMessage(setJointMotionMessage);
		setJointMotionMessageDestroy(setJointMotionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setJointMotionMessageToJausMessage failed\n");
		}
		else
		{
			setJointMotionMessage = setJointMotionMessageFromJausMessage(jausMessage);
			if(setJointMotionMessage == NULL)
			{
				printf("setJointMotionMessageFromJausMessage failed\n");
			}
			else
			{
				setJointMotionMessageDestroy(setJointMotionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setJointEffortsMessage:\n");
	setJointEffortsMessage = setJointEffortsMessageCreate();
	if(setJointEffortsMessage == NULL)
	{
		printf("setJointEffortsMessageCreate failed\n");
	}
	else
	{
		msgStr = setJointEffortsMessageToString(setJointEffortsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setJointEffortsMessageToJausMessage(setJointEffortsMessage);
		setJointEffortsMessageDestroy(setJointEffortsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setJointEffortsMessageToJausMessage failed\n");
		}
		else
		{
			setJointEffortsMessage = setJointEffortsMessageFromJausMessage(jausMessage);
			if(setJointEffortsMessage == NULL)
			{
				printf("setJointEffortsMessageFromJausMessage failed\n");
			}
			else
			{
				setJointEffortsMessageDestroy(setJointEffortsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setJointPositionsMessage:\n");
	setJointPositionsMessage = setJointPositionsMessageCreate();
	if(setJointPositionsMessage == NULL)
	{
		printf("setJointPositionsMessageCreate failed\n");
	}
	else
	{
		msgStr = setJointPositionsMessageToString(setJointPositionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setJointPositionsMessageToJausMessage(setJointPositionsMessage);
		setJointPositionsMessageDestroy(setJointPositionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setJointPositionsMessageToJausMessage failed\n");
		}
		else
		{
			setJointPositionsMessage = setJointPositionsMessageFromJausMessage(jausMessage);
			if(setJointPositionsMessage == NULL)
			{
				printf("setJointPositionsMessageFromJausMessage failed\n");
			}
			else
			{
				setJointPositionsMessageDestroy(setJointPositionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setToolPointMessage:\n");
	setToolPointMessage = setToolPointMessageCreate();
	if(setToolPointMessage == NULL)
	{
		printf("setToolPointMessageCreate failed\n");
	}
	else
	{
		msgStr = setToolPointMessageToString(setToolPointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setToolPointMessageToJausMessage(setToolPointMessage);
		setToolPointMessageDestroy(setToolPointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setToolPointMessageToJausMessage failed\n");
		}
		else
		{
			setToolPointMessage = setToolPointMessageFromJausMessage(jausMessage);
			if(setToolPointMessage == NULL)
			{
				printf("setToolPointMessageFromJausMessage failed\n");
			}
			else
			{
				setToolPointMessageDestroy(setToolPointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setEndEffectorPathMotionMessage:\n");
	setEndEffectorPathMotionMessage = setEndEffectorPathMotionMessageCreate();
	if(setEndEffectorPathMotionMessage == NULL)
	{
		printf("setEndEffectorPathMotionMessageCreate failed\n");
	}
	else
	{
		msgStr = setEndEffectorPathMotionMessageToString(setEndEffectorPathMotionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setEndEffectorPathMotionMessageToJausMessage(setEndEffectorPathMotionMessage);
		setEndEffectorPathMotionMessageDestroy(setEndEffectorPathMotionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setEndEffectorPathMotionMessageToJausMessage failed\n");
		}
		else
		{
			setEndEffectorPathMotionMessage = setEndEffectorPathMotionMessageFromJausMessage(jausMessage);
			if(setEndEffectorPathMotionMessage == NULL)
			{
				printf("setEndEffectorPathMotionMessageFromJausMessage failed\n");
			}
			else
			{
				setEndEffectorPathMotionMessageDestroy(setEndEffectorPathMotionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setEndEffectorPoseMessage:\n");
	setEndEffectorPoseMessage = setEndEffectorPoseMessageCreate();
	if(setEndEffectorPoseMessage == NULL)
	{
		printf("setEndEffectorPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = setEndEffectorPoseMessageToString(setEndEffectorPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setEndEffectorPoseMessageToJausMessage(setEndEffectorPoseMessage);
		setEndEffectorPoseMessageDestroy(setEndEffectorPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setEndEffectorPoseMessageToJausMessage failed\n");
		}
		else
		{
			setEndEffectorPoseMessage = setEndEffectorPoseMessageFromJausMessage(jausMessage);
			if(setEndEffectorPoseMessage == NULL)
			{
				printf("setEndEffectorPoseMessageFromJausMessage failed\n");
			}
			else
			{
				setEndEffectorPoseMessageDestroy(setEndEffectorPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing createVksObjectsMessage:\n");
	createVksObjectsMessage = createVksObjectsMessageCreate();
	if(createVksObjectsMessage == NULL)
	{
		printf("createVksObjectsMessageCreate failed\n");
	}
	else
	{
		msgStr = createVksObjectsMessageToString(createVksObjectsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = createVksObjectsMessageToJausMessage(createVksObjectsMessage);
		createVksObjectsMessageDestroy(createVksObjectsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("createVksObjectsMessageToJausMessage failed\n");
		}
		else
		{
			createVksObjectsMessage = createVksObjectsMessageFromJausMessage(jausMessage);
			if(createVksObjectsMessage == NULL)
			{
				printf("createVksObjectsMessageFromJausMessage failed\n");
			}
			else
			{
				createVksObjectsMessageDestroy(createVksObjectsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing deleteVksObjectsMessage:\n");
	deleteVksObjectsMessage = deleteVksObjectsMessageCreate();
	if(deleteVksObjectsMessage == NULL)
	{
		printf("deleteVksObjectsMessageCreate failed\n");
	}
	else
	{
		msgStr = deleteVksObjectsMessageToString(deleteVksObjectsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = deleteVksObjectsMessageToJausMessage(deleteVksObjectsMessage);
		deleteVksObjectsMessageDestroy(deleteVksObjectsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("deleteVksObjectsMessageToJausMessage failed\n");
		}
		else
		{
			deleteVksObjectsMessage = deleteVksObjectsMessageFromJausMessage(jausMessage);
			if(deleteVksObjectsMessage == NULL)
			{
				printf("deleteVksObjectsMessageFromJausMessage failed\n");
			}
			else
			{
				deleteVksObjectsMessageDestroy(deleteVksObjectsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setVksFeatureClassMetadataMessage:\n");
	setVksFeatureClassMetadataMessage = setVksFeatureClassMetadataMessageCreate();
	if(setVksFeatureClassMetadataMessage == NULL)
	{
		printf("setVksFeatureClassMetadataMessageCreate failed\n");
	}
	else
	{
		msgStr = setVksFeatureClassMetadataMessageToString(setVksFeatureClassMetadataMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setVksFeatureClassMetadataMessageToJausMessage(setVksFeatureClassMetadataMessage);
		setVksFeatureClassMetadataMessageDestroy(setVksFeatureClassMetadataMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setVksFeatureClassMetadataMessageToJausMessage failed\n");
		}
		else
		{
			setVksFeatureClassMetadataMessage = setVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
			if(setVksFeatureClassMetadataMessage == NULL)
			{
				printf("setVksFeatureClassMetadataMessageFromJausMessage failed\n");
			}
			else
			{
				setVksFeatureClassMetadataMessageDestroy(setVksFeatureClassMetadataMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing terminateVksDataTransferMessage:\n");
	terminateVksDataTransferMessage = terminateVksDataTransferMessageCreate();
	if(terminateVksDataTransferMessage == NULL)
	{
		printf("terminateVksDataTransferMessageCreate failed\n");
	}
	else
	{
		msgStr = terminateVksDataTransferMessageToString(terminateVksDataTransferMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = terminateVksDataTransferMessageToJausMessage(terminateVksDataTransferMessage);
		terminateVksDataTransferMessageDestroy(terminateVksDataTransferMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("terminateVksDataTransferMessageToJausMessage failed\n");
		}
		else
		{
			terminateVksDataTransferMessage = terminateVksDataTransferMessageFromJausMessage(jausMessage);
			if(terminateVksDataTransferMessage == NULL)
			{
				printf("terminateVksDataTransferMessageFromJausMessage failed\n");
			}
			else
			{
				terminateVksDataTransferMessageDestroy(terminateVksDataTransferMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing pauseMissionMessage:\n");
	pauseMissionMessage = pauseMissionMessageCreate();
	if(pauseMissionMessage == NULL)
	{
		printf("pauseMissionMessageCreate failed\n");
	}
	else
	{
		msgStr = pauseMissionMessageToString(pauseMissionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = pauseMissionMessageToJausMessage(pauseMissionMessage);
		pauseMissionMessageDestroy(pauseMissionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("pauseMissionMessageToJausMessage failed\n");
		}
		else
		{
			pauseMissionMessage = pauseMissionMessageFromJausMessage(jausMessage);
			if(pauseMissionMessage == NULL)
			{
				printf("pauseMissionMessageFromJausMessage failed\n");
			}
			else
			{
				pauseMissionMessageDestroy(pauseMissionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing replaceMessagesMessage:\n");
	replaceMessagesMessage = replaceMessagesMessageCreate();
	if(replaceMessagesMessage == NULL)
	{
		printf("replaceMessagesMessageCreate failed\n");
	}
	else
	{
		msgStr = replaceMessagesMessageToString(replaceMessagesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = replaceMessagesMessageToJausMessage(replaceMessagesMessage);
		replaceMessagesMessageDestroy(replaceMessagesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("replaceMessagesMessageToJausMessage failed\n");
		}
		else
		{
			replaceMessagesMessage = replaceMessagesMessageFromJausMessage(jausMessage);
			if(replaceMessagesMessage == NULL)
			{
				printf("replaceMessagesMessageFromJausMessage failed\n");
			}
			else
			{
				replaceMessagesMessageDestroy(replaceMessagesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing spoolMissionMessage:\n");
	spoolMissionMessage = spoolMissionMessageCreate();
	if(spoolMissionMessage == NULL)
	{
		printf("spoolMissionMessageCreate failed\n");
	}
	else
	{
		msgStr = spoolMissionMessageToString(spoolMissionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = spoolMissionMessageToJausMessage(spoolMissionMessage);
		spoolMissionMessageDestroy(spoolMissionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("spoolMissionMessageToJausMessage failed\n");
		}
		else
		{
			spoolMissionMessage = spoolMissionMessageFromJausMessage(jausMessage);
			if(spoolMissionMessage == NULL)
			{
				printf("spoolMissionMessageFromJausMessage failed\n");
			}
			else
			{
				spoolMissionMessageDestroy(spoolMissionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing removeMessagesMessage:\n");
	removeMessagesMessage = removeMessagesMessageCreate();
	if(removeMessagesMessage == NULL)
	{
		printf("removeMessagesMessageCreate failed\n");
	}
	else
	{
		msgStr = removeMessagesMessageToString(removeMessagesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = removeMessagesMessageToJausMessage(removeMessagesMessage);
		removeMessagesMessageDestroy(removeMessagesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("removeMessagesMessageToJausMessage failed\n");
		}
		else
		{
			removeMessagesMessage = removeMessagesMessageFromJausMessage(jausMessage);
			if(removeMessagesMessage == NULL)
			{
				printf("removeMessagesMessageFromJausMessage failed\n");
			}
			else
			{
				removeMessagesMessageDestroy(removeMessagesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing abortMissionMessage:\n");
	abortMissionMessage = abortMissionMessageCreate();
	if(abortMissionMessage == NULL)
	{
		printf("abortMissionMessageCreate failed\n");
	}
	else
	{
		msgStr = abortMissionMessageToString(abortMissionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = abortMissionMessageToJausMessage(abortMissionMessage);
		abortMissionMessageDestroy(abortMissionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("abortMissionMessageToJausMessage failed\n");
		}
		else
		{
			abortMissionMessage = abortMissionMessageFromJausMessage(jausMessage);
			if(abortMissionMessage == NULL)
			{
				printf("abortMissionMessageFromJausMessage failed\n");
			}
			else
			{
				abortMissionMessageDestroy(abortMissionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing runMissionMessage:\n");
	runMissionMessage = runMissionMessageCreate();
	if(runMissionMessage == NULL)
	{
		printf("runMissionMessageCreate failed\n");
	}
	else
	{
		msgStr = runMissionMessageToString(runMissionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = runMissionMessageToJausMessage(runMissionMessage);
		runMissionMessageDestroy(runMissionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("runMissionMessageToJausMessage failed\n");
		}
		else
		{
			runMissionMessage = runMissionMessageFromJausMessage(jausMessage);
			if(runMissionMessage == NULL)
			{
				printf("runMissionMessageFromJausMessage failed\n");
			}
			else
			{
				runMissionMessageDestroy(runMissionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing resumeMissionMessage:\n");
	resumeMissionMessage = resumeMissionMessageCreate();
	if(resumeMissionMessage == NULL)
	{
		printf("resumeMissionMessageCreate failed\n");
	}
	else
	{
		msgStr = resumeMissionMessageToString(resumeMissionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = resumeMissionMessageToJausMessage(resumeMissionMessage);
		resumeMissionMessageDestroy(resumeMissionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("resumeMissionMessageToJausMessage failed\n");
		}
		else
		{
			resumeMissionMessage = resumeMissionMessageFromJausMessage(jausMessage);
			if(resumeMissionMessage == NULL)
			{
				printf("resumeMissionMessageFromJausMessage failed\n");
			}
			else
			{
				resumeMissionMessageDestroy(resumeMissionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing standbyMessage:\n");
	standbyMessage = standbyMessageCreate();
	if(standbyMessage == NULL)
	{
		printf("standbyMessageCreate failed\n");
	}
	else
	{
		msgStr = standbyMessageToString(standbyMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = standbyMessageToJausMessage(standbyMessage);
		standbyMessageDestroy(standbyMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("standbyMessageToJausMessage failed\n");
		}
		else
		{
			standbyMessage = standbyMessageFromJausMessage(jausMessage);
			if(standbyMessage == NULL)
			{
				printf("standbyMessageFromJausMessage failed\n");
			}
			else
			{
				standbyMessageDestroy(standbyMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing shutdownMessage:\n");
	shutdownMessage = shutdownMessageCreate();
	if(shutdownMessage == NULL)
	{
		printf("shutdownMessageCreate failed\n");
	}
	else
	{
		msgStr = shutdownMessageToString(shutdownMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = shutdownMessageToJausMessage(shutdownMessage);
		shutdownMessageDestroy(shutdownMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("shutdownMessageToJausMessage failed\n");
		}
		else
		{
			shutdownMessage = shutdownMessageFromJausMessage(jausMessage);
			if(shutdownMessage == NULL)
			{
				printf("shutdownMessageFromJausMessage failed\n");
			}
			else
			{
				shutdownMessageDestroy(shutdownMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing confirmServiceConnectionMessage:\n");
	confirmServiceConnectionMessage = confirmServiceConnectionMessageCreate();
	if(confirmServiceConnectionMessage == NULL)
	{
		printf("confirmServiceConnectionMessageCreate failed\n");
	}
	else
	{
		msgStr = confirmServiceConnectionMessageToString(confirmServiceConnectionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = confirmServiceConnectionMessageToJausMessage(confirmServiceConnectionMessage);
		confirmServiceConnectionMessageDestroy(confirmServiceConnectionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("confirmServiceConnectionMessageToJausMessage failed\n");
		}
		else
		{
			confirmServiceConnectionMessage = confirmServiceConnectionMessageFromJausMessage(jausMessage);
			if(confirmServiceConnectionMessage == NULL)
			{
				printf("confirmServiceConnectionMessageFromJausMessage failed\n");
			}
			else
			{
				confirmServiceConnectionMessageDestroy(confirmServiceConnectionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setEmergencyMessage:\n");
	setEmergencyMessage = setEmergencyMessageCreate();
	if(setEmergencyMessage == NULL)
	{
		printf("setEmergencyMessageCreate failed\n");
	}
	else
	{
		msgStr = setEmergencyMessageToString(setEmergencyMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setEmergencyMessageToJausMessage(setEmergencyMessage);
		setEmergencyMessageDestroy(setEmergencyMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setEmergencyMessageToJausMessage failed\n");
		}
		else
		{
			setEmergencyMessage = setEmergencyMessageFromJausMessage(jausMessage);
			if(setEmergencyMessage == NULL)
			{
				printf("setEmergencyMessageFromJausMessage failed\n");
			}
			else
			{
				setEmergencyMessageDestroy(setEmergencyMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing activateServiceConnectionMessage:\n");
	activateServiceConnectionMessage = activateServiceConnectionMessageCreate();
	if(activateServiceConnectionMessage == NULL)
	{
		printf("activateServiceConnectionMessageCreate failed\n");
	}
	else
	{
		msgStr = activateServiceConnectionMessageToString(activateServiceConnectionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = activateServiceConnectionMessageToJausMessage(activateServiceConnectionMessage);
		activateServiceConnectionMessageDestroy(activateServiceConnectionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("activateServiceConnectionMessageToJausMessage failed\n");
		}
		else
		{
			activateServiceConnectionMessage = activateServiceConnectionMessageFromJausMessage(jausMessage);
			if(activateServiceConnectionMessage == NULL)
			{
				printf("activateServiceConnectionMessageFromJausMessage failed\n");
			}
			else
			{
				activateServiceConnectionMessageDestroy(activateServiceConnectionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setComponentAuthorityMessage:\n");
	setComponentAuthorityMessage = setComponentAuthorityMessageCreate();
	if(setComponentAuthorityMessage == NULL)
	{
		printf("setComponentAuthorityMessageCreate failed\n");
	}
	else
	{
		msgStr = setComponentAuthorityMessageToString(setComponentAuthorityMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setComponentAuthorityMessageToJausMessage(setComponentAuthorityMessage);
		setComponentAuthorityMessageDestroy(setComponentAuthorityMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setComponentAuthorityMessageToJausMessage failed\n");
		}
		else
		{
			setComponentAuthorityMessage = setComponentAuthorityMessageFromJausMessage(jausMessage);
			if(setComponentAuthorityMessage == NULL)
			{
				printf("setComponentAuthorityMessageFromJausMessage failed\n");
			}
			else
			{
				setComponentAuthorityMessageDestroy(setComponentAuthorityMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing rejectComponentControlMessage:\n");
	rejectComponentControlMessage = rejectComponentControlMessageCreate();
	if(rejectComponentControlMessage == NULL)
	{
		printf("rejectComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = rejectComponentControlMessageToString(rejectComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = rejectComponentControlMessageToJausMessage(rejectComponentControlMessage);
		rejectComponentControlMessageDestroy(rejectComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("rejectComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			rejectComponentControlMessage = rejectComponentControlMessageFromJausMessage(jausMessage);
			if(rejectComponentControlMessage == NULL)
			{
				printf("rejectComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				rejectComponentControlMessageDestroy(rejectComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing terminateServiceConnectionMessage:\n");
	terminateServiceConnectionMessage = terminateServiceConnectionMessageCreate();
	if(terminateServiceConnectionMessage == NULL)
	{
		printf("terminateServiceConnectionMessageCreate failed\n");
	}
	else
	{
		msgStr = terminateServiceConnectionMessageToString(terminateServiceConnectionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = terminateServiceConnectionMessageToJausMessage(terminateServiceConnectionMessage);
		terminateServiceConnectionMessageDestroy(terminateServiceConnectionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("terminateServiceConnectionMessageToJausMessage failed\n");
		}
		else
		{
			terminateServiceConnectionMessage = terminateServiceConnectionMessageFromJausMessage(jausMessage);
			if(terminateServiceConnectionMessage == NULL)
			{
				printf("terminateServiceConnectionMessageFromJausMessage failed\n");
			}
			else
			{
				terminateServiceConnectionMessageDestroy(terminateServiceConnectionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing requestComponentControlMessage:\n");
	requestComponentControlMessage = requestComponentControlMessageCreate();
	if(requestComponentControlMessage == NULL)
	{
		printf("requestComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = requestComponentControlMessageToString(requestComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = requestComponentControlMessageToJausMessage(requestComponentControlMessage);
		requestComponentControlMessageDestroy(requestComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("requestComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			requestComponentControlMessage = requestComponentControlMessageFromJausMessage(jausMessage);
			if(requestComponentControlMessage == NULL)
			{
				printf("requestComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				requestComponentControlMessageDestroy(requestComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setTimeMessage:\n");
	setTimeMessage = setTimeMessageCreate();
	if(setTimeMessage == NULL)
	{
		printf("setTimeMessageCreate failed\n");
	}
	else
	{
		msgStr = setTimeMessageToString(setTimeMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setTimeMessageToJausMessage(setTimeMessage);
		setTimeMessageDestroy(setTimeMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setTimeMessageToJausMessage failed\n");
		}
		else
		{
			setTimeMessage = setTimeMessageFromJausMessage(jausMessage);
			if(setTimeMessage == NULL)
			{
				printf("setTimeMessageFromJausMessage failed\n");
			}
			else
			{
				setTimeMessageDestroy(setTimeMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing resumeMessage:\n");
	resumeMessage = resumeMessageCreate();
	if(resumeMessage == NULL)
	{
		printf("resumeMessageCreate failed\n");
	}
	else
	{
		msgStr = resumeMessageToString(resumeMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = resumeMessageToJausMessage(resumeMessage);
		resumeMessageDestroy(resumeMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("resumeMessageToJausMessage failed\n");
		}
		else
		{
			resumeMessage = resumeMessageFromJausMessage(jausMessage);
			if(resumeMessage == NULL)
			{
				printf("resumeMessageFromJausMessage failed\n");
			}
			else
			{
				resumeMessageDestroy(resumeMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing suspendServiceConnectionMessage:\n");
	suspendServiceConnectionMessage = suspendServiceConnectionMessageCreate();
	if(suspendServiceConnectionMessage == NULL)
	{
		printf("suspendServiceConnectionMessageCreate failed\n");
	}
	else
	{
		msgStr = suspendServiceConnectionMessageToString(suspendServiceConnectionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = suspendServiceConnectionMessageToJausMessage(suspendServiceConnectionMessage);
		suspendServiceConnectionMessageDestroy(suspendServiceConnectionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("suspendServiceConnectionMessageToJausMessage failed\n");
		}
		else
		{
			suspendServiceConnectionMessage = suspendServiceConnectionMessageFromJausMessage(jausMessage);
			if(suspendServiceConnectionMessage == NULL)
			{
				printf("suspendServiceConnectionMessageFromJausMessage failed\n");
			}
			else
			{
				suspendServiceConnectionMessageDestroy(suspendServiceConnectionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing resetMessage:\n");
	resetMessage = resetMessageCreate();
	if(resetMessage == NULL)
	{
		printf("resetMessageCreate failed\n");
	}
	else
	{
		msgStr = resetMessageToString(resetMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = resetMessageToJausMessage(resetMessage);
		resetMessageDestroy(resetMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("resetMessageToJausMessage failed\n");
		}
		else
		{
			resetMessage = resetMessageFromJausMessage(jausMessage);
			if(resetMessage == NULL)
			{
				printf("resetMessageFromJausMessage failed\n");
			}
			else
			{
				resetMessageDestroy(resetMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing createServiceConnectionMessage:\n");
	createServiceConnectionMessage = createServiceConnectionMessageCreate();
	if(createServiceConnectionMessage == NULL)
	{
		printf("createServiceConnectionMessageCreate failed\n");
	}
	else
	{
		msgStr = createServiceConnectionMessageToString(createServiceConnectionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = createServiceConnectionMessageToJausMessage(createServiceConnectionMessage);
		createServiceConnectionMessageDestroy(createServiceConnectionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("createServiceConnectionMessageToJausMessage failed\n");
		}
		else
		{
			createServiceConnectionMessage = createServiceConnectionMessageFromJausMessage(jausMessage);
			if(createServiceConnectionMessage == NULL)
			{
				printf("createServiceConnectionMessageFromJausMessage failed\n");
			}
			else
			{
				createServiceConnectionMessageDestroy(createServiceConnectionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing releaseComponentControlMessage:\n");
	releaseComponentControlMessage = releaseComponentControlMessageCreate();
	if(releaseComponentControlMessage == NULL)
	{
		printf("releaseComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = releaseComponentControlMessageToString(releaseComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = releaseComponentControlMessageToJausMessage(releaseComponentControlMessage);
		releaseComponentControlMessageDestroy(releaseComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("releaseComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			releaseComponentControlMessage = releaseComponentControlMessageFromJausMessage(jausMessage);
			if(releaseComponentControlMessage == NULL)
			{
				printf("releaseComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				releaseComponentControlMessageDestroy(releaseComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing clearEmergencyMessage:\n");
	clearEmergencyMessage = clearEmergencyMessageCreate();
	if(clearEmergencyMessage == NULL)
	{
		printf("clearEmergencyMessageCreate failed\n");
	}
	else
	{
		msgStr = clearEmergencyMessageToString(clearEmergencyMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = clearEmergencyMessageToJausMessage(clearEmergencyMessage);
		clearEmergencyMessageDestroy(clearEmergencyMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("clearEmergencyMessageToJausMessage failed\n");
		}
		else
		{
			clearEmergencyMessage = clearEmergencyMessageFromJausMessage(jausMessage);
			if(clearEmergencyMessage == NULL)
			{
				printf("clearEmergencyMessageFromJausMessage failed\n");
			}
			else
			{
				clearEmergencyMessageDestroy(clearEmergencyMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing confirmComponentControlMessage:\n");
	confirmComponentControlMessage = confirmComponentControlMessageCreate();
	if(confirmComponentControlMessage == NULL)
	{
		printf("confirmComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = confirmComponentControlMessageToString(confirmComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = confirmComponentControlMessageToJausMessage(confirmComponentControlMessage);
		confirmComponentControlMessageDestroy(confirmComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("confirmComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			confirmComponentControlMessage = confirmComponentControlMessageFromJausMessage(jausMessage);
			if(confirmComponentControlMessage == NULL)
			{
				printf("confirmComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				confirmComponentControlMessageDestroy(confirmComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing rejectEventRequestMessage:\n");
	rejectEventRequestMessage = rejectEventRequestMessageCreate();
	if(rejectEventRequestMessage == NULL)
	{
		printf("rejectEventRequestMessageCreate failed\n");
	}
	else
	{
		msgStr = rejectEventRequestMessageToString(rejectEventRequestMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = rejectEventRequestMessageToJausMessage(rejectEventRequestMessage);
		rejectEventRequestMessageDestroy(rejectEventRequestMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("rejectEventRequestMessageToJausMessage failed\n");
		}
		else
		{
			rejectEventRequestMessage = rejectEventRequestMessageFromJausMessage(jausMessage);
			if(rejectEventRequestMessage == NULL)
			{
				printf("rejectEventRequestMessageFromJausMessage failed\n");
			}
			else
			{
				rejectEventRequestMessageDestroy(rejectEventRequestMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing updateEventMessage:\n");
	updateEventMessage = updateEventMessageCreate();
	if(updateEventMessage == NULL)
	{
		printf("updateEventMessageCreate failed\n");
	}
	else
	{
		msgStr = updateEventMessageToString(updateEventMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = updateEventMessageToJausMessage(updateEventMessage);
		updateEventMessageDestroy(updateEventMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("updateEventMessageToJausMessage failed\n");
		}
		else
		{
			updateEventMessage = updateEventMessageFromJausMessage(jausMessage);
			if(updateEventMessage == NULL)
			{
				printf("updateEventMessageFromJausMessage failed\n");
			}
			else
			{
				updateEventMessageDestroy(updateEventMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing createEventMessage:\n");
	createEventMessage = createEventMessageCreate();
	if(createEventMessage == NULL)
	{
		printf("createEventMessageCreate failed\n");
	}
	else
	{
		msgStr = createEventMessageToString(createEventMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = createEventMessageToJausMessage(createEventMessage);
		createEventMessageDestroy(createEventMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("createEventMessageToJausMessage failed\n");
		}
		else
		{
			createEventMessage = createEventMessageFromJausMessage(jausMessage);
			if(createEventMessage == NULL)
			{
				printf("createEventMessageFromJausMessage failed\n");
			}
			else
			{
				createEventMessageDestroy(createEventMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing cancelEventMessage:\n");
	cancelEventMessage = cancelEventMessageCreate();
	if(cancelEventMessage == NULL)
	{
		printf("cancelEventMessageCreate failed\n");
	}
	else
	{
		msgStr = cancelEventMessageToString(cancelEventMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = cancelEventMessageToJausMessage(cancelEventMessage);
		cancelEventMessageDestroy(cancelEventMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("cancelEventMessageToJausMessage failed\n");
		}
		else
		{
			cancelEventMessage = cancelEventMessageFromJausMessage(jausMessage);
			if(cancelEventMessage == NULL)
			{
				printf("cancelEventMessageFromJausMessage failed\n");
			}
			else
			{
				cancelEventMessageDestroy(cancelEventMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing confirmEventRequestMessage:\n");
	confirmEventRequestMessage = confirmEventRequestMessageCreate();
	if(confirmEventRequestMessage == NULL)
	{
		printf("confirmEventRequestMessageCreate failed\n");
	}
	else
	{
		msgStr = confirmEventRequestMessageToString(confirmEventRequestMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = confirmEventRequestMessageToJausMessage(confirmEventRequestMessage);
		confirmEventRequestMessageDestroy(confirmEventRequestMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("confirmEventRequestMessageToJausMessage failed\n");
		}
		else
		{
			confirmEventRequestMessage = confirmEventRequestMessageFromJausMessage(jausMessage);
			if(confirmEventRequestMessage == NULL)
			{
				printf("confirmEventRequestMessageFromJausMessage failed\n");
			}
			else
			{
				confirmEventRequestMessageDestroy(confirmEventRequestMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setSelectedDataLinkStateMessage:\n");
	setSelectedDataLinkStateMessage = setSelectedDataLinkStateMessageCreate();
	if(setSelectedDataLinkStateMessage == NULL)
	{
		printf("setSelectedDataLinkStateMessageCreate failed\n");
	}
	else
	{
		msgStr = setSelectedDataLinkStateMessageToString(setSelectedDataLinkStateMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setSelectedDataLinkStateMessageToJausMessage(setSelectedDataLinkStateMessage);
		setSelectedDataLinkStateMessageDestroy(setSelectedDataLinkStateMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setSelectedDataLinkStateMessageToJausMessage failed\n");
		}
		else
		{
			setSelectedDataLinkStateMessage = setSelectedDataLinkStateMessageFromJausMessage(jausMessage);
			if(setSelectedDataLinkStateMessage == NULL)
			{
				printf("setSelectedDataLinkStateMessageFromJausMessage failed\n");
			}
			else
			{
				setSelectedDataLinkStateMessageDestroy(setSelectedDataLinkStateMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setDataLinkStatusMessage:\n");
	setDataLinkStatusMessage = setDataLinkStatusMessageCreate();
	if(setDataLinkStatusMessage == NULL)
	{
		printf("setDataLinkStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = setDataLinkStatusMessageToString(setDataLinkStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setDataLinkStatusMessageToJausMessage(setDataLinkStatusMessage);
		setDataLinkStatusMessageDestroy(setDataLinkStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setDataLinkStatusMessageToJausMessage failed\n");
		}
		else
		{
			setDataLinkStatusMessage = setDataLinkStatusMessageFromJausMessage(jausMessage);
			if(setDataLinkStatusMessage == NULL)
			{
				printf("setDataLinkStatusMessageFromJausMessage failed\n");
			}
			else
			{
				setDataLinkStatusMessageDestroy(setDataLinkStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setDataLinkSelectMessage:\n");
	setDataLinkSelectMessage = setDataLinkSelectMessageCreate();
	if(setDataLinkSelectMessage == NULL)
	{
		printf("setDataLinkSelectMessageCreate failed\n");
	}
	else
	{
		msgStr = setDataLinkSelectMessageToString(setDataLinkSelectMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setDataLinkSelectMessageToJausMessage(setDataLinkSelectMessage);
		setDataLinkSelectMessageDestroy(setDataLinkSelectMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setDataLinkSelectMessageToJausMessage failed\n");
		}
		else
		{
			setDataLinkSelectMessage = setDataLinkSelectMessageFromJausMessage(jausMessage);
			if(setDataLinkSelectMessage == NULL)
			{
				printf("setDataLinkSelectMessageFromJausMessage failed\n");
			}
			else
			{
				setDataLinkSelectMessageDestroy(setDataLinkSelectMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setLocalWaypointMessage:\n");
	setLocalWaypointMessage = setLocalWaypointMessageCreate();
	if(setLocalWaypointMessage == NULL)
	{
		printf("setLocalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = setLocalWaypointMessageToString(setLocalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setLocalWaypointMessageToJausMessage(setLocalWaypointMessage);
		setLocalWaypointMessageDestroy(setLocalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setLocalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			setLocalWaypointMessage = setLocalWaypointMessageFromJausMessage(jausMessage);
			if(setLocalWaypointMessage == NULL)
			{
				printf("setLocalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				setLocalWaypointMessageDestroy(setLocalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setLocalVectorMessage:\n");
	setLocalVectorMessage = setLocalVectorMessageCreate();
	if(setLocalVectorMessage == NULL)
	{
		printf("setLocalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = setLocalVectorMessageToString(setLocalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setLocalVectorMessageToJausMessage(setLocalVectorMessage);
		setLocalVectorMessageDestroy(setLocalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setLocalVectorMessageToJausMessage failed\n");
		}
		else
		{
			setLocalVectorMessage = setLocalVectorMessageFromJausMessage(jausMessage);
			if(setLocalVectorMessage == NULL)
			{
				printf("setLocalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				setLocalVectorMessageDestroy(setLocalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setVelocityStateMessage:\n");
	setVelocityStateMessage = setVelocityStateMessageCreate();
	if(setVelocityStateMessage == NULL)
	{
		printf("setVelocityStateMessageCreate failed\n");
	}
	else
	{
		msgStr = setVelocityStateMessageToString(setVelocityStateMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setVelocityStateMessageToJausMessage(setVelocityStateMessage);
		setVelocityStateMessageDestroy(setVelocityStateMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setVelocityStateMessageToJausMessage failed\n");
		}
		else
		{
			setVelocityStateMessage = setVelocityStateMessageFromJausMessage(jausMessage);
			if(setVelocityStateMessage == NULL)
			{
				printf("setVelocityStateMessageFromJausMessage failed\n");
			}
			else
			{
				setVelocityStateMessageDestroy(setVelocityStateMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setGlobalPathSegmentMessage:\n");
	setGlobalPathSegmentMessage = setGlobalPathSegmentMessageCreate();
	if(setGlobalPathSegmentMessage == NULL)
	{
		printf("setGlobalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = setGlobalPathSegmentMessageToString(setGlobalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setGlobalPathSegmentMessageToJausMessage(setGlobalPathSegmentMessage);
		setGlobalPathSegmentMessageDestroy(setGlobalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setGlobalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			setGlobalPathSegmentMessage = setGlobalPathSegmentMessageFromJausMessage(jausMessage);
			if(setGlobalPathSegmentMessage == NULL)
			{
				printf("setGlobalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				setGlobalPathSegmentMessageDestroy(setGlobalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setGlobalWaypointMessage:\n");
	setGlobalWaypointMessage = setGlobalWaypointMessageCreate();
	if(setGlobalWaypointMessage == NULL)
	{
		printf("setGlobalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = setGlobalWaypointMessageToString(setGlobalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setGlobalWaypointMessageToJausMessage(setGlobalWaypointMessage);
		setGlobalWaypointMessageDestroy(setGlobalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setGlobalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			setGlobalWaypointMessage = setGlobalWaypointMessageFromJausMessage(jausMessage);
			if(setGlobalWaypointMessage == NULL)
			{
				printf("setGlobalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				setGlobalWaypointMessageDestroy(setGlobalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setDiscreteDevicesMessage:\n");
	setDiscreteDevicesMessage = setDiscreteDevicesMessageCreate();
	if(setDiscreteDevicesMessage == NULL)
	{
		printf("setDiscreteDevicesMessageCreate failed\n");
	}
	else
	{
		msgStr = setDiscreteDevicesMessageToString(setDiscreteDevicesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setDiscreteDevicesMessageToJausMessage(setDiscreteDevicesMessage);
		setDiscreteDevicesMessageDestroy(setDiscreteDevicesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setDiscreteDevicesMessageToJausMessage failed\n");
		}
		else
		{
			setDiscreteDevicesMessage = setDiscreteDevicesMessageFromJausMessage(jausMessage);
			if(setDiscreteDevicesMessage == NULL)
			{
				printf("setDiscreteDevicesMessageFromJausMessage failed\n");
			}
			else
			{
				setDiscreteDevicesMessageDestroy(setDiscreteDevicesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setWrenchEffortMessage:\n");
	setWrenchEffortMessage = setWrenchEffortMessageCreate();
	if(setWrenchEffortMessage == NULL)
	{
		printf("setWrenchEffortMessageCreate failed\n");
	}
	else
	{
		msgStr = setWrenchEffortMessageToString(setWrenchEffortMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setWrenchEffortMessageToJausMessage(setWrenchEffortMessage);
		setWrenchEffortMessageDestroy(setWrenchEffortMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setWrenchEffortMessageToJausMessage failed\n");
		}
		else
		{
			setWrenchEffortMessage = setWrenchEffortMessageFromJausMessage(jausMessage);
			if(setWrenchEffortMessage == NULL)
			{
				printf("setWrenchEffortMessageFromJausMessage failed\n");
			}
			else
			{
				setWrenchEffortMessageDestroy(setWrenchEffortMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setLocalPathSegmentMessage:\n");
	setLocalPathSegmentMessage = setLocalPathSegmentMessageCreate();
	if(setLocalPathSegmentMessage == NULL)
	{
		printf("setLocalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = setLocalPathSegmentMessageToString(setLocalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setLocalPathSegmentMessageToJausMessage(setLocalPathSegmentMessage);
		setLocalPathSegmentMessageDestroy(setLocalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setLocalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			setLocalPathSegmentMessage = setLocalPathSegmentMessageFromJausMessage(jausMessage);
			if(setLocalPathSegmentMessage == NULL)
			{
				printf("setLocalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				setLocalPathSegmentMessageDestroy(setLocalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setTravelSpeedMessage:\n");
	setTravelSpeedMessage = setTravelSpeedMessageCreate();
	if(setTravelSpeedMessage == NULL)
	{
		printf("setTravelSpeedMessageCreate failed\n");
	}
	else
	{
		msgStr = setTravelSpeedMessageToString(setTravelSpeedMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setTravelSpeedMessageToJausMessage(setTravelSpeedMessage);
		setTravelSpeedMessageDestroy(setTravelSpeedMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setTravelSpeedMessageToJausMessage failed\n");
		}
		else
		{
			setTravelSpeedMessage = setTravelSpeedMessageFromJausMessage(jausMessage);
			if(setTravelSpeedMessage == NULL)
			{
				printf("setTravelSpeedMessageFromJausMessage failed\n");
			}
			else
			{
				setTravelSpeedMessageDestroy(setTravelSpeedMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing setGlobalVectorMessage:\n");
	setGlobalVectorMessage = setGlobalVectorMessageCreate();
	if(setGlobalVectorMessage == NULL)
	{
		printf("setGlobalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = setGlobalVectorMessageToString(setGlobalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = setGlobalVectorMessageToJausMessage(setGlobalVectorMessage);
		setGlobalVectorMessageDestroy(setGlobalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("setGlobalVectorMessageToJausMessage failed\n");
		}
		else
		{
			setGlobalVectorMessage = setGlobalVectorMessageFromJausMessage(jausMessage);
			if(setGlobalVectorMessage == NULL)
			{
				printf("setGlobalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				setGlobalVectorMessageDestroy(setGlobalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryImageMessage:\n");
	queryImageMessage = queryImageMessageCreate();
	if(queryImageMessage == NULL)
	{
		printf("queryImageMessageCreate failed\n");
	}
	else
	{
		msgStr = queryImageMessageToString(queryImageMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryImageMessageToJausMessage(queryImageMessage);
		queryImageMessageDestroy(queryImageMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryImageMessageToJausMessage failed\n");
		}
		else
		{
			queryImageMessage = queryImageMessageFromJausMessage(jausMessage);
			if(queryImageMessage == NULL)
			{
				printf("queryImageMessageFromJausMessage failed\n");
			}
			else
			{
				queryImageMessageDestroy(queryImageMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing querySelectedCameraMessage:\n");
	querySelectedCameraMessage = querySelectedCameraMessageCreate();
	if(querySelectedCameraMessage == NULL)
	{
		printf("querySelectedCameraMessageCreate failed\n");
	}
	else
	{
		msgStr = querySelectedCameraMessageToString(querySelectedCameraMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = querySelectedCameraMessageToJausMessage(querySelectedCameraMessage);
		querySelectedCameraMessageDestroy(querySelectedCameraMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("querySelectedCameraMessageToJausMessage failed\n");
		}
		else
		{
			querySelectedCameraMessage = querySelectedCameraMessageFromJausMessage(jausMessage);
			if(querySelectedCameraMessage == NULL)
			{
				printf("querySelectedCameraMessageFromJausMessage failed\n");
			}
			else
			{
				querySelectedCameraMessageDestroy(querySelectedCameraMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryCameraFormatOptionsMessage:\n");
	queryCameraFormatOptionsMessage = queryCameraFormatOptionsMessageCreate();
	if(queryCameraFormatOptionsMessage == NULL)
	{
		printf("queryCameraFormatOptionsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryCameraFormatOptionsMessageToString(queryCameraFormatOptionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryCameraFormatOptionsMessageToJausMessage(queryCameraFormatOptionsMessage);
		queryCameraFormatOptionsMessageDestroy(queryCameraFormatOptionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryCameraFormatOptionsMessageToJausMessage failed\n");
		}
		else
		{
			queryCameraFormatOptionsMessage = queryCameraFormatOptionsMessageFromJausMessage(jausMessage);
			if(queryCameraFormatOptionsMessage == NULL)
			{
				printf("queryCameraFormatOptionsMessageFromJausMessage failed\n");
			}
			else
			{
				queryCameraFormatOptionsMessageDestroy(queryCameraFormatOptionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryCameraCountMessage:\n");
	queryCameraCountMessage = queryCameraCountMessageCreate();
	if(queryCameraCountMessage == NULL)
	{
		printf("queryCameraCountMessageCreate failed\n");
	}
	else
	{
		msgStr = queryCameraCountMessageToString(queryCameraCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryCameraCountMessageToJausMessage(queryCameraCountMessage);
		queryCameraCountMessageDestroy(queryCameraCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryCameraCountMessageToJausMessage failed\n");
		}
		else
		{
			queryCameraCountMessage = queryCameraCountMessageFromJausMessage(jausMessage);
			if(queryCameraCountMessage == NULL)
			{
				printf("queryCameraCountMessageFromJausMessage failed\n");
			}
			else
			{
				queryCameraCountMessageDestroy(queryCameraCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryCameraPoseMessage:\n");
	queryCameraPoseMessage = queryCameraPoseMessageCreate();
	if(queryCameraPoseMessage == NULL)
	{
		printf("queryCameraPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = queryCameraPoseMessageToString(queryCameraPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryCameraPoseMessageToJausMessage(queryCameraPoseMessage);
		queryCameraPoseMessageDestroy(queryCameraPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryCameraPoseMessageToJausMessage failed\n");
		}
		else
		{
			queryCameraPoseMessage = queryCameraPoseMessageFromJausMessage(jausMessage);
			if(queryCameraPoseMessage == NULL)
			{
				printf("queryCameraPoseMessageFromJausMessage failed\n");
			}
			else
			{
				queryCameraPoseMessageDestroy(queryCameraPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryCameraCapabilitiesMessage:\n");
	queryCameraCapabilitiesMessage = queryCameraCapabilitiesMessageCreate();
	if(queryCameraCapabilitiesMessage == NULL)
	{
		printf("queryCameraCapabilitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = queryCameraCapabilitiesMessageToString(queryCameraCapabilitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryCameraCapabilitiesMessageToJausMessage(queryCameraCapabilitiesMessage);
		queryCameraCapabilitiesMessageDestroy(queryCameraCapabilitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryCameraCapabilitiesMessageToJausMessage failed\n");
		}
		else
		{
			queryCameraCapabilitiesMessage = queryCameraCapabilitiesMessageFromJausMessage(jausMessage);
			if(queryCameraCapabilitiesMessage == NULL)
			{
				printf("queryCameraCapabilitiesMessageFromJausMessage failed\n");
			}
			else
			{
				queryCameraCapabilitiesMessageDestroy(queryCameraCapabilitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryRelativeObjectPositionMessage:\n");
	queryRelativeObjectPositionMessage = queryRelativeObjectPositionMessageCreate();
	if(queryRelativeObjectPositionMessage == NULL)
	{
		printf("queryRelativeObjectPositionMessageCreate failed\n");
	}
	else
	{
		msgStr = queryRelativeObjectPositionMessageToString(queryRelativeObjectPositionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryRelativeObjectPositionMessageToJausMessage(queryRelativeObjectPositionMessage);
		queryRelativeObjectPositionMessageDestroy(queryRelativeObjectPositionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryRelativeObjectPositionMessageToJausMessage failed\n");
		}
		else
		{
			queryRelativeObjectPositionMessage = queryRelativeObjectPositionMessageFromJausMessage(jausMessage);
			if(queryRelativeObjectPositionMessage == NULL)
			{
				printf("queryRelativeObjectPositionMessageFromJausMessage failed\n");
			}
			else
			{
				queryRelativeObjectPositionMessageDestroy(queryRelativeObjectPositionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryJointForceTorquesMessage:\n");
	queryJointForceTorquesMessage = queryJointForceTorquesMessageCreate();
	if(queryJointForceTorquesMessage == NULL)
	{
		printf("queryJointForceTorquesMessageCreate failed\n");
	}
	else
	{
		msgStr = queryJointForceTorquesMessageToString(queryJointForceTorquesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryJointForceTorquesMessageToJausMessage(queryJointForceTorquesMessage);
		queryJointForceTorquesMessageDestroy(queryJointForceTorquesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryJointForceTorquesMessageToJausMessage failed\n");
		}
		else
		{
			queryJointForceTorquesMessage = queryJointForceTorquesMessageFromJausMessage(jausMessage);
			if(queryJointForceTorquesMessage == NULL)
			{
				printf("queryJointForceTorquesMessageFromJausMessage failed\n");
			}
			else
			{
				queryJointForceTorquesMessageDestroy(queryJointForceTorquesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryManipulatorSpecificationsMessage:\n");
	queryManipulatorSpecificationsMessage = queryManipulatorSpecificationsMessageCreate();
	if(queryManipulatorSpecificationsMessage == NULL)
	{
		printf("queryManipulatorSpecificationsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryManipulatorSpecificationsMessageToString(queryManipulatorSpecificationsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryManipulatorSpecificationsMessageToJausMessage(queryManipulatorSpecificationsMessage);
		queryManipulatorSpecificationsMessageDestroy(queryManipulatorSpecificationsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryManipulatorSpecificationsMessageToJausMessage failed\n");
		}
		else
		{
			queryManipulatorSpecificationsMessage = queryManipulatorSpecificationsMessageFromJausMessage(jausMessage);
			if(queryManipulatorSpecificationsMessage == NULL)
			{
				printf("queryManipulatorSpecificationsMessageFromJausMessage failed\n");
			}
			else
			{
				queryManipulatorSpecificationsMessageDestroy(queryManipulatorSpecificationsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryToolPointMessage:\n");
	queryToolPointMessage = queryToolPointMessageCreate();
	if(queryToolPointMessage == NULL)
	{
		printf("queryToolPointMessageCreate failed\n");
	}
	else
	{
		msgStr = queryToolPointMessageToString(queryToolPointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryToolPointMessageToJausMessage(queryToolPointMessage);
		queryToolPointMessageDestroy(queryToolPointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryToolPointMessageToJausMessage failed\n");
		}
		else
		{
			queryToolPointMessage = queryToolPointMessageFromJausMessage(jausMessage);
			if(queryToolPointMessage == NULL)
			{
				printf("queryToolPointMessageFromJausMessage failed\n");
			}
			else
			{
				queryToolPointMessageDestroy(queryToolPointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryJointEffortsMessage:\n");
	queryJointEffortsMessage = queryJointEffortsMessageCreate();
	if(queryJointEffortsMessage == NULL)
	{
		printf("queryJointEffortsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryJointEffortsMessageToString(queryJointEffortsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryJointEffortsMessageToJausMessage(queryJointEffortsMessage);
		queryJointEffortsMessageDestroy(queryJointEffortsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryJointEffortsMessageToJausMessage failed\n");
		}
		else
		{
			queryJointEffortsMessage = queryJointEffortsMessageFromJausMessage(jausMessage);
			if(queryJointEffortsMessage == NULL)
			{
				printf("queryJointEffortsMessageFromJausMessage failed\n");
			}
			else
			{
				queryJointEffortsMessageDestroy(queryJointEffortsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryJointVelocitiesMessage:\n");
	queryJointVelocitiesMessage = queryJointVelocitiesMessageCreate();
	if(queryJointVelocitiesMessage == NULL)
	{
		printf("queryJointVelocitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = queryJointVelocitiesMessageToString(queryJointVelocitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryJointVelocitiesMessageToJausMessage(queryJointVelocitiesMessage);
		queryJointVelocitiesMessageDestroy(queryJointVelocitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryJointVelocitiesMessageToJausMessage failed\n");
		}
		else
		{
			queryJointVelocitiesMessage = queryJointVelocitiesMessageFromJausMessage(jausMessage);
			if(queryJointVelocitiesMessage == NULL)
			{
				printf("queryJointVelocitiesMessageFromJausMessage failed\n");
			}
			else
			{
				queryJointVelocitiesMessageDestroy(queryJointVelocitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryJointPositionsMessage:\n");
	queryJointPositionsMessage = queryJointPositionsMessageCreate();
	if(queryJointPositionsMessage == NULL)
	{
		printf("queryJointPositionsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryJointPositionsMessageToString(queryJointPositionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryJointPositionsMessageToJausMessage(queryJointPositionsMessage);
		queryJointPositionsMessageDestroy(queryJointPositionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryJointPositionsMessageToJausMessage failed\n");
		}
		else
		{
			queryJointPositionsMessage = queryJointPositionsMessageFromJausMessage(jausMessage);
			if(queryJointPositionsMessage == NULL)
			{
				printf("queryJointPositionsMessageFromJausMessage failed\n");
			}
			else
			{
				queryJointPositionsMessageDestroy(queryJointPositionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryVksObjectsMessage:\n");
	queryVksObjectsMessage = queryVksObjectsMessageCreate();
	if(queryVksObjectsMessage == NULL)
	{
		printf("queryVksObjectsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryVksObjectsMessageToString(queryVksObjectsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryVksObjectsMessageToJausMessage(queryVksObjectsMessage);
		queryVksObjectsMessageDestroy(queryVksObjectsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryVksObjectsMessageToJausMessage failed\n");
		}
		else
		{
			queryVksObjectsMessage = queryVksObjectsMessageFromJausMessage(jausMessage);
			if(queryVksObjectsMessage == NULL)
			{
				printf("queryVksObjectsMessageFromJausMessage failed\n");
			}
			else
			{
				queryVksObjectsMessageDestroy(queryVksObjectsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryVksFeatureClassMetadataMessage:\n");
	queryVksFeatureClassMetadataMessage = queryVksFeatureClassMetadataMessageCreate();
	if(queryVksFeatureClassMetadataMessage == NULL)
	{
		printf("queryVksFeatureClassMetadataMessageCreate failed\n");
	}
	else
	{
		msgStr = queryVksFeatureClassMetadataMessageToString(queryVksFeatureClassMetadataMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryVksFeatureClassMetadataMessageToJausMessage(queryVksFeatureClassMetadataMessage);
		queryVksFeatureClassMetadataMessageDestroy(queryVksFeatureClassMetadataMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryVksFeatureClassMetadataMessageToJausMessage failed\n");
		}
		else
		{
			queryVksFeatureClassMetadataMessage = queryVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
			if(queryVksFeatureClassMetadataMessage == NULL)
			{
				printf("queryVksFeatureClassMetadataMessageFromJausMessage failed\n");
			}
			else
			{
				queryVksFeatureClassMetadataMessageDestroy(queryVksFeatureClassMetadataMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryVksBoundsMessage:\n");
	queryVksBoundsMessage = queryVksBoundsMessageCreate();
	if(queryVksBoundsMessage == NULL)
	{
		printf("queryVksBoundsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryVksBoundsMessageToString(queryVksBoundsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryVksBoundsMessageToJausMessage(queryVksBoundsMessage);
		queryVksBoundsMessageDestroy(queryVksBoundsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryVksBoundsMessageToJausMessage failed\n");
		}
		else
		{
			queryVksBoundsMessage = queryVksBoundsMessageFromJausMessage(jausMessage);
			if(queryVksBoundsMessage == NULL)
			{
				printf("queryVksBoundsMessageFromJausMessage failed\n");
			}
			else
			{
				queryVksBoundsMessageDestroy(queryVksBoundsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing querySubsystemListMessage:\n");
	querySubsystemListMessage = querySubsystemListMessageCreate();
	if(querySubsystemListMessage == NULL)
	{
		printf("querySubsystemListMessageCreate failed\n");
	}
	else
	{
		msgStr = querySubsystemListMessageToString(querySubsystemListMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = querySubsystemListMessageToJausMessage(querySubsystemListMessage);
		querySubsystemListMessageDestroy(querySubsystemListMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("querySubsystemListMessageToJausMessage failed\n");
		}
		else
		{
			querySubsystemListMessage = querySubsystemListMessageFromJausMessage(jausMessage);
			if(querySubsystemListMessage == NULL)
			{
				printf("querySubsystemListMessageFromJausMessage failed\n");
			}
			else
			{
				querySubsystemListMessageDestroy(querySubsystemListMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryIdentificationMessage:\n");
	queryIdentificationMessage = queryIdentificationMessageCreate();
	if(queryIdentificationMessage == NULL)
	{
		printf("queryIdentificationMessageCreate failed\n");
	}
	else
	{
		msgStr = queryIdentificationMessageToString(queryIdentificationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryIdentificationMessageToJausMessage(queryIdentificationMessage);
		queryIdentificationMessageDestroy(queryIdentificationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryIdentificationMessageToJausMessage failed\n");
		}
		else
		{
			queryIdentificationMessage = queryIdentificationMessageFromJausMessage(jausMessage);
			if(queryIdentificationMessage == NULL)
			{
				printf("queryIdentificationMessageFromJausMessage failed\n");
			}
			else
			{
				queryIdentificationMessageDestroy(queryIdentificationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryServicesMessage:\n");
	queryServicesMessage = queryServicesMessageCreate();
	if(queryServicesMessage == NULL)
	{
		printf("queryServicesMessageCreate failed\n");
	}
	else
	{
		msgStr = queryServicesMessageToString(queryServicesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryServicesMessageToJausMessage(queryServicesMessage);
		queryServicesMessageDestroy(queryServicesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryServicesMessageToJausMessage failed\n");
		}
		else
		{
			queryServicesMessage = queryServicesMessageFromJausMessage(jausMessage);
			if(queryServicesMessage == NULL)
			{
				printf("queryServicesMessageFromJausMessage failed\n");
			}
			else
			{
				queryServicesMessageDestroy(queryServicesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryConfigurationMessage:\n");
	queryConfigurationMessage = queryConfigurationMessageCreate();
	if(queryConfigurationMessage == NULL)
	{
		printf("queryConfigurationMessageCreate failed\n");
	}
	else
	{
		msgStr = queryConfigurationMessageToString(queryConfigurationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryConfigurationMessageToJausMessage(queryConfigurationMessage);
		queryConfigurationMessageDestroy(queryConfigurationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryConfigurationMessageToJausMessage failed\n");
		}
		else
		{
			queryConfigurationMessage = queryConfigurationMessageFromJausMessage(jausMessage);
			if(queryConfigurationMessage == NULL)
			{
				printf("queryConfigurationMessageFromJausMessage failed\n");
			}
			else
			{
				queryConfigurationMessageDestroy(queryConfigurationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryMissionStatusMessage:\n");
	queryMissionStatusMessage = queryMissionStatusMessageCreate();
	if(queryMissionStatusMessage == NULL)
	{
		printf("queryMissionStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = queryMissionStatusMessageToString(queryMissionStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryMissionStatusMessageToJausMessage(queryMissionStatusMessage);
		queryMissionStatusMessageDestroy(queryMissionStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryMissionStatusMessageToJausMessage failed\n");
		}
		else
		{
			queryMissionStatusMessage = queryMissionStatusMessageFromJausMessage(jausMessage);
			if(queryMissionStatusMessage == NULL)
			{
				printf("queryMissionStatusMessageFromJausMessage failed\n");
			}
			else
			{
				queryMissionStatusMessageDestroy(queryMissionStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing querySpoolingPreferenceMessage:\n");
	querySpoolingPreferenceMessage = querySpoolingPreferenceMessageCreate();
	if(querySpoolingPreferenceMessage == NULL)
	{
		printf("querySpoolingPreferenceMessageCreate failed\n");
	}
	else
	{
		msgStr = querySpoolingPreferenceMessageToString(querySpoolingPreferenceMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = querySpoolingPreferenceMessageToJausMessage(querySpoolingPreferenceMessage);
		querySpoolingPreferenceMessageDestroy(querySpoolingPreferenceMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("querySpoolingPreferenceMessageToJausMessage failed\n");
		}
		else
		{
			querySpoolingPreferenceMessage = querySpoolingPreferenceMessageFromJausMessage(jausMessage);
			if(querySpoolingPreferenceMessage == NULL)
			{
				printf("querySpoolingPreferenceMessageFromJausMessage failed\n");
			}
			else
			{
				querySpoolingPreferenceMessageDestroy(querySpoolingPreferenceMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryComponentStatusMessage:\n");
	queryComponentStatusMessage = queryComponentStatusMessageCreate();
	if(queryComponentStatusMessage == NULL)
	{
		printf("queryComponentStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = queryComponentStatusMessageToString(queryComponentStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryComponentStatusMessageToJausMessage(queryComponentStatusMessage);
		queryComponentStatusMessageDestroy(queryComponentStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryComponentStatusMessageToJausMessage failed\n");
		}
		else
		{
			queryComponentStatusMessage = queryComponentStatusMessageFromJausMessage(jausMessage);
			if(queryComponentStatusMessage == NULL)
			{
				printf("queryComponentStatusMessageFromJausMessage failed\n");
			}
			else
			{
				queryComponentStatusMessageDestroy(queryComponentStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryTimeMessage:\n");
	queryTimeMessage = queryTimeMessageCreate();
	if(queryTimeMessage == NULL)
	{
		printf("queryTimeMessageCreate failed\n");
	}
	else
	{
		msgStr = queryTimeMessageToString(queryTimeMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryTimeMessageToJausMessage(queryTimeMessage);
		queryTimeMessageDestroy(queryTimeMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryTimeMessageToJausMessage failed\n");
		}
		else
		{
			queryTimeMessage = queryTimeMessageFromJausMessage(jausMessage);
			if(queryTimeMessage == NULL)
			{
				printf("queryTimeMessageFromJausMessage failed\n");
			}
			else
			{
				queryTimeMessageDestroy(queryTimeMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryComponentControlMessage:\n");
	queryComponentControlMessage = queryComponentControlMessageCreate();
	if(queryComponentControlMessage == NULL)
	{
		printf("queryComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = queryComponentControlMessageToString(queryComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryComponentControlMessageToJausMessage(queryComponentControlMessage);
		queryComponentControlMessageDestroy(queryComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			queryComponentControlMessage = queryComponentControlMessageFromJausMessage(jausMessage);
			if(queryComponentControlMessage == NULL)
			{
				printf("queryComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				queryComponentControlMessageDestroy(queryComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryComponentAuthorityMessage:\n");
	queryComponentAuthorityMessage = queryComponentAuthorityMessageCreate();
	if(queryComponentAuthorityMessage == NULL)
	{
		printf("queryComponentAuthorityMessageCreate failed\n");
	}
	else
	{
		msgStr = queryComponentAuthorityMessageToString(queryComponentAuthorityMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryComponentAuthorityMessageToJausMessage(queryComponentAuthorityMessage);
		queryComponentAuthorityMessageDestroy(queryComponentAuthorityMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryComponentAuthorityMessageToJausMessage failed\n");
		}
		else
		{
			queryComponentAuthorityMessage = queryComponentAuthorityMessageFromJausMessage(jausMessage);
			if(queryComponentAuthorityMessage == NULL)
			{
				printf("queryComponentAuthorityMessageFromJausMessage failed\n");
			}
			else
			{
				queryComponentAuthorityMessageDestroy(queryComponentAuthorityMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryEventsMessage:\n");
	queryEventsMessage = queryEventsMessageCreate();
	if(queryEventsMessage == NULL)
	{
		printf("queryEventsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryEventsMessageToString(queryEventsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryEventsMessageToJausMessage(queryEventsMessage);
		queryEventsMessageDestroy(queryEventsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryEventsMessageToJausMessage failed\n");
		}
		else
		{
			queryEventsMessage = queryEventsMessageFromJausMessage(jausMessage);
			if(queryEventsMessage == NULL)
			{
				printf("queryEventsMessageFromJausMessage failed\n");
			}
			else
			{
				queryEventsMessageDestroy(queryEventsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryHeartbeatPulseMessage:\n");
	queryHeartbeatPulseMessage = queryHeartbeatPulseMessageCreate();
	if(queryHeartbeatPulseMessage == NULL)
	{
		printf("queryHeartbeatPulseMessageCreate failed\n");
	}
	else
	{
		msgStr = queryHeartbeatPulseMessageToString(queryHeartbeatPulseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryHeartbeatPulseMessageToJausMessage(queryHeartbeatPulseMessage);
		queryHeartbeatPulseMessageDestroy(queryHeartbeatPulseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryHeartbeatPulseMessageToJausMessage failed\n");
		}
		else
		{
			queryHeartbeatPulseMessage = queryHeartbeatPulseMessageFromJausMessage(jausMessage);
			if(queryHeartbeatPulseMessage == NULL)
			{
				printf("queryHeartbeatPulseMessageFromJausMessage failed\n");
			}
			else
			{
				queryHeartbeatPulseMessageDestroy(queryHeartbeatPulseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing querySelectedDataLinkStatusMessage:\n");
	querySelectedDataLinkStatusMessage = querySelectedDataLinkStatusMessageCreate();
	if(querySelectedDataLinkStatusMessage == NULL)
	{
		printf("querySelectedDataLinkStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = querySelectedDataLinkStatusMessageToString(querySelectedDataLinkStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = querySelectedDataLinkStatusMessageToJausMessage(querySelectedDataLinkStatusMessage);
		querySelectedDataLinkStatusMessageDestroy(querySelectedDataLinkStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("querySelectedDataLinkStatusMessageToJausMessage failed\n");
		}
		else
		{
			querySelectedDataLinkStatusMessage = querySelectedDataLinkStatusMessageFromJausMessage(jausMessage);
			if(querySelectedDataLinkStatusMessage == NULL)
			{
				printf("querySelectedDataLinkStatusMessageFromJausMessage failed\n");
			}
			else
			{
				querySelectedDataLinkStatusMessageDestroy(querySelectedDataLinkStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryDataLinkStatusMessage:\n");
	queryDataLinkStatusMessage = queryDataLinkStatusMessageCreate();
	if(queryDataLinkStatusMessage == NULL)
	{
		printf("queryDataLinkStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = queryDataLinkStatusMessageToString(queryDataLinkStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryDataLinkStatusMessageToJausMessage(queryDataLinkStatusMessage);
		queryDataLinkStatusMessageDestroy(queryDataLinkStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryDataLinkStatusMessageToJausMessage failed\n");
		}
		else
		{
			queryDataLinkStatusMessage = queryDataLinkStatusMessageFromJausMessage(jausMessage);
			if(queryDataLinkStatusMessage == NULL)
			{
				printf("queryDataLinkStatusMessageFromJausMessage failed\n");
			}
			else
			{
				queryDataLinkStatusMessageDestroy(queryDataLinkStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryWaypointCountMessage:\n");
	queryWaypointCountMessage = queryWaypointCountMessageCreate();
	if(queryWaypointCountMessage == NULL)
	{
		printf("queryWaypointCountMessageCreate failed\n");
	}
	else
	{
		msgStr = queryWaypointCountMessageToString(queryWaypointCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryWaypointCountMessageToJausMessage(queryWaypointCountMessage);
		queryWaypointCountMessageDestroy(queryWaypointCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryWaypointCountMessageToJausMessage failed\n");
		}
		else
		{
			queryWaypointCountMessage = queryWaypointCountMessageFromJausMessage(jausMessage);
			if(queryWaypointCountMessage == NULL)
			{
				printf("queryWaypointCountMessageFromJausMessage failed\n");
			}
			else
			{
				queryWaypointCountMessageDestroy(queryWaypointCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryLocalWaypointMessage:\n");
	queryLocalWaypointMessage = queryLocalWaypointMessageCreate();
	if(queryLocalWaypointMessage == NULL)
	{
		printf("queryLocalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = queryLocalWaypointMessageToString(queryLocalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryLocalWaypointMessageToJausMessage(queryLocalWaypointMessage);
		queryLocalWaypointMessageDestroy(queryLocalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryLocalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			queryLocalWaypointMessage = queryLocalWaypointMessageFromJausMessage(jausMessage);
			if(queryLocalWaypointMessage == NULL)
			{
				printf("queryLocalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				queryLocalWaypointMessageDestroy(queryLocalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryLocalPoseMessage:\n");
	queryLocalPoseMessage = queryLocalPoseMessageCreate();
	if(queryLocalPoseMessage == NULL)
	{
		printf("queryLocalPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = queryLocalPoseMessageToString(queryLocalPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryLocalPoseMessageToJausMessage(queryLocalPoseMessage);
		queryLocalPoseMessageDestroy(queryLocalPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryLocalPoseMessageToJausMessage failed\n");
		}
		else
		{
			queryLocalPoseMessage = queryLocalPoseMessageFromJausMessage(jausMessage);
			if(queryLocalPoseMessage == NULL)
			{
				printf("queryLocalPoseMessageFromJausMessage failed\n");
			}
			else
			{
				queryLocalPoseMessageDestroy(queryLocalPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryLocalPathSegmentMessage:\n");
	queryLocalPathSegmentMessage = queryLocalPathSegmentMessageCreate();
	if(queryLocalPathSegmentMessage == NULL)
	{
		printf("queryLocalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = queryLocalPathSegmentMessageToString(queryLocalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryLocalPathSegmentMessageToJausMessage(queryLocalPathSegmentMessage);
		queryLocalPathSegmentMessageDestroy(queryLocalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryLocalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			queryLocalPathSegmentMessage = queryLocalPathSegmentMessageFromJausMessage(jausMessage);
			if(queryLocalPathSegmentMessage == NULL)
			{
				printf("queryLocalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				queryLocalPathSegmentMessageDestroy(queryLocalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryGlobalPoseMessage:\n");
	queryGlobalPoseMessage = queryGlobalPoseMessageCreate();
	if(queryGlobalPoseMessage == NULL)
	{
		printf("queryGlobalPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = queryGlobalPoseMessageToString(queryGlobalPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryGlobalPoseMessageToJausMessage(queryGlobalPoseMessage);
		queryGlobalPoseMessageDestroy(queryGlobalPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryGlobalPoseMessageToJausMessage failed\n");
		}
		else
		{
			queryGlobalPoseMessage = queryGlobalPoseMessageFromJausMessage(jausMessage);
			if(queryGlobalPoseMessage == NULL)
			{
				printf("queryGlobalPoseMessageFromJausMessage failed\n");
			}
			else
			{
				queryGlobalPoseMessageDestroy(queryGlobalPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryGlobalVectorMessage:\n");
	queryGlobalVectorMessage = queryGlobalVectorMessageCreate();
	if(queryGlobalVectorMessage == NULL)
	{
		printf("queryGlobalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = queryGlobalVectorMessageToString(queryGlobalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryGlobalVectorMessageToJausMessage(queryGlobalVectorMessage);
		queryGlobalVectorMessageDestroy(queryGlobalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryGlobalVectorMessageToJausMessage failed\n");
		}
		else
		{
			queryGlobalVectorMessage = queryGlobalVectorMessageFromJausMessage(jausMessage);
			if(queryGlobalVectorMessage == NULL)
			{
				printf("queryGlobalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				queryGlobalVectorMessageDestroy(queryGlobalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryGlobalPathSegmentMessage:\n");
	queryGlobalPathSegmentMessage = queryGlobalPathSegmentMessageCreate();
	if(queryGlobalPathSegmentMessage == NULL)
	{
		printf("queryGlobalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = queryGlobalPathSegmentMessageToString(queryGlobalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryGlobalPathSegmentMessageToJausMessage(queryGlobalPathSegmentMessage);
		queryGlobalPathSegmentMessageDestroy(queryGlobalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryGlobalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			queryGlobalPathSegmentMessage = queryGlobalPathSegmentMessageFromJausMessage(jausMessage);
			if(queryGlobalPathSegmentMessage == NULL)
			{
				printf("queryGlobalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				queryGlobalPathSegmentMessageDestroy(queryGlobalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryDiscreteDevicesMessage:\n");
	queryDiscreteDevicesMessage = queryDiscreteDevicesMessageCreate();
	if(queryDiscreteDevicesMessage == NULL)
	{
		printf("queryDiscreteDevicesMessageCreate failed\n");
	}
	else
	{
		msgStr = queryDiscreteDevicesMessageToString(queryDiscreteDevicesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryDiscreteDevicesMessageToJausMessage(queryDiscreteDevicesMessage);
		queryDiscreteDevicesMessageDestroy(queryDiscreteDevicesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryDiscreteDevicesMessageToJausMessage failed\n");
		}
		else
		{
			queryDiscreteDevicesMessage = queryDiscreteDevicesMessageFromJausMessage(jausMessage);
			if(queryDiscreteDevicesMessage == NULL)
			{
				printf("queryDiscreteDevicesMessageFromJausMessage failed\n");
			}
			else
			{
				queryDiscreteDevicesMessageDestroy(queryDiscreteDevicesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryPathSegmentCountMessage:\n");
	queryPathSegmentCountMessage = queryPathSegmentCountMessageCreate();
	if(queryPathSegmentCountMessage == NULL)
	{
		printf("queryPathSegmentCountMessageCreate failed\n");
	}
	else
	{
		msgStr = queryPathSegmentCountMessageToString(queryPathSegmentCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryPathSegmentCountMessageToJausMessage(queryPathSegmentCountMessage);
		queryPathSegmentCountMessageDestroy(queryPathSegmentCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryPathSegmentCountMessageToJausMessage failed\n");
		}
		else
		{
			queryPathSegmentCountMessage = queryPathSegmentCountMessageFromJausMessage(jausMessage);
			if(queryPathSegmentCountMessage == NULL)
			{
				printf("queryPathSegmentCountMessageFromJausMessage failed\n");
			}
			else
			{
				queryPathSegmentCountMessageDestroy(queryPathSegmentCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryTravelSpeedMessage:\n");
	queryTravelSpeedMessage = queryTravelSpeedMessageCreate();
	if(queryTravelSpeedMessage == NULL)
	{
		printf("queryTravelSpeedMessageCreate failed\n");
	}
	else
	{
		msgStr = queryTravelSpeedMessageToString(queryTravelSpeedMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryTravelSpeedMessageToJausMessage(queryTravelSpeedMessage);
		queryTravelSpeedMessageDestroy(queryTravelSpeedMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryTravelSpeedMessageToJausMessage failed\n");
		}
		else
		{
			queryTravelSpeedMessage = queryTravelSpeedMessageFromJausMessage(jausMessage);
			if(queryTravelSpeedMessage == NULL)
			{
				printf("queryTravelSpeedMessageFromJausMessage failed\n");
			}
			else
			{
				queryTravelSpeedMessageDestroy(queryTravelSpeedMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryPlatformOperationalDataMessage:\n");
	queryPlatformOperationalDataMessage = queryPlatformOperationalDataMessageCreate();
	if(queryPlatformOperationalDataMessage == NULL)
	{
		printf("queryPlatformOperationalDataMessageCreate failed\n");
	}
	else
	{
		msgStr = queryPlatformOperationalDataMessageToString(queryPlatformOperationalDataMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryPlatformOperationalDataMessageToJausMessage(queryPlatformOperationalDataMessage);
		queryPlatformOperationalDataMessageDestroy(queryPlatformOperationalDataMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryPlatformOperationalDataMessageToJausMessage failed\n");
		}
		else
		{
			queryPlatformOperationalDataMessage = queryPlatformOperationalDataMessageFromJausMessage(jausMessage);
			if(queryPlatformOperationalDataMessage == NULL)
			{
				printf("queryPlatformOperationalDataMessageFromJausMessage failed\n");
			}
			else
			{
				queryPlatformOperationalDataMessageDestroy(queryPlatformOperationalDataMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryWrenchEffortMessage:\n");
	queryWrenchEffortMessage = queryWrenchEffortMessageCreate();
	if(queryWrenchEffortMessage == NULL)
	{
		printf("queryWrenchEffortMessageCreate failed\n");
	}
	else
	{
		msgStr = queryWrenchEffortMessageToString(queryWrenchEffortMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryWrenchEffortMessageToJausMessage(queryWrenchEffortMessage);
		queryWrenchEffortMessageDestroy(queryWrenchEffortMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryWrenchEffortMessageToJausMessage failed\n");
		}
		else
		{
			queryWrenchEffortMessage = queryWrenchEffortMessageFromJausMessage(jausMessage);
			if(queryWrenchEffortMessage == NULL)
			{
				printf("queryWrenchEffortMessageFromJausMessage failed\n");
			}
			else
			{
				queryWrenchEffortMessageDestroy(queryWrenchEffortMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryVelocityStateMessage:\n");
	queryVelocityStateMessage = queryVelocityStateMessageCreate();
	if(queryVelocityStateMessage == NULL)
	{
		printf("queryVelocityStateMessageCreate failed\n");
	}
	else
	{
		msgStr = queryVelocityStateMessageToString(queryVelocityStateMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryVelocityStateMessageToJausMessage(queryVelocityStateMessage);
		queryVelocityStateMessageDestroy(queryVelocityStateMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryVelocityStateMessageToJausMessage failed\n");
		}
		else
		{
			queryVelocityStateMessage = queryVelocityStateMessageFromJausMessage(jausMessage);
			if(queryVelocityStateMessage == NULL)
			{
				printf("queryVelocityStateMessageFromJausMessage failed\n");
			}
			else
			{
				queryVelocityStateMessageDestroy(queryVelocityStateMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryGlobalWaypointMessage:\n");
	queryGlobalWaypointMessage = queryGlobalWaypointMessageCreate();
	if(queryGlobalWaypointMessage == NULL)
	{
		printf("queryGlobalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = queryGlobalWaypointMessageToString(queryGlobalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryGlobalWaypointMessageToJausMessage(queryGlobalWaypointMessage);
		queryGlobalWaypointMessageDestroy(queryGlobalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryGlobalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			queryGlobalWaypointMessage = queryGlobalWaypointMessageFromJausMessage(jausMessage);
			if(queryGlobalWaypointMessage == NULL)
			{
				printf("queryGlobalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				queryGlobalWaypointMessageDestroy(queryGlobalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryLocalVectorMessage:\n");
	queryLocalVectorMessage = queryLocalVectorMessageCreate();
	if(queryLocalVectorMessage == NULL)
	{
		printf("queryLocalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = queryLocalVectorMessageToString(queryLocalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryLocalVectorMessageToJausMessage(queryLocalVectorMessage);
		queryLocalVectorMessageDestroy(queryLocalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryLocalVectorMessageToJausMessage failed\n");
		}
		else
		{
			queryLocalVectorMessage = queryLocalVectorMessageFromJausMessage(jausMessage);
			if(queryLocalVectorMessage == NULL)
			{
				printf("queryLocalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				queryLocalVectorMessageDestroy(queryLocalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing queryPlatformSpecificationsMessage:\n");
	queryPlatformSpecificationsMessage = queryPlatformSpecificationsMessageCreate();
	if(queryPlatformSpecificationsMessage == NULL)
	{
		printf("queryPlatformSpecificationsMessageCreate failed\n");
	}
	else
	{
		msgStr = queryPlatformSpecificationsMessageToString(queryPlatformSpecificationsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = queryPlatformSpecificationsMessageToJausMessage(queryPlatformSpecificationsMessage);
		queryPlatformSpecificationsMessageDestroy(queryPlatformSpecificationsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("queryPlatformSpecificationsMessageToJausMessage failed\n");
		}
		else
		{
			queryPlatformSpecificationsMessage = queryPlatformSpecificationsMessageFromJausMessage(jausMessage);
			if(queryPlatformSpecificationsMessage == NULL)
			{
				printf("queryPlatformSpecificationsMessageFromJausMessage failed\n");
			}
			else
			{
				queryPlatformSpecificationsMessageDestroy(queryPlatformSpecificationsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportRelativeObjectPositionMessage:\n");
	reportRelativeObjectPositionMessage = reportRelativeObjectPositionMessageCreate();
	if(reportRelativeObjectPositionMessage == NULL)
	{
		printf("reportRelativeObjectPositionMessageCreate failed\n");
	}
	else
	{
		msgStr = reportRelativeObjectPositionMessageToString(reportRelativeObjectPositionMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportRelativeObjectPositionMessageToJausMessage(reportRelativeObjectPositionMessage);
		reportRelativeObjectPositionMessageDestroy(reportRelativeObjectPositionMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportRelativeObjectPositionMessageToJausMessage failed\n");
		}
		else
		{
			reportRelativeObjectPositionMessage = reportRelativeObjectPositionMessageFromJausMessage(jausMessage);
			if(reportRelativeObjectPositionMessage == NULL)
			{
				printf("reportRelativeObjectPositionMessageFromJausMessage failed\n");
			}
			else
			{
				reportRelativeObjectPositionMessageDestroy(reportRelativeObjectPositionMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportImageMessage:\n");
	reportImageMessage = reportImageMessageCreate();
	if(reportImageMessage == NULL)
	{
		printf("reportImageMessageCreate failed\n");
	}
	else
	{
		msgStr = reportImageMessageToString(reportImageMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportImageMessageToJausMessage(reportImageMessage);
		reportImageMessageDestroy(reportImageMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportImageMessageToJausMessage failed\n");
		}
		else
		{
			reportImageMessage = reportImageMessageFromJausMessage(jausMessage);
			if(reportImageMessage == NULL)
			{
				printf("reportImageMessageFromJausMessage failed\n");
			}
			else
			{
				reportImageMessageDestroy(reportImageMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportCameraCapabilitiesMessage:\n");
	reportCameraCapabilitiesMessage = reportCameraCapabilitiesMessageCreate();
	if(reportCameraCapabilitiesMessage == NULL)
	{
		printf("reportCameraCapabilitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = reportCameraCapabilitiesMessageToString(reportCameraCapabilitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportCameraCapabilitiesMessageToJausMessage(reportCameraCapabilitiesMessage);
		reportCameraCapabilitiesMessageDestroy(reportCameraCapabilitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportCameraCapabilitiesMessageToJausMessage failed\n");
		}
		else
		{
			reportCameraCapabilitiesMessage = reportCameraCapabilitiesMessageFromJausMessage(jausMessage);
			if(reportCameraCapabilitiesMessage == NULL)
			{
				printf("reportCameraCapabilitiesMessageFromJausMessage failed\n");
			}
			else
			{
				reportCameraCapabilitiesMessageDestroy(reportCameraCapabilitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportSelectedCameraMessage:\n");
	reportSelectedCameraMessage = reportSelectedCameraMessageCreate();
	if(reportSelectedCameraMessage == NULL)
	{
		printf("reportSelectedCameraMessageCreate failed\n");
	}
	else
	{
		msgStr = reportSelectedCameraMessageToString(reportSelectedCameraMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportSelectedCameraMessageToJausMessage(reportSelectedCameraMessage);
		reportSelectedCameraMessageDestroy(reportSelectedCameraMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportSelectedCameraMessageToJausMessage failed\n");
		}
		else
		{
			reportSelectedCameraMessage = reportSelectedCameraMessageFromJausMessage(jausMessage);
			if(reportSelectedCameraMessage == NULL)
			{
				printf("reportSelectedCameraMessageFromJausMessage failed\n");
			}
			else
			{
				reportSelectedCameraMessageDestroy(reportSelectedCameraMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportCameraCountMessage:\n");
	reportCameraCountMessage = reportCameraCountMessageCreate();
	if(reportCameraCountMessage == NULL)
	{
		printf("reportCameraCountMessageCreate failed\n");
	}
	else
	{
		msgStr = reportCameraCountMessageToString(reportCameraCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportCameraCountMessageToJausMessage(reportCameraCountMessage);
		reportCameraCountMessageDestroy(reportCameraCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportCameraCountMessageToJausMessage failed\n");
		}
		else
		{
			reportCameraCountMessage = reportCameraCountMessageFromJausMessage(jausMessage);
			if(reportCameraCountMessage == NULL)
			{
				printf("reportCameraCountMessageFromJausMessage failed\n");
			}
			else
			{
				reportCameraCountMessageDestroy(reportCameraCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportCameraFormatOptionsMessage:\n");
	reportCameraFormatOptionsMessage = reportCameraFormatOptionsMessageCreate();
	if(reportCameraFormatOptionsMessage == NULL)
	{
		printf("reportCameraFormatOptionsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportCameraFormatOptionsMessageToString(reportCameraFormatOptionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportCameraFormatOptionsMessageToJausMessage(reportCameraFormatOptionsMessage);
		reportCameraFormatOptionsMessageDestroy(reportCameraFormatOptionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportCameraFormatOptionsMessageToJausMessage failed\n");
		}
		else
		{
			reportCameraFormatOptionsMessage = reportCameraFormatOptionsMessageFromJausMessage(jausMessage);
			if(reportCameraFormatOptionsMessage == NULL)
			{
				printf("reportCameraFormatOptionsMessageFromJausMessage failed\n");
			}
			else
			{
				reportCameraFormatOptionsMessageDestroy(reportCameraFormatOptionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportCameraPoseMessage:\n");
	reportCameraPoseMessage = reportCameraPoseMessageCreate();
	if(reportCameraPoseMessage == NULL)
	{
		printf("reportCameraPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = reportCameraPoseMessageToString(reportCameraPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportCameraPoseMessageToJausMessage(reportCameraPoseMessage);
		reportCameraPoseMessageDestroy(reportCameraPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportCameraPoseMessageToJausMessage failed\n");
		}
		else
		{
			reportCameraPoseMessage = reportCameraPoseMessageFromJausMessage(jausMessage);
			if(reportCameraPoseMessage == NULL)
			{
				printf("reportCameraPoseMessageFromJausMessage failed\n");
			}
			else
			{
				reportCameraPoseMessageDestroy(reportCameraPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportJointPositionsMessage:\n");
	reportJointPositionsMessage = reportJointPositionsMessageCreate();
	if(reportJointPositionsMessage == NULL)
	{
		printf("reportJointPositionsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportJointPositionsMessageToString(reportJointPositionsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportJointPositionsMessageToJausMessage(reportJointPositionsMessage);
		reportJointPositionsMessageDestroy(reportJointPositionsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportJointPositionsMessageToJausMessage failed\n");
		}
		else
		{
			reportJointPositionsMessage = reportJointPositionsMessageFromJausMessage(jausMessage);
			if(reportJointPositionsMessage == NULL)
			{
				printf("reportJointPositionsMessageFromJausMessage failed\n");
			}
			else
			{
				reportJointPositionsMessageDestroy(reportJointPositionsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportJointVelocitiesMessage:\n");
	reportJointVelocitiesMessage = reportJointVelocitiesMessageCreate();
	if(reportJointVelocitiesMessage == NULL)
	{
		printf("reportJointVelocitiesMessageCreate failed\n");
	}
	else
	{
		msgStr = reportJointVelocitiesMessageToString(reportJointVelocitiesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportJointVelocitiesMessageToJausMessage(reportJointVelocitiesMessage);
		reportJointVelocitiesMessageDestroy(reportJointVelocitiesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportJointVelocitiesMessageToJausMessage failed\n");
		}
		else
		{
			reportJointVelocitiesMessage = reportJointVelocitiesMessageFromJausMessage(jausMessage);
			if(reportJointVelocitiesMessage == NULL)
			{
				printf("reportJointVelocitiesMessageFromJausMessage failed\n");
			}
			else
			{
				reportJointVelocitiesMessageDestroy(reportJointVelocitiesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportManipulatorSpecificationsMessage:\n");
	reportManipulatorSpecificationsMessage = reportManipulatorSpecificationsMessageCreate();
	if(reportManipulatorSpecificationsMessage == NULL)
	{
		printf("reportManipulatorSpecificationsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportManipulatorSpecificationsMessageToString(reportManipulatorSpecificationsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportManipulatorSpecificationsMessageToJausMessage(reportManipulatorSpecificationsMessage);
		reportManipulatorSpecificationsMessageDestroy(reportManipulatorSpecificationsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportManipulatorSpecificationsMessageToJausMessage failed\n");
		}
		else
		{
			reportManipulatorSpecificationsMessage = reportManipulatorSpecificationsMessageFromJausMessage(jausMessage);
			if(reportManipulatorSpecificationsMessage == NULL)
			{
				printf("reportManipulatorSpecificationsMessageFromJausMessage failed\n");
			}
			else
			{
				reportManipulatorSpecificationsMessageDestroy(reportManipulatorSpecificationsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportJointEffortsMessage:\n");
	reportJointEffortsMessage = reportJointEffortsMessageCreate();
	if(reportJointEffortsMessage == NULL)
	{
		printf("reportJointEffortsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportJointEffortsMessageToString(reportJointEffortsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportJointEffortsMessageToJausMessage(reportJointEffortsMessage);
		reportJointEffortsMessageDestroy(reportJointEffortsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportJointEffortsMessageToJausMessage failed\n");
		}
		else
		{
			reportJointEffortsMessage = reportJointEffortsMessageFromJausMessage(jausMessage);
			if(reportJointEffortsMessage == NULL)
			{
				printf("reportJointEffortsMessageFromJausMessage failed\n");
			}
			else
			{
				reportJointEffortsMessageDestroy(reportJointEffortsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportToolPointMessage:\n");
	reportToolPointMessage = reportToolPointMessageCreate();
	if(reportToolPointMessage == NULL)
	{
		printf("reportToolPointMessageCreate failed\n");
	}
	else
	{
		msgStr = reportToolPointMessageToString(reportToolPointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportToolPointMessageToJausMessage(reportToolPointMessage);
		reportToolPointMessageDestroy(reportToolPointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportToolPointMessageToJausMessage failed\n");
		}
		else
		{
			reportToolPointMessage = reportToolPointMessageFromJausMessage(jausMessage);
			if(reportToolPointMessage == NULL)
			{
				printf("reportToolPointMessageFromJausMessage failed\n");
			}
			else
			{
				reportToolPointMessageDestroy(reportToolPointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportJointForceTorquesMessage:\n");
	reportJointForceTorquesMessage = reportJointForceTorquesMessageCreate();
	if(reportJointForceTorquesMessage == NULL)
	{
		printf("reportJointForceTorquesMessageCreate failed\n");
	}
	else
	{
		msgStr = reportJointForceTorquesMessageToString(reportJointForceTorquesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportJointForceTorquesMessageToJausMessage(reportJointForceTorquesMessage);
		reportJointForceTorquesMessageDestroy(reportJointForceTorquesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportJointForceTorquesMessageToJausMessage failed\n");
		}
		else
		{
			reportJointForceTorquesMessage = reportJointForceTorquesMessageFromJausMessage(jausMessage);
			if(reportJointForceTorquesMessage == NULL)
			{
				printf("reportJointForceTorquesMessageFromJausMessage failed\n");
			}
			else
			{
				reportJointForceTorquesMessageDestroy(reportJointForceTorquesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVksBoundsMessage:\n");
	reportVksBoundsMessage = reportVksBoundsMessageCreate();
	if(reportVksBoundsMessage == NULL)
	{
		printf("reportVksBoundsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVksBoundsMessageToString(reportVksBoundsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVksBoundsMessageToJausMessage(reportVksBoundsMessage);
		reportVksBoundsMessageDestroy(reportVksBoundsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVksBoundsMessageToJausMessage failed\n");
		}
		else
		{
			reportVksBoundsMessage = reportVksBoundsMessageFromJausMessage(jausMessage);
			if(reportVksBoundsMessage == NULL)
			{
				printf("reportVksBoundsMessageFromJausMessage failed\n");
			}
			else
			{
				reportVksBoundsMessageDestroy(reportVksBoundsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVksFeatureClassMetadataMessage:\n");
	reportVksFeatureClassMetadataMessage = reportVksFeatureClassMetadataMessageCreate();
	if(reportVksFeatureClassMetadataMessage == NULL)
	{
		printf("reportVksFeatureClassMetadataMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVksFeatureClassMetadataMessageToString(reportVksFeatureClassMetadataMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVksFeatureClassMetadataMessageToJausMessage(reportVksFeatureClassMetadataMessage);
		reportVksFeatureClassMetadataMessageDestroy(reportVksFeatureClassMetadataMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVksFeatureClassMetadataMessageToJausMessage failed\n");
		}
		else
		{
			reportVksFeatureClassMetadataMessage = reportVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
			if(reportVksFeatureClassMetadataMessage == NULL)
			{
				printf("reportVksFeatureClassMetadataMessageFromJausMessage failed\n");
			}
			else
			{
				reportVksFeatureClassMetadataMessageDestroy(reportVksFeatureClassMetadataMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVksDataTransferTerminationMessage:\n");
	reportVksDataTransferTerminationMessage = reportVksDataTransferTerminationMessageCreate();
	if(reportVksDataTransferTerminationMessage == NULL)
	{
		printf("reportVksDataTransferTerminationMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVksDataTransferTerminationMessageToString(reportVksDataTransferTerminationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVksDataTransferTerminationMessageToJausMessage(reportVksDataTransferTerminationMessage);
		reportVksDataTransferTerminationMessageDestroy(reportVksDataTransferTerminationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVksDataTransferTerminationMessageToJausMessage failed\n");
		}
		else
		{
			reportVksDataTransferTerminationMessage = reportVksDataTransferTerminationMessageFromJausMessage(jausMessage);
			if(reportVksDataTransferTerminationMessage == NULL)
			{
				printf("reportVksDataTransferTerminationMessageFromJausMessage failed\n");
			}
			else
			{
				reportVksDataTransferTerminationMessageDestroy(reportVksDataTransferTerminationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVksObjectsCreationMessage:\n");
	reportVksObjectsCreationMessage = reportVksObjectsCreationMessageCreate();
	if(reportVksObjectsCreationMessage == NULL)
	{
		printf("reportVksObjectsCreationMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVksObjectsCreationMessageToString(reportVksObjectsCreationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVksObjectsCreationMessageToJausMessage(reportVksObjectsCreationMessage);
		reportVksObjectsCreationMessageDestroy(reportVksObjectsCreationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVksObjectsCreationMessageToJausMessage failed\n");
		}
		else
		{
			reportVksObjectsCreationMessage = reportVksObjectsCreationMessageFromJausMessage(jausMessage);
			if(reportVksObjectsCreationMessage == NULL)
			{
				printf("reportVksObjectsCreationMessageFromJausMessage failed\n");
			}
			else
			{
				reportVksObjectsCreationMessageDestroy(reportVksObjectsCreationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVksObjectsMessage:\n");
	reportVksObjectsMessage = reportVksObjectsMessageCreate();
	if(reportVksObjectsMessage == NULL)
	{
		printf("reportVksObjectsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVksObjectsMessageToString(reportVksObjectsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVksObjectsMessageToJausMessage(reportVksObjectsMessage);
		reportVksObjectsMessageDestroy(reportVksObjectsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVksObjectsMessageToJausMessage failed\n");
		}
		else
		{
			reportVksObjectsMessage = reportVksObjectsMessageFromJausMessage(jausMessage);
			if(reportVksObjectsMessage == NULL)
			{
				printf("reportVksObjectsMessageFromJausMessage failed\n");
			}
			else
			{
				reportVksObjectsMessageDestroy(reportVksObjectsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportServicesMessage:\n");
	reportServicesMessage = reportServicesMessageCreate();
	if(reportServicesMessage == NULL)
	{
		printf("reportServicesMessageCreate failed\n");
	}
	else
	{
		msgStr = reportServicesMessageToString(reportServicesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportServicesMessageToJausMessage(reportServicesMessage);
		reportServicesMessageDestroy(reportServicesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportServicesMessageToJausMessage failed\n");
		}
		else
		{
			reportServicesMessage = reportServicesMessageFromJausMessage(jausMessage);
			if(reportServicesMessage == NULL)
			{
				printf("reportServicesMessageFromJausMessage failed\n");
			}
			else
			{
				reportServicesMessageDestroy(reportServicesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportIdentificationMessage:\n");
	reportIdentificationMessage = reportIdentificationMessageCreate();
	if(reportIdentificationMessage == NULL)
	{
		printf("reportIdentificationMessageCreate failed\n");
	}
	else
	{
		msgStr = reportIdentificationMessageToString(reportIdentificationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportIdentificationMessageToJausMessage(reportIdentificationMessage);
		reportIdentificationMessageDestroy(reportIdentificationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportIdentificationMessageToJausMessage failed\n");
		}
		else
		{
			reportIdentificationMessage = reportIdentificationMessageFromJausMessage(jausMessage);
			if(reportIdentificationMessage == NULL)
			{
				printf("reportIdentificationMessageFromJausMessage failed\n");
			}
			else
			{
				reportIdentificationMessageDestroy(reportIdentificationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportConfigurationMessage:\n");
	reportConfigurationMessage = reportConfigurationMessageCreate();
	if(reportConfigurationMessage == NULL)
	{
		printf("reportConfigurationMessageCreate failed\n");
	}
	else
	{
		msgStr = reportConfigurationMessageToString(reportConfigurationMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportConfigurationMessageToJausMessage(reportConfigurationMessage);
		reportConfigurationMessageDestroy(reportConfigurationMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportConfigurationMessageToJausMessage failed\n");
		}
		else
		{
			reportConfigurationMessage = reportConfigurationMessageFromJausMessage(jausMessage);
			if(reportConfigurationMessage == NULL)
			{
				printf("reportConfigurationMessageFromJausMessage failed\n");
			}
			else
			{
				reportConfigurationMessageDestroy(reportConfigurationMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportSubsystemListMessage:\n");
	reportSubsystemListMessage = reportSubsystemListMessageCreate();
	if(reportSubsystemListMessage == NULL)
	{
		printf("reportSubsystemListMessageCreate failed\n");
	}
	else
	{
		msgStr = reportSubsystemListMessageToString(reportSubsystemListMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportSubsystemListMessageToJausMessage(reportSubsystemListMessage);
		reportSubsystemListMessageDestroy(reportSubsystemListMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportSubsystemListMessageToJausMessage failed\n");
		}
		else
		{
			reportSubsystemListMessage = reportSubsystemListMessageFromJausMessage(jausMessage);
			if(reportSubsystemListMessage == NULL)
			{
				printf("reportSubsystemListMessageFromJausMessage failed\n");
			}
			else
			{
				reportSubsystemListMessageDestroy(reportSubsystemListMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportMissionStatusMessage:\n");
	reportMissionStatusMessage = reportMissionStatusMessageCreate();
	if(reportMissionStatusMessage == NULL)
	{
		printf("reportMissionStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = reportMissionStatusMessageToString(reportMissionStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportMissionStatusMessageToJausMessage(reportMissionStatusMessage);
		reportMissionStatusMessageDestroy(reportMissionStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportMissionStatusMessageToJausMessage failed\n");
		}
		else
		{
			reportMissionStatusMessage = reportMissionStatusMessageFromJausMessage(jausMessage);
			if(reportMissionStatusMessage == NULL)
			{
				printf("reportMissionStatusMessageFromJausMessage failed\n");
			}
			else
			{
				reportMissionStatusMessageDestroy(reportMissionStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportSpoolingPreferenceMessage:\n");
	reportSpoolingPreferenceMessage = reportSpoolingPreferenceMessageCreate();
	if(reportSpoolingPreferenceMessage == NULL)
	{
		printf("reportSpoolingPreferenceMessageCreate failed\n");
	}
	else
	{
		msgStr = reportSpoolingPreferenceMessageToString(reportSpoolingPreferenceMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportSpoolingPreferenceMessageToJausMessage(reportSpoolingPreferenceMessage);
		reportSpoolingPreferenceMessageDestroy(reportSpoolingPreferenceMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportSpoolingPreferenceMessageToJausMessage failed\n");
		}
		else
		{
			reportSpoolingPreferenceMessage = reportSpoolingPreferenceMessageFromJausMessage(jausMessage);
			if(reportSpoolingPreferenceMessage == NULL)
			{
				printf("reportSpoolingPreferenceMessageFromJausMessage failed\n");
			}
			else
			{
				reportSpoolingPreferenceMessageDestroy(reportSpoolingPreferenceMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportTimeMessage:\n");
	reportTimeMessage = reportTimeMessageCreate();
	if(reportTimeMessage == NULL)
	{
		printf("reportTimeMessageCreate failed\n");
	}
	else
	{
		msgStr = reportTimeMessageToString(reportTimeMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportTimeMessageToJausMessage(reportTimeMessage);
		reportTimeMessageDestroy(reportTimeMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportTimeMessageToJausMessage failed\n");
		}
		else
		{
			reportTimeMessage = reportTimeMessageFromJausMessage(jausMessage);
			if(reportTimeMessage == NULL)
			{
				printf("reportTimeMessageFromJausMessage failed\n");
			}
			else
			{
				reportTimeMessageDestroy(reportTimeMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportComponentAuthorityMessage:\n");
	reportComponentAuthorityMessage = reportComponentAuthorityMessageCreate();
	if(reportComponentAuthorityMessage == NULL)
	{
		printf("reportComponentAuthorityMessageCreate failed\n");
	}
	else
	{
		msgStr = reportComponentAuthorityMessageToString(reportComponentAuthorityMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportComponentAuthorityMessageToJausMessage(reportComponentAuthorityMessage);
		reportComponentAuthorityMessageDestroy(reportComponentAuthorityMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportComponentAuthorityMessageToJausMessage failed\n");
		}
		else
		{
			reportComponentAuthorityMessage = reportComponentAuthorityMessageFromJausMessage(jausMessage);
			if(reportComponentAuthorityMessage == NULL)
			{
				printf("reportComponentAuthorityMessageFromJausMessage failed\n");
			}
			else
			{
				reportComponentAuthorityMessageDestroy(reportComponentAuthorityMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportComponentStatusMessage:\n");
	reportComponentStatusMessage = reportComponentStatusMessageCreate();
	if(reportComponentStatusMessage == NULL)
	{
		printf("reportComponentStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = reportComponentStatusMessageToString(reportComponentStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportComponentStatusMessageToJausMessage(reportComponentStatusMessage);
		reportComponentStatusMessageDestroy(reportComponentStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportComponentStatusMessageToJausMessage failed\n");
		}
		else
		{
			reportComponentStatusMessage = reportComponentStatusMessageFromJausMessage(jausMessage);
			if(reportComponentStatusMessage == NULL)
			{
				printf("reportComponentStatusMessageFromJausMessage failed\n");
			}
			else
			{
				reportComponentStatusMessageDestroy(reportComponentStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportComponentControlMessage:\n");
	reportComponentControlMessage = reportComponentControlMessageCreate();
	if(reportComponentControlMessage == NULL)
	{
		printf("reportComponentControlMessageCreate failed\n");
	}
	else
	{
		msgStr = reportComponentControlMessageToString(reportComponentControlMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportComponentControlMessageToJausMessage(reportComponentControlMessage);
		reportComponentControlMessageDestroy(reportComponentControlMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportComponentControlMessageToJausMessage failed\n");
		}
		else
		{
			reportComponentControlMessage = reportComponentControlMessageFromJausMessage(jausMessage);
			if(reportComponentControlMessage == NULL)
			{
				printf("reportComponentControlMessageFromJausMessage failed\n");
			}
			else
			{
				reportComponentControlMessageDestroy(reportComponentControlMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportEventsMessage:\n");
	reportEventsMessage = reportEventsMessageCreate();
	if(reportEventsMessage == NULL)
	{
		printf("reportEventsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportEventsMessageToString(reportEventsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportEventsMessageToJausMessage(reportEventsMessage);
		reportEventsMessageDestroy(reportEventsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportEventsMessageToJausMessage failed\n");
		}
		else
		{
			reportEventsMessage = reportEventsMessageFromJausMessage(jausMessage);
			if(reportEventsMessage == NULL)
			{
				printf("reportEventsMessageFromJausMessage failed\n");
			}
			else
			{
				reportEventsMessageDestroy(reportEventsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing eventMessage:\n");
	eventMessage = eventMessageCreate();
	if(eventMessage == NULL)
	{
		printf("eventMessageCreate failed\n");
	}
	else
	{
		msgStr = eventMessageToString(eventMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = eventMessageToJausMessage(eventMessage);
		eventMessageDestroy(eventMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("eventMessageToJausMessage failed\n");
		}
		else
		{
			eventMessage = eventMessageFromJausMessage(jausMessage);
			if(eventMessage == NULL)
			{
				printf("eventMessageFromJausMessage failed\n");
			}
			else
			{
				eventMessageDestroy(eventMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportDataLinkStatusMessage:\n");
	reportDataLinkStatusMessage = reportDataLinkStatusMessageCreate();
	if(reportDataLinkStatusMessage == NULL)
	{
		printf("reportDataLinkStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = reportDataLinkStatusMessageToString(reportDataLinkStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportDataLinkStatusMessageToJausMessage(reportDataLinkStatusMessage);
		reportDataLinkStatusMessageDestroy(reportDataLinkStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportDataLinkStatusMessageToJausMessage failed\n");
		}
		else
		{
			reportDataLinkStatusMessage = reportDataLinkStatusMessageFromJausMessage(jausMessage);
			if(reportDataLinkStatusMessage == NULL)
			{
				printf("reportDataLinkStatusMessageFromJausMessage failed\n");
			}
			else
			{
				reportDataLinkStatusMessageDestroy(reportDataLinkStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportHeartbeatPulseMessage:\n");
	reportHeartbeatPulseMessage = reportHeartbeatPulseMessageCreate();
	if(reportHeartbeatPulseMessage == NULL)
	{
		printf("reportHeartbeatPulseMessageCreate failed\n");
	}
	else
	{
		msgStr = reportHeartbeatPulseMessageToString(reportHeartbeatPulseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportHeartbeatPulseMessageToJausMessage(reportHeartbeatPulseMessage);
		reportHeartbeatPulseMessageDestroy(reportHeartbeatPulseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportHeartbeatPulseMessageToJausMessage failed\n");
		}
		else
		{
			reportHeartbeatPulseMessage = reportHeartbeatPulseMessageFromJausMessage(jausMessage);
			if(reportHeartbeatPulseMessage == NULL)
			{
				printf("reportHeartbeatPulseMessageFromJausMessage failed\n");
			}
			else
			{
				reportHeartbeatPulseMessageDestroy(reportHeartbeatPulseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportSelectedDataLinkStatusMessage:\n");
	reportSelectedDataLinkStatusMessage = reportSelectedDataLinkStatusMessageCreate();
	if(reportSelectedDataLinkStatusMessage == NULL)
	{
		printf("reportSelectedDataLinkStatusMessageCreate failed\n");
	}
	else
	{
		msgStr = reportSelectedDataLinkStatusMessageToString(reportSelectedDataLinkStatusMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportSelectedDataLinkStatusMessageToJausMessage(reportSelectedDataLinkStatusMessage);
		reportSelectedDataLinkStatusMessageDestroy(reportSelectedDataLinkStatusMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportSelectedDataLinkStatusMessageToJausMessage failed\n");
		}
		else
		{
			reportSelectedDataLinkStatusMessage = reportSelectedDataLinkStatusMessageFromJausMessage(jausMessage);
			if(reportSelectedDataLinkStatusMessage == NULL)
			{
				printf("reportSelectedDataLinkStatusMessageFromJausMessage failed\n");
			}
			else
			{
				reportSelectedDataLinkStatusMessageDestroy(reportSelectedDataLinkStatusMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportVelocityStateMessage:\n");
	reportVelocityStateMessage = reportVelocityStateMessageCreate();
	if(reportVelocityStateMessage == NULL)
	{
		printf("reportVelocityStateMessageCreate failed\n");
	}
	else
	{
		msgStr = reportVelocityStateMessageToString(reportVelocityStateMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportVelocityStateMessageToJausMessage(reportVelocityStateMessage);
		reportVelocityStateMessageDestroy(reportVelocityStateMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportVelocityStateMessageToJausMessage failed\n");
		}
		else
		{
			reportVelocityStateMessage = reportVelocityStateMessageFromJausMessage(jausMessage);
			if(reportVelocityStateMessage == NULL)
			{
				printf("reportVelocityStateMessageFromJausMessage failed\n");
			}
			else
			{
				reportVelocityStateMessageDestroy(reportVelocityStateMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportPlatformSpecificationsMessage:\n");
	reportPlatformSpecificationsMessage = reportPlatformSpecificationsMessageCreate();
	if(reportPlatformSpecificationsMessage == NULL)
	{
		printf("reportPlatformSpecificationsMessageCreate failed\n");
	}
	else
	{
		msgStr = reportPlatformSpecificationsMessageToString(reportPlatformSpecificationsMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportPlatformSpecificationsMessageToJausMessage(reportPlatformSpecificationsMessage);
		reportPlatformSpecificationsMessageDestroy(reportPlatformSpecificationsMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportPlatformSpecificationsMessageToJausMessage failed\n");
		}
		else
		{
			reportPlatformSpecificationsMessage = reportPlatformSpecificationsMessageFromJausMessage(jausMessage);
			if(reportPlatformSpecificationsMessage == NULL)
			{
				printf("reportPlatformSpecificationsMessageFromJausMessage failed\n");
			}
			else
			{
				reportPlatformSpecificationsMessageDestroy(reportPlatformSpecificationsMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportWrenchEffortMessage:\n");
	reportWrenchEffortMessage = reportWrenchEffortMessageCreate();
	if(reportWrenchEffortMessage == NULL)
	{
		printf("reportWrenchEffortMessageCreate failed\n");
	}
	else
	{
		msgStr = reportWrenchEffortMessageToString(reportWrenchEffortMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportWrenchEffortMessageToJausMessage(reportWrenchEffortMessage);
		reportWrenchEffortMessageDestroy(reportWrenchEffortMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportWrenchEffortMessageToJausMessage failed\n");
		}
		else
		{
			reportWrenchEffortMessage = reportWrenchEffortMessageFromJausMessage(jausMessage);
			if(reportWrenchEffortMessage == NULL)
			{
				printf("reportWrenchEffortMessageFromJausMessage failed\n");
			}
			else
			{
				reportWrenchEffortMessageDestroy(reportWrenchEffortMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportLocalPathSegmentMessage:\n");
	reportLocalPathSegmentMessage = reportLocalPathSegmentMessageCreate();
	if(reportLocalPathSegmentMessage == NULL)
	{
		printf("reportLocalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = reportLocalPathSegmentMessageToString(reportLocalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportLocalPathSegmentMessageToJausMessage(reportLocalPathSegmentMessage);
		reportLocalPathSegmentMessageDestroy(reportLocalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportLocalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			reportLocalPathSegmentMessage = reportLocalPathSegmentMessageFromJausMessage(jausMessage);
			if(reportLocalPathSegmentMessage == NULL)
			{
				printf("reportLocalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				reportLocalPathSegmentMessageDestroy(reportLocalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportWaypointCountMessage:\n");
	reportWaypointCountMessage = reportWaypointCountMessageCreate();
	if(reportWaypointCountMessage == NULL)
	{
		printf("reportWaypointCountMessageCreate failed\n");
	}
	else
	{
		msgStr = reportWaypointCountMessageToString(reportWaypointCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportWaypointCountMessageToJausMessage(reportWaypointCountMessage);
		reportWaypointCountMessageDestroy(reportWaypointCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportWaypointCountMessageToJausMessage failed\n");
		}
		else
		{
			reportWaypointCountMessage = reportWaypointCountMessageFromJausMessage(jausMessage);
			if(reportWaypointCountMessage == NULL)
			{
				printf("reportWaypointCountMessageFromJausMessage failed\n");
			}
			else
			{
				reportWaypointCountMessageDestroy(reportWaypointCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportLocalPoseMessage:\n");
	reportLocalPoseMessage = reportLocalPoseMessageCreate();
	if(reportLocalPoseMessage == NULL)
	{
		printf("reportLocalPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = reportLocalPoseMessageToString(reportLocalPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportLocalPoseMessageToJausMessage(reportLocalPoseMessage);
		reportLocalPoseMessageDestroy(reportLocalPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportLocalPoseMessageToJausMessage failed\n");
		}
		else
		{
			reportLocalPoseMessage = reportLocalPoseMessageFromJausMessage(jausMessage);
			if(reportLocalPoseMessage == NULL)
			{
				printf("reportLocalPoseMessageFromJausMessage failed\n");
			}
			else
			{
				reportLocalPoseMessageDestroy(reportLocalPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportLocalWaypointMessage:\n");
	reportLocalWaypointMessage = reportLocalWaypointMessageCreate();
	if(reportLocalWaypointMessage == NULL)
	{
		printf("reportLocalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = reportLocalWaypointMessageToString(reportLocalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportLocalWaypointMessageToJausMessage(reportLocalWaypointMessage);
		reportLocalWaypointMessageDestroy(reportLocalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportLocalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			reportLocalWaypointMessage = reportLocalWaypointMessageFromJausMessage(jausMessage);
			if(reportLocalWaypointMessage == NULL)
			{
				printf("reportLocalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				reportLocalWaypointMessageDestroy(reportLocalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportPathSegmentCountMessage:\n");
	reportPathSegmentCountMessage = reportPathSegmentCountMessageCreate();
	if(reportPathSegmentCountMessage == NULL)
	{
		printf("reportPathSegmentCountMessageCreate failed\n");
	}
	else
	{
		msgStr = reportPathSegmentCountMessageToString(reportPathSegmentCountMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportPathSegmentCountMessageToJausMessage(reportPathSegmentCountMessage);
		reportPathSegmentCountMessageDestroy(reportPathSegmentCountMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportPathSegmentCountMessageToJausMessage failed\n");
		}
		else
		{
			reportPathSegmentCountMessage = reportPathSegmentCountMessageFromJausMessage(jausMessage);
			if(reportPathSegmentCountMessage == NULL)
			{
				printf("reportPathSegmentCountMessageFromJausMessage failed\n");
			}
			else
			{
				reportPathSegmentCountMessageDestroy(reportPathSegmentCountMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportPlatformOperationalDataMessage:\n");
	reportPlatformOperationalDataMessage = reportPlatformOperationalDataMessageCreate();
	if(reportPlatformOperationalDataMessage == NULL)
	{
		printf("reportPlatformOperationalDataMessageCreate failed\n");
	}
	else
	{
		msgStr = reportPlatformOperationalDataMessageToString(reportPlatformOperationalDataMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportPlatformOperationalDataMessageToJausMessage(reportPlatformOperationalDataMessage);
		reportPlatformOperationalDataMessageDestroy(reportPlatformOperationalDataMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportPlatformOperationalDataMessageToJausMessage failed\n");
		}
		else
		{
			reportPlatformOperationalDataMessage = reportPlatformOperationalDataMessageFromJausMessage(jausMessage);
			if(reportPlatformOperationalDataMessage == NULL)
			{
				printf("reportPlatformOperationalDataMessageFromJausMessage failed\n");
			}
			else
			{
				reportPlatformOperationalDataMessageDestroy(reportPlatformOperationalDataMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportGlobalPoseMessage:\n");
	reportGlobalPoseMessage = reportGlobalPoseMessageCreate();
	if(reportGlobalPoseMessage == NULL)
	{
		printf("reportGlobalPoseMessageCreate failed\n");
	}
	else
	{
		msgStr = reportGlobalPoseMessageToString(reportGlobalPoseMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportGlobalPoseMessageToJausMessage(reportGlobalPoseMessage);
		reportGlobalPoseMessageDestroy(reportGlobalPoseMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportGlobalPoseMessageToJausMessage failed\n");
		}
		else
		{
			reportGlobalPoseMessage = reportGlobalPoseMessageFromJausMessage(jausMessage);
			if(reportGlobalPoseMessage == NULL)
			{
				printf("reportGlobalPoseMessageFromJausMessage failed\n");
			}
			else
			{
				reportGlobalPoseMessageDestroy(reportGlobalPoseMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportLocalVectorMessage:\n");
	reportLocalVectorMessage = reportLocalVectorMessageCreate();
	if(reportLocalVectorMessage == NULL)
	{
		printf("reportLocalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = reportLocalVectorMessageToString(reportLocalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportLocalVectorMessageToJausMessage(reportLocalVectorMessage);
		reportLocalVectorMessageDestroy(reportLocalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportLocalVectorMessageToJausMessage failed\n");
		}
		else
		{
			reportLocalVectorMessage = reportLocalVectorMessageFromJausMessage(jausMessage);
			if(reportLocalVectorMessage == NULL)
			{
				printf("reportLocalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				reportLocalVectorMessageDestroy(reportLocalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportDiscreteDevicesMessage:\n");
	reportDiscreteDevicesMessage = reportDiscreteDevicesMessageCreate();
	if(reportDiscreteDevicesMessage == NULL)
	{
		printf("reportDiscreteDevicesMessageCreate failed\n");
	}
	else
	{
		msgStr = reportDiscreteDevicesMessageToString(reportDiscreteDevicesMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportDiscreteDevicesMessageToJausMessage(reportDiscreteDevicesMessage);
		reportDiscreteDevicesMessageDestroy(reportDiscreteDevicesMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportDiscreteDevicesMessageToJausMessage failed\n");
		}
		else
		{
			reportDiscreteDevicesMessage = reportDiscreteDevicesMessageFromJausMessage(jausMessage);
			if(reportDiscreteDevicesMessage == NULL)
			{
				printf("reportDiscreteDevicesMessageFromJausMessage failed\n");
			}
			else
			{
				reportDiscreteDevicesMessageDestroy(reportDiscreteDevicesMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportGlobalPathSegmentMessage:\n");
	reportGlobalPathSegmentMessage = reportGlobalPathSegmentMessageCreate();
	if(reportGlobalPathSegmentMessage == NULL)
	{
		printf("reportGlobalPathSegmentMessageCreate failed\n");
	}
	else
	{
		msgStr = reportGlobalPathSegmentMessageToString(reportGlobalPathSegmentMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportGlobalPathSegmentMessageToJausMessage(reportGlobalPathSegmentMessage);
		reportGlobalPathSegmentMessageDestroy(reportGlobalPathSegmentMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportGlobalPathSegmentMessageToJausMessage failed\n");
		}
		else
		{
			reportGlobalPathSegmentMessage = reportGlobalPathSegmentMessageFromJausMessage(jausMessage);
			if(reportGlobalPathSegmentMessage == NULL)
			{
				printf("reportGlobalPathSegmentMessageFromJausMessage failed\n");
			}
			else
			{
				reportGlobalPathSegmentMessageDestroy(reportGlobalPathSegmentMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportTravelSpeedMessage:\n");
	reportTravelSpeedMessage = reportTravelSpeedMessageCreate();
	if(reportTravelSpeedMessage == NULL)
	{
		printf("reportTravelSpeedMessageCreate failed\n");
	}
	else
	{
		msgStr = reportTravelSpeedMessageToString(reportTravelSpeedMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportTravelSpeedMessageToJausMessage(reportTravelSpeedMessage);
		reportTravelSpeedMessageDestroy(reportTravelSpeedMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportTravelSpeedMessageToJausMessage failed\n");
		}
		else
		{
			reportTravelSpeedMessage = reportTravelSpeedMessageFromJausMessage(jausMessage);
			if(reportTravelSpeedMessage == NULL)
			{
				printf("reportTravelSpeedMessageFromJausMessage failed\n");
			}
			else
			{
				reportTravelSpeedMessageDestroy(reportTravelSpeedMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportGlobalWaypointMessage:\n");
	reportGlobalWaypointMessage = reportGlobalWaypointMessageCreate();
	if(reportGlobalWaypointMessage == NULL)
	{
		printf("reportGlobalWaypointMessageCreate failed\n");
	}
	else
	{
		msgStr = reportGlobalWaypointMessageToString(reportGlobalWaypointMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportGlobalWaypointMessageToJausMessage(reportGlobalWaypointMessage);
		reportGlobalWaypointMessageDestroy(reportGlobalWaypointMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportGlobalWaypointMessageToJausMessage failed\n");
		}
		else
		{
			reportGlobalWaypointMessage = reportGlobalWaypointMessageFromJausMessage(jausMessage);
			if(reportGlobalWaypointMessage == NULL)
			{
				printf("reportGlobalWaypointMessageFromJausMessage failed\n");
			}
			else
			{
				reportGlobalWaypointMessageDestroy(reportGlobalWaypointMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	printf("Testing reportGlobalVectorMessage:\n");
	reportGlobalVectorMessage = reportGlobalVectorMessageCreate();
	if(reportGlobalVectorMessage == NULL)
	{
		printf("reportGlobalVectorMessageCreate failed\n");
	}
	else
	{
		msgStr = reportGlobalVectorMessageToString(reportGlobalVectorMessage);
		printf("%s\n", msgStr);
		free(msgStr);
		jausMessage = reportGlobalVectorMessageToJausMessage(reportGlobalVectorMessage);
		reportGlobalVectorMessageDestroy(reportGlobalVectorMessage);
		if(jausMessage->dataSize == 0)
		{
			printf("reportGlobalVectorMessageToJausMessage failed\n");
		}
		else
		{
			reportGlobalVectorMessage = reportGlobalVectorMessageFromJausMessage(jausMessage);
			if(reportGlobalVectorMessage == NULL)
			{
				printf("reportGlobalVectorMessageFromJausMessage failed\n");
			}
			else
			{
				reportGlobalVectorMessageDestroy(reportGlobalVectorMessage);
			}
		}
		jausMessageDestroy(jausMessage);
	}
	printf("\n");

	return 0;
}
