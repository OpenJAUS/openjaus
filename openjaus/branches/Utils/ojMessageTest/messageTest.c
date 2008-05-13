#include <stdio.h>
#include <jaus.h>


int main(void)
{
	JausMessage jausMessage;
	ReportComponentControlMessage reportComponentControlMessage;
	ReportComponentStatusMessage reportComponentStatusMessage;
	ReportComponentAuthorityMessage reportComponentAuthorityMessage;
	ReportTimeMessage reportTimeMessage;
	ReportWrenchEffortMessage reportWrenchEffortMessage;
	ReportLocalVectorMessage reportLocalVectorMessage;
	ReportLocalPoseMessage reportLocalPoseMessage;
	ReportGlobalPathSegmentMessage reportGlobalPathSegmentMessage;
	ReportTravelSpeedMessage reportTravelSpeedMessage;
	ReportGlobalVectorMessage reportGlobalVectorMessage;
	ReportWaypointCountMessage reportWaypointCountMessage;
	ReportPlatformSpecificationsMessage reportPlatformSpecificationsMessage;
	ReportGlobalWaypointMessage reportGlobalWaypointMessage;
	ReportLocalPathSegmentMessage reportLocalPathSegmentMessage;
	ReportPathSegmentCountMessage reportPathSegmentCountMessage;
	ReportLocalWaypointMessage reportLocalWaypointMessage;
	ReportPlatformOperationalDataMessage reportPlatformOperationalDataMessage;
	ReportVelocityStateMessage reportVelocityStateMessage;
	ReportGlobalPoseMessage reportGlobalPoseMessage;
	ReportDiscreteDevicesMessage reportDiscreteDevicesMessage;
	ReportToolPointMessage reportToolPointMessage;
	ReportJointEffortsMessage reportJointEffortsMessage;
	ReportManipulatorSpecificationsMessage reportManipulatorSpecificationsMessage;
	ReportJointVelocitiesMessage reportJointVelocitiesMessage;
	ReportJointForceTorquesMessage reportJointForceTorquesMessage;
	ReportJointPositionsMessage reportJointPositionsMessage;
	ReportVksFeatureClassMetadataMessage reportVksFeatureClassMetadataMessage;
	ReportVksObjectsMessage reportVksObjectsMessage;
	ReportVksDataTransferTerminationMessage reportVksDataTransferTerminationMessage;
	ReportVksBoundsMessage reportVksBoundsMessage;
	ReportVksObjectsCreationMessage reportVksObjectsCreationMessage;
	ReportPayloadInterfaceMessage reportPayloadInterfaceMessage;
	ReportPayloadDataElementMessage reportPayloadDataElementMessage;
	EventMessage eventMessage;
	ReportEventsMessage reportEventsMessage;
	ReportConfigurationMessage reportConfigurationMessage;
	ReportSubsystemListMessage reportSubsystemListMessage;
	ReportIdentificationMessage reportIdentificationMessage;
	ReportServicesMessage reportServicesMessage;
	ReportDataLinkStatusMessage reportDataLinkStatusMessage;
	ReportSelectedDataLinkStatusMessage reportSelectedDataLinkStatusMessage;
	ReportHeartbeatPulseMessage reportHeartbeatPulseMessage;
	ReportImageMessage reportImageMessage;
	ReportCameraCapabilitiesMessage reportCameraCapabilitiesMessage;
	ReportRelativeObjectPositionMessage reportRelativeObjectPositionMessage;
	ReportCameraPoseMessage reportCameraPoseMessage;
	ReportCameraFormatOptionsMessage reportCameraFormatOptionsMessage;
	ReportCameraCountMessage reportCameraCountMessage;
	ReportSelectedCameraMessage reportSelectedCameraMessage;
	ClearEmergencyMessage clearEmergencyMessage;
	SetEmergencyMessage setEmergencyMessage;
	ConfirmServiceConnectionMessage confirmServiceConnectionMessage;
	ReleaseComponentControlMessage releaseComponentControlMessage;
	ShutdownMessage shutdownMessage;
	StandbyMessage standbyMessage;
	ConfirmComponentControlMessage confirmComponentControlMessage;
	SetTimeMessage setTimeMessage;
	ResetMessage resetMessage;
	SuspendServiceConnectionMessage suspendServiceConnectionMessage;
	TerminateServiceConnectionMessage terminateServiceConnectionMessage;
	CreateServiceConnectionMessage createServiceConnectionMessage;
	RequestComponentControlMessage requestComponentControlMessage;
	RejectComponentControlMessage rejectComponentControlMessage;
	ActivateServiceConnectionMessage activateServiceConnectionMessage;
	SetComponentAuthorityMessage setComponentAuthorityMessage;
	ResumeMessage resumeMessage;
	SetLocalVectorMessage setLocalVectorMessage;
	SetGlobalVectorMessage setGlobalVectorMessage;
	SetGlobalPathSegmentMessage setGlobalPathSegmentMessage;
	SetLocalWaypointMessage setLocalWaypointMessage;
	SetTravelSpeedMessage setTravelSpeedMessage;
	SetVelocityStateMessage setVelocityStateMessage;
	SetWrenchEffortMessage setWrenchEffortMessage;
	SetDiscreteDevicesMessage setDiscreteDevicesMessage;
	SetLocalPathSegmentMessage setLocalPathSegmentMessage;
	SetGlobalWaypointMessage setGlobalWaypointMessage;
	SetJointPositionsMessage setJointPositionsMessage;
	SetToolPointMessage setToolPointMessage;
	SetJointMotionMessage setJointMotionMessage;
	SetEndEffectorPoseMessage setEndEffectorPoseMessage;
	SetJointEffortsMessage setJointEffortsMessage;
	SetJointVelocitiesMessage setJointVelocitiesMessage;
	SetEndEffectorPathMotionMessage setEndEffectorPathMotionMessage;
	SetEndEffectorVelocityStateMessage setEndEffectorVelocityStateMessage;
	CreateVksObjectsMessage createVksObjectsMessage;
	SetVksFeatureClassMetadataMessage setVksFeatureClassMetadataMessage;
	DeleteVksObjectsMessage deleteVksObjectsMessage;
	TerminateVksDataTransferMessage terminateVksDataTransferMessage;
	SetPayloadDataElementMessage setPayloadDataElementMessage;
	RejectEventRequestMessage rejectEventRequestMessage;
	CancelEventMessage cancelEventMessage;
	UpdateEventMessage updateEventMessage;
	CreateEventMessage createEventMessage;
	ConfirmEventRequestMessage confirmEventRequestMessage;
	SetDataLinkStatusMessage setDataLinkStatusMessage;
	SetSelectedDataLinkStateMessage setSelectedDataLinkStateMessage;
	SetDataLinkSelectMessage setDataLinkSelectMessage;
	SetCameraFormatOptionsMessage setCameraFormatOptionsMessage;
	SelectCameraMessage selectCameraMessage;
	SetCameraCapabilitiesMessage setCameraCapabilitiesMessage;
	SetCameraPoseMessage setCameraPoseMessage;
	QueryTimeMessage queryTimeMessage;
	QueryComponentControlMessage queryComponentControlMessage;
	QueryComponentStatusMessage queryComponentStatusMessage;
	QueryComponentAuthorityMessage queryComponentAuthorityMessage;
	QueryGlobalPoseMessage queryGlobalPoseMessage;
	QueryGlobalWaypointMessage queryGlobalWaypointMessage;
	QueryPlatformSpecificationsMessage queryPlatformSpecificationsMessage;
	QueryLocalVectorMessage queryLocalVectorMessage;
	QueryLocalWaypointMessage queryLocalWaypointMessage;
	QueryDiscreteDevicesMessage queryDiscreteDevicesMessage;
	QueryTravelSpeedMessage queryTravelSpeedMessage;
	QueryPlatformOperationalDataMessage queryPlatformOperationalDataMessage;
	QueryVelocityStateMessage queryVelocityStateMessage;
	QueryLocalPoseMessage queryLocalPoseMessage;
	QueryGlobalVectorMessage queryGlobalVectorMessage;
	QueryLocalPathSegmentMessage queryLocalPathSegmentMessage;
	QueryWaypointCountMessage queryWaypointCountMessage;
	QueryPathSegmentCountMessage queryPathSegmentCountMessage;
	QueryGlobalPathSegmentMessage queryGlobalPathSegmentMessage;
	QueryWrenchEffortMessage queryWrenchEffortMessage;
	QueryManipulatorSpecificationsMessage queryManipulatorSpecificationsMessage;
	QueryJointPositionsMessage queryJointPositionsMessage;
	QueryJointVelocitiesMessage queryJointVelocitiesMessage;
	QueryToolPointMessage queryToolPointMessage;
	QueryJointEffortsMessage queryJointEffortsMessage;
	QueryJointForceTorquesMessage queryJointForceTorquesMessage;
	QueryVksFeatureClassMetadataMessage queryVksFeatureClassMetadataMessage;
	QueryVksObjectsMessage queryVksObjectsMessage;
	QueryVksBoundsMessage queryVksBoundsMessage;
	QueryPayloadInterfaceMessage queryPayloadInterfaceMessage;
	QueryPayloadDataElementMessage queryPayloadDataElementMessage;
	QueryEventsMessage queryEventsMessage;
	QueryServicesMessage queryServicesMessage;
	QueryConfigurationMessage queryConfigurationMessage;
	QuerySubsystemListMessage querySubsystemListMessage;
	QueryIdentificationMessage queryIdentificationMessage;
	QuerySelectedDataLinkStatusMessage querySelectedDataLinkStatusMessage;
	QueryDataLinkStatusMessage queryDataLinkStatusMessage;
	QueryHeartbeatPulseMessage queryHeartbeatPulseMessage;
	QueryCameraFormatOptionsMessage queryCameraFormatOptionsMessage;
	QueryCameraCountMessage queryCameraCountMessage;
	QueryImageMessage queryImageMessage;
	QuerySelectedCameraMessage querySelectedCameraMessage;
	QueryRelativeObjectPositionMessage queryRelativeObjectPositionMessage;
	QueryCameraPoseMessage queryCameraPoseMessage;
	QueryCameraCapabilitiesMessage queryCameraCapabilitiesMessage;


	reportComponentControlMessage = reportComponentControlMessageCreate();
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

	reportComponentStatusMessage = reportComponentStatusMessageCreate();
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

	reportComponentAuthorityMessage = reportComponentAuthorityMessageCreate();
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

	reportTimeMessage = reportTimeMessageCreate();
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

	reportWrenchEffortMessage = reportWrenchEffortMessageCreate();
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

	reportLocalVectorMessage = reportLocalVectorMessageCreate();
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

	reportLocalPoseMessage = reportLocalPoseMessageCreate();
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

	reportGlobalPathSegmentMessage = reportGlobalPathSegmentMessageCreate();
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

	reportTravelSpeedMessage = reportTravelSpeedMessageCreate();
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

	reportGlobalVectorMessage = reportGlobalVectorMessageCreate();
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

	reportWaypointCountMessage = reportWaypointCountMessageCreate();
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

	reportPlatformSpecificationsMessage = reportPlatformSpecificationsMessageCreate();
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

	reportGlobalWaypointMessage = reportGlobalWaypointMessageCreate();
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

	reportLocalPathSegmentMessage = reportLocalPathSegmentMessageCreate();
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

	reportPathSegmentCountMessage = reportPathSegmentCountMessageCreate();
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

	reportLocalWaypointMessage = reportLocalWaypointMessageCreate();
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

	reportPlatformOperationalDataMessage = reportPlatformOperationalDataMessageCreate();
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

	reportVelocityStateMessage = reportVelocityStateMessageCreate();
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

	reportGlobalPoseMessage = reportGlobalPoseMessageCreate();
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

	reportDiscreteDevicesMessage = reportDiscreteDevicesMessageCreate();
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

	reportToolPointMessage = reportToolPointMessageCreate();
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

	reportJointEffortsMessage = reportJointEffortsMessageCreate();
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

	reportManipulatorSpecificationsMessage = reportManipulatorSpecificationsMessageCreate();
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

	reportJointVelocitiesMessage = reportJointVelocitiesMessageCreate();
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

	reportJointForceTorquesMessage = reportJointForceTorquesMessageCreate();
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

	reportJointPositionsMessage = reportJointPositionsMessageCreate();
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

	reportVksFeatureClassMetadataMessage = reportVksFeatureClassMetadataMessageCreate();
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

	reportVksObjectsMessage = reportVksObjectsMessageCreate();
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

	reportVksDataTransferTerminationMessage = reportVksDataTransferTerminationMessageCreate();
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

	reportVksBoundsMessage = reportVksBoundsMessageCreate();
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

	reportVksObjectsCreationMessage = reportVksObjectsCreationMessageCreate();
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

	reportPayloadInterfaceMessage = reportPayloadInterfaceMessageCreate();
	jausMessage = reportPayloadInterfaceMessageToJausMessage(reportPayloadInterfaceMessage);
	reportPayloadInterfaceMessageDestroy(reportPayloadInterfaceMessage);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPayloadInterfaceMessageToJausMessage failed\n");
	}
	else
	{
		reportPayloadInterfaceMessage = reportPayloadInterfaceMessageFromJausMessage(jausMessage);
		if(reportPayloadInterfaceMessage == NULL)
		{
			printf("reportPayloadInterfaceMessageFromJausMessage failed\n");
		}
		else
		{
			reportPayloadInterfaceMessageDestroy(reportPayloadInterfaceMessage);
		}
	}
	jausMessageDestroy(jausMessage);

	reportPayloadDataElementMessage = reportPayloadDataElementMessageCreate();
	jausMessage = reportPayloadDataElementMessageToJausMessage(reportPayloadDataElementMessage);
	reportPayloadDataElementMessageDestroy(reportPayloadDataElementMessage);
	if(jausMessage->dataSize == 0)
	{
		printf("reportPayloadDataElementMessageToJausMessage failed\n");
	}
	else
	{
		reportPayloadDataElementMessage = reportPayloadDataElementMessageFromJausMessage(jausMessage);
		if(reportPayloadDataElementMessage == NULL)
		{
			printf("reportPayloadDataElementMessageFromJausMessage failed\n");
		}
		else
		{
			reportPayloadDataElementMessageDestroy(reportPayloadDataElementMessage);
		}
	}
	jausMessageDestroy(jausMessage);

	eventMessage = eventMessageCreate();
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

	reportEventsMessage = reportEventsMessageCreate();
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

	reportConfigurationMessage = reportConfigurationMessageCreate();
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

	reportSubsystemListMessage = reportSubsystemListMessageCreate();
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

	reportIdentificationMessage = reportIdentificationMessageCreate();
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

	reportServicesMessage = reportServicesMessageCreate();
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

	reportDataLinkStatusMessage = reportDataLinkStatusMessageCreate();
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

	reportSelectedDataLinkStatusMessage = reportSelectedDataLinkStatusMessageCreate();
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

	reportHeartbeatPulseMessage = reportHeartbeatPulseMessageCreate();
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

	reportImageMessage = reportImageMessageCreate();
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

	reportCameraCapabilitiesMessage = reportCameraCapabilitiesMessageCreate();
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

	reportRelativeObjectPositionMessage = reportRelativeObjectPositionMessageCreate();
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

	reportCameraPoseMessage = reportCameraPoseMessageCreate();
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

	reportCameraFormatOptionsMessage = reportCameraFormatOptionsMessageCreate();
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

	reportCameraCountMessage = reportCameraCountMessageCreate();
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

	reportSelectedCameraMessage = reportSelectedCameraMessageCreate();
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

	clearEmergencyMessage = clearEmergencyMessageCreate();
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

	setEmergencyMessage = setEmergencyMessageCreate();
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

	confirmServiceConnectionMessage = confirmServiceConnectionMessageCreate();
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

	releaseComponentControlMessage = releaseComponentControlMessageCreate();
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

	shutdownMessage = shutdownMessageCreate();
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

	standbyMessage = standbyMessageCreate();
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

	confirmComponentControlMessage = confirmComponentControlMessageCreate();
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

	setTimeMessage = setTimeMessageCreate();
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

	resetMessage = resetMessageCreate();
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

	suspendServiceConnectionMessage = suspendServiceConnectionMessageCreate();
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

	terminateServiceConnectionMessage = terminateServiceConnectionMessageCreate();
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

	createServiceConnectionMessage = createServiceConnectionMessageCreate();
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

	requestComponentControlMessage = requestComponentControlMessageCreate();
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

	rejectComponentControlMessage = rejectComponentControlMessageCreate();
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

	activateServiceConnectionMessage = activateServiceConnectionMessageCreate();
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

	setComponentAuthorityMessage = setComponentAuthorityMessageCreate();
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

	resumeMessage = resumeMessageCreate();
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

	setLocalVectorMessage = setLocalVectorMessageCreate();
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

	setGlobalVectorMessage = setGlobalVectorMessageCreate();
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

	setGlobalPathSegmentMessage = setGlobalPathSegmentMessageCreate();
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

	setLocalWaypointMessage = setLocalWaypointMessageCreate();
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

	setTravelSpeedMessage = setTravelSpeedMessageCreate();
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

	setVelocityStateMessage = setVelocityStateMessageCreate();
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

	setWrenchEffortMessage = setWrenchEffortMessageCreate();
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

	setDiscreteDevicesMessage = setDiscreteDevicesMessageCreate();
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

	setLocalPathSegmentMessage = setLocalPathSegmentMessageCreate();
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

	setGlobalWaypointMessage = setGlobalWaypointMessageCreate();
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

	setJointPositionsMessage = setJointPositionsMessageCreate();
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

	setToolPointMessage = setToolPointMessageCreate();
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

	setJointMotionMessage = setJointMotionMessageCreate();
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

	setEndEffectorPoseMessage = setEndEffectorPoseMessageCreate();
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

	setJointEffortsMessage = setJointEffortsMessageCreate();
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

	setJointVelocitiesMessage = setJointVelocitiesMessageCreate();
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

	setEndEffectorPathMotionMessage = setEndEffectorPathMotionMessageCreate();
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

	setEndEffectorVelocityStateMessage = setEndEffectorVelocityStateMessageCreate();
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

	createVksObjectsMessage = createVksObjectsMessageCreate();
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

	setVksFeatureClassMetadataMessage = setVksFeatureClassMetadataMessageCreate();
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

	deleteVksObjectsMessage = deleteVksObjectsMessageCreate();
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

	terminateVksDataTransferMessage = terminateVksDataTransferMessageCreate();
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

	rejectEventRequestMessage = rejectEventRequestMessageCreate();
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

	cancelEventMessage = cancelEventMessageCreate();
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

	updateEventMessage = updateEventMessageCreate();
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

	createEventMessage = createEventMessageCreate();
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

	confirmEventRequestMessage = confirmEventRequestMessageCreate();
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

	setDataLinkStatusMessage = setDataLinkStatusMessageCreate();
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

	setSelectedDataLinkStateMessage = setSelectedDataLinkStateMessageCreate();
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

	setDataLinkSelectMessage = setDataLinkSelectMessageCreate();
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

	setCameraFormatOptionsMessage = setCameraFormatOptionsMessageCreate();
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

	selectCameraMessage = selectCameraMessageCreate();
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

	setCameraCapabilitiesMessage = setCameraCapabilitiesMessageCreate();
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

	setCameraPoseMessage = setCameraPoseMessageCreate();
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

	queryTimeMessage = queryTimeMessageCreate();
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

	queryComponentControlMessage = queryComponentControlMessageCreate();
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

	queryComponentStatusMessage = queryComponentStatusMessageCreate();
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

	queryComponentAuthorityMessage = queryComponentAuthorityMessageCreate();
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

	queryGlobalPoseMessage = queryGlobalPoseMessageCreate();
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

	queryGlobalWaypointMessage = queryGlobalWaypointMessageCreate();
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

	queryPlatformSpecificationsMessage = queryPlatformSpecificationsMessageCreate();
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

	queryLocalVectorMessage = queryLocalVectorMessageCreate();
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

	queryLocalWaypointMessage = queryLocalWaypointMessageCreate();
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

	queryDiscreteDevicesMessage = queryDiscreteDevicesMessageCreate();
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

	queryTravelSpeedMessage = queryTravelSpeedMessageCreate();
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

	queryPlatformOperationalDataMessage = queryPlatformOperationalDataMessageCreate();
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

	queryVelocityStateMessage = queryVelocityStateMessageCreate();
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

	queryLocalPoseMessage = queryLocalPoseMessageCreate();
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

	queryGlobalVectorMessage = queryGlobalVectorMessageCreate();
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

	queryLocalPathSegmentMessage = queryLocalPathSegmentMessageCreate();
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

	queryWaypointCountMessage = queryWaypointCountMessageCreate();
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

	queryPathSegmentCountMessage = queryPathSegmentCountMessageCreate();
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

	queryGlobalPathSegmentMessage = queryGlobalPathSegmentMessageCreate();
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

	queryWrenchEffortMessage = queryWrenchEffortMessageCreate();
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

	queryManipulatorSpecificationsMessage = queryManipulatorSpecificationsMessageCreate();
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

	queryJointPositionsMessage = queryJointPositionsMessageCreate();
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

	queryJointVelocitiesMessage = queryJointVelocitiesMessageCreate();
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

	queryToolPointMessage = queryToolPointMessageCreate();
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

	queryJointEffortsMessage = queryJointEffortsMessageCreate();
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

	queryJointForceTorquesMessage = queryJointForceTorquesMessageCreate();
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

	queryVksFeatureClassMetadataMessage = queryVksFeatureClassMetadataMessageCreate();
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

	queryVksObjectsMessage = queryVksObjectsMessageCreate();
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

	queryVksBoundsMessage = queryVksBoundsMessageCreate();
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

	queryPayloadInterfaceMessage = queryPayloadInterfaceMessageCreate();
	jausMessage = queryPayloadInterfaceMessageToJausMessage(queryPayloadInterfaceMessage);
	queryPayloadInterfaceMessageDestroy(queryPayloadInterfaceMessage);
	if(jausMessage->dataSize == 0)
	{
		printf("queryPayloadInterfaceMessageToJausMessage failed\n");
	}
	else
	{
		queryPayloadInterfaceMessage = queryPayloadInterfaceMessageFromJausMessage(jausMessage);
		if(queryPayloadInterfaceMessage == NULL)
		{
			printf("queryPayloadInterfaceMessageFromJausMessage failed\n");
		}
		else
		{
			queryPayloadInterfaceMessageDestroy(queryPayloadInterfaceMessage);
		}
	}
	jausMessageDestroy(jausMessage);

	queryPayloadDataElementMessage = queryPayloadDataElementMessageCreate();
	jausMessage = queryPayloadDataElementMessageToJausMessage(queryPayloadDataElementMessage);
	queryPayloadDataElementMessageDestroy(queryPayloadDataElementMessage);
	if(jausMessage->dataSize == 0)
	{
		printf("queryPayloadDataElementMessageToJausMessage failed\n");
	}
	else
	{
		queryPayloadDataElementMessage = queryPayloadDataElementMessageFromJausMessage(jausMessage);
		if(queryPayloadDataElementMessage == NULL)
		{
			printf("queryPayloadDataElementMessageFromJausMessage failed\n");
		}
		else
		{
			queryPayloadDataElementMessageDestroy(queryPayloadDataElementMessage);
		}
	}
	jausMessageDestroy(jausMessage);

	queryEventsMessage = queryEventsMessageCreate();
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

	queryServicesMessage = queryServicesMessageCreate();
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

	queryConfigurationMessage = queryConfigurationMessageCreate();
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

	querySubsystemListMessage = querySubsystemListMessageCreate();
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

	queryIdentificationMessage = queryIdentificationMessageCreate();
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

	querySelectedDataLinkStatusMessage = querySelectedDataLinkStatusMessageCreate();
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

	queryDataLinkStatusMessage = queryDataLinkStatusMessageCreate();
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

	queryHeartbeatPulseMessage = queryHeartbeatPulseMessageCreate();
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

	queryCameraFormatOptionsMessage = queryCameraFormatOptionsMessageCreate();
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

	queryCameraCountMessage = queryCameraCountMessageCreate();
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

	queryImageMessage = queryImageMessageCreate();
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

	querySelectedCameraMessage = querySelectedCameraMessageCreate();
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

	queryRelativeObjectPositionMessage = queryRelativeObjectPositionMessageCreate();
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

	queryCameraPoseMessage = queryCameraPoseMessageCreate();
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

	queryCameraCapabilitiesMessage = queryCameraCapabilitiesMessageCreate();
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

	return 0;
}
