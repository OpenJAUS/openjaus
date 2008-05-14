#include <stdio.h>
#include <stdlib.h>
#include <jaus.h>

int main(void)
{
	JausMessage jausMessage;
	ActivateServiceConnectionMessage activateServiceConnectionMessage1;
	ActivateServiceConnectionMessage activateServiceConnectionMessage2;
	CancelEventMessage cancelEventMessage1;
	CancelEventMessage cancelEventMessage2;
	ClearEmergencyMessage clearEmergencyMessage1;
	ClearEmergencyMessage clearEmergencyMessage2;
	ConfirmComponentControlMessage confirmComponentControlMessage1;
	ConfirmComponentControlMessage confirmComponentControlMessage2;
	ConfirmEventRequestMessage confirmEventRequestMessage1;
	ConfirmEventRequestMessage confirmEventRequestMessage2;
	ConfirmServiceConnectionMessage confirmServiceConnectionMessage1;
	ConfirmServiceConnectionMessage confirmServiceConnectionMessage2;
	CreateEventMessage createEventMessage1;
	CreateEventMessage createEventMessage2;
	CreateServiceConnectionMessage createServiceConnectionMessage1;
	CreateServiceConnectionMessage createServiceConnectionMessage2;
	CreateVksObjectsMessage createVksObjectsMessage1;
	CreateVksObjectsMessage createVksObjectsMessage2;
	DeleteVksObjectsMessage deleteVksObjectsMessage1;
	DeleteVksObjectsMessage deleteVksObjectsMessage2;
	EventMessage eventMessage1;
	EventMessage eventMessage2;
	QueryCameraCapabilitiesMessage queryCameraCapabilitiesMessage1;
	QueryCameraCapabilitiesMessage queryCameraCapabilitiesMessage2;
	QueryCameraCountMessage queryCameraCountMessage1;
	QueryCameraCountMessage queryCameraCountMessage2;
	QueryCameraFormatOptionsMessage queryCameraFormatOptionsMessage1;
	QueryCameraFormatOptionsMessage queryCameraFormatOptionsMessage2;
	QueryCameraPoseMessage queryCameraPoseMessage1;
	QueryCameraPoseMessage queryCameraPoseMessage2;
	QueryComponentAuthorityMessage queryComponentAuthorityMessage1;
	QueryComponentAuthorityMessage queryComponentAuthorityMessage2;
	QueryComponentControlMessage queryComponentControlMessage1;
	QueryComponentControlMessage queryComponentControlMessage2;
	QueryComponentStatusMessage queryComponentStatusMessage1;
	QueryComponentStatusMessage queryComponentStatusMessage2;
	QueryConfigurationMessage queryConfigurationMessage1;
	QueryConfigurationMessage queryConfigurationMessage2;
	QueryDataLinkStatusMessage queryDataLinkStatusMessage1;
	QueryDataLinkStatusMessage queryDataLinkStatusMessage2;
	QueryDiscreteDevicesMessage queryDiscreteDevicesMessage1;
	QueryDiscreteDevicesMessage queryDiscreteDevicesMessage2;
	QueryEventsMessage queryEventsMessage1;
	QueryEventsMessage queryEventsMessage2;
	QueryGlobalPathSegmentMessage queryGlobalPathSegmentMessage1;
	QueryGlobalPathSegmentMessage queryGlobalPathSegmentMessage2;
	QueryGlobalPoseMessage queryGlobalPoseMessage1;
	QueryGlobalPoseMessage queryGlobalPoseMessage2;
	QueryGlobalVectorMessage queryGlobalVectorMessage1;
	QueryGlobalVectorMessage queryGlobalVectorMessage2;
	QueryGlobalWaypointMessage queryGlobalWaypointMessage1;
	QueryGlobalWaypointMessage queryGlobalWaypointMessage2;
	QueryHeartbeatPulseMessage queryHeartbeatPulseMessage1;
	QueryHeartbeatPulseMessage queryHeartbeatPulseMessage2;
	QueryIdentificationMessage queryIdentificationMessage1;
	QueryIdentificationMessage queryIdentificationMessage2;
	QueryImageMessage queryImageMessage1;
	QueryImageMessage queryImageMessage2;
	QueryJointEffortsMessage queryJointEffortsMessage1;
	QueryJointEffortsMessage queryJointEffortsMessage2;
	QueryJointForceTorquesMessage queryJointForceTorquesMessage1;
	QueryJointForceTorquesMessage queryJointForceTorquesMessage2;
	QueryJointPositionsMessage queryJointPositionsMessage1;
	QueryJointPositionsMessage queryJointPositionsMessage2;
	QueryJointVelocitiesMessage queryJointVelocitiesMessage1;
	QueryJointVelocitiesMessage queryJointVelocitiesMessage2;
	QueryLocalPathSegmentMessage queryLocalPathSegmentMessage1;
	QueryLocalPathSegmentMessage queryLocalPathSegmentMessage2;
	QueryLocalPoseMessage queryLocalPoseMessage1;
	QueryLocalPoseMessage queryLocalPoseMessage2;
	QueryLocalVectorMessage queryLocalVectorMessage1;
	QueryLocalVectorMessage queryLocalVectorMessage2;
	QueryLocalWaypointMessage queryLocalWaypointMessage1;
	QueryLocalWaypointMessage queryLocalWaypointMessage2;
	QueryManipulatorSpecificationsMessage queryManipulatorSpecificationsMessage1;
	QueryManipulatorSpecificationsMessage queryManipulatorSpecificationsMessage2;
	QueryPathSegmentCountMessage queryPathSegmentCountMessage1;
	QueryPathSegmentCountMessage queryPathSegmentCountMessage2;
	QueryPayloadDataElementMessage queryPayloadDataElementMessage1;
	QueryPayloadDataElementMessage queryPayloadDataElementMessage2;
	QueryPayloadInterfaceMessage queryPayloadInterfaceMessage1;
	QueryPayloadInterfaceMessage queryPayloadInterfaceMessage2;
	QueryPlatformOperationalDataMessage queryPlatformOperationalDataMessage1;
	QueryPlatformOperationalDataMessage queryPlatformOperationalDataMessage2;
	QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessage1;
	QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessage2;
	QueryRelativeObjectPositionMessage queryRelativeObjectPositionMessage1;
	QueryRelativeObjectPositionMessage queryRelativeObjectPositionMessage2;
	QuerySelectedCameraMessage querySelectedCameraMessage1;
	QuerySelectedCameraMessage querySelectedCameraMessage2;
	QuerySelectedDataLinkStatusMessage querySelectedDataLinkStatusMessage1;
	QuerySelectedDataLinkStatusMessage querySelectedDataLinkStatusMessage2;
	QueryServicesMessage queryServicesMessage1;
	QueryServicesMessage queryServicesMessage2;
	QuerySubsystemListMessage querySubsystemListMessage1;
	QuerySubsystemListMessage querySubsystemListMessage2;
	QueryTimeMessage queryTimeMessage1;
	QueryTimeMessage queryTimeMessage2;
	QueryToolPointMessage queryToolPointMessage1;
	QueryToolPointMessage queryToolPointMessage2;
	QueryTravelSpeedMessage queryTravelSpeedMessage1;
	QueryTravelSpeedMessage queryTravelSpeedMessage2;
	QueryVelocityStateMessage queryVelocityStateMessage1;
	QueryVelocityStateMessage queryVelocityStateMessage2;
	QueryVksBoundsMessage queryVksBoundsMessage1;
	QueryVksBoundsMessage queryVksBoundsMessage2;
	QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessage1;
	QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessage2;
	QueryVksObjectsMessage queryVksObjectsMessage1;
	QueryVksObjectsMessage queryVksObjectsMessage2;
	QueryWaypointCountMessage queryWaypointCountMessage1;
	QueryWaypointCountMessage queryWaypointCountMessage2;
	QueryWrenchEffortMessage queryWrenchEffortMessage1;
	QueryWrenchEffortMessage queryWrenchEffortMessage2;
	RejectComponentControlMessage rejectComponentControlMessage1;
	RejectComponentControlMessage rejectComponentControlMessage2;
	RejectEventRequestMessage rejectEventRequestMessage1;
	RejectEventRequestMessage rejectEventRequestMessage2;
	ReleaseComponentControlMessage releaseComponentControlMessage1;
	ReleaseComponentControlMessage releaseComponentControlMessage2;
	ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessage1;
	ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessage2;
	ReportCameraCountMessage reportCameraCountMessage1;
	ReportCameraCountMessage reportCameraCountMessage2;
	ReportCameraFormatOptionsMessage reportCameraFormatOptionsMessage1;
	ReportCameraFormatOptionsMessage reportCameraFormatOptionsMessage2;
	ReportCameraPoseMessage reportCameraPoseMessage1;
	ReportCameraPoseMessage reportCameraPoseMessage2;
	ReportComponentAuthorityMessage reportComponentAuthorityMessage1;
	ReportComponentAuthorityMessage reportComponentAuthorityMessage2;
	ReportComponentControlMessage reportComponentControlMessage1;
	ReportComponentControlMessage reportComponentControlMessage2;
	ReportComponentStatusMessage reportComponentStatusMessage1;
	ReportComponentStatusMessage reportComponentStatusMessage2;
	ReportConfigurationMessage reportConfigurationMessage1;
	ReportConfigurationMessage reportConfigurationMessage2;
	ReportDataLinkStatusMessage reportDataLinkStatusMessage1;
	ReportDataLinkStatusMessage reportDataLinkStatusMessage2;
	ReportDiscreteDevicesMessage reportDiscreteDevicesMessage1;
	ReportDiscreteDevicesMessage reportDiscreteDevicesMessage2;
	ReportEventsMessage reportEventsMessage1;
	ReportEventsMessage reportEventsMessage2;
	ReportGlobalPathSegmentMessage reportGlobalPathSegmentMessage1;
	ReportGlobalPathSegmentMessage reportGlobalPathSegmentMessage2;
	ReportGlobalPoseMessage reportGlobalPoseMessage1;
	ReportGlobalPoseMessage reportGlobalPoseMessage2;
	ReportGlobalVectorMessage reportGlobalVectorMessage1;
	ReportGlobalVectorMessage reportGlobalVectorMessage2;
	ReportGlobalWaypointMessage reportGlobalWaypointMessage1;
	ReportGlobalWaypointMessage reportGlobalWaypointMessage2;
	ReportHeartbeatPulseMessage reportHeartbeatPulseMessage1;
	ReportHeartbeatPulseMessage reportHeartbeatPulseMessage2;
	ReportIdentificationMessage reportIdentificationMessage1;
	ReportIdentificationMessage reportIdentificationMessage2;
	ReportImageMessage reportImageMessage1;
	ReportImageMessage reportImageMessage2;
	ReportJointEffortsMessage reportJointEffortsMessage1;
	ReportJointEffortsMessage reportJointEffortsMessage2;
	ReportJointForceTorquesMessage reportJointForceTorquesMessage1;
	ReportJointForceTorquesMessage reportJointForceTorquesMessage2;
	ReportJointPositionsMessage reportJointPositionsMessage1;
	ReportJointPositionsMessage reportJointPositionsMessage2;
	ReportJointVelocitiesMessage reportJointVelocitiesMessage1;
	ReportJointVelocitiesMessage reportJointVelocitiesMessage2;
	ReportLocalPathSegmentMessage reportLocalPathSegmentMessage1;
	ReportLocalPathSegmentMessage reportLocalPathSegmentMessage2;
	ReportLocalPoseMessage reportLocalPoseMessage1;
	ReportLocalPoseMessage reportLocalPoseMessage2;
	ReportLocalVectorMessage reportLocalVectorMessage1;
	ReportLocalVectorMessage reportLocalVectorMessage2;
	ReportLocalWaypointMessage reportLocalWaypointMessage1;
	ReportLocalWaypointMessage reportLocalWaypointMessage2;
	ReportManipulatorSpecificationsMessage reportManipulatorSpecificationsMessage1;
	ReportManipulatorSpecificationsMessage reportManipulatorSpecificationsMessage2;
	ReportPathSegmentCountMessage reportPathSegmentCountMessage1;
	ReportPathSegmentCountMessage reportPathSegmentCountMessage2;
	ReportPayloadDataElementMessage reportPayloadDataElementMessage1;
	ReportPayloadDataElementMessage reportPayloadDataElementMessage2;
	ReportPayloadInterfaceMessage reportPayloadInterfaceMessage1;
	ReportPayloadInterfaceMessage reportPayloadInterfaceMessage2;
	ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessage1;
	ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessage2;
	ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessage1;
	ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessage2;
	ReportRelativeObjectPositionMessage reportRelativeObjectPositionMessage1;
	ReportRelativeObjectPositionMessage reportRelativeObjectPositionMessage2;
	ReportSelectedCameraMessage reportSelectedCameraMessage1;
	ReportSelectedCameraMessage reportSelectedCameraMessage2;
	ReportSelectedDataLinkStatusMessage reportSelectedDataLinkStatusMessage1;
	ReportSelectedDataLinkStatusMessage reportSelectedDataLinkStatusMessage2;
	ReportServicesMessage reportServicesMessage1;
	ReportServicesMessage reportServicesMessage2;
	ReportSubsystemListMessage reportSubsystemListMessage1;
	ReportSubsystemListMessage reportSubsystemListMessage2;
	ReportTimeMessage reportTimeMessage1;
	ReportTimeMessage reportTimeMessage2;
	ReportToolPointMessage reportToolPointMessage1;
	ReportToolPointMessage reportToolPointMessage2;
	ReportTravelSpeedMessage reportTravelSpeedMessage1;
	ReportTravelSpeedMessage reportTravelSpeedMessage2;
	ReportVelocityStateMessage reportVelocityStateMessage1;
	ReportVelocityStateMessage reportVelocityStateMessage2;
	ReportVksBoundsMessage reportVksBoundsMessage1;
	ReportVksBoundsMessage reportVksBoundsMessage2;
	ReportVksDataTransferTerminationMessage reportVksDataTransferTerminationMessage1;
	ReportVksDataTransferTerminationMessage reportVksDataTransferTerminationMessage2;
	ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessage1;
	ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessage2;
	ReportVksObjectsCreationMessage reportVksObjectsCreationMessage1;
	ReportVksObjectsCreationMessage reportVksObjectsCreationMessage2;
	ReportVksObjectsMessage reportVksObjectsMessage1;
	ReportVksObjectsMessage reportVksObjectsMessage2;
	ReportWaypointCountMessage reportWaypointCountMessage1;
	ReportWaypointCountMessage reportWaypointCountMessage2;
	ReportWrenchEffortMessage reportWrenchEffortMessage1;
	ReportWrenchEffortMessage reportWrenchEffortMessage2;
	RequestComponentControlMessage requestComponentControlMessage1;
	RequestComponentControlMessage requestComponentControlMessage2;
	ResetMessage resetMessage1;
	ResetMessage resetMessage2;
	ResumeMessage resumeMessage1;
	ResumeMessage resumeMessage2;
	SelectCameraMessage selectCameraMessage1;
	SelectCameraMessage selectCameraMessage2;
	SetCameraCapabilitiesMessage setCameraCapabilitiesMessage1;
	SetCameraCapabilitiesMessage setCameraCapabilitiesMessage2;
	SetCameraFormatOptionsMessage setCameraFormatOptionsMessage1;
	SetCameraFormatOptionsMessage setCameraFormatOptionsMessage2;
	SetCameraPoseMessage setCameraPoseMessage1;
	SetCameraPoseMessage setCameraPoseMessage2;
	SetComponentAuthorityMessage setComponentAuthorityMessage1;
	SetComponentAuthorityMessage setComponentAuthorityMessage2;
	SetDataLinkSelectMessage setDataLinkSelectMessage1;
	SetDataLinkSelectMessage setDataLinkSelectMessage2;
	SetDataLinkStatusMessage setDataLinkStatusMessage1;
	SetDataLinkStatusMessage setDataLinkStatusMessage2;
	SetDiscreteDevicesMessage setDiscreteDevicesMessage1;
	SetDiscreteDevicesMessage setDiscreteDevicesMessage2;
	SetEmergencyMessage setEmergencyMessage1;
	SetEmergencyMessage setEmergencyMessage2;
	SetEndEffectorPathMotionMessage setEndEffectorPathMotionMessage1;
	SetEndEffectorPathMotionMessage setEndEffectorPathMotionMessage2;
	SetEndEffectorPoseMessage setEndEffectorPoseMessage1;
	SetEndEffectorPoseMessage setEndEffectorPoseMessage2;
	SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessage1;
	SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessage2;
	SetGlobalPathSegmentMessage setGlobalPathSegmentMessage1;
	SetGlobalPathSegmentMessage setGlobalPathSegmentMessage2;
	SetGlobalVectorMessage setGlobalVectorMessage1;
	SetGlobalVectorMessage setGlobalVectorMessage2;
	SetGlobalWaypointMessage setGlobalWaypointMessage1;
	SetGlobalWaypointMessage setGlobalWaypointMessage2;
	SetJointEffortsMessage setJointEffortsMessage1;
	SetJointEffortsMessage setJointEffortsMessage2;
	SetJointMotionMessage setJointMotionMessage1;
	SetJointMotionMessage setJointMotionMessage2;
	SetJointPositionsMessage setJointPositionsMessage1;
	SetJointPositionsMessage setJointPositionsMessage2;
	SetJointVelocitiesMessage setJointVelocitiesMessage1;
	SetJointVelocitiesMessage setJointVelocitiesMessage2;
	SetLocalPathSegmentMessage setLocalPathSegmentMessage1;
	SetLocalPathSegmentMessage setLocalPathSegmentMessage2;
	SetLocalVectorMessage setLocalVectorMessage1;
	SetLocalVectorMessage setLocalVectorMessage2;
	SetLocalWaypointMessage setLocalWaypointMessage1;
	SetLocalWaypointMessage setLocalWaypointMessage2;
	SetPayloadDataElementMessage setPayloadDataElementMessage1;
	SetPayloadDataElementMessage setPayloadDataElementMessage2;
	SetSelectedDataLinkStateMessage setSelectedDataLinkStateMessage1;
	SetSelectedDataLinkStateMessage setSelectedDataLinkStateMessage2;
	SetTimeMessage setTimeMessage1;
	SetTimeMessage setTimeMessage2;
	SetToolPointMessage setToolPointMessage1;
	SetToolPointMessage setToolPointMessage2;
	SetTravelSpeedMessage setTravelSpeedMessage1;
	SetTravelSpeedMessage setTravelSpeedMessage2;
	SetVelocityStateMessage setVelocityStateMessage1;
	SetVelocityStateMessage setVelocityStateMessage2;
	SetVksFeatureClassMetadataMessage setVksFeatureClassMetadataMessage1;
	SetVksFeatureClassMetadataMessage setVksFeatureClassMetadataMessage2;
	SetWrenchEffortMessage setWrenchEffortMessage1;
	SetWrenchEffortMessage setWrenchEffortMessage2;
	ShutdownMessage shutdownMessage1;
	ShutdownMessage shutdownMessage2;
	StandbyMessage standbyMessage1;
	StandbyMessage standbyMessage2;
	SuspendServiceConnectionMessage suspendServiceConnectionMessage1;
	SuspendServiceConnectionMessage suspendServiceConnectionMessage2;
	TerminateServiceConnectionMessage terminateServiceConnectionMessage1;
	TerminateServiceConnectionMessage terminateServiceConnectionMessage2;
	TerminateVksDataTransferMessage terminateVksDataTransferMessage1;
	TerminateVksDataTransferMessage terminateVksDataTransferMessage2;
	UpdateEventMessage updateEventMessage1;
	UpdateEventMessage updateEventMessage2;

	printf("Testing ActivateServiceConnectionMessage\n");
	activateServiceConnectionMessage1 = activateServiceConnectionMessageCreate();
	jausMessage = activateServiceConnectionMessageToJausMessage(activateServiceConnectionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("activateServiceConnectionMessageToJausMessage failed\n");
	}
	else
	{
		activateServiceConnectionMessage2 = activateServiceConnectionMessageFromJausMessage(jausMessage);
		if(activateServiceConnectionMessage2 == NULL)
		{
			printf("activateServiceConnectionMessageFromJausMessage failed\n");
		}
		else
		{
			activateServiceConnectionMessageDestroy(activateServiceConnectionMessage2);
		}
	}
	activateServiceConnectionMessageDestroy(activateServiceConnectionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing CancelEventMessage\n");
	cancelEventMessage1 = cancelEventMessageCreate();
	jausMessage = cancelEventMessageToJausMessage(cancelEventMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("cancelEventMessageToJausMessage failed\n");
	}
	else
	{
		cancelEventMessage2 = cancelEventMessageFromJausMessage(jausMessage);
		if(cancelEventMessage2 == NULL)
		{
			printf("cancelEventMessageFromJausMessage failed\n");
		}
		else
		{
			cancelEventMessageDestroy(cancelEventMessage2);
		}
	}
	cancelEventMessageDestroy(cancelEventMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ClearEmergencyMessage\n");
	clearEmergencyMessage1 = clearEmergencyMessageCreate();
	jausMessage = clearEmergencyMessageToJausMessage(clearEmergencyMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("clearEmergencyMessageToJausMessage failed\n");
	}
	else
	{
		clearEmergencyMessage2 = clearEmergencyMessageFromJausMessage(jausMessage);
		if(clearEmergencyMessage2 == NULL)
		{
			printf("clearEmergencyMessageFromJausMessage failed\n");
		}
		else
		{
			clearEmergencyMessageDestroy(clearEmergencyMessage2);
		}
	}
	clearEmergencyMessageDestroy(clearEmergencyMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ConfirmComponentControlMessage\n");
	confirmComponentControlMessage1 = confirmComponentControlMessageCreate();
	jausMessage = confirmComponentControlMessageToJausMessage(confirmComponentControlMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("confirmComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		confirmComponentControlMessage2 = confirmComponentControlMessageFromJausMessage(jausMessage);
		if(confirmComponentControlMessage2 == NULL)
		{
			printf("confirmComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			confirmComponentControlMessageDestroy(confirmComponentControlMessage2);
		}
	}
	confirmComponentControlMessageDestroy(confirmComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ConfirmEventRequestMessage\n");
	confirmEventRequestMessage1 = confirmEventRequestMessageCreate();
	jausMessage = confirmEventRequestMessageToJausMessage(confirmEventRequestMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("confirmEventRequestMessageToJausMessage failed\n");
	}
	else
	{
		confirmEventRequestMessage2 = confirmEventRequestMessageFromJausMessage(jausMessage);
		if(confirmEventRequestMessage2 == NULL)
		{
			printf("confirmEventRequestMessageFromJausMessage failed\n");
		}
		else
		{
			confirmEventRequestMessageDestroy(confirmEventRequestMessage2);
		}
	}
	confirmEventRequestMessageDestroy(confirmEventRequestMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ConfirmServiceConnectionMessage\n");
	confirmServiceConnectionMessage1 = confirmServiceConnectionMessageCreate();
	jausMessage = confirmServiceConnectionMessageToJausMessage(confirmServiceConnectionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("confirmServiceConnectionMessageToJausMessage failed\n");
	}
	else
	{
		confirmServiceConnectionMessage2 = confirmServiceConnectionMessageFromJausMessage(jausMessage);
		if(confirmServiceConnectionMessage2 == NULL)
		{
			printf("confirmServiceConnectionMessageFromJausMessage failed\n");
		}
		else
		{
			confirmServiceConnectionMessageDestroy(confirmServiceConnectionMessage2);
		}
	}
	confirmServiceConnectionMessageDestroy(confirmServiceConnectionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing CreateEventMessage\n");
	createEventMessage1 = createEventMessageCreate();
	jausMessage = createEventMessageToJausMessage(createEventMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("createEventMessageToJausMessage failed\n");
	}
	else
	{
		createEventMessage2 = createEventMessageFromJausMessage(jausMessage);
		if(createEventMessage2 == NULL)
		{
			printf("createEventMessageFromJausMessage failed\n");
		}
		else
		{
			createEventMessageDestroy(createEventMessage2);
		}
	}
	createEventMessageDestroy(createEventMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing CreateServiceConnectionMessage\n");
	createServiceConnectionMessage1 = createServiceConnectionMessageCreate();
	jausMessage = createServiceConnectionMessageToJausMessage(createServiceConnectionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("createServiceConnectionMessageToJausMessage failed\n");
	}
	else
	{
		createServiceConnectionMessage2 = createServiceConnectionMessageFromJausMessage(jausMessage);
		if(createServiceConnectionMessage2 == NULL)
		{
			printf("createServiceConnectionMessageFromJausMessage failed\n");
		}
		else
		{
			createServiceConnectionMessageDestroy(createServiceConnectionMessage2);
		}
	}
	createServiceConnectionMessageDestroy(createServiceConnectionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing CreateVksObjectsMessage\n");
	createVksObjectsMessage1 = createVksObjectsMessageCreate();
	jausMessage = createVksObjectsMessageToJausMessage(createVksObjectsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("createVksObjectsMessageToJausMessage failed\n");
	}
	else
	{
		createVksObjectsMessage2 = createVksObjectsMessageFromJausMessage(jausMessage);
		if(createVksObjectsMessage2 == NULL)
		{
			printf("createVksObjectsMessageFromJausMessage failed\n");
		}
		else
		{
			createVksObjectsMessageDestroy(createVksObjectsMessage2);
		}
	}
	createVksObjectsMessageDestroy(createVksObjectsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing DeleteVksObjectsMessage\n");
	deleteVksObjectsMessage1 = deleteVksObjectsMessageCreate();
	jausMessage = deleteVksObjectsMessageToJausMessage(deleteVksObjectsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("deleteVksObjectsMessageToJausMessage failed\n");
	}
	else
	{
		deleteVksObjectsMessage2 = deleteVksObjectsMessageFromJausMessage(jausMessage);
		if(deleteVksObjectsMessage2 == NULL)
		{
			printf("deleteVksObjectsMessageFromJausMessage failed\n");
		}
		else
		{
			deleteVksObjectsMessageDestroy(deleteVksObjectsMessage2);
		}
	}
	deleteVksObjectsMessageDestroy(deleteVksObjectsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing EventMessage\n");
	eventMessage1 = eventMessageCreate();
	jausMessage = eventMessageToJausMessage(eventMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("eventMessageToJausMessage failed\n");
	}
	else
	{
		eventMessage2 = eventMessageFromJausMessage(jausMessage);
		if(eventMessage2 == NULL)
		{
			printf("eventMessageFromJausMessage failed\n");
		}
		else
		{
			eventMessageDestroy(eventMessage2);
		}
	}
	eventMessageDestroy(eventMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryCameraCapabilitiesMessage\n");
	queryCameraCapabilitiesMessage1 = queryCameraCapabilitiesMessageCreate();
	jausMessage = queryCameraCapabilitiesMessageToJausMessage(queryCameraCapabilitiesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryCameraCapabilitiesMessageToJausMessage failed\n");
	}
	else
	{
		queryCameraCapabilitiesMessage2 = queryCameraCapabilitiesMessageFromJausMessage(jausMessage);
		if(queryCameraCapabilitiesMessage2 == NULL)
		{
			printf("queryCameraCapabilitiesMessageFromJausMessage failed\n");
		}
		else
		{
			queryCameraCapabilitiesMessageDestroy(queryCameraCapabilitiesMessage2);
		}
	}
	queryCameraCapabilitiesMessageDestroy(queryCameraCapabilitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryCameraCountMessage\n");
	queryCameraCountMessage1 = queryCameraCountMessageCreate();
	jausMessage = queryCameraCountMessageToJausMessage(queryCameraCountMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryCameraCountMessageToJausMessage failed\n");
	}
	else
	{
		queryCameraCountMessage2 = queryCameraCountMessageFromJausMessage(jausMessage);
		if(queryCameraCountMessage2 == NULL)
		{
			printf("queryCameraCountMessageFromJausMessage failed\n");
		}
		else
		{
			queryCameraCountMessageDestroy(queryCameraCountMessage2);
		}
	}
	queryCameraCountMessageDestroy(queryCameraCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryCameraFormatOptionsMessage\n");
	queryCameraFormatOptionsMessage1 = queryCameraFormatOptionsMessageCreate();
	jausMessage = queryCameraFormatOptionsMessageToJausMessage(queryCameraFormatOptionsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryCameraFormatOptionsMessageToJausMessage failed\n");
	}
	else
	{
		queryCameraFormatOptionsMessage2 = queryCameraFormatOptionsMessageFromJausMessage(jausMessage);
		if(queryCameraFormatOptionsMessage2 == NULL)
		{
			printf("queryCameraFormatOptionsMessageFromJausMessage failed\n");
		}
		else
		{
			queryCameraFormatOptionsMessageDestroy(queryCameraFormatOptionsMessage2);
		}
	}
	queryCameraFormatOptionsMessageDestroy(queryCameraFormatOptionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryCameraPoseMessage\n");
	queryCameraPoseMessage1 = queryCameraPoseMessageCreate();
	jausMessage = queryCameraPoseMessageToJausMessage(queryCameraPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryCameraPoseMessageToJausMessage failed\n");
	}
	else
	{
		queryCameraPoseMessage2 = queryCameraPoseMessageFromJausMessage(jausMessage);
		if(queryCameraPoseMessage2 == NULL)
		{
			printf("queryCameraPoseMessageFromJausMessage failed\n");
		}
		else
		{
			queryCameraPoseMessageDestroy(queryCameraPoseMessage2);
		}
	}
	queryCameraPoseMessageDestroy(queryCameraPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryComponentAuthorityMessage\n");
	queryComponentAuthorityMessage1 = queryComponentAuthorityMessageCreate();
	jausMessage = queryComponentAuthorityMessageToJausMessage(queryComponentAuthorityMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryComponentAuthorityMessageToJausMessage failed\n");
	}
	else
	{
		queryComponentAuthorityMessage2 = queryComponentAuthorityMessageFromJausMessage(jausMessage);
		if(queryComponentAuthorityMessage2 == NULL)
		{
			printf("queryComponentAuthorityMessageFromJausMessage failed\n");
		}
		else
		{
			queryComponentAuthorityMessageDestroy(queryComponentAuthorityMessage2);
		}
	}
	queryComponentAuthorityMessageDestroy(queryComponentAuthorityMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryComponentControlMessage\n");
	queryComponentControlMessage1 = queryComponentControlMessageCreate();
	jausMessage = queryComponentControlMessageToJausMessage(queryComponentControlMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		queryComponentControlMessage2 = queryComponentControlMessageFromJausMessage(jausMessage);
		if(queryComponentControlMessage2 == NULL)
		{
			printf("queryComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			queryComponentControlMessageDestroy(queryComponentControlMessage2);
		}
	}
	queryComponentControlMessageDestroy(queryComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryComponentStatusMessage\n");
	queryComponentStatusMessage1 = queryComponentStatusMessageCreate();
	jausMessage = queryComponentStatusMessageToJausMessage(queryComponentStatusMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryComponentStatusMessageToJausMessage failed\n");
	}
	else
	{
		queryComponentStatusMessage2 = queryComponentStatusMessageFromJausMessage(jausMessage);
		if(queryComponentStatusMessage2 == NULL)
		{
			printf("queryComponentStatusMessageFromJausMessage failed\n");
		}
		else
		{
			queryComponentStatusMessageDestroy(queryComponentStatusMessage2);
		}
	}
	queryComponentStatusMessageDestroy(queryComponentStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryConfigurationMessage\n");
	queryConfigurationMessage1 = queryConfigurationMessageCreate();
	jausMessage = queryConfigurationMessageToJausMessage(queryConfigurationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryConfigurationMessageToJausMessage failed\n");
	}
	else
	{
		queryConfigurationMessage2 = queryConfigurationMessageFromJausMessage(jausMessage);
		if(queryConfigurationMessage2 == NULL)
		{
			printf("queryConfigurationMessageFromJausMessage failed\n");
		}
		else
		{
			queryConfigurationMessageDestroy(queryConfigurationMessage2);
		}
	}
	queryConfigurationMessageDestroy(queryConfigurationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryDataLinkStatusMessage\n");
	queryDataLinkStatusMessage1 = queryDataLinkStatusMessageCreate();
	jausMessage = queryDataLinkStatusMessageToJausMessage(queryDataLinkStatusMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryDataLinkStatusMessageToJausMessage failed\n");
	}
	else
	{
		queryDataLinkStatusMessage2 = queryDataLinkStatusMessageFromJausMessage(jausMessage);
		if(queryDataLinkStatusMessage2 == NULL)
		{
			printf("queryDataLinkStatusMessageFromJausMessage failed\n");
		}
		else
		{
			queryDataLinkStatusMessageDestroy(queryDataLinkStatusMessage2);
		}
	}
	queryDataLinkStatusMessageDestroy(queryDataLinkStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryDiscreteDevicesMessage\n");
	queryDiscreteDevicesMessage1 = queryDiscreteDevicesMessageCreate();
	jausMessage = queryDiscreteDevicesMessageToJausMessage(queryDiscreteDevicesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryDiscreteDevicesMessageToJausMessage failed\n");
	}
	else
	{
		queryDiscreteDevicesMessage2 = queryDiscreteDevicesMessageFromJausMessage(jausMessage);
		if(queryDiscreteDevicesMessage2 == NULL)
		{
			printf("queryDiscreteDevicesMessageFromJausMessage failed\n");
		}
		else
		{
			queryDiscreteDevicesMessageDestroy(queryDiscreteDevicesMessage2);
		}
	}
	queryDiscreteDevicesMessageDestroy(queryDiscreteDevicesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryEventsMessage\n");
	queryEventsMessage1 = queryEventsMessageCreate();
	jausMessage = queryEventsMessageToJausMessage(queryEventsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryEventsMessageToJausMessage failed\n");
	}
	else
	{
		queryEventsMessage2 = queryEventsMessageFromJausMessage(jausMessage);
		if(queryEventsMessage2 == NULL)
		{
			printf("queryEventsMessageFromJausMessage failed\n");
		}
		else
		{
			queryEventsMessageDestroy(queryEventsMessage2);
		}
	}
	queryEventsMessageDestroy(queryEventsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryGlobalPathSegmentMessage\n");
	queryGlobalPathSegmentMessage1 = queryGlobalPathSegmentMessageCreate();
	jausMessage = queryGlobalPathSegmentMessageToJausMessage(queryGlobalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryGlobalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		queryGlobalPathSegmentMessage2 = queryGlobalPathSegmentMessageFromJausMessage(jausMessage);
		if(queryGlobalPathSegmentMessage2 == NULL)
		{
			printf("queryGlobalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			queryGlobalPathSegmentMessageDestroy(queryGlobalPathSegmentMessage2);
		}
	}
	queryGlobalPathSegmentMessageDestroy(queryGlobalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryGlobalPoseMessage\n");
	queryGlobalPoseMessage1 = queryGlobalPoseMessageCreate();
	jausMessage = queryGlobalPoseMessageToJausMessage(queryGlobalPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryGlobalPoseMessageToJausMessage failed\n");
	}
	else
	{
		queryGlobalPoseMessage2 = queryGlobalPoseMessageFromJausMessage(jausMessage);
		if(queryGlobalPoseMessage2 == NULL)
		{
			printf("queryGlobalPoseMessageFromJausMessage failed\n");
		}
		else
		{
			queryGlobalPoseMessageDestroy(queryGlobalPoseMessage2);
		}
	}
	queryGlobalPoseMessageDestroy(queryGlobalPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryGlobalVectorMessage\n");
	queryGlobalVectorMessage1 = queryGlobalVectorMessageCreate();
	jausMessage = queryGlobalVectorMessageToJausMessage(queryGlobalVectorMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryGlobalVectorMessageToJausMessage failed\n");
	}
	else
	{
		queryGlobalVectorMessage2 = queryGlobalVectorMessageFromJausMessage(jausMessage);
		if(queryGlobalVectorMessage2 == NULL)
		{
			printf("queryGlobalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			queryGlobalVectorMessageDestroy(queryGlobalVectorMessage2);
		}
	}
	queryGlobalVectorMessageDestroy(queryGlobalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryGlobalWaypointMessage\n");
	queryGlobalWaypointMessage1 = queryGlobalWaypointMessageCreate();
	jausMessage = queryGlobalWaypointMessageToJausMessage(queryGlobalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryGlobalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		queryGlobalWaypointMessage2 = queryGlobalWaypointMessageFromJausMessage(jausMessage);
		if(queryGlobalWaypointMessage2 == NULL)
		{
			printf("queryGlobalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			queryGlobalWaypointMessageDestroy(queryGlobalWaypointMessage2);
		}
	}
	queryGlobalWaypointMessageDestroy(queryGlobalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryHeartbeatPulseMessage\n");
	queryHeartbeatPulseMessage1 = queryHeartbeatPulseMessageCreate();
	jausMessage = queryHeartbeatPulseMessageToJausMessage(queryHeartbeatPulseMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryHeartbeatPulseMessageToJausMessage failed\n");
	}
	else
	{
		queryHeartbeatPulseMessage2 = queryHeartbeatPulseMessageFromJausMessage(jausMessage);
		if(queryHeartbeatPulseMessage2 == NULL)
		{
			printf("queryHeartbeatPulseMessageFromJausMessage failed\n");
		}
		else
		{
			queryHeartbeatPulseMessageDestroy(queryHeartbeatPulseMessage2);
		}
	}
	queryHeartbeatPulseMessageDestroy(queryHeartbeatPulseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryIdentificationMessage\n");
	queryIdentificationMessage1 = queryIdentificationMessageCreate();
	jausMessage = queryIdentificationMessageToJausMessage(queryIdentificationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryIdentificationMessageToJausMessage failed\n");
	}
	else
	{
		queryIdentificationMessage2 = queryIdentificationMessageFromJausMessage(jausMessage);
		if(queryIdentificationMessage2 == NULL)
		{
			printf("queryIdentificationMessageFromJausMessage failed\n");
		}
		else
		{
			queryIdentificationMessageDestroy(queryIdentificationMessage2);
		}
	}
	queryIdentificationMessageDestroy(queryIdentificationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryImageMessage\n");
	queryImageMessage1 = queryImageMessageCreate();
	jausMessage = queryImageMessageToJausMessage(queryImageMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryImageMessageToJausMessage failed\n");
	}
	else
	{
		queryImageMessage2 = queryImageMessageFromJausMessage(jausMessage);
		if(queryImageMessage2 == NULL)
		{
			printf("queryImageMessageFromJausMessage failed\n");
		}
		else
		{
			queryImageMessageDestroy(queryImageMessage2);
		}
	}
	queryImageMessageDestroy(queryImageMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryJointEffortsMessage\n");
	queryJointEffortsMessage1 = queryJointEffortsMessageCreate();
	jausMessage = queryJointEffortsMessageToJausMessage(queryJointEffortsMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryJointEffortsMessageToJausMessage failed\n");
	}
	else
	{
		queryJointEffortsMessage2 = queryJointEffortsMessageFromJausMessage(jausMessage);
		if(queryJointEffortsMessage2 == NULL)
		{
			printf("queryJointEffortsMessageFromJausMessage failed\n");
		}
		else
		{
			queryJointEffortsMessageDestroy(queryJointEffortsMessage2);
		}
	}
	queryJointEffortsMessageDestroy(queryJointEffortsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryJointForceTorquesMessage\n");
	queryJointForceTorquesMessage1 = queryJointForceTorquesMessageCreate();
	jausMessage = queryJointForceTorquesMessageToJausMessage(queryJointForceTorquesMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryJointForceTorquesMessageToJausMessage failed\n");
	}
	else
	{
		queryJointForceTorquesMessage2 = queryJointForceTorquesMessageFromJausMessage(jausMessage);
		if(queryJointForceTorquesMessage2 == NULL)
		{
			printf("queryJointForceTorquesMessageFromJausMessage failed\n");
		}
		else
		{
			queryJointForceTorquesMessageDestroy(queryJointForceTorquesMessage2);
		}
	}
	queryJointForceTorquesMessageDestroy(queryJointForceTorquesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryJointPositionsMessage\n");
	queryJointPositionsMessage1 = queryJointPositionsMessageCreate();
	jausMessage = queryJointPositionsMessageToJausMessage(queryJointPositionsMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryJointPositionsMessageToJausMessage failed\n");
	}
	else
	{
		queryJointPositionsMessage2 = queryJointPositionsMessageFromJausMessage(jausMessage);
		if(queryJointPositionsMessage2 == NULL)
		{
			printf("queryJointPositionsMessageFromJausMessage failed\n");
		}
		else
		{
			queryJointPositionsMessageDestroy(queryJointPositionsMessage2);
		}
	}
	queryJointPositionsMessageDestroy(queryJointPositionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryJointVelocitiesMessage\n");
	queryJointVelocitiesMessage1 = queryJointVelocitiesMessageCreate();
	jausMessage = queryJointVelocitiesMessageToJausMessage(queryJointVelocitiesMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryJointVelocitiesMessageToJausMessage failed\n");
	}
	else
	{
		queryJointVelocitiesMessage2 = queryJointVelocitiesMessageFromJausMessage(jausMessage);
		if(queryJointVelocitiesMessage2 == NULL)
		{
			printf("queryJointVelocitiesMessageFromJausMessage failed\n");
		}
		else
		{
			queryJointVelocitiesMessageDestroy(queryJointVelocitiesMessage2);
		}
	}
	queryJointVelocitiesMessageDestroy(queryJointVelocitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryLocalPathSegmentMessage\n");
	queryLocalPathSegmentMessage1 = queryLocalPathSegmentMessageCreate();
	jausMessage = queryLocalPathSegmentMessageToJausMessage(queryLocalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryLocalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		queryLocalPathSegmentMessage2 = queryLocalPathSegmentMessageFromJausMessage(jausMessage);
		if(queryLocalPathSegmentMessage2 == NULL)
		{
			printf("queryLocalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			queryLocalPathSegmentMessageDestroy(queryLocalPathSegmentMessage2);
		}
	}
	queryLocalPathSegmentMessageDestroy(queryLocalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryLocalPoseMessage\n");
	queryLocalPoseMessage1 = queryLocalPoseMessageCreate();
	jausMessage = queryLocalPoseMessageToJausMessage(queryLocalPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryLocalPoseMessageToJausMessage failed\n");
	}
	else
	{
		queryLocalPoseMessage2 = queryLocalPoseMessageFromJausMessage(jausMessage);
		if(queryLocalPoseMessage2 == NULL)
		{
			printf("queryLocalPoseMessageFromJausMessage failed\n");
		}
		else
		{
			queryLocalPoseMessageDestroy(queryLocalPoseMessage2);
		}
	}
	queryLocalPoseMessageDestroy(queryLocalPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryLocalVectorMessage\n");
	queryLocalVectorMessage1 = queryLocalVectorMessageCreate();
	jausMessage = queryLocalVectorMessageToJausMessage(queryLocalVectorMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryLocalVectorMessageToJausMessage failed\n");
	}
	else
	{
		queryLocalVectorMessage2 = queryLocalVectorMessageFromJausMessage(jausMessage);
		if(queryLocalVectorMessage2 == NULL)
		{
			printf("queryLocalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			queryLocalVectorMessageDestroy(queryLocalVectorMessage2);
		}
	}
	queryLocalVectorMessageDestroy(queryLocalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryLocalWaypointMessage\n");
	queryLocalWaypointMessage1 = queryLocalWaypointMessageCreate();
	jausMessage = queryLocalWaypointMessageToJausMessage(queryLocalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryLocalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		queryLocalWaypointMessage2 = queryLocalWaypointMessageFromJausMessage(jausMessage);
		if(queryLocalWaypointMessage2 == NULL)
		{
			printf("queryLocalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			queryLocalWaypointMessageDestroy(queryLocalWaypointMessage2);
		}
	}
	queryLocalWaypointMessageDestroy(queryLocalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryManipulatorSpecificationsMessage\n");
	queryManipulatorSpecificationsMessage1 = queryManipulatorSpecificationsMessageCreate();
	jausMessage = queryManipulatorSpecificationsMessageToJausMessage(queryManipulatorSpecificationsMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryManipulatorSpecificationsMessageToJausMessage failed\n");
	}
	else
	{
		queryManipulatorSpecificationsMessage2 = queryManipulatorSpecificationsMessageFromJausMessage(jausMessage);
		if(queryManipulatorSpecificationsMessage2 == NULL)
		{
			printf("queryManipulatorSpecificationsMessageFromJausMessage failed\n");
		}
		else
		{
			queryManipulatorSpecificationsMessageDestroy(queryManipulatorSpecificationsMessage2);
		}
	}
	queryManipulatorSpecificationsMessageDestroy(queryManipulatorSpecificationsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryPathSegmentCountMessage\n");
	queryPathSegmentCountMessage1 = queryPathSegmentCountMessageCreate();
	jausMessage = queryPathSegmentCountMessageToJausMessage(queryPathSegmentCountMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryPathSegmentCountMessageToJausMessage failed\n");
	}
	else
	{
		queryPathSegmentCountMessage2 = queryPathSegmentCountMessageFromJausMessage(jausMessage);
		if(queryPathSegmentCountMessage2 == NULL)
		{
			printf("queryPathSegmentCountMessageFromJausMessage failed\n");
		}
		else
		{
			queryPathSegmentCountMessageDestroy(queryPathSegmentCountMessage2);
		}
	}
	queryPathSegmentCountMessageDestroy(queryPathSegmentCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryPayloadDataElementMessage\n");
	queryPayloadDataElementMessage1 = queryPayloadDataElementMessageCreate();
	jausMessage = queryPayloadDataElementMessageToJausMessage(queryPayloadDataElementMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryPayloadDataElementMessageToJausMessage failed\n");
	}
	else
	{
		queryPayloadDataElementMessage2 = queryPayloadDataElementMessageFromJausMessage(jausMessage);
		if(queryPayloadDataElementMessage2 == NULL)
		{
			printf("queryPayloadDataElementMessageFromJausMessage failed\n");
		}
		else
		{
			queryPayloadDataElementMessageDestroy(queryPayloadDataElementMessage2);
		}
	}
	queryPayloadDataElementMessageDestroy(queryPayloadDataElementMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryPayloadInterfaceMessage\n");
	queryPayloadInterfaceMessage1 = queryPayloadInterfaceMessageCreate();
	jausMessage = queryPayloadInterfaceMessageToJausMessage(queryPayloadInterfaceMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryPayloadInterfaceMessageToJausMessage failed\n");
	}
	else
	{
		queryPayloadInterfaceMessage2 = queryPayloadInterfaceMessageFromJausMessage(jausMessage);
		if(queryPayloadInterfaceMessage2 == NULL)
		{
			printf("queryPayloadInterfaceMessageFromJausMessage failed\n");
		}
		else
		{
			queryPayloadInterfaceMessageDestroy(queryPayloadInterfaceMessage2);
		}
	}
	queryPayloadInterfaceMessageDestroy(queryPayloadInterfaceMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryPlatformOperationalDataMessage\n");
	queryPlatformOperationalDataMessage1 = queryPlatformOperationalDataMessageCreate();
	jausMessage = queryPlatformOperationalDataMessageToJausMessage(queryPlatformOperationalDataMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryPlatformOperationalDataMessageToJausMessage failed\n");
	}
	else
	{
		queryPlatformOperationalDataMessage2 = queryPlatformOperationalDataMessageFromJausMessage(jausMessage);
		if(queryPlatformOperationalDataMessage2 == NULL)
		{
			printf("queryPlatformOperationalDataMessageFromJausMessage failed\n");
		}
		else
		{
			queryPlatformOperationalDataMessageDestroy(queryPlatformOperationalDataMessage2);
		}
	}
	queryPlatformOperationalDataMessageDestroy(queryPlatformOperationalDataMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryPlatformSpecificationsMessage\n");
	queryPlatformSpecificationsMessage1 = queryPlatformSpecificationsMessageCreate();
	jausMessage = queryPlatformSpecificationsMessageToJausMessage(queryPlatformSpecificationsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryPlatformSpecificationsMessageToJausMessage failed\n");
	}
	else
	{
		queryPlatformSpecificationsMessage2 = queryPlatformSpecificationsMessageFromJausMessage(jausMessage);
		if(queryPlatformSpecificationsMessage2 == NULL)
		{
			printf("queryPlatformSpecificationsMessageFromJausMessage failed\n");
		}
		else
		{
			queryPlatformSpecificationsMessageDestroy(queryPlatformSpecificationsMessage2);
		}
	}
	queryPlatformSpecificationsMessageDestroy(queryPlatformSpecificationsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryRelativeObjectPositionMessage\n");
	queryRelativeObjectPositionMessage1 = queryRelativeObjectPositionMessageCreate();
	jausMessage = queryRelativeObjectPositionMessageToJausMessage(queryRelativeObjectPositionMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryRelativeObjectPositionMessageToJausMessage failed\n");
	}
	else
	{
		queryRelativeObjectPositionMessage2 = queryRelativeObjectPositionMessageFromJausMessage(jausMessage);
		if(queryRelativeObjectPositionMessage2 == NULL)
		{
			printf("queryRelativeObjectPositionMessageFromJausMessage failed\n");
		}
		else
		{
			queryRelativeObjectPositionMessageDestroy(queryRelativeObjectPositionMessage2);
		}
	}
	queryRelativeObjectPositionMessageDestroy(queryRelativeObjectPositionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QuerySelectedCameraMessage\n");
	querySelectedCameraMessage1 = querySelectedCameraMessageCreate();
	jausMessage = querySelectedCameraMessageToJausMessage(querySelectedCameraMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("querySelectedCameraMessageToJausMessage failed\n");
	}
	else
	{
		querySelectedCameraMessage2 = querySelectedCameraMessageFromJausMessage(jausMessage);
		if(querySelectedCameraMessage2 == NULL)
		{
			printf("querySelectedCameraMessageFromJausMessage failed\n");
		}
		else
		{
			querySelectedCameraMessageDestroy(querySelectedCameraMessage2);
		}
	}
	querySelectedCameraMessageDestroy(querySelectedCameraMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QuerySelectedDataLinkStatusMessage\n");
	querySelectedDataLinkStatusMessage1 = querySelectedDataLinkStatusMessageCreate();
	jausMessage = querySelectedDataLinkStatusMessageToJausMessage(querySelectedDataLinkStatusMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("querySelectedDataLinkStatusMessageToJausMessage failed\n");
	}
	else
	{
		querySelectedDataLinkStatusMessage2 = querySelectedDataLinkStatusMessageFromJausMessage(jausMessage);
		if(querySelectedDataLinkStatusMessage2 == NULL)
		{
			printf("querySelectedDataLinkStatusMessageFromJausMessage failed\n");
		}
		else
		{
			querySelectedDataLinkStatusMessageDestroy(querySelectedDataLinkStatusMessage2);
		}
	}
	querySelectedDataLinkStatusMessageDestroy(querySelectedDataLinkStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryServicesMessage\n");
	queryServicesMessage1 = queryServicesMessageCreate();
	jausMessage = queryServicesMessageToJausMessage(queryServicesMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryServicesMessageToJausMessage failed\n");
	}
	else
	{
		queryServicesMessage2 = queryServicesMessageFromJausMessage(jausMessage);
		if(queryServicesMessage2 == NULL)
		{
			printf("queryServicesMessageFromJausMessage failed\n");
		}
		else
		{
			queryServicesMessageDestroy(queryServicesMessage2);
		}
	}
	queryServicesMessageDestroy(queryServicesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QuerySubsystemListMessage\n");
	querySubsystemListMessage1 = querySubsystemListMessageCreate();
	jausMessage = querySubsystemListMessageToJausMessage(querySubsystemListMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("querySubsystemListMessageToJausMessage failed\n");
	}
	else
	{
		querySubsystemListMessage2 = querySubsystemListMessageFromJausMessage(jausMessage);
		if(querySubsystemListMessage2 == NULL)
		{
			printf("querySubsystemListMessageFromJausMessage failed\n");
		}
		else
		{
			querySubsystemListMessageDestroy(querySubsystemListMessage2);
		}
	}
	querySubsystemListMessageDestroy(querySubsystemListMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryTimeMessage\n");
	queryTimeMessage1 = queryTimeMessageCreate();
	jausMessage = queryTimeMessageToJausMessage(queryTimeMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryTimeMessageToJausMessage failed\n");
	}
	else
	{
		queryTimeMessage2 = queryTimeMessageFromJausMessage(jausMessage);
		if(queryTimeMessage2 == NULL)
		{
			printf("queryTimeMessageFromJausMessage failed\n");
		}
		else
		{
			queryTimeMessageDestroy(queryTimeMessage2);
		}
	}
	queryTimeMessageDestroy(queryTimeMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryToolPointMessage\n");
	queryToolPointMessage1 = queryToolPointMessageCreate();
	jausMessage = queryToolPointMessageToJausMessage(queryToolPointMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryToolPointMessageToJausMessage failed\n");
	}
	else
	{
		queryToolPointMessage2 = queryToolPointMessageFromJausMessage(jausMessage);
		if(queryToolPointMessage2 == NULL)
		{
			printf("queryToolPointMessageFromJausMessage failed\n");
		}
		else
		{
			queryToolPointMessageDestroy(queryToolPointMessage2);
		}
	}
	queryToolPointMessageDestroy(queryToolPointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryTravelSpeedMessage\n");
	queryTravelSpeedMessage1 = queryTravelSpeedMessageCreate();
	jausMessage = queryTravelSpeedMessageToJausMessage(queryTravelSpeedMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryTravelSpeedMessageToJausMessage failed\n");
	}
	else
	{
		queryTravelSpeedMessage2 = queryTravelSpeedMessageFromJausMessage(jausMessage);
		if(queryTravelSpeedMessage2 == NULL)
		{
			printf("queryTravelSpeedMessageFromJausMessage failed\n");
		}
		else
		{
			queryTravelSpeedMessageDestroy(queryTravelSpeedMessage2);
		}
	}
	queryTravelSpeedMessageDestroy(queryTravelSpeedMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryVelocityStateMessage\n");
	queryVelocityStateMessage1 = queryVelocityStateMessageCreate();
	jausMessage = queryVelocityStateMessageToJausMessage(queryVelocityStateMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryVelocityStateMessageToJausMessage failed\n");
	}
	else
	{
		queryVelocityStateMessage2 = queryVelocityStateMessageFromJausMessage(jausMessage);
		if(queryVelocityStateMessage2 == NULL)
		{
			printf("queryVelocityStateMessageFromJausMessage failed\n");
		}
		else
		{
			queryVelocityStateMessageDestroy(queryVelocityStateMessage2);
		}
	}
	queryVelocityStateMessageDestroy(queryVelocityStateMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryVksBoundsMessage\n");
	queryVksBoundsMessage1 = queryVksBoundsMessageCreate();
	jausMessage = queryVksBoundsMessageToJausMessage(queryVksBoundsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryVksBoundsMessageToJausMessage failed\n");
	}
	else
	{
		queryVksBoundsMessage2 = queryVksBoundsMessageFromJausMessage(jausMessage);
		if(queryVksBoundsMessage2 == NULL)
		{
			printf("queryVksBoundsMessageFromJausMessage failed\n");
		}
		else
		{
			queryVksBoundsMessageDestroy(queryVksBoundsMessage2);
		}
	}
	queryVksBoundsMessageDestroy(queryVksBoundsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryVksFeatureClassMetadataMessage\n");
	queryVksFeatureClassMetadataMessage1 = queryVksFeatureClassMetadataMessageCreate();
	jausMessage = queryVksFeatureClassMetadataMessageToJausMessage(queryVksFeatureClassMetadataMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryVksFeatureClassMetadataMessageToJausMessage failed\n");
	}
	else
	{
		queryVksFeatureClassMetadataMessage2 = queryVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
		if(queryVksFeatureClassMetadataMessage2 == NULL)
		{
			printf("queryVksFeatureClassMetadataMessageFromJausMessage failed\n");
		}
		else
		{
			queryVksFeatureClassMetadataMessageDestroy(queryVksFeatureClassMetadataMessage2);
		}
	}
	queryVksFeatureClassMetadataMessageDestroy(queryVksFeatureClassMetadataMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryVksObjectsMessage\n");
	queryVksObjectsMessage1 = queryVksObjectsMessageCreate();
	jausMessage = queryVksObjectsMessageToJausMessage(queryVksObjectsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryVksObjectsMessageToJausMessage failed\n");
	}
	else
	{
		queryVksObjectsMessage2 = queryVksObjectsMessageFromJausMessage(jausMessage);
		if(queryVksObjectsMessage2 == NULL)
		{
			printf("queryVksObjectsMessageFromJausMessage failed\n");
		}
		else
		{
			queryVksObjectsMessageDestroy(queryVksObjectsMessage2);
		}
	}
	queryVksObjectsMessageDestroy(queryVksObjectsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryWaypointCountMessage\n");
	queryWaypointCountMessage1 = queryWaypointCountMessageCreate();
	jausMessage = queryWaypointCountMessageToJausMessage(queryWaypointCountMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("queryWaypointCountMessageToJausMessage failed\n");
	}
	else
	{
		queryWaypointCountMessage2 = queryWaypointCountMessageFromJausMessage(jausMessage);
		if(queryWaypointCountMessage2 == NULL)
		{
			printf("queryWaypointCountMessageFromJausMessage failed\n");
		}
		else
		{
			queryWaypointCountMessageDestroy(queryWaypointCountMessage2);
		}
	}
	queryWaypointCountMessageDestroy(queryWaypointCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing QueryWrenchEffortMessage\n");
	queryWrenchEffortMessage1 = queryWrenchEffortMessageCreate();
	jausMessage = queryWrenchEffortMessageToJausMessage(queryWrenchEffortMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("queryWrenchEffortMessageToJausMessage failed\n");
	}
	else
	{
		queryWrenchEffortMessage2 = queryWrenchEffortMessageFromJausMessage(jausMessage);
		if(queryWrenchEffortMessage2 == NULL)
		{
			printf("queryWrenchEffortMessageFromJausMessage failed\n");
		}
		else
		{
			queryWrenchEffortMessageDestroy(queryWrenchEffortMessage2);
		}
	}
	queryWrenchEffortMessageDestroy(queryWrenchEffortMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing RejectComponentControlMessage\n");
	rejectComponentControlMessage1 = rejectComponentControlMessageCreate();
	jausMessage = rejectComponentControlMessageToJausMessage(rejectComponentControlMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("rejectComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		rejectComponentControlMessage2 = rejectComponentControlMessageFromJausMessage(jausMessage);
		if(rejectComponentControlMessage2 == NULL)
		{
			printf("rejectComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			rejectComponentControlMessageDestroy(rejectComponentControlMessage2);
		}
	}
	rejectComponentControlMessageDestroy(rejectComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing RejectEventRequestMessage\n");
	rejectEventRequestMessage1 = rejectEventRequestMessageCreate();
	jausMessage = rejectEventRequestMessageToJausMessage(rejectEventRequestMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("rejectEventRequestMessageToJausMessage failed\n");
	}
	else
	{
		rejectEventRequestMessage2 = rejectEventRequestMessageFromJausMessage(jausMessage);
		if(rejectEventRequestMessage2 == NULL)
		{
			printf("rejectEventRequestMessageFromJausMessage failed\n");
		}
		else
		{
			rejectEventRequestMessageDestroy(rejectEventRequestMessage2);
		}
	}
	rejectEventRequestMessageDestroy(rejectEventRequestMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReleaseComponentControlMessage\n");
	releaseComponentControlMessage1 = releaseComponentControlMessageCreate();
	jausMessage = releaseComponentControlMessageToJausMessage(releaseComponentControlMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("releaseComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		releaseComponentControlMessage2 = releaseComponentControlMessageFromJausMessage(jausMessage);
		if(releaseComponentControlMessage2 == NULL)
		{
			printf("releaseComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			releaseComponentControlMessageDestroy(releaseComponentControlMessage2);
		}
	}
	releaseComponentControlMessageDestroy(releaseComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportCameraCapabilitiesMessage\n");
	reportCameraCapabilitiesMessage1 = reportCameraCapabilitiesMessageCreate();
	jausMessage = reportCameraCapabilitiesMessageToJausMessage(reportCameraCapabilitiesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportCameraCapabilitiesMessageToJausMessage failed\n");
	}
	else
	{
		reportCameraCapabilitiesMessage2 = reportCameraCapabilitiesMessageFromJausMessage(jausMessage);
		if(reportCameraCapabilitiesMessage2 == NULL)
		{
			printf("reportCameraCapabilitiesMessageFromJausMessage failed\n");
		}
		else
		{
			reportCameraCapabilitiesMessageDestroy(reportCameraCapabilitiesMessage2);
		}
	}
	reportCameraCapabilitiesMessageDestroy(reportCameraCapabilitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportCameraCountMessage\n");
	reportCameraCountMessage1 = reportCameraCountMessageCreate();
	jausMessage = reportCameraCountMessageToJausMessage(reportCameraCountMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportCameraCountMessageToJausMessage failed\n");
	}
	else
	{
		reportCameraCountMessage2 = reportCameraCountMessageFromJausMessage(jausMessage);
		if(reportCameraCountMessage2 == NULL)
		{
			printf("reportCameraCountMessageFromJausMessage failed\n");
		}
		else
		{
			reportCameraCountMessageDestroy(reportCameraCountMessage2);
		}
	}
	reportCameraCountMessageDestroy(reportCameraCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportCameraFormatOptionsMessage\n");
	reportCameraFormatOptionsMessage1 = reportCameraFormatOptionsMessageCreate();
	jausMessage = reportCameraFormatOptionsMessageToJausMessage(reportCameraFormatOptionsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportCameraFormatOptionsMessageToJausMessage failed\n");
	}
	else
	{
		reportCameraFormatOptionsMessage2 = reportCameraFormatOptionsMessageFromJausMessage(jausMessage);
		if(reportCameraFormatOptionsMessage2 == NULL)
		{
			printf("reportCameraFormatOptionsMessageFromJausMessage failed\n");
		}
		else
		{
			reportCameraFormatOptionsMessageDestroy(reportCameraFormatOptionsMessage2);
		}
	}
	reportCameraFormatOptionsMessageDestroy(reportCameraFormatOptionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportCameraPoseMessage\n");
	reportCameraPoseMessage1 = reportCameraPoseMessageCreate();
	jausMessage = reportCameraPoseMessageToJausMessage(reportCameraPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportCameraPoseMessageToJausMessage failed\n");
	}
	else
	{
		reportCameraPoseMessage2 = reportCameraPoseMessageFromJausMessage(jausMessage);
		if(reportCameraPoseMessage2 == NULL)
		{
			printf("reportCameraPoseMessageFromJausMessage failed\n");
		}
		else
		{
			reportCameraPoseMessageDestroy(reportCameraPoseMessage2);
		}
	}
	reportCameraPoseMessageDestroy(reportCameraPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportComponentAuthorityMessage\n");
	reportComponentAuthorityMessage1 = reportComponentAuthorityMessageCreate();
	jausMessage = reportComponentAuthorityMessageToJausMessage(reportComponentAuthorityMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportComponentAuthorityMessageToJausMessage failed\n");
	}
	else
	{
		reportComponentAuthorityMessage2 = reportComponentAuthorityMessageFromJausMessage(jausMessage);
		if(reportComponentAuthorityMessage2 == NULL)
		{
			printf("reportComponentAuthorityMessageFromJausMessage failed\n");
		}
		else
		{
			reportComponentAuthorityMessageDestroy(reportComponentAuthorityMessage2);
		}
	}
	reportComponentAuthorityMessageDestroy(reportComponentAuthorityMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportComponentControlMessage\n");
	reportComponentControlMessage1 = reportComponentControlMessageCreate();
	jausMessage = reportComponentControlMessageToJausMessage(reportComponentControlMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		reportComponentControlMessage2 = reportComponentControlMessageFromJausMessage(jausMessage);
		if(reportComponentControlMessage2 == NULL)
		{
			printf("reportComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			reportComponentControlMessageDestroy(reportComponentControlMessage2);
		}
	}
	reportComponentControlMessageDestroy(reportComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportComponentStatusMessage\n");
	reportComponentStatusMessage1 = reportComponentStatusMessageCreate();
	jausMessage = reportComponentStatusMessageToJausMessage(reportComponentStatusMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportComponentStatusMessageToJausMessage failed\n");
	}
	else
	{
		reportComponentStatusMessage2 = reportComponentStatusMessageFromJausMessage(jausMessage);
		if(reportComponentStatusMessage2 == NULL)
		{
			printf("reportComponentStatusMessageFromJausMessage failed\n");
		}
		else
		{
			reportComponentStatusMessageDestroy(reportComponentStatusMessage2);
		}
	}
	reportComponentStatusMessageDestroy(reportComponentStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportConfigurationMessage\n");
	reportConfigurationMessage1 = reportConfigurationMessageCreate();
	jausMessage = reportConfigurationMessageToJausMessage(reportConfigurationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportConfigurationMessageToJausMessage failed\n");
	}
	else
	{
		reportConfigurationMessage2 = reportConfigurationMessageFromJausMessage(jausMessage);
		if(reportConfigurationMessage2 == NULL)
		{
			printf("reportConfigurationMessageFromJausMessage failed\n");
		}
		else
		{
			reportConfigurationMessageDestroy(reportConfigurationMessage2);
		}
	}
	reportConfigurationMessageDestroy(reportConfigurationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportDataLinkStatusMessage\n");
	reportDataLinkStatusMessage1 = reportDataLinkStatusMessageCreate();
	jausMessage = reportDataLinkStatusMessageToJausMessage(reportDataLinkStatusMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportDataLinkStatusMessageToJausMessage failed\n");
	}
	else
	{
		reportDataLinkStatusMessage2 = reportDataLinkStatusMessageFromJausMessage(jausMessage);
		if(reportDataLinkStatusMessage2 == NULL)
		{
			printf("reportDataLinkStatusMessageFromJausMessage failed\n");
		}
		else
		{
			reportDataLinkStatusMessageDestroy(reportDataLinkStatusMessage2);
		}
	}
	reportDataLinkStatusMessageDestroy(reportDataLinkStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportDiscreteDevicesMessage\n");
	reportDiscreteDevicesMessage1 = reportDiscreteDevicesMessageCreate();
	jausMessage = reportDiscreteDevicesMessageToJausMessage(reportDiscreteDevicesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportDiscreteDevicesMessageToJausMessage failed\n");
	}
	else
	{
		reportDiscreteDevicesMessage2 = reportDiscreteDevicesMessageFromJausMessage(jausMessage);
		if(reportDiscreteDevicesMessage2 == NULL)
		{
			printf("reportDiscreteDevicesMessageFromJausMessage failed\n");
		}
		else
		{
			reportDiscreteDevicesMessageDestroy(reportDiscreteDevicesMessage2);
		}
	}
	reportDiscreteDevicesMessageDestroy(reportDiscreteDevicesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportEventsMessage\n");
	reportEventsMessage1 = reportEventsMessageCreate();
	jausMessage = reportEventsMessageToJausMessage(reportEventsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportEventsMessageToJausMessage failed\n");
	}
	else
	{
		reportEventsMessage2 = reportEventsMessageFromJausMessage(jausMessage);
		if(reportEventsMessage2 == NULL)
		{
			printf("reportEventsMessageFromJausMessage failed\n");
		}
		else
		{
			reportEventsMessageDestroy(reportEventsMessage2);
		}
	}
	reportEventsMessageDestroy(reportEventsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportGlobalPathSegmentMessage\n");
	reportGlobalPathSegmentMessage1 = reportGlobalPathSegmentMessageCreate();
	jausMessage = reportGlobalPathSegmentMessageToJausMessage(reportGlobalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportGlobalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		reportGlobalPathSegmentMessage2 = reportGlobalPathSegmentMessageFromJausMessage(jausMessage);
		if(reportGlobalPathSegmentMessage2 == NULL)
		{
			printf("reportGlobalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			reportGlobalPathSegmentMessageDestroy(reportGlobalPathSegmentMessage2);
		}
	}
	reportGlobalPathSegmentMessageDestroy(reportGlobalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportGlobalPoseMessage\n");
	reportGlobalPoseMessage1 = reportGlobalPoseMessageCreate();
	jausMessage = reportGlobalPoseMessageToJausMessage(reportGlobalPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportGlobalPoseMessageToJausMessage failed\n");
	}
	else
	{
		reportGlobalPoseMessage2 = reportGlobalPoseMessageFromJausMessage(jausMessage);
		if(reportGlobalPoseMessage2 == NULL)
		{
			printf("reportGlobalPoseMessageFromJausMessage failed\n");
		}
		else
		{
			reportGlobalPoseMessageDestroy(reportGlobalPoseMessage2);
		}
	}
	reportGlobalPoseMessageDestroy(reportGlobalPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportGlobalVectorMessage\n");
	reportGlobalVectorMessage1 = reportGlobalVectorMessageCreate();
	jausMessage = reportGlobalVectorMessageToJausMessage(reportGlobalVectorMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportGlobalVectorMessageToJausMessage failed\n");
	}
	else
	{
		reportGlobalVectorMessage2 = reportGlobalVectorMessageFromJausMessage(jausMessage);
		if(reportGlobalVectorMessage2 == NULL)
		{
			printf("reportGlobalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			reportGlobalVectorMessageDestroy(reportGlobalVectorMessage2);
		}
	}
	reportGlobalVectorMessageDestroy(reportGlobalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportGlobalWaypointMessage\n");
	reportGlobalWaypointMessage1 = reportGlobalWaypointMessageCreate();
	jausMessage = reportGlobalWaypointMessageToJausMessage(reportGlobalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportGlobalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		reportGlobalWaypointMessage2 = reportGlobalWaypointMessageFromJausMessage(jausMessage);
		if(reportGlobalWaypointMessage2 == NULL)
		{
			printf("reportGlobalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			reportGlobalWaypointMessageDestroy(reportGlobalWaypointMessage2);
		}
	}
	reportGlobalWaypointMessageDestroy(reportGlobalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportHeartbeatPulseMessage\n");
	reportHeartbeatPulseMessage1 = reportHeartbeatPulseMessageCreate();
	jausMessage = reportHeartbeatPulseMessageToJausMessage(reportHeartbeatPulseMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("reportHeartbeatPulseMessageToJausMessage failed\n");
	}
	else
	{
		reportHeartbeatPulseMessage2 = reportHeartbeatPulseMessageFromJausMessage(jausMessage);
		if(reportHeartbeatPulseMessage2 == NULL)
		{
			printf("reportHeartbeatPulseMessageFromJausMessage failed\n");
		}
		else
		{
			reportHeartbeatPulseMessageDestroy(reportHeartbeatPulseMessage2);
		}
	}
	reportHeartbeatPulseMessageDestroy(reportHeartbeatPulseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportIdentificationMessage\n");
	reportIdentificationMessage1 = reportIdentificationMessageCreate();
	jausMessage = reportIdentificationMessageToJausMessage(reportIdentificationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportIdentificationMessageToJausMessage failed\n");
	}
	else
	{
		reportIdentificationMessage2 = reportIdentificationMessageFromJausMessage(jausMessage);
		if(reportIdentificationMessage2 == NULL)
		{
			printf("reportIdentificationMessageFromJausMessage failed\n");
		}
		else
		{
			reportIdentificationMessageDestroy(reportIdentificationMessage2);
		}
	}
	reportIdentificationMessageDestroy(reportIdentificationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportImageMessage\n");
	reportImageMessage1 = reportImageMessageCreate();
	jausMessage = reportImageMessageToJausMessage(reportImageMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportImageMessageToJausMessage failed\n");
	}
	else
	{
		reportImageMessage2 = reportImageMessageFromJausMessage(jausMessage);
		if(reportImageMessage2 == NULL)
		{
			printf("reportImageMessageFromJausMessage failed\n");
		}
		else
		{
			reportImageMessageDestroy(reportImageMessage2);
		}
	}
	reportImageMessageDestroy(reportImageMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportJointEffortsMessage\n");
	reportJointEffortsMessage1 = reportJointEffortsMessageCreate();
	jausMessage = reportJointEffortsMessageToJausMessage(reportJointEffortsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportJointEffortsMessageToJausMessage failed\n");
	}
	else
	{
		reportJointEffortsMessage2 = reportJointEffortsMessageFromJausMessage(jausMessage);
		if(reportJointEffortsMessage2 == NULL)
		{
			printf("reportJointEffortsMessageFromJausMessage failed\n");
		}
		else
		{
			reportJointEffortsMessageDestroy(reportJointEffortsMessage2);
		}
	}
	reportJointEffortsMessageDestroy(reportJointEffortsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportJointForceTorquesMessage\n");
	reportJointForceTorquesMessage1 = reportJointForceTorquesMessageCreate();
	jausMessage = reportJointForceTorquesMessageToJausMessage(reportJointForceTorquesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportJointForceTorquesMessageToJausMessage failed\n");
	}
	else
	{
		reportJointForceTorquesMessage2 = reportJointForceTorquesMessageFromJausMessage(jausMessage);
		if(reportJointForceTorquesMessage2 == NULL)
		{
			printf("reportJointForceTorquesMessageFromJausMessage failed\n");
		}
		else
		{
			reportJointForceTorquesMessageDestroy(reportJointForceTorquesMessage2);
		}
	}
	reportJointForceTorquesMessageDestroy(reportJointForceTorquesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportJointPositionsMessage\n");
	reportJointPositionsMessage1 = reportJointPositionsMessageCreate();
	jausMessage = reportJointPositionsMessageToJausMessage(reportJointPositionsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportJointPositionsMessageToJausMessage failed\n");
	}
	else
	{
		reportJointPositionsMessage2 = reportJointPositionsMessageFromJausMessage(jausMessage);
		if(reportJointPositionsMessage2 == NULL)
		{
			printf("reportJointPositionsMessageFromJausMessage failed\n");
		}
		else
		{
			reportJointPositionsMessageDestroy(reportJointPositionsMessage2);
		}
	}
	reportJointPositionsMessageDestroy(reportJointPositionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportJointVelocitiesMessage\n");
	reportJointVelocitiesMessage1 = reportJointVelocitiesMessageCreate();
	jausMessage = reportJointVelocitiesMessageToJausMessage(reportJointVelocitiesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportJointVelocitiesMessageToJausMessage failed\n");
	}
	else
	{
		reportJointVelocitiesMessage2 = reportJointVelocitiesMessageFromJausMessage(jausMessage);
		if(reportJointVelocitiesMessage2 == NULL)
		{
			printf("reportJointVelocitiesMessageFromJausMessage failed\n");
		}
		else
		{
			reportJointVelocitiesMessageDestroy(reportJointVelocitiesMessage2);
		}
	}
	reportJointVelocitiesMessageDestroy(reportJointVelocitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportLocalPathSegmentMessage\n");
	reportLocalPathSegmentMessage1 = reportLocalPathSegmentMessageCreate();
	jausMessage = reportLocalPathSegmentMessageToJausMessage(reportLocalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportLocalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		reportLocalPathSegmentMessage2 = reportLocalPathSegmentMessageFromJausMessage(jausMessage);
		if(reportLocalPathSegmentMessage2 == NULL)
		{
			printf("reportLocalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			reportLocalPathSegmentMessageDestroy(reportLocalPathSegmentMessage2);
		}
	}
	reportLocalPathSegmentMessageDestroy(reportLocalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportLocalPoseMessage\n");
	reportLocalPoseMessage1 = reportLocalPoseMessageCreate();
	jausMessage = reportLocalPoseMessageToJausMessage(reportLocalPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportLocalPoseMessageToJausMessage failed\n");
	}
	else
	{
		reportLocalPoseMessage2 = reportLocalPoseMessageFromJausMessage(jausMessage);
		if(reportLocalPoseMessage2 == NULL)
		{
			printf("reportLocalPoseMessageFromJausMessage failed\n");
		}
		else
		{
			reportLocalPoseMessageDestroy(reportLocalPoseMessage2);
		}
	}
	reportLocalPoseMessageDestroy(reportLocalPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportLocalVectorMessage\n");
	reportLocalVectorMessage1 = reportLocalVectorMessageCreate();
	jausMessage = reportLocalVectorMessageToJausMessage(reportLocalVectorMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportLocalVectorMessageToJausMessage failed\n");
	}
	else
	{
		reportLocalVectorMessage2 = reportLocalVectorMessageFromJausMessage(jausMessage);
		if(reportLocalVectorMessage2 == NULL)
		{
			printf("reportLocalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			reportLocalVectorMessageDestroy(reportLocalVectorMessage2);
		}
	}
	reportLocalVectorMessageDestroy(reportLocalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportLocalWaypointMessage\n");
	reportLocalWaypointMessage1 = reportLocalWaypointMessageCreate();
	jausMessage = reportLocalWaypointMessageToJausMessage(reportLocalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportLocalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		reportLocalWaypointMessage2 = reportLocalWaypointMessageFromJausMessage(jausMessage);
		if(reportLocalWaypointMessage2 == NULL)
		{
			printf("reportLocalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			reportLocalWaypointMessageDestroy(reportLocalWaypointMessage2);
		}
	}
	reportLocalWaypointMessageDestroy(reportLocalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportManipulatorSpecificationsMessage\n");
	reportManipulatorSpecificationsMessage1 = reportManipulatorSpecificationsMessageCreate();
	jausMessage = reportManipulatorSpecificationsMessageToJausMessage(reportManipulatorSpecificationsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportManipulatorSpecificationsMessageToJausMessage failed\n");
	}
	else
	{
		reportManipulatorSpecificationsMessage2 = reportManipulatorSpecificationsMessageFromJausMessage(jausMessage);
		if(reportManipulatorSpecificationsMessage2 == NULL)
		{
			printf("reportManipulatorSpecificationsMessageFromJausMessage failed\n");
		}
		else
		{
			reportManipulatorSpecificationsMessageDestroy(reportManipulatorSpecificationsMessage2);
		}
	}
	reportManipulatorSpecificationsMessageDestroy(reportManipulatorSpecificationsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportPathSegmentCountMessage\n");
	reportPathSegmentCountMessage1 = reportPathSegmentCountMessageCreate();
	jausMessage = reportPathSegmentCountMessageToJausMessage(reportPathSegmentCountMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPathSegmentCountMessageToJausMessage failed\n");
	}
	else
	{
		reportPathSegmentCountMessage2 = reportPathSegmentCountMessageFromJausMessage(jausMessage);
		if(reportPathSegmentCountMessage2 == NULL)
		{
			printf("reportPathSegmentCountMessageFromJausMessage failed\n");
		}
		else
		{
			reportPathSegmentCountMessageDestroy(reportPathSegmentCountMessage2);
		}
	}
	reportPathSegmentCountMessageDestroy(reportPathSegmentCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportPayloadDataElementMessage\n");
	reportPayloadDataElementMessage1 = reportPayloadDataElementMessageCreate();
	jausMessage = reportPayloadDataElementMessageToJausMessage(reportPayloadDataElementMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPayloadDataElementMessageToJausMessage failed\n");
	}
	else
	{
		reportPayloadDataElementMessage2 = reportPayloadDataElementMessageFromJausMessage(jausMessage);
		if(reportPayloadDataElementMessage2 == NULL)
		{
			printf("reportPayloadDataElementMessageFromJausMessage failed\n");
		}
		else
		{
			reportPayloadDataElementMessageDestroy(reportPayloadDataElementMessage2);
		}
	}
	reportPayloadDataElementMessageDestroy(reportPayloadDataElementMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportPayloadInterfaceMessage\n");
	reportPayloadInterfaceMessage1 = reportPayloadInterfaceMessageCreate();
	jausMessage = reportPayloadInterfaceMessageToJausMessage(reportPayloadInterfaceMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPayloadInterfaceMessageToJausMessage failed\n");
	}
	else
	{
		reportPayloadInterfaceMessage2 = reportPayloadInterfaceMessageFromJausMessage(jausMessage);
		if(reportPayloadInterfaceMessage2 == NULL)
		{
			printf("reportPayloadInterfaceMessageFromJausMessage failed\n");
		}
		else
		{
			reportPayloadInterfaceMessageDestroy(reportPayloadInterfaceMessage2);
		}
	}
	reportPayloadInterfaceMessageDestroy(reportPayloadInterfaceMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportPlatformOperationalDataMessage\n");
	reportPlatformOperationalDataMessage1 = reportPlatformOperationalDataMessageCreate();
	jausMessage = reportPlatformOperationalDataMessageToJausMessage(reportPlatformOperationalDataMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPlatformOperationalDataMessageToJausMessage failed\n");
	}
	else
	{
		reportPlatformOperationalDataMessage2 = reportPlatformOperationalDataMessageFromJausMessage(jausMessage);
		if(reportPlatformOperationalDataMessage2 == NULL)
		{
			printf("reportPlatformOperationalDataMessageFromJausMessage failed\n");
		}
		else
		{
			reportPlatformOperationalDataMessageDestroy(reportPlatformOperationalDataMessage2);
		}
	}
	reportPlatformOperationalDataMessageDestroy(reportPlatformOperationalDataMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportPlatformSpecificationsMessage\n");
	reportPlatformSpecificationsMessage1 = reportPlatformSpecificationsMessageCreate();
	jausMessage = reportPlatformSpecificationsMessageToJausMessage(reportPlatformSpecificationsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPlatformSpecificationsMessageToJausMessage failed\n");
	}
	else
	{
		reportPlatformSpecificationsMessage2 = reportPlatformSpecificationsMessageFromJausMessage(jausMessage);
		if(reportPlatformSpecificationsMessage2 == NULL)
		{
			printf("reportPlatformSpecificationsMessageFromJausMessage failed\n");
		}
		else
		{
			reportPlatformSpecificationsMessageDestroy(reportPlatformSpecificationsMessage2);
		}
	}
	reportPlatformSpecificationsMessageDestroy(reportPlatformSpecificationsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportRelativeObjectPositionMessage\n");
	reportRelativeObjectPositionMessage1 = reportRelativeObjectPositionMessageCreate();
	jausMessage = reportRelativeObjectPositionMessageToJausMessage(reportRelativeObjectPositionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportRelativeObjectPositionMessageToJausMessage failed\n");
	}
	else
	{
		reportRelativeObjectPositionMessage2 = reportRelativeObjectPositionMessageFromJausMessage(jausMessage);
		if(reportRelativeObjectPositionMessage2 == NULL)
		{
			printf("reportRelativeObjectPositionMessageFromJausMessage failed\n");
		}
		else
		{
			reportRelativeObjectPositionMessageDestroy(reportRelativeObjectPositionMessage2);
		}
	}
	reportRelativeObjectPositionMessageDestroy(reportRelativeObjectPositionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportSelectedCameraMessage\n");
	reportSelectedCameraMessage1 = reportSelectedCameraMessageCreate();
	jausMessage = reportSelectedCameraMessageToJausMessage(reportSelectedCameraMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportSelectedCameraMessageToJausMessage failed\n");
	}
	else
	{
		reportSelectedCameraMessage2 = reportSelectedCameraMessageFromJausMessage(jausMessage);
		if(reportSelectedCameraMessage2 == NULL)
		{
			printf("reportSelectedCameraMessageFromJausMessage failed\n");
		}
		else
		{
			reportSelectedCameraMessageDestroy(reportSelectedCameraMessage2);
		}
	}
	reportSelectedCameraMessageDestroy(reportSelectedCameraMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportSelectedDataLinkStatusMessage\n");
	reportSelectedDataLinkStatusMessage1 = reportSelectedDataLinkStatusMessageCreate();
	jausMessage = reportSelectedDataLinkStatusMessageToJausMessage(reportSelectedDataLinkStatusMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportSelectedDataLinkStatusMessageToJausMessage failed\n");
	}
	else
	{
		reportSelectedDataLinkStatusMessage2 = reportSelectedDataLinkStatusMessageFromJausMessage(jausMessage);
		if(reportSelectedDataLinkStatusMessage2 == NULL)
		{
			printf("reportSelectedDataLinkStatusMessageFromJausMessage failed\n");
		}
		else
		{
			reportSelectedDataLinkStatusMessageDestroy(reportSelectedDataLinkStatusMessage2);
		}
	}
	reportSelectedDataLinkStatusMessageDestroy(reportSelectedDataLinkStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportServicesMessage\n");
	reportServicesMessage1 = reportServicesMessageCreate();
	jausMessage = reportServicesMessageToJausMessage(reportServicesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportServicesMessageToJausMessage failed\n");
	}
	else
	{
		reportServicesMessage2 = reportServicesMessageFromJausMessage(jausMessage);
		if(reportServicesMessage2 == NULL)
		{
			printf("reportServicesMessageFromJausMessage failed\n");
		}
		else
		{
			reportServicesMessageDestroy(reportServicesMessage2);
		}
	}
	reportServicesMessageDestroy(reportServicesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportSubsystemListMessage\n");
	reportSubsystemListMessage1 = reportSubsystemListMessageCreate();
	jausMessage = reportSubsystemListMessageToJausMessage(reportSubsystemListMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportSubsystemListMessageToJausMessage failed\n");
	}
	else
	{
		reportSubsystemListMessage2 = reportSubsystemListMessageFromJausMessage(jausMessage);
		if(reportSubsystemListMessage2 == NULL)
		{
			printf("reportSubsystemListMessageFromJausMessage failed\n");
		}
		else
		{
			reportSubsystemListMessageDestroy(reportSubsystemListMessage2);
		}
	}
	reportSubsystemListMessageDestroy(reportSubsystemListMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportTimeMessage\n");
	reportTimeMessage1 = reportTimeMessageCreate();
	jausMessage = reportTimeMessageToJausMessage(reportTimeMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportTimeMessageToJausMessage failed\n");
	}
	else
	{
		reportTimeMessage2 = reportTimeMessageFromJausMessage(jausMessage);
		if(reportTimeMessage2 == NULL)
		{
			printf("reportTimeMessageFromJausMessage failed\n");
		}
		else
		{
			reportTimeMessageDestroy(reportTimeMessage2);
		}
	}
	reportTimeMessageDestroy(reportTimeMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportToolPointMessage\n");
	reportToolPointMessage1 = reportToolPointMessageCreate();
	jausMessage = reportToolPointMessageToJausMessage(reportToolPointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportToolPointMessageToJausMessage failed\n");
	}
	else
	{
		reportToolPointMessage2 = reportToolPointMessageFromJausMessage(jausMessage);
		if(reportToolPointMessage2 == NULL)
		{
			printf("reportToolPointMessageFromJausMessage failed\n");
		}
		else
		{
			reportToolPointMessageDestroy(reportToolPointMessage2);
		}
	}
	reportToolPointMessageDestroy(reportToolPointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportTravelSpeedMessage\n");
	reportTravelSpeedMessage1 = reportTravelSpeedMessageCreate();
	jausMessage = reportTravelSpeedMessageToJausMessage(reportTravelSpeedMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportTravelSpeedMessageToJausMessage failed\n");
	}
	else
	{
		reportTravelSpeedMessage2 = reportTravelSpeedMessageFromJausMessage(jausMessage);
		if(reportTravelSpeedMessage2 == NULL)
		{
			printf("reportTravelSpeedMessageFromJausMessage failed\n");
		}
		else
		{
			reportTravelSpeedMessageDestroy(reportTravelSpeedMessage2);
		}
	}
	reportTravelSpeedMessageDestroy(reportTravelSpeedMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVelocityStateMessage\n");
	reportVelocityStateMessage1 = reportVelocityStateMessageCreate();
	jausMessage = reportVelocityStateMessageToJausMessage(reportVelocityStateMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVelocityStateMessageToJausMessage failed\n");
	}
	else
	{
		reportVelocityStateMessage2 = reportVelocityStateMessageFromJausMessage(jausMessage);
		if(reportVelocityStateMessage2 == NULL)
		{
			printf("reportVelocityStateMessageFromJausMessage failed\n");
		}
		else
		{
			reportVelocityStateMessageDestroy(reportVelocityStateMessage2);
		}
	}
	reportVelocityStateMessageDestroy(reportVelocityStateMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVksBoundsMessage\n");
	reportVksBoundsMessage1 = reportVksBoundsMessageCreate();
	jausMessage = reportVksBoundsMessageToJausMessage(reportVksBoundsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVksBoundsMessageToJausMessage failed\n");
	}
	else
	{
		reportVksBoundsMessage2 = reportVksBoundsMessageFromJausMessage(jausMessage);
		if(reportVksBoundsMessage2 == NULL)
		{
			printf("reportVksBoundsMessageFromJausMessage failed\n");
		}
		else
		{
			reportVksBoundsMessageDestroy(reportVksBoundsMessage2);
		}
	}
	reportVksBoundsMessageDestroy(reportVksBoundsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVksDataTransferTerminationMessage\n");
	reportVksDataTransferTerminationMessage1 = reportVksDataTransferTerminationMessageCreate();
	jausMessage = reportVksDataTransferTerminationMessageToJausMessage(reportVksDataTransferTerminationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVksDataTransferTerminationMessageToJausMessage failed\n");
	}
	else
	{
		reportVksDataTransferTerminationMessage2 = reportVksDataTransferTerminationMessageFromJausMessage(jausMessage);
		if(reportVksDataTransferTerminationMessage2 == NULL)
		{
			printf("reportVksDataTransferTerminationMessageFromJausMessage failed\n");
		}
		else
		{
			reportVksDataTransferTerminationMessageDestroy(reportVksDataTransferTerminationMessage2);
		}
	}
	reportVksDataTransferTerminationMessageDestroy(reportVksDataTransferTerminationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVksFeatureClassMetadataMessage\n");
	reportVksFeatureClassMetadataMessage1 = reportVksFeatureClassMetadataMessageCreate();
	jausMessage = reportVksFeatureClassMetadataMessageToJausMessage(reportVksFeatureClassMetadataMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVksFeatureClassMetadataMessageToJausMessage failed\n");
	}
	else
	{
		reportVksFeatureClassMetadataMessage2 = reportVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
		if(reportVksFeatureClassMetadataMessage2 == NULL)
		{
			printf("reportVksFeatureClassMetadataMessageFromJausMessage failed\n");
		}
		else
		{
			reportVksFeatureClassMetadataMessageDestroy(reportVksFeatureClassMetadataMessage2);
		}
	}
	reportVksFeatureClassMetadataMessageDestroy(reportVksFeatureClassMetadataMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVksObjectsCreationMessage\n");
	reportVksObjectsCreationMessage1 = reportVksObjectsCreationMessageCreate();
	jausMessage = reportVksObjectsCreationMessageToJausMessage(reportVksObjectsCreationMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVksObjectsCreationMessageToJausMessage failed\n");
	}
	else
	{
		reportVksObjectsCreationMessage2 = reportVksObjectsCreationMessageFromJausMessage(jausMessage);
		if(reportVksObjectsCreationMessage2 == NULL)
		{
			printf("reportVksObjectsCreationMessageFromJausMessage failed\n");
		}
		else
		{
			reportVksObjectsCreationMessageDestroy(reportVksObjectsCreationMessage2);
		}
	}
	reportVksObjectsCreationMessageDestroy(reportVksObjectsCreationMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportVksObjectsMessage\n");
	reportVksObjectsMessage1 = reportVksObjectsMessageCreate();
	jausMessage = reportVksObjectsMessageToJausMessage(reportVksObjectsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportVksObjectsMessageToJausMessage failed\n");
	}
	else
	{
		reportVksObjectsMessage2 = reportVksObjectsMessageFromJausMessage(jausMessage);
		if(reportVksObjectsMessage2 == NULL)
		{
			printf("reportVksObjectsMessageFromJausMessage failed\n");
		}
		else
		{
			reportVksObjectsMessageDestroy(reportVksObjectsMessage2);
		}
	}
	reportVksObjectsMessageDestroy(reportVksObjectsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportWaypointCountMessage\n");
	reportWaypointCountMessage1 = reportWaypointCountMessageCreate();
	jausMessage = reportWaypointCountMessageToJausMessage(reportWaypointCountMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportWaypointCountMessageToJausMessage failed\n");
	}
	else
	{
		reportWaypointCountMessage2 = reportWaypointCountMessageFromJausMessage(jausMessage);
		if(reportWaypointCountMessage2 == NULL)
		{
			printf("reportWaypointCountMessageFromJausMessage failed\n");
		}
		else
		{
			reportWaypointCountMessageDestroy(reportWaypointCountMessage2);
		}
	}
	reportWaypointCountMessageDestroy(reportWaypointCountMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ReportWrenchEffortMessage\n");
	reportWrenchEffortMessage1 = reportWrenchEffortMessageCreate();
	jausMessage = reportWrenchEffortMessageToJausMessage(reportWrenchEffortMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("reportWrenchEffortMessageToJausMessage failed\n");
	}
	else
	{
		reportWrenchEffortMessage2 = reportWrenchEffortMessageFromJausMessage(jausMessage);
		if(reportWrenchEffortMessage2 == NULL)
		{
			printf("reportWrenchEffortMessageFromJausMessage failed\n");
		}
		else
		{
			reportWrenchEffortMessageDestroy(reportWrenchEffortMessage2);
		}
	}
	reportWrenchEffortMessageDestroy(reportWrenchEffortMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing RequestComponentControlMessage\n");
	requestComponentControlMessage1 = requestComponentControlMessageCreate();
	jausMessage = requestComponentControlMessageToJausMessage(requestComponentControlMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("requestComponentControlMessageToJausMessage failed\n");
	}
	else
	{
		requestComponentControlMessage2 = requestComponentControlMessageFromJausMessage(jausMessage);
		if(requestComponentControlMessage2 == NULL)
		{
			printf("requestComponentControlMessageFromJausMessage failed\n");
		}
		else
		{
			requestComponentControlMessageDestroy(requestComponentControlMessage2);
		}
	}
	requestComponentControlMessageDestroy(requestComponentControlMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ResetMessage\n");
	resetMessage1 = resetMessageCreate();
	jausMessage = resetMessageToJausMessage(resetMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("resetMessageToJausMessage failed\n");
	}
	else
	{
		resetMessage2 = resetMessageFromJausMessage(jausMessage);
		if(resetMessage2 == NULL)
		{
			printf("resetMessageFromJausMessage failed\n");
		}
		else
		{
			resetMessageDestroy(resetMessage2);
		}
	}
	resetMessageDestroy(resetMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ResumeMessage\n");
	resumeMessage1 = resumeMessageCreate();
	jausMessage = resumeMessageToJausMessage(resumeMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("resumeMessageToJausMessage failed\n");
	}
	else
	{
		resumeMessage2 = resumeMessageFromJausMessage(jausMessage);
		if(resumeMessage2 == NULL)
		{
			printf("resumeMessageFromJausMessage failed\n");
		}
		else
		{
			resumeMessageDestroy(resumeMessage2);
		}
	}
	resumeMessageDestroy(resumeMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SelectCameraMessage\n");
	selectCameraMessage1 = selectCameraMessageCreate();
	jausMessage = selectCameraMessageToJausMessage(selectCameraMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("selectCameraMessageToJausMessage failed\n");
	}
	else
	{
		selectCameraMessage2 = selectCameraMessageFromJausMessage(jausMessage);
		if(selectCameraMessage2 == NULL)
		{
			printf("selectCameraMessageFromJausMessage failed\n");
		}
		else
		{
			selectCameraMessageDestroy(selectCameraMessage2);
		}
	}
	selectCameraMessageDestroy(selectCameraMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetCameraCapabilitiesMessage\n");
	setCameraCapabilitiesMessage1 = setCameraCapabilitiesMessageCreate();
	jausMessage = setCameraCapabilitiesMessageToJausMessage(setCameraCapabilitiesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setCameraCapabilitiesMessageToJausMessage failed\n");
	}
	else
	{
		setCameraCapabilitiesMessage2 = setCameraCapabilitiesMessageFromJausMessage(jausMessage);
		if(setCameraCapabilitiesMessage2 == NULL)
		{
			printf("setCameraCapabilitiesMessageFromJausMessage failed\n");
		}
		else
		{
			setCameraCapabilitiesMessageDestroy(setCameraCapabilitiesMessage2);
		}
	}
	setCameraCapabilitiesMessageDestroy(setCameraCapabilitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetCameraFormatOptionsMessage\n");
	setCameraFormatOptionsMessage1 = setCameraFormatOptionsMessageCreate();
	jausMessage = setCameraFormatOptionsMessageToJausMessage(setCameraFormatOptionsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setCameraFormatOptionsMessageToJausMessage failed\n");
	}
	else
	{
		setCameraFormatOptionsMessage2 = setCameraFormatOptionsMessageFromJausMessage(jausMessage);
		if(setCameraFormatOptionsMessage2 == NULL)
		{
			printf("setCameraFormatOptionsMessageFromJausMessage failed\n");
		}
		else
		{
			setCameraFormatOptionsMessageDestroy(setCameraFormatOptionsMessage2);
		}
	}
	setCameraFormatOptionsMessageDestroy(setCameraFormatOptionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetCameraPoseMessage\n");
	setCameraPoseMessage1 = setCameraPoseMessageCreate();
	jausMessage = setCameraPoseMessageToJausMessage(setCameraPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setCameraPoseMessageToJausMessage failed\n");
	}
	else
	{
		setCameraPoseMessage2 = setCameraPoseMessageFromJausMessage(jausMessage);
		if(setCameraPoseMessage2 == NULL)
		{
			printf("setCameraPoseMessageFromJausMessage failed\n");
		}
		else
		{
			setCameraPoseMessageDestroy(setCameraPoseMessage2);
		}
	}
	setCameraPoseMessageDestroy(setCameraPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetComponentAuthorityMessage\n");
	setComponentAuthorityMessage1 = setComponentAuthorityMessageCreate();
	jausMessage = setComponentAuthorityMessageToJausMessage(setComponentAuthorityMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setComponentAuthorityMessageToJausMessage failed\n");
	}
	else
	{
		setComponentAuthorityMessage2 = setComponentAuthorityMessageFromJausMessage(jausMessage);
		if(setComponentAuthorityMessage2 == NULL)
		{
			printf("setComponentAuthorityMessageFromJausMessage failed\n");
		}
		else
		{
			setComponentAuthorityMessageDestroy(setComponentAuthorityMessage2);
		}
	}
	setComponentAuthorityMessageDestroy(setComponentAuthorityMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetDataLinkSelectMessage\n");
	setDataLinkSelectMessage1 = setDataLinkSelectMessageCreate();
	jausMessage = setDataLinkSelectMessageToJausMessage(setDataLinkSelectMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setDataLinkSelectMessageToJausMessage failed\n");
	}
	else
	{
		setDataLinkSelectMessage2 = setDataLinkSelectMessageFromJausMessage(jausMessage);
		if(setDataLinkSelectMessage2 == NULL)
		{
			printf("setDataLinkSelectMessageFromJausMessage failed\n");
		}
		else
		{
			setDataLinkSelectMessageDestroy(setDataLinkSelectMessage2);
		}
	}
	setDataLinkSelectMessageDestroy(setDataLinkSelectMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetDataLinkStatusMessage\n");
	setDataLinkStatusMessage1 = setDataLinkStatusMessageCreate();
	jausMessage = setDataLinkStatusMessageToJausMessage(setDataLinkStatusMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setDataLinkStatusMessageToJausMessage failed\n");
	}
	else
	{
		setDataLinkStatusMessage2 = setDataLinkStatusMessageFromJausMessage(jausMessage);
		if(setDataLinkStatusMessage2 == NULL)
		{
			printf("setDataLinkStatusMessageFromJausMessage failed\n");
		}
		else
		{
			setDataLinkStatusMessageDestroy(setDataLinkStatusMessage2);
		}
	}
	setDataLinkStatusMessageDestroy(setDataLinkStatusMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetDiscreteDevicesMessage\n");
	setDiscreteDevicesMessage1 = setDiscreteDevicesMessageCreate();
	jausMessage = setDiscreteDevicesMessageToJausMessage(setDiscreteDevicesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setDiscreteDevicesMessageToJausMessage failed\n");
	}
	else
	{
		setDiscreteDevicesMessage2 = setDiscreteDevicesMessageFromJausMessage(jausMessage);
		if(setDiscreteDevicesMessage2 == NULL)
		{
			printf("setDiscreteDevicesMessageFromJausMessage failed\n");
		}
		else
		{
			setDiscreteDevicesMessageDestroy(setDiscreteDevicesMessage2);
		}
	}
	setDiscreteDevicesMessageDestroy(setDiscreteDevicesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetEmergencyMessage\n");
	setEmergencyMessage1 = setEmergencyMessageCreate();
	jausMessage = setEmergencyMessageToJausMessage(setEmergencyMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setEmergencyMessageToJausMessage failed\n");
	}
	else
	{
		setEmergencyMessage2 = setEmergencyMessageFromJausMessage(jausMessage);
		if(setEmergencyMessage2 == NULL)
		{
			printf("setEmergencyMessageFromJausMessage failed\n");
		}
		else
		{
			setEmergencyMessageDestroy(setEmergencyMessage2);
		}
	}
	setEmergencyMessageDestroy(setEmergencyMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetEndEffectorPathMotionMessage\n");
	setEndEffectorPathMotionMessage1 = setEndEffectorPathMotionMessageCreate();
	jausMessage = setEndEffectorPathMotionMessageToJausMessage(setEndEffectorPathMotionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setEndEffectorPathMotionMessageToJausMessage failed\n");
	}
	else
	{
		setEndEffectorPathMotionMessage2 = setEndEffectorPathMotionMessageFromJausMessage(jausMessage);
		if(setEndEffectorPathMotionMessage2 == NULL)
		{
			printf("setEndEffectorPathMotionMessageFromJausMessage failed\n");
		}
		else
		{
			setEndEffectorPathMotionMessageDestroy(setEndEffectorPathMotionMessage2);
		}
	}
	setEndEffectorPathMotionMessageDestroy(setEndEffectorPathMotionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetEndEffectorPoseMessage\n");
	setEndEffectorPoseMessage1 = setEndEffectorPoseMessageCreate();
	jausMessage = setEndEffectorPoseMessageToJausMessage(setEndEffectorPoseMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setEndEffectorPoseMessageToJausMessage failed\n");
	}
	else
	{
		setEndEffectorPoseMessage2 = setEndEffectorPoseMessageFromJausMessage(jausMessage);
		if(setEndEffectorPoseMessage2 == NULL)
		{
			printf("setEndEffectorPoseMessageFromJausMessage failed\n");
		}
		else
		{
			setEndEffectorPoseMessageDestroy(setEndEffectorPoseMessage2);
		}
	}
	setEndEffectorPoseMessageDestroy(setEndEffectorPoseMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetEndEffectorVelocityStateMessage\n");
	setEndEffectorVelocityStateMessage1 = setEndEffectorVelocityStateMessageCreate();
	jausMessage = setEndEffectorVelocityStateMessageToJausMessage(setEndEffectorVelocityStateMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setEndEffectorVelocityStateMessageToJausMessage failed\n");
	}
	else
	{
		setEndEffectorVelocityStateMessage2 = setEndEffectorVelocityStateMessageFromJausMessage(jausMessage);
		if(setEndEffectorVelocityStateMessage2 == NULL)
		{
			printf("setEndEffectorVelocityStateMessageFromJausMessage failed\n");
		}
		else
		{
			setEndEffectorVelocityStateMessageDestroy(setEndEffectorVelocityStateMessage2);
		}
	}
	setEndEffectorVelocityStateMessageDestroy(setEndEffectorVelocityStateMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetGlobalPathSegmentMessage\n");
	setGlobalPathSegmentMessage1 = setGlobalPathSegmentMessageCreate();
	jausMessage = setGlobalPathSegmentMessageToJausMessage(setGlobalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setGlobalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		setGlobalPathSegmentMessage2 = setGlobalPathSegmentMessageFromJausMessage(jausMessage);
		if(setGlobalPathSegmentMessage2 == NULL)
		{
			printf("setGlobalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			setGlobalPathSegmentMessageDestroy(setGlobalPathSegmentMessage2);
		}
	}
	setGlobalPathSegmentMessageDestroy(setGlobalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetGlobalVectorMessage\n");
	setGlobalVectorMessage1 = setGlobalVectorMessageCreate();
	jausMessage = setGlobalVectorMessageToJausMessage(setGlobalVectorMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setGlobalVectorMessageToJausMessage failed\n");
	}
	else
	{
		setGlobalVectorMessage2 = setGlobalVectorMessageFromJausMessage(jausMessage);
		if(setGlobalVectorMessage2 == NULL)
		{
			printf("setGlobalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			setGlobalVectorMessageDestroy(setGlobalVectorMessage2);
		}
	}
	setGlobalVectorMessageDestroy(setGlobalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetGlobalWaypointMessage\n");
	setGlobalWaypointMessage1 = setGlobalWaypointMessageCreate();
	jausMessage = setGlobalWaypointMessageToJausMessage(setGlobalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setGlobalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		setGlobalWaypointMessage2 = setGlobalWaypointMessageFromJausMessage(jausMessage);
		if(setGlobalWaypointMessage2 == NULL)
		{
			printf("setGlobalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			setGlobalWaypointMessageDestroy(setGlobalWaypointMessage2);
		}
	}
	setGlobalWaypointMessageDestroy(setGlobalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetJointEffortsMessage\n");
	setJointEffortsMessage1 = setJointEffortsMessageCreate();
	jausMessage = setJointEffortsMessageToJausMessage(setJointEffortsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setJointEffortsMessageToJausMessage failed\n");
	}
	else
	{
		setJointEffortsMessage2 = setJointEffortsMessageFromJausMessage(jausMessage);
		if(setJointEffortsMessage2 == NULL)
		{
			printf("setJointEffortsMessageFromJausMessage failed\n");
		}
		else
		{
			setJointEffortsMessageDestroy(setJointEffortsMessage2);
		}
	}
	setJointEffortsMessageDestroy(setJointEffortsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetJointMotionMessage\n");
	setJointMotionMessage1 = setJointMotionMessageCreate();
	jausMessage = setJointMotionMessageToJausMessage(setJointMotionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setJointMotionMessageToJausMessage failed\n");
	}
	else
	{
		setJointMotionMessage2 = setJointMotionMessageFromJausMessage(jausMessage);
		if(setJointMotionMessage2 == NULL)
		{
			printf("setJointMotionMessageFromJausMessage failed\n");
		}
		else
		{
			setJointMotionMessageDestroy(setJointMotionMessage2);
		}
	}
	setJointMotionMessageDestroy(setJointMotionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetJointPositionsMessage\n");
	setJointPositionsMessage1 = setJointPositionsMessageCreate();
	jausMessage = setJointPositionsMessageToJausMessage(setJointPositionsMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setJointPositionsMessageToJausMessage failed\n");
	}
	else
	{
		setJointPositionsMessage2 = setJointPositionsMessageFromJausMessage(jausMessage);
		if(setJointPositionsMessage2 == NULL)
		{
			printf("setJointPositionsMessageFromJausMessage failed\n");
		}
		else
		{
			setJointPositionsMessageDestroy(setJointPositionsMessage2);
		}
	}
	setJointPositionsMessageDestroy(setJointPositionsMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetJointVelocitiesMessage\n");
	setJointVelocitiesMessage1 = setJointVelocitiesMessageCreate();
	jausMessage = setJointVelocitiesMessageToJausMessage(setJointVelocitiesMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setJointVelocitiesMessageToJausMessage failed\n");
	}
	else
	{
		setJointVelocitiesMessage2 = setJointVelocitiesMessageFromJausMessage(jausMessage);
		if(setJointVelocitiesMessage2 == NULL)
		{
			printf("setJointVelocitiesMessageFromJausMessage failed\n");
		}
		else
		{
			setJointVelocitiesMessageDestroy(setJointVelocitiesMessage2);
		}
	}
	setJointVelocitiesMessageDestroy(setJointVelocitiesMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetLocalPathSegmentMessage\n");
	setLocalPathSegmentMessage1 = setLocalPathSegmentMessageCreate();
	jausMessage = setLocalPathSegmentMessageToJausMessage(setLocalPathSegmentMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setLocalPathSegmentMessageToJausMessage failed\n");
	}
	else
	{
		setLocalPathSegmentMessage2 = setLocalPathSegmentMessageFromJausMessage(jausMessage);
		if(setLocalPathSegmentMessage2 == NULL)
		{
			printf("setLocalPathSegmentMessageFromJausMessage failed\n");
		}
		else
		{
			setLocalPathSegmentMessageDestroy(setLocalPathSegmentMessage2);
		}
	}
	setLocalPathSegmentMessageDestroy(setLocalPathSegmentMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetLocalVectorMessage\n");
	setLocalVectorMessage1 = setLocalVectorMessageCreate();
	jausMessage = setLocalVectorMessageToJausMessage(setLocalVectorMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setLocalVectorMessageToJausMessage failed\n");
	}
	else
	{
		setLocalVectorMessage2 = setLocalVectorMessageFromJausMessage(jausMessage);
		if(setLocalVectorMessage2 == NULL)
		{
			printf("setLocalVectorMessageFromJausMessage failed\n");
		}
		else
		{
			setLocalVectorMessageDestroy(setLocalVectorMessage2);
		}
	}
	setLocalVectorMessageDestroy(setLocalVectorMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetLocalWaypointMessage\n");
	setLocalWaypointMessage1 = setLocalWaypointMessageCreate();
	jausMessage = setLocalWaypointMessageToJausMessage(setLocalWaypointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setLocalWaypointMessageToJausMessage failed\n");
	}
	else
	{
		setLocalWaypointMessage2 = setLocalWaypointMessageFromJausMessage(jausMessage);
		if(setLocalWaypointMessage2 == NULL)
		{
			printf("setLocalWaypointMessageFromJausMessage failed\n");
		}
		else
		{
			setLocalWaypointMessageDestroy(setLocalWaypointMessage2);
		}
	}
	setLocalWaypointMessageDestroy(setLocalWaypointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetSelectedDataLinkStateMessage\n");
	setSelectedDataLinkStateMessage1 = setSelectedDataLinkStateMessageCreate();
	jausMessage = setSelectedDataLinkStateMessageToJausMessage(setSelectedDataLinkStateMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setSelectedDataLinkStateMessageToJausMessage failed\n");
	}
	else
	{
		setSelectedDataLinkStateMessage2 = setSelectedDataLinkStateMessageFromJausMessage(jausMessage);
		if(setSelectedDataLinkStateMessage2 == NULL)
		{
			printf("setSelectedDataLinkStateMessageFromJausMessage failed\n");
		}
		else
		{
			setSelectedDataLinkStateMessageDestroy(setSelectedDataLinkStateMessage2);
		}
	}
	setSelectedDataLinkStateMessageDestroy(setSelectedDataLinkStateMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetTimeMessage\n");
	setTimeMessage1 = setTimeMessageCreate();
	jausMessage = setTimeMessageToJausMessage(setTimeMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setTimeMessageToJausMessage failed\n");
	}
	else
	{
		setTimeMessage2 = setTimeMessageFromJausMessage(jausMessage);
		if(setTimeMessage2 == NULL)
		{
			printf("setTimeMessageFromJausMessage failed\n");
		}
		else
		{
			setTimeMessageDestroy(setTimeMessage2);
		}
	}
	setTimeMessageDestroy(setTimeMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetToolPointMessage\n");
	setToolPointMessage1 = setToolPointMessageCreate();
	jausMessage = setToolPointMessageToJausMessage(setToolPointMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setToolPointMessageToJausMessage failed\n");
	}
	else
	{
		setToolPointMessage2 = setToolPointMessageFromJausMessage(jausMessage);
		if(setToolPointMessage2 == NULL)
		{
			printf("setToolPointMessageFromJausMessage failed\n");
		}
		else
		{
			setToolPointMessageDestroy(setToolPointMessage2);
		}
	}
	setToolPointMessageDestroy(setToolPointMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetTravelSpeedMessage\n");
	setTravelSpeedMessage1 = setTravelSpeedMessageCreate();
	jausMessage = setTravelSpeedMessageToJausMessage(setTravelSpeedMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setTravelSpeedMessageToJausMessage failed\n");
	}
	else
	{
		setTravelSpeedMessage2 = setTravelSpeedMessageFromJausMessage(jausMessage);
		if(setTravelSpeedMessage2 == NULL)
		{
			printf("setTravelSpeedMessageFromJausMessage failed\n");
		}
		else
		{
			setTravelSpeedMessageDestroy(setTravelSpeedMessage2);
		}
	}
	setTravelSpeedMessageDestroy(setTravelSpeedMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetVelocityStateMessage\n");
	setVelocityStateMessage1 = setVelocityStateMessageCreate();
	jausMessage = setVelocityStateMessageToJausMessage(setVelocityStateMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setVelocityStateMessageToJausMessage failed\n");
	}
	else
	{
		setVelocityStateMessage2 = setVelocityStateMessageFromJausMessage(jausMessage);
		if(setVelocityStateMessage2 == NULL)
		{
			printf("setVelocityStateMessageFromJausMessage failed\n");
		}
		else
		{
			setVelocityStateMessageDestroy(setVelocityStateMessage2);
		}
	}
	setVelocityStateMessageDestroy(setVelocityStateMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetVksFeatureClassMetadataMessage\n");
	setVksFeatureClassMetadataMessage1 = setVksFeatureClassMetadataMessageCreate();
	jausMessage = setVksFeatureClassMetadataMessageToJausMessage(setVksFeatureClassMetadataMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setVksFeatureClassMetadataMessageToJausMessage failed\n");
	}
	else
	{
		setVksFeatureClassMetadataMessage2 = setVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
		if(setVksFeatureClassMetadataMessage2 == NULL)
		{
			printf("setVksFeatureClassMetadataMessageFromJausMessage failed\n");
		}
		else
		{
			setVksFeatureClassMetadataMessageDestroy(setVksFeatureClassMetadataMessage2);
		}
	}
	setVksFeatureClassMetadataMessageDestroy(setVksFeatureClassMetadataMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SetWrenchEffortMessage\n");
	setWrenchEffortMessage1 = setWrenchEffortMessageCreate();
	jausMessage = setWrenchEffortMessageToJausMessage(setWrenchEffortMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("setWrenchEffortMessageToJausMessage failed\n");
	}
	else
	{
		setWrenchEffortMessage2 = setWrenchEffortMessageFromJausMessage(jausMessage);
		if(setWrenchEffortMessage2 == NULL)
		{
			printf("setWrenchEffortMessageFromJausMessage failed\n");
		}
		else
		{
			setWrenchEffortMessageDestroy(setWrenchEffortMessage2);
		}
	}
	setWrenchEffortMessageDestroy(setWrenchEffortMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing ShutdownMessage\n");
	shutdownMessage1 = shutdownMessageCreate();
	jausMessage = shutdownMessageToJausMessage(shutdownMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("shutdownMessageToJausMessage failed\n");
	}
	else
	{
		shutdownMessage2 = shutdownMessageFromJausMessage(jausMessage);
		if(shutdownMessage2 == NULL)
		{
			printf("shutdownMessageFromJausMessage failed\n");
		}
		else
		{
			shutdownMessageDestroy(shutdownMessage2);
		}
	}
	shutdownMessageDestroy(shutdownMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing StandbyMessage\n");
	standbyMessage1 = standbyMessageCreate();
	jausMessage = standbyMessageToJausMessage(standbyMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("standbyMessageToJausMessage failed\n");
	}
	else
	{
		standbyMessage2 = standbyMessageFromJausMessage(jausMessage);
		if(standbyMessage2 == NULL)
		{
			printf("standbyMessageFromJausMessage failed\n");
		}
		else
		{
			standbyMessageDestroy(standbyMessage2);
		}
	}
	standbyMessageDestroy(standbyMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing SuspendServiceConnectionMessage\n");
	suspendServiceConnectionMessage1 = suspendServiceConnectionMessageCreate();
	jausMessage = suspendServiceConnectionMessageToJausMessage(suspendServiceConnectionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("suspendServiceConnectionMessageToJausMessage failed\n");
	}
	else
	{
		suspendServiceConnectionMessage2 = suspendServiceConnectionMessageFromJausMessage(jausMessage);
		if(suspendServiceConnectionMessage2 == NULL)
		{
			printf("suspendServiceConnectionMessageFromJausMessage failed\n");
		}
		else
		{
			suspendServiceConnectionMessageDestroy(suspendServiceConnectionMessage2);
		}
	}
	suspendServiceConnectionMessageDestroy(suspendServiceConnectionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing TerminateServiceConnectionMessage\n");
	terminateServiceConnectionMessage1 = terminateServiceConnectionMessageCreate();
	jausMessage = terminateServiceConnectionMessageToJausMessage(terminateServiceConnectionMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("terminateServiceConnectionMessageToJausMessage failed\n");
	}
	else
	{
		terminateServiceConnectionMessage2 = terminateServiceConnectionMessageFromJausMessage(jausMessage);
		if(terminateServiceConnectionMessage2 == NULL)
		{
			printf("terminateServiceConnectionMessageFromJausMessage failed\n");
		}
		else
		{
			terminateServiceConnectionMessageDestroy(terminateServiceConnectionMessage2);
		}
	}
	terminateServiceConnectionMessageDestroy(terminateServiceConnectionMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing TerminateVksDataTransferMessage\n");
	terminateVksDataTransferMessage1 = terminateVksDataTransferMessageCreate();
	jausMessage = terminateVksDataTransferMessageToJausMessage(terminateVksDataTransferMessage1);
	if(jausMessage->dataSize != 0)
	{
		printf("terminateVksDataTransferMessageToJausMessage failed\n");
	}
	else
	{
		terminateVksDataTransferMessage2 = terminateVksDataTransferMessageFromJausMessage(jausMessage);
		if(terminateVksDataTransferMessage2 == NULL)
		{
			printf("terminateVksDataTransferMessageFromJausMessage failed\n");
		}
		else
		{
			terminateVksDataTransferMessageDestroy(terminateVksDataTransferMessage2);
		}
	}
	terminateVksDataTransferMessageDestroy(terminateVksDataTransferMessage1);
	jausMessageDestroy(jausMessage);

	printf("Testing UpdateEventMessage\n");
	updateEventMessage1 = updateEventMessageCreate();
	jausMessage = updateEventMessageToJausMessage(updateEventMessage1);
	if(jausMessage->dataSize == 0)
	{
		printf("updateEventMessageToJausMessage failed\n");
	}
	else
	{
		updateEventMessage2 = updateEventMessageFromJausMessage(jausMessage);
		if(updateEventMessage2 == NULL)
		{
			printf("updateEventMessageFromJausMessage failed\n");
		}
		else
		{
			updateEventMessageDestroy(updateEventMessage2);
		}
	}
	updateEventMessageDestroy(updateEventMessage1);
	jausMessageDestroy(jausMessage);

	system("pause");

	return 0;
}
