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
	reportComponentControlMessage = reportComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportComponentStatusMessage = reportComponentStatusMessageCreate();
	jausMessage = reportComponentStatusMessageToJausMessage(reportComponentStatusMessage);
	reportComponentStatusMessage = reportComponentStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportComponentAuthorityMessage = reportComponentAuthorityMessageCreate();
	jausMessage = reportComponentAuthorityMessageToJausMessage(reportComponentAuthorityMessage);
	reportComponentAuthorityMessage = reportComponentAuthorityMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportTimeMessage = reportTimeMessageCreate();
	jausMessage = reportTimeMessageToJausMessage(reportTimeMessage);
	reportTimeMessage = reportTimeMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportWrenchEffortMessage = reportWrenchEffortMessageCreate();
	jausMessage = reportWrenchEffortMessageToJausMessage(reportWrenchEffortMessage);
	reportWrenchEffortMessage = reportWrenchEffortMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportLocalVectorMessage = reportLocalVectorMessageCreate();
	jausMessage = reportLocalVectorMessageToJausMessage(reportLocalVectorMessage);
	reportLocalVectorMessage = reportLocalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportLocalPoseMessage = reportLocalPoseMessageCreate();
	jausMessage = reportLocalPoseMessageToJausMessage(reportLocalPoseMessage);
	reportLocalPoseMessage = reportLocalPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportGlobalPathSegmentMessage = reportGlobalPathSegmentMessageCreate();
	jausMessage = reportGlobalPathSegmentMessageToJausMessage(reportGlobalPathSegmentMessage);
	reportGlobalPathSegmentMessage = reportGlobalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportTravelSpeedMessage = reportTravelSpeedMessageCreate();
	jausMessage = reportTravelSpeedMessageToJausMessage(reportTravelSpeedMessage);
	reportTravelSpeedMessage = reportTravelSpeedMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportGlobalVectorMessage = reportGlobalVectorMessageCreate();
	jausMessage = reportGlobalVectorMessageToJausMessage(reportGlobalVectorMessage);
	reportGlobalVectorMessage = reportGlobalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportWaypointCountMessage = reportWaypointCountMessageCreate();
	jausMessage = reportWaypointCountMessageToJausMessage(reportWaypointCountMessage);
	reportWaypointCountMessage = reportWaypointCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportPlatformSpecificationsMessage = reportPlatformSpecificationsMessageCreate();
	jausMessage = reportPlatformSpecificationsMessageToJausMessage(reportPlatformSpecificationsMessage);
	reportPlatformSpecificationsMessage = reportPlatformSpecificationsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportGlobalWaypointMessage = reportGlobalWaypointMessageCreate();
	jausMessage = reportGlobalWaypointMessageToJausMessage(reportGlobalWaypointMessage);
	reportGlobalWaypointMessage = reportGlobalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportLocalPathSegmentMessage = reportLocalPathSegmentMessageCreate();
	jausMessage = reportLocalPathSegmentMessageToJausMessage(reportLocalPathSegmentMessage);
	reportLocalPathSegmentMessage = reportLocalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportPathSegmentCountMessage = reportPathSegmentCountMessageCreate();
	jausMessage = reportPathSegmentCountMessageToJausMessage(reportPathSegmentCountMessage);
	reportPathSegmentCountMessage = reportPathSegmentCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportLocalWaypointMessage = reportLocalWaypointMessageCreate();
	jausMessage = reportLocalWaypointMessageToJausMessage(reportLocalWaypointMessage);
	reportLocalWaypointMessage = reportLocalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportPlatformOperationalDataMessage = reportPlatformOperationalDataMessageCreate();
	jausMessage = reportPlatformOperationalDataMessageToJausMessage(reportPlatformOperationalDataMessage);
	reportPlatformOperationalDataMessage = reportPlatformOperationalDataMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVelocityStateMessage = reportVelocityStateMessageCreate();
	jausMessage = reportVelocityStateMessageToJausMessage(reportVelocityStateMessage);
	reportVelocityStateMessage = reportVelocityStateMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportGlobalPoseMessage = reportGlobalPoseMessageCreate();
	jausMessage = reportGlobalPoseMessageToJausMessage(reportGlobalPoseMessage);
	reportGlobalPoseMessage = reportGlobalPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportDiscreteDevicesMessage = reportDiscreteDevicesMessageCreate();
	jausMessage = reportDiscreteDevicesMessageToJausMessage(reportDiscreteDevicesMessage);
	reportDiscreteDevicesMessage = reportDiscreteDevicesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportToolPointMessage = reportToolPointMessageCreate();
	jausMessage = reportToolPointMessageToJausMessage(reportToolPointMessage);
	reportToolPointMessage = reportToolPointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportJointEffortsMessage = reportJointEffortsMessageCreate();
	jausMessage = reportJointEffortsMessageToJausMessage(reportJointEffortsMessage);
	reportJointEffortsMessage = reportJointEffortsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportManipulatorSpecificationsMessage = reportManipulatorSpecificationsMessageCreate();
	jausMessage = reportManipulatorSpecificationsMessageToJausMessage(reportManipulatorSpecificationsMessage);
	reportManipulatorSpecificationsMessage = reportManipulatorSpecificationsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportJointVelocitiesMessage = reportJointVelocitiesMessageCreate();
	jausMessage = reportJointVelocitiesMessageToJausMessage(reportJointVelocitiesMessage);
	reportJointVelocitiesMessage = reportJointVelocitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportJointForceTorquesMessage = reportJointForceTorquesMessageCreate();
	jausMessage = reportJointForceTorquesMessageToJausMessage(reportJointForceTorquesMessage);
	reportJointForceTorquesMessage = reportJointForceTorquesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportJointPositionsMessage = reportJointPositionsMessageCreate();
	jausMessage = reportJointPositionsMessageToJausMessage(reportJointPositionsMessage);
	reportJointPositionsMessage = reportJointPositionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVksFeatureClassMetadataMessage = reportVksFeatureClassMetadataMessageCreate();
	jausMessage = reportVksFeatureClassMetadataMessageToJausMessage(reportVksFeatureClassMetadataMessage);
	reportVksFeatureClassMetadataMessage = reportVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVksObjectsMessage = reportVksObjectsMessageCreate();
	jausMessage = reportVksObjectsMessageToJausMessage(reportVksObjectsMessage);
	reportVksObjectsMessage = reportVksObjectsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVksDataTransferTerminationMessage = reportVksDataTransferTerminationMessageCreate();
	jausMessage = reportVksDataTransferTerminationMessageToJausMessage(reportVksDataTransferTerminationMessage);
	reportVksDataTransferTerminationMessage = reportVksDataTransferTerminationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVksBoundsMessage = reportVksBoundsMessageCreate();
	jausMessage = reportVksBoundsMessageToJausMessage(reportVksBoundsMessage);
	reportVksBoundsMessage = reportVksBoundsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportVksObjectsCreationMessage = reportVksObjectsCreationMessageCreate();
	jausMessage = reportVksObjectsCreationMessageToJausMessage(reportVksObjectsCreationMessage);
	reportVksObjectsCreationMessage = reportVksObjectsCreationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportPayloadDataElementMessage = reportPayloadDataElementMessageCreate();
	jausMessage = reportPayloadDataElementMessageToJausMessage(reportPayloadDataElementMessage);
	reportPayloadDataElementMessage = reportPayloadDataElementMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	eventMessage = eventMessageCreate();
	jausMessage = eventMessageToJausMessage(eventMessage);
	eventMessage = eventMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportEventsMessage = reportEventsMessageCreate();
	jausMessage = reportEventsMessageToJausMessage(reportEventsMessage);
	reportEventsMessage = reportEventsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportConfigurationMessage = reportConfigurationMessageCreate();
	jausMessage = reportConfigurationMessageToJausMessage(reportConfigurationMessage);
	reportConfigurationMessage = reportConfigurationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportSubsystemListMessage = reportSubsystemListMessageCreate();
	jausMessage = reportSubsystemListMessageToJausMessage(reportSubsystemListMessage);
	reportSubsystemListMessage = reportSubsystemListMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportIdentificationMessage = reportIdentificationMessageCreate();
	jausMessage = reportIdentificationMessageToJausMessage(reportIdentificationMessage);
	reportIdentificationMessage = reportIdentificationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportServicesMessage = reportServicesMessageCreate();
	jausMessage = reportServicesMessageToJausMessage(reportServicesMessage);
	reportServicesMessage = reportServicesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportDataLinkStatusMessage = reportDataLinkStatusMessageCreate();
	jausMessage = reportDataLinkStatusMessageToJausMessage(reportDataLinkStatusMessage);
	reportDataLinkStatusMessage = reportDataLinkStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportSelectedDataLinkStatusMessage = reportSelectedDataLinkStatusMessageCreate();
	jausMessage = reportSelectedDataLinkStatusMessageToJausMessage(reportSelectedDataLinkStatusMessage);
	reportSelectedDataLinkStatusMessage = reportSelectedDataLinkStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportHeartbeatPulseMessage = reportHeartbeatPulseMessageCreate();
	jausMessage = reportHeartbeatPulseMessageToJausMessage(reportHeartbeatPulseMessage);
	reportHeartbeatPulseMessage = reportHeartbeatPulseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportImageMessage = reportImageMessageCreate();
	jausMessage = reportImageMessageToJausMessage(reportImageMessage);
	reportImageMessage = reportImageMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportCameraCapabilitiesMessage = reportCameraCapabilitiesMessageCreate();
	jausMessage = reportCameraCapabilitiesMessageToJausMessage(reportCameraCapabilitiesMessage);
	reportCameraCapabilitiesMessage = reportCameraCapabilitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportRelativeObjectPositionMessage = reportRelativeObjectPositionMessageCreate();
	jausMessage = reportRelativeObjectPositionMessageToJausMessage(reportRelativeObjectPositionMessage);
	reportRelativeObjectPositionMessage = reportRelativeObjectPositionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportCameraPoseMessage = reportCameraPoseMessageCreate();
	jausMessage = reportCameraPoseMessageToJausMessage(reportCameraPoseMessage);
	reportCameraPoseMessage = reportCameraPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportCameraFormatOptionsMessage = reportCameraFormatOptionsMessageCreate();
	jausMessage = reportCameraFormatOptionsMessageToJausMessage(reportCameraFormatOptionsMessage);
	reportCameraFormatOptionsMessage = reportCameraFormatOptionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportCameraCountMessage = reportCameraCountMessageCreate();
	jausMessage = reportCameraCountMessageToJausMessage(reportCameraCountMessage);
	reportCameraCountMessage = reportCameraCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	reportSelectedCameraMessage = reportSelectedCameraMessageCreate();
	jausMessage = reportSelectedCameraMessageToJausMessage(reportSelectedCameraMessage);
	reportSelectedCameraMessage = reportSelectedCameraMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	clearEmergencyMessage = clearEmergencyMessageCreate();
	jausMessage = clearEmergencyMessageToJausMessage(clearEmergencyMessage);
	clearEmergencyMessage = clearEmergencyMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setEmergencyMessage = setEmergencyMessageCreate();
	jausMessage = setEmergencyMessageToJausMessage(setEmergencyMessage);
	setEmergencyMessage = setEmergencyMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	confirmServiceConnectionMessage = confirmServiceConnectionMessageCreate();
	jausMessage = confirmServiceConnectionMessageToJausMessage(confirmServiceConnectionMessage);
	confirmServiceConnectionMessage = confirmServiceConnectionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	releaseComponentControlMessage = releaseComponentControlMessageCreate();
	jausMessage = releaseComponentControlMessageToJausMessage(releaseComponentControlMessage);
	releaseComponentControlMessage = releaseComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	shutdownMessage = shutdownMessageCreate();
	jausMessage = shutdownMessageToJausMessage(shutdownMessage);
	shutdownMessage = shutdownMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	standbyMessage = standbyMessageCreate();
	jausMessage = standbyMessageToJausMessage(standbyMessage);
	standbyMessage = standbyMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	confirmComponentControlMessage = confirmComponentControlMessageCreate();
	jausMessage = confirmComponentControlMessageToJausMessage(confirmComponentControlMessage);
	confirmComponentControlMessage = confirmComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setTimeMessage = setTimeMessageCreate();
	jausMessage = setTimeMessageToJausMessage(setTimeMessage);
	setTimeMessage = setTimeMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	resetMessage = resetMessageCreate();
	jausMessage = resetMessageToJausMessage(resetMessage);
	resetMessage = resetMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	suspendServiceConnectionMessage = suspendServiceConnectionMessageCreate();
	jausMessage = suspendServiceConnectionMessageToJausMessage(suspendServiceConnectionMessage);
	suspendServiceConnectionMessage = suspendServiceConnectionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	terminateServiceConnectionMessage = terminateServiceConnectionMessageCreate();
	jausMessage = terminateServiceConnectionMessageToJausMessage(terminateServiceConnectionMessage);
	terminateServiceConnectionMessage = terminateServiceConnectionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	createServiceConnectionMessage = createServiceConnectionMessageCreate();
	jausMessage = createServiceConnectionMessageToJausMessage(createServiceConnectionMessage);
	createServiceConnectionMessage = createServiceConnectionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	requestComponentControlMessage = requestComponentControlMessageCreate();
	jausMessage = requestComponentControlMessageToJausMessage(requestComponentControlMessage);
	requestComponentControlMessage = requestComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	rejectComponentControlMessage = rejectComponentControlMessageCreate();
	jausMessage = rejectComponentControlMessageToJausMessage(rejectComponentControlMessage);
	rejectComponentControlMessage = rejectComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	activateServiceConnectionMessage = activateServiceConnectionMessageCreate();
	jausMessage = activateServiceConnectionMessageToJausMessage(activateServiceConnectionMessage);
	activateServiceConnectionMessage = activateServiceConnectionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setComponentAuthorityMessage = setComponentAuthorityMessageCreate();
	jausMessage = setComponentAuthorityMessageToJausMessage(setComponentAuthorityMessage);
	setComponentAuthorityMessage = setComponentAuthorityMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	resumeMessage = resumeMessageCreate();
	jausMessage = resumeMessageToJausMessage(resumeMessage);
	resumeMessage = resumeMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setLocalVectorMessage = setLocalVectorMessageCreate();
	jausMessage = setLocalVectorMessageToJausMessage(setLocalVectorMessage);
	setLocalVectorMessage = setLocalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setGlobalVectorMessage = setGlobalVectorMessageCreate();
	jausMessage = setGlobalVectorMessageToJausMessage(setGlobalVectorMessage);
	setGlobalVectorMessage = setGlobalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setGlobalPathSegmentMessage = setGlobalPathSegmentMessageCreate();
	jausMessage = setGlobalPathSegmentMessageToJausMessage(setGlobalPathSegmentMessage);
	setGlobalPathSegmentMessage = setGlobalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setLocalWaypointMessage = setLocalWaypointMessageCreate();
	jausMessage = setLocalWaypointMessageToJausMessage(setLocalWaypointMessage);
	setLocalWaypointMessage = setLocalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setTravelSpeedMessage = setTravelSpeedMessageCreate();
	jausMessage = setTravelSpeedMessageToJausMessage(setTravelSpeedMessage);
	setTravelSpeedMessage = setTravelSpeedMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setVelocityStateMessage = setVelocityStateMessageCreate();
	jausMessage = setVelocityStateMessageToJausMessage(setVelocityStateMessage);
	setVelocityStateMessage = setVelocityStateMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setWrenchEffortMessage = setWrenchEffortMessageCreate();
	jausMessage = setWrenchEffortMessageToJausMessage(setWrenchEffortMessage);
	setWrenchEffortMessage = setWrenchEffortMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setDiscreteDevicesMessage = setDiscreteDevicesMessageCreate();
	jausMessage = setDiscreteDevicesMessageToJausMessage(setDiscreteDevicesMessage);
	setDiscreteDevicesMessage = setDiscreteDevicesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setLocalPathSegmentMessage = setLocalPathSegmentMessageCreate();
	jausMessage = setLocalPathSegmentMessageToJausMessage(setLocalPathSegmentMessage);
	setLocalPathSegmentMessage = setLocalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setGlobalWaypointMessage = setGlobalWaypointMessageCreate();
	jausMessage = setGlobalWaypointMessageToJausMessage(setGlobalWaypointMessage);
	setGlobalWaypointMessage = setGlobalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setJointPositionsMessage = setJointPositionsMessageCreate();
	jausMessage = setJointPositionsMessageToJausMessage(setJointPositionsMessage);
	setJointPositionsMessage = setJointPositionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setToolPointMessage = setToolPointMessageCreate();
	jausMessage = setToolPointMessageToJausMessage(setToolPointMessage);
	setToolPointMessage = setToolPointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setJointMotionMessage = setJointMotionMessageCreate();
	jausMessage = setJointMotionMessageToJausMessage(setJointMotionMessage);
	setJointMotionMessage = setJointMotionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setEndEffectorPoseMessage = setEndEffectorPoseMessageCreate();
	jausMessage = setEndEffectorPoseMessageToJausMessage(setEndEffectorPoseMessage);
	setEndEffectorPoseMessage = setEndEffectorPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setJointEffortsMessage = setJointEffortsMessageCreate();
	jausMessage = setJointEffortsMessageToJausMessage(setJointEffortsMessage);
	setJointEffortsMessage = setJointEffortsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setJointVelocitiesMessage = setJointVelocitiesMessageCreate();
	jausMessage = setJointVelocitiesMessageToJausMessage(setJointVelocitiesMessage);
	setJointVelocitiesMessage = setJointVelocitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setEndEffectorPathMotionMessage = setEndEffectorPathMotionMessageCreate();
	jausMessage = setEndEffectorPathMotionMessageToJausMessage(setEndEffectorPathMotionMessage);
	setEndEffectorPathMotionMessage = setEndEffectorPathMotionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setEndEffectorVelocityStateMessage = setEndEffectorVelocityStateMessageCreate();
	jausMessage = setEndEffectorVelocityStateMessageToJausMessage(setEndEffectorVelocityStateMessage);
	setEndEffectorVelocityStateMessage = setEndEffectorVelocityStateMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	createVksObjectsMessage = createVksObjectsMessageCreate();
	jausMessage = createVksObjectsMessageToJausMessage(createVksObjectsMessage);
	createVksObjectsMessage = createVksObjectsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setVksFeatureClassMetadataMessage = setVksFeatureClassMetadataMessageCreate();
	jausMessage = setVksFeatureClassMetadataMessageToJausMessage(setVksFeatureClassMetadataMessage);
	setVksFeatureClassMetadataMessage = setVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	deleteVksObjectsMessage = deleteVksObjectsMessageCreate();
	jausMessage = deleteVksObjectsMessageToJausMessage(deleteVksObjectsMessage);
	deleteVksObjectsMessage = deleteVksObjectsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	terminateVksDataTransferMessage = terminateVksDataTransferMessageCreate();
	jausMessage = terminateVksDataTransferMessageToJausMessage(terminateVksDataTransferMessage);
	terminateVksDataTransferMessage = terminateVksDataTransferMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	rejectEventRequestMessage = rejectEventRequestMessageCreate();
	jausMessage = rejectEventRequestMessageToJausMessage(rejectEventRequestMessage);
	rejectEventRequestMessage = rejectEventRequestMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	cancelEventMessage = cancelEventMessageCreate();
	jausMessage = cancelEventMessageToJausMessage(cancelEventMessage);
	cancelEventMessage = cancelEventMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	updateEventMessage = updateEventMessageCreate();
	jausMessage = updateEventMessageToJausMessage(updateEventMessage);
	updateEventMessage = updateEventMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	createEventMessage = createEventMessageCreate();
	jausMessage = createEventMessageToJausMessage(createEventMessage);
	createEventMessage = createEventMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	confirmEventRequestMessage = confirmEventRequestMessageCreate();
	jausMessage = confirmEventRequestMessageToJausMessage(confirmEventRequestMessage);
	confirmEventRequestMessage = confirmEventRequestMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setDataLinkStatusMessage = setDataLinkStatusMessageCreate();
	jausMessage = setDataLinkStatusMessageToJausMessage(setDataLinkStatusMessage);
	setDataLinkStatusMessage = setDataLinkStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setSelectedDataLinkStateMessage = setSelectedDataLinkStateMessageCreate();
	jausMessage = setSelectedDataLinkStateMessageToJausMessage(setSelectedDataLinkStateMessage);
	setSelectedDataLinkStateMessage = setSelectedDataLinkStateMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setDataLinkSelectMessage = setDataLinkSelectMessageCreate();
	jausMessage = setDataLinkSelectMessageToJausMessage(setDataLinkSelectMessage);
	setDataLinkSelectMessage = setDataLinkSelectMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setCameraFormatOptionsMessage = setCameraFormatOptionsMessageCreate();
	jausMessage = setCameraFormatOptionsMessageToJausMessage(setCameraFormatOptionsMessage);
	setCameraFormatOptionsMessage = setCameraFormatOptionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	selectCameraMessage = selectCameraMessageCreate();
	jausMessage = selectCameraMessageToJausMessage(selectCameraMessage);
	selectCameraMessage = selectCameraMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setCameraCapabilitiesMessage = setCameraCapabilitiesMessageCreate();
	jausMessage = setCameraCapabilitiesMessageToJausMessage(setCameraCapabilitiesMessage);
	setCameraCapabilitiesMessage = setCameraCapabilitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	setCameraPoseMessage = setCameraPoseMessageCreate();
	jausMessage = setCameraPoseMessageToJausMessage(setCameraPoseMessage);
	setCameraPoseMessage = setCameraPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryTimeMessage = queryTimeMessageCreate();
	jausMessage = queryTimeMessageToJausMessage(queryTimeMessage);
	queryTimeMessage = queryTimeMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryComponentControlMessage = queryComponentControlMessageCreate();
	jausMessage = queryComponentControlMessageToJausMessage(queryComponentControlMessage);
	queryComponentControlMessage = queryComponentControlMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryComponentStatusMessage = queryComponentStatusMessageCreate();
	jausMessage = queryComponentStatusMessageToJausMessage(queryComponentStatusMessage);
	queryComponentStatusMessage = queryComponentStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryComponentAuthorityMessage = queryComponentAuthorityMessageCreate();
	jausMessage = queryComponentAuthorityMessageToJausMessage(queryComponentAuthorityMessage);
	queryComponentAuthorityMessage = queryComponentAuthorityMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryGlobalPoseMessage = queryGlobalPoseMessageCreate();
	jausMessage = queryGlobalPoseMessageToJausMessage(queryGlobalPoseMessage);
	queryGlobalPoseMessage = queryGlobalPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryGlobalWaypointMessage = queryGlobalWaypointMessageCreate();
	jausMessage = queryGlobalWaypointMessageToJausMessage(queryGlobalWaypointMessage);
	queryGlobalWaypointMessage = queryGlobalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryPlatformSpecificationsMessage = queryPlatformSpecificationsMessageCreate();
	jausMessage = queryPlatformSpecificationsMessageToJausMessage(queryPlatformSpecificationsMessage);
	queryPlatformSpecificationsMessage = queryPlatformSpecificationsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryLocalVectorMessage = queryLocalVectorMessageCreate();
	jausMessage = queryLocalVectorMessageToJausMessage(queryLocalVectorMessage);
	queryLocalVectorMessage = queryLocalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryLocalWaypointMessage = queryLocalWaypointMessageCreate();
	jausMessage = queryLocalWaypointMessageToJausMessage(queryLocalWaypointMessage);
	queryLocalWaypointMessage = queryLocalWaypointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryDiscreteDevicesMessage = queryDiscreteDevicesMessageCreate();
	jausMessage = queryDiscreteDevicesMessageToJausMessage(queryDiscreteDevicesMessage);
	queryDiscreteDevicesMessage = queryDiscreteDevicesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryTravelSpeedMessage = queryTravelSpeedMessageCreate();
	jausMessage = queryTravelSpeedMessageToJausMessage(queryTravelSpeedMessage);
	queryTravelSpeedMessage = queryTravelSpeedMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryPlatformOperationalDataMessage = queryPlatformOperationalDataMessageCreate();
	jausMessage = queryPlatformOperationalDataMessageToJausMessage(queryPlatformOperationalDataMessage);
	queryPlatformOperationalDataMessage = queryPlatformOperationalDataMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryVelocityStateMessage = queryVelocityStateMessageCreate();
	jausMessage = queryVelocityStateMessageToJausMessage(queryVelocityStateMessage);
	queryVelocityStateMessage = queryVelocityStateMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryLocalPoseMessage = queryLocalPoseMessageCreate();
	jausMessage = queryLocalPoseMessageToJausMessage(queryLocalPoseMessage);
	queryLocalPoseMessage = queryLocalPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryGlobalVectorMessage = queryGlobalVectorMessageCreate();
	jausMessage = queryGlobalVectorMessageToJausMessage(queryGlobalVectorMessage);
	queryGlobalVectorMessage = queryGlobalVectorMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryLocalPathSegmentMessage = queryLocalPathSegmentMessageCreate();
	jausMessage = queryLocalPathSegmentMessageToJausMessage(queryLocalPathSegmentMessage);
	queryLocalPathSegmentMessage = queryLocalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryWaypointCountMessage = queryWaypointCountMessageCreate();
	jausMessage = queryWaypointCountMessageToJausMessage(queryWaypointCountMessage);
	queryWaypointCountMessage = queryWaypointCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryPathSegmentCountMessage = queryPathSegmentCountMessageCreate();
	jausMessage = queryPathSegmentCountMessageToJausMessage(queryPathSegmentCountMessage);
	queryPathSegmentCountMessage = queryPathSegmentCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryGlobalPathSegmentMessage = queryGlobalPathSegmentMessageCreate();
	jausMessage = queryGlobalPathSegmentMessageToJausMessage(queryGlobalPathSegmentMessage);
	queryGlobalPathSegmentMessage = queryGlobalPathSegmentMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryWrenchEffortMessage = queryWrenchEffortMessageCreate();
	jausMessage = queryWrenchEffortMessageToJausMessage(queryWrenchEffortMessage);
	queryWrenchEffortMessage = queryWrenchEffortMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryManipulatorSpecificationsMessage = queryManipulatorSpecificationsMessageCreate();
	jausMessage = queryManipulatorSpecificationsMessageToJausMessage(queryManipulatorSpecificationsMessage);
	queryManipulatorSpecificationsMessage = queryManipulatorSpecificationsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryJointPositionsMessage = queryJointPositionsMessageCreate();
	jausMessage = queryJointPositionsMessageToJausMessage(queryJointPositionsMessage);
	queryJointPositionsMessage = queryJointPositionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryJointVelocitiesMessage = queryJointVelocitiesMessageCreate();
	jausMessage = queryJointVelocitiesMessageToJausMessage(queryJointVelocitiesMessage);
	queryJointVelocitiesMessage = queryJointVelocitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryToolPointMessage = queryToolPointMessageCreate();
	jausMessage = queryToolPointMessageToJausMessage(queryToolPointMessage);
	queryToolPointMessage = queryToolPointMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryJointEffortsMessage = queryJointEffortsMessageCreate();
	jausMessage = queryJointEffortsMessageToJausMessage(queryJointEffortsMessage);
	queryJointEffortsMessage = queryJointEffortsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryJointForceTorquesMessage = queryJointForceTorquesMessageCreate();
	jausMessage = queryJointForceTorquesMessageToJausMessage(queryJointForceTorquesMessage);
	queryJointForceTorquesMessage = queryJointForceTorquesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryVksFeatureClassMetadataMessage = queryVksFeatureClassMetadataMessageCreate();
	jausMessage = queryVksFeatureClassMetadataMessageToJausMessage(queryVksFeatureClassMetadataMessage);
	queryVksFeatureClassMetadataMessage = queryVksFeatureClassMetadataMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryVksObjectsMessage = queryVksObjectsMessageCreate();
	jausMessage = queryVksObjectsMessageToJausMessage(queryVksObjectsMessage);
	queryVksObjectsMessage = queryVksObjectsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryVksBoundsMessage = queryVksBoundsMessageCreate();
	jausMessage = queryVksBoundsMessageToJausMessage(queryVksBoundsMessage);
	queryVksBoundsMessage = queryVksBoundsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryPayloadInterfaceMessage = queryPayloadInterfaceMessageCreate();
	jausMessage = queryPayloadInterfaceMessageToJausMessage(queryPayloadInterfaceMessage);
	queryPayloadInterfaceMessage = queryPayloadInterfaceMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryPayloadDataElementMessage = queryPayloadDataElementMessageCreate();
	jausMessage = queryPayloadDataElementMessageToJausMessage(queryPayloadDataElementMessage);
	queryPayloadDataElementMessage = queryPayloadDataElementMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryEventsMessage = queryEventsMessageCreate();
	jausMessage = queryEventsMessageToJausMessage(queryEventsMessage);
	queryEventsMessage = queryEventsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryServicesMessage = queryServicesMessageCreate();
	jausMessage = queryServicesMessageToJausMessage(queryServicesMessage);
	queryServicesMessage = queryServicesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryConfigurationMessage = queryConfigurationMessageCreate();
	jausMessage = queryConfigurationMessageToJausMessage(queryConfigurationMessage);
	queryConfigurationMessage = queryConfigurationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	querySubsystemListMessage = querySubsystemListMessageCreate();
	jausMessage = querySubsystemListMessageToJausMessage(querySubsystemListMessage);
	querySubsystemListMessage = querySubsystemListMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryIdentificationMessage = queryIdentificationMessageCreate();
	jausMessage = queryIdentificationMessageToJausMessage(queryIdentificationMessage);
	queryIdentificationMessage = queryIdentificationMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	querySelectedDataLinkStatusMessage = querySelectedDataLinkStatusMessageCreate();
	jausMessage = querySelectedDataLinkStatusMessageToJausMessage(querySelectedDataLinkStatusMessage);
	querySelectedDataLinkStatusMessage = querySelectedDataLinkStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryDataLinkStatusMessage = queryDataLinkStatusMessageCreate();
	jausMessage = queryDataLinkStatusMessageToJausMessage(queryDataLinkStatusMessage);
	queryDataLinkStatusMessage = queryDataLinkStatusMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryHeartbeatPulseMessage = queryHeartbeatPulseMessageCreate();
	jausMessage = queryHeartbeatPulseMessageToJausMessage(queryHeartbeatPulseMessage);
	queryHeartbeatPulseMessage = queryHeartbeatPulseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryCameraFormatOptionsMessage = queryCameraFormatOptionsMessageCreate();
	jausMessage = queryCameraFormatOptionsMessageToJausMessage(queryCameraFormatOptionsMessage);
	queryCameraFormatOptionsMessage = queryCameraFormatOptionsMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryCameraCountMessage = queryCameraCountMessageCreate();
	jausMessage = queryCameraCountMessageToJausMessage(queryCameraCountMessage);
	queryCameraCountMessage = queryCameraCountMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryImageMessage = queryImageMessageCreate();
	jausMessage = queryImageMessageToJausMessage(queryImageMessage);
	queryImageMessage = queryImageMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	querySelectedCameraMessage = querySelectedCameraMessageCreate();
	jausMessage = querySelectedCameraMessageToJausMessage(querySelectedCameraMessage);
	querySelectedCameraMessage = querySelectedCameraMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryRelativeObjectPositionMessage = queryRelativeObjectPositionMessageCreate();
	jausMessage = queryRelativeObjectPositionMessageToJausMessage(queryRelativeObjectPositionMessage);
	queryRelativeObjectPositionMessage = queryRelativeObjectPositionMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryCameraPoseMessage = queryCameraPoseMessageCreate();
	jausMessage = queryCameraPoseMessageToJausMessage(queryCameraPoseMessage);
	queryCameraPoseMessage = queryCameraPoseMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	queryCameraCapabilitiesMessage = queryCameraCapabilitiesMessageCreate();
	jausMessage = queryCameraCapabilitiesMessageToJausMessage(queryCameraCapabilitiesMessage);
	queryCameraCapabilitiesMessage = queryCameraCapabilitiesMessageFromJausMessage(jausMessage);
	jausMessageDestroy(jausMessage);

	return 0;

}
