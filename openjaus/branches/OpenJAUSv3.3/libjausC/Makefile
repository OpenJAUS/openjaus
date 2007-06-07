TARGET	= 	./lib/libjaus.so
CCFLAGS	=	-Wall -std=c99 -O2 -c -g -I ./include/
SOURCES =	./src/jausSubsystem.c \
			./src/jausComponent.c \
			./src/jausNode.c \
			./src/jausState.c \
			./src/jausAddress.c \
			./src/message/inform/platform/reportWrenchEffortMessage.c \
			./src/message/inform/platform/reportPlatformOperationalDataMessage.c \
			./src/message/inform/platform/reportWaypointCountMessage.c \
			./src/message/inform/platform/reportPlatformSpecificationsMessage.c \
			./src/message/inform/platform/reportVelocityStateMessage.c \
			./src/message/inform/platform/reportGlobalWaypointMessage.c \
			./src/message/inform/platform/reportGlobalVectorMessage.c \
			./src/message/inform/platform/reportGlobalPoseMessage.c \
			./src/message/inform/platform/reportTravelSpeedMessage.c \
			./src/message/inform/platform/reportDiscreteDevicesMessage.c \
			./src/message/inform/core/reportTimeMessage.c \
			./src/message/inform/core/reportComponentAuthorityMessage.c \
			./src/message/inform/core/reportComponentStatusMessage.c \
			./src/message/inform/communications/reportHeartbeatPulseMessage.c \
			./src/message/inform/environment/reportVideoFrameMessage.c \
			./src/message/query/platform/queryTravelSpeedMessage.c \
			./src/message/query/platform/queryPlatformOperationalDataMessage.c \
			./src/message/query/platform/queryGlobalWaypointMessage.c \
			./src/message/query/platform/queryWrenchEffortMessage.c \
			./src/message/query/platform/queryGlobalVectorMessage.c \
			./src/message/query/platform/queryPlatformSpecificationsMessage.c \
			./src/message/query/platform/queryDiscreteDevicesMessage.c \
			./src/message/query/platform/queryVelocityStateMessage.c \
			./src/message/query/platform/queryGlobalPoseMessage.c \
			./src/message/query/platform/queryWaypointCountMessage.c \
			./src/message/query/core/queryComponentAuthorityMessage.c \
			./src/message/query/core/queryTimeMessage.c \
			./src/message/query/core/queryComponentStatusMessage.c \
			./src/message/query/communications/queryHeartbeatPulseMessage.c \
			./src/message/query/environment/queryVideoFrameMessage.c \
			./src/message/jausBytePresenceVector.c \
			./src/message/jausIntegerPresenceVector.c \
			./src/message/jausShortPresenceVector.c \
			./src/message/experimental/queryPayloadDataElementMessage.c \
			./src/message/experimental/queryPayloadInterfaceMessage.c \
			./src/message/experimental/reportConfigurationMessage.c \
			./src/message/experimental/events/cancelEventMessage.c \
			./src/message/experimental/events/confirmEventMessage.c \
			./src/message/experimental/events/createEventMessage.c \
			./src/message/experimental/reportIdentificationMessage.c \
			./src/message/experimental/configurationChangedEventNotificationMessage.c \
			./src/message/experimental/queryIdentificationMessage.c \
			./src/message/experimental/reportPayloadDataElementMessage.c \
			./src/message/experimental/queryServicesMessage.c \
			./src/message/experimental/reportPayloadInterfaceMessage.c \
			./src/message/experimental/configurationChangedEventSetupMessage.c \
			./src/message/experimental/setPayloadDataElementMessage.c \
			./src/message/experimental/queryConfigurationMessage.c \
			./src/message/experimental/reportServicesMessage.c \
			./src/message/experimental/worldModel/queryVksFeatureClassMetadataMessage.c \
			./src/message/experimental/worldModel/reportVksBoundsMessage.c \
			./src/message/experimental/worldModel/reportVksObjectsMessage.c \
			./src/message/experimental/worldModel/queryVksBoundsMessage.c \
			./src/message/experimental/worldModel/queryVksObjectsMessage.c \
			./src/message/experimental/worldModel/createVksObjectsMessage.c \
			./src/message/experimental/worldModel/reportVksObjectsCreationMessage.c \
			./src/message/experimental/worldModel/deleteVksObjectsMessage.c \
			./src/message/experimental/worldModel/reportVksFeatureClassMetadataMessage.c \
			./src/message/command/platform/setVelocityStateMessage.c \
			./src/message/command/platform/setGlobalWaypointMessage.c \
			./src/message/command/platform/setDiscreteDevicesMessage.c \
			./src/message/command/platform/setWrenchEffortMessage.c \
			./src/message/command/platform/setGlobalVectorMessage.c \
			./src/message/command/platform/setTravelSpeedMessage.c \
			./src/message/command/core/setEmergencyMessage.c \
			./src/message/command/core/requestComponentControlMessage.c \
			./src/message/command/core/setComponentAuthorityMessage.c \
			./src/message/command/core/shutdownMessage.c \
			./src/message/command/core/activateServiceConnectionMessage.c \
			./src/message/command/core/confirmComponentControlMessage.c \
			./src/message/command/core/standbyMessage.c \
			./src/message/command/core/createServiceConnectionMessage.c \
			./src/message/command/core/setTimeMessage.c \
			./src/message/command/core/suspendServiceConnectionMessage.c \
			./src/message/command/core/releaseComponentControlMessage.c \
			./src/message/command/core/clearEmergencyMessage.c \
			./src/message/command/core/resetMessage.c \
			./src/message/command/core/confirmServiceConnectionMessage.c \
			./src/message/command/core/rejectComponentControlMessage.c \
			./src/message/command/core/resumeMessage.c \
			./src/message/command/core/terminateServiceConnectionMessage.c \
			./src/message/command/environment/selectCameraMessage.c \
			./src/message/jausMessage.c \
			./src/type/jausUnsignedLong.c \
			./src/type/jausByte.c \
			./src/type/jausTime.c \
			./src/type/jausShort.c \
			./src/type/jausFloat.c \
			./src/type/jausDouble.c \
			./src/type/jausLong.c \
			./src/type/jausUnsignedShort.c \
			./src/type/jausWorldModelVectorObject.c \
			./src/type/jausUnsignedInteger.c \
			./src/type/jausType.c \
			./src/type/jausInteger.c \
			./src/type/jausWorldModelFeatureClass.c \
			./src/type/jausEventLimit.c \
			./src/jausPayloadInterface.c \
			./src/jausService.c \
			./src/jausArray.c \
			./src/pointLla.c

OBJECTS =	./Build/jausSubsystem.o \
			./Build/jausComponent.o \
			./Build/jausNode.o \
			./Build/jausState.o \
			./Build/jausAddress.o \
			./Build/reportWrenchEffortMessage.o \
			./Build/reportPlatformOperationalDataMessage.o \
			./Build/reportWaypointCountMessage.o \
			./Build/reportPlatformSpecificationsMessage.o \
			./Build/reportVelocityStateMessage.o \
			./Build/reportGlobalWaypointMessage.o \
			./Build/reportGlobalVectorMessage.o \
			./Build/reportGlobalPoseMessage.o \
			./Build/reportTravelSpeedMessage.o \
			./Build/reportDiscreteDevicesMessage.o \
			./Build/reportTimeMessage.o \
			./Build/reportComponentAuthorityMessage.o \
			./Build/reportComponentStatusMessage.o \
			./Build/reportHeartbeatPulseMessage.o \
			./Build/reportVideoFrameMessage.o \
			./Build/queryTravelSpeedMessage.o \
			./Build/queryPlatformOperationalDataMessage.o \
			./Build/queryGlobalWaypointMessage.o \
			./Build/queryWrenchEffortMessage.o \
			./Build/queryGlobalVectorMessage.o \
			./Build/queryPlatformSpecificationsMessage.o \
			./Build/queryDiscreteDevicesMessage.o \
			./Build/queryVelocityStateMessage.o \
			./Build/queryGlobalPoseMessage.o \
			./Build/queryWaypointCountMessage.o \
			./Build/queryComponentAuthorityMessage.o \
			./Build/queryTimeMessage.o \
			./Build/queryComponentStatusMessage.o \
			./Build/queryHeartbeatPulseMessage.o \
			./Build/queryVideoFrameMessage.o \
			./Build/jausBytePresenceVector.o \
			./Build/jausIntegerPresenceVector.o \
			./Build/jausShortPresenceVector.o \
			./Build/queryPayloadDataElementMessage.o \
			./Build/queryPayloadInterfaceMessage.o \
			./Build/reportConfigurationMessage.o \
			./Build/cancelEventMessage.o \
			./Build/confirmEventMessage.o \
			./Build/createEventMessage.o \
			./Build/reportIdentificationMessage.o \
			./Build/configurationChangedEventNotificationMessage.o \
			./Build/queryIdentificationMessage.o \
			./Build/reportPayloadDataElementMessage.o \
			./Build/queryServicesMessage.o \
			./Build/reportPayloadInterfaceMessage.o \
			./Build/configurationChangedEventSetupMessage.o \
			./Build/setPayloadDataElementMessage.o \
			./Build/queryConfigurationMessage.o \
			./Build/reportServicesMessage.o \
			./Build/queryVksFeatureClassMetadataMessage.o \
			./Build/reportVksBoundsMessage.o \
			./Build/reportVksObjectsMessage.o \
			./Build/queryVksBoundsMessage.o \
			./Build/queryVksObjectsMessage.o \
			./Build/createVksObjectsMessage.o \
			./Build/reportVksObjectsCreationMessage.o \
			./Build/deleteVksObjectsMessage.o \
			./Build/reportVksFeatureClassMetadataMessage.o \
			./Build/setVelocityStateMessage.o \
			./Build/setGlobalWaypointMessage.o \
			./Build/setDiscreteDevicesMessage.o \
			./Build/setWrenchEffortMessage.o \
			./Build/setGlobalVectorMessage.o \
			./Build/setTravelSpeedMessage.o \
			./Build/setEmergencyMessage.o \
			./Build/requestComponentControlMessage.o \
			./Build/setComponentAuthorityMessage.o \
			./Build/shutdownMessage.o \
			./Build/activateServiceConnectionMessage.o \
			./Build/confirmComponentControlMessage.o \
			./Build/standbyMessage.o \
			./Build/createServiceConnectionMessage.o \
			./Build/setTimeMessage.o \
			./Build/suspendServiceConnectionMessage.o \
			./Build/releaseComponentControlMessage.o \
			./Build/clearEmergencyMessage.o \
			./Build/resetMessage.o \
			./Build/confirmServiceConnectionMessage.o \
			./Build/rejectComponentControlMessage.o \
			./Build/resumeMessage.o \
			./Build/terminateServiceConnectionMessage.o \
			./Build/selectCameraMessage.o \
			./Build/jausMessage.o \
			./Build/jausUnsignedLong.o \
			./Build/jausByte.o \
			./Build/jausTime.o \
			./Build/jausShort.o \
			./Build/jausFloat.o \
			./Build/jausDouble.o \
			./Build/jausLong.o \
			./Build/jausUnsignedShort.o \
			./Build/jausWorldModelVectorObject.o \
			./Build/jausUnsignedInteger.o \
			./Build/jausType.o \
			./Build/jausInteger.o \
			./Build/jausWorldModelFeatureClass.o \
			./Build/jausEventLimit.o \
			./Build/jausPayloadInterface.o \
			./Build/jausService.o \
			./Build/jausArray.o \
			./Build/pointLla.o

default : all

all : $(TARGET)

clean :
	rm -f ./Build/*.o
	rm -f $(TARGET)

$(TARGET) : $(OBJECTS)
	gcc -shared -o $(TARGET) $(OBJECTS)

./Build/jausSubsystem.o : ./src/jausSubsystem.c
	gcc $(CCFLAGS) -o ./Build/jausSubsystem.o ./src/jausSubsystem.c

./Build/jausComponent.o : ./src/jausComponent.c
	gcc $(CCFLAGS) -o ./Build/jausComponent.o ./src/jausComponent.c

./Build/jausNode.o : ./src/jausNode.c
	gcc $(CCFLAGS) -o ./Build/jausNode.o ./src/jausNode.c

./Build/jausState.o : ./src/jausState.c
	gcc $(CCFLAGS) -o ./Build/jausState.o ./src/jausState.c

./Build/jausAddress.o : ./src/jausAddress.c
	gcc $(CCFLAGS) -o ./Build/jausAddress.o ./src/jausAddress.c

./Build/reportWrenchEffortMessage.o : ./src/message/inform/platform/reportWrenchEffortMessage.c
	gcc $(CCFLAGS) -o ./Build/reportWrenchEffortMessage.o ./src/message/inform/platform/reportWrenchEffortMessage.c

./Build/reportPlatformOperationalDataMessage.o : ./src/message/inform/platform/reportPlatformOperationalDataMessage.c
	gcc $(CCFLAGS) -o ./Build/reportPlatformOperationalDataMessage.o ./src/message/inform/platform/reportPlatformOperationalDataMessage.c

./Build/reportWaypointCountMessage.o : ./src/message/inform/platform/reportWaypointCountMessage.c
	gcc $(CCFLAGS) -o ./Build/reportWaypointCountMessage.o ./src/message/inform/platform/reportWaypointCountMessage.c

./Build/reportPlatformSpecificationsMessage.o : ./src/message/inform/platform/reportPlatformSpecificationsMessage.c
	gcc $(CCFLAGS) -o ./Build/reportPlatformSpecificationsMessage.o ./src/message/inform/platform/reportPlatformSpecificationsMessage.c

./Build/reportVelocityStateMessage.o : ./src/message/inform/platform/reportVelocityStateMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVelocityStateMessage.o ./src/message/inform/platform/reportVelocityStateMessage.c

./Build/reportGlobalWaypointMessage.o : ./src/message/inform/platform/reportGlobalWaypointMessage.c
	gcc $(CCFLAGS) -o ./Build/reportGlobalWaypointMessage.o ./src/message/inform/platform/reportGlobalWaypointMessage.c

./Build/reportGlobalVectorMessage.o : ./src/message/inform/platform/reportGlobalVectorMessage.c
	gcc $(CCFLAGS) -o ./Build/reportGlobalVectorMessage.o ./src/message/inform/platform/reportGlobalVectorMessage.c

./Build/reportGlobalPoseMessage.o : ./src/message/inform/platform/reportGlobalPoseMessage.c
	gcc $(CCFLAGS) -o ./Build/reportGlobalPoseMessage.o ./src/message/inform/platform/reportGlobalPoseMessage.c

./Build/reportTravelSpeedMessage.o : ./src/message/inform/platform/reportTravelSpeedMessage.c
	gcc $(CCFLAGS) -o ./Build/reportTravelSpeedMessage.o ./src/message/inform/platform/reportTravelSpeedMessage.c

./Build/reportDiscreteDevicesMessage.o : ./src/message/inform/platform/reportDiscreteDevicesMessage.c
	gcc $(CCFLAGS) -o ./Build/reportDiscreteDevicesMessage.o ./src/message/inform/platform/reportDiscreteDevicesMessage.c

./Build/reportTimeMessage.o : ./src/message/inform/core/reportTimeMessage.c
	gcc $(CCFLAGS) -o ./Build/reportTimeMessage.o ./src/message/inform/core/reportTimeMessage.c

./Build/reportComponentAuthorityMessage.o : ./src/message/inform/core/reportComponentAuthorityMessage.c
	gcc $(CCFLAGS) -o ./Build/reportComponentAuthorityMessage.o ./src/message/inform/core/reportComponentAuthorityMessage.c

./Build/reportComponentStatusMessage.o : ./src/message/inform/core/reportComponentStatusMessage.c
	gcc $(CCFLAGS) -o ./Build/reportComponentStatusMessage.o ./src/message/inform/core/reportComponentStatusMessage.c

./Build/reportHeartbeatPulseMessage.o : ./src/message/inform/communications/reportHeartbeatPulseMessage.c
	gcc $(CCFLAGS) -o ./Build/reportHeartbeatPulseMessage.o ./src/message/inform/communications/reportHeartbeatPulseMessage.c

./Build/reportVideoFrameMessage.o : ./src/message/inform/environment/reportVideoFrameMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVideoFrameMessage.o ./src/message/inform/environment/reportVideoFrameMessage.c

./Build/queryTravelSpeedMessage.o : ./src/message/query/platform/queryTravelSpeedMessage.c
	gcc $(CCFLAGS) -o ./Build/queryTravelSpeedMessage.o ./src/message/query/platform/queryTravelSpeedMessage.c

./Build/queryPlatformOperationalDataMessage.o : ./src/message/query/platform/queryPlatformOperationalDataMessage.c
	gcc $(CCFLAGS) -o ./Build/queryPlatformOperationalDataMessage.o ./src/message/query/platform/queryPlatformOperationalDataMessage.c

./Build/queryGlobalWaypointMessage.o : ./src/message/query/platform/queryGlobalWaypointMessage.c
	gcc $(CCFLAGS) -o ./Build/queryGlobalWaypointMessage.o ./src/message/query/platform/queryGlobalWaypointMessage.c

./Build/queryWrenchEffortMessage.o : ./src/message/query/platform/queryWrenchEffortMessage.c
	gcc $(CCFLAGS) -o ./Build/queryWrenchEffortMessage.o ./src/message/query/platform/queryWrenchEffortMessage.c

./Build/queryGlobalVectorMessage.o : ./src/message/query/platform/queryGlobalVectorMessage.c
	gcc $(CCFLAGS) -o ./Build/queryGlobalVectorMessage.o ./src/message/query/platform/queryGlobalVectorMessage.c

./Build/queryPlatformSpecificationsMessage.o : ./src/message/query/platform/queryPlatformSpecificationsMessage.c
	gcc $(CCFLAGS) -o ./Build/queryPlatformSpecificationsMessage.o ./src/message/query/platform/queryPlatformSpecificationsMessage.c

./Build/queryDiscreteDevicesMessage.o : ./src/message/query/platform/queryDiscreteDevicesMessage.c
	gcc $(CCFLAGS) -o ./Build/queryDiscreteDevicesMessage.o ./src/message/query/platform/queryDiscreteDevicesMessage.c

./Build/queryVelocityStateMessage.o : ./src/message/query/platform/queryVelocityStateMessage.c
	gcc $(CCFLAGS) -o ./Build/queryVelocityStateMessage.o ./src/message/query/platform/queryVelocityStateMessage.c

./Build/queryGlobalPoseMessage.o : ./src/message/query/platform/queryGlobalPoseMessage.c
	gcc $(CCFLAGS) -o ./Build/queryGlobalPoseMessage.o ./src/message/query/platform/queryGlobalPoseMessage.c

./Build/queryWaypointCountMessage.o : ./src/message/query/platform/queryWaypointCountMessage.c
	gcc $(CCFLAGS) -o ./Build/queryWaypointCountMessage.o ./src/message/query/platform/queryWaypointCountMessage.c

./Build/queryComponentAuthorityMessage.o : ./src/message/query/core/queryComponentAuthorityMessage.c
	gcc $(CCFLAGS) -o ./Build/queryComponentAuthorityMessage.o ./src/message/query/core/queryComponentAuthorityMessage.c

./Build/queryTimeMessage.o : ./src/message/query/core/queryTimeMessage.c
	gcc $(CCFLAGS) -o ./Build/queryTimeMessage.o ./src/message/query/core/queryTimeMessage.c

./Build/queryComponentStatusMessage.o : ./src/message/query/core/queryComponentStatusMessage.c
	gcc $(CCFLAGS) -o ./Build/queryComponentStatusMessage.o ./src/message/query/core/queryComponentStatusMessage.c

./Build/queryHeartbeatPulseMessage.o : ./src/message/query/communications/queryHeartbeatPulseMessage.c
	gcc $(CCFLAGS) -o ./Build/queryHeartbeatPulseMessage.o ./src/message/query/communications/queryHeartbeatPulseMessage.c

./Build/queryVideoFrameMessage.o : ./src/message/query/environment/queryVideoFrameMessage.c
	gcc $(CCFLAGS) -o ./Build/queryVideoFrameMessage.o ./src/message/query/environment/queryVideoFrameMessage.c

./Build/jausBytePresenceVector.o : ./src/message/jausBytePresenceVector.c
	gcc $(CCFLAGS) -o ./Build/jausBytePresenceVector.o ./src/message/jausBytePresenceVector.c

./Build/jausIntegerPresenceVector.o : ./src/message/jausIntegerPresenceVector.c
	gcc $(CCFLAGS) -o ./Build/jausIntegerPresenceVector.o ./src/message/jausIntegerPresenceVector.c

./Build/jausShortPresenceVector.o : ./src/message/jausShortPresenceVector.c
	gcc $(CCFLAGS) -o ./Build/jausShortPresenceVector.o ./src/message/jausShortPresenceVector.c

./Build/queryPayloadDataElementMessage.o : ./src/message/experimental/queryPayloadDataElementMessage.c
	gcc $(CCFLAGS) -o ./Build/queryPayloadDataElementMessage.o ./src/message/experimental/queryPayloadDataElementMessage.c

./Build/queryPayloadInterfaceMessage.o : ./src/message/experimental/queryPayloadInterfaceMessage.c
	gcc $(CCFLAGS) -o ./Build/queryPayloadInterfaceMessage.o ./src/message/experimental/queryPayloadInterfaceMessage.c

./Build/reportConfigurationMessage.o : ./src/message/experimental/reportConfigurationMessage.c
	gcc $(CCFLAGS) -o ./Build/reportConfigurationMessage.o ./src/message/experimental/reportConfigurationMessage.c

./Build/cancelEventMessage.o : ./src/message/experimental/events/cancelEventMessage.c
	gcc $(CCFLAGS) -o ./Build/cancelEventMessage.o ./src/message/experimental/events/cancelEventMessage.c

./Build/confirmEventMessage.o : ./src/message/experimental/events/confirmEventMessage.c
	gcc $(CCFLAGS) -o ./Build/confirmEventMessage.o ./src/message/experimental/events/confirmEventMessage.c

./Build/createEventMessage.o : ./src/message/experimental/events/createEventMessage.c
	gcc $(CCFLAGS) -o ./Build/createEventMessage.o ./src/message/experimental/events/createEventMessage.c

./Build/reportIdentificationMessage.o : ./src/message/experimental/reportIdentificationMessage.c
	gcc $(CCFLAGS) -o ./Build/reportIdentificationMessage.o ./src/message/experimental/reportIdentificationMessage.c

./Build/configurationChangedEventNotificationMessage.o : ./src/message/experimental/configurationChangedEventNotificationMessage.c
	gcc $(CCFLAGS) -o ./Build/configurationChangedEventNotificationMessage.o ./src/message/experimental/configurationChangedEventNotificationMessage.c

./Build/queryIdentificationMessage.o : ./src/message/experimental/queryIdentificationMessage.c
	gcc $(CCFLAGS) -o ./Build/queryIdentificationMessage.o ./src/message/experimental/queryIdentificationMessage.c

./Build/reportPayloadDataElementMessage.o : ./src/message/experimental/reportPayloadDataElementMessage.c
	gcc $(CCFLAGS) -o ./Build/reportPayloadDataElementMessage.o ./src/message/experimental/reportPayloadDataElementMessage.c

./Build/queryServicesMessage.o : ./src/message/experimental/queryServicesMessage.c
	gcc $(CCFLAGS) -o ./Build/queryServicesMessage.o ./src/message/experimental/queryServicesMessage.c

./Build/reportPayloadInterfaceMessage.o : ./src/message/experimental/reportPayloadInterfaceMessage.c
	gcc $(CCFLAGS) -o ./Build/reportPayloadInterfaceMessage.o ./src/message/experimental/reportPayloadInterfaceMessage.c

./Build/configurationChangedEventSetupMessage.o : ./src/message/experimental/configurationChangedEventSetupMessage.c
	gcc $(CCFLAGS) -o ./Build/configurationChangedEventSetupMessage.o ./src/message/experimental/configurationChangedEventSetupMessage.c

./Build/setPayloadDataElementMessage.o : ./src/message/experimental/setPayloadDataElementMessage.c
	gcc $(CCFLAGS) -o ./Build/setPayloadDataElementMessage.o ./src/message/experimental/setPayloadDataElementMessage.c

./Build/queryConfigurationMessage.o : ./src/message/experimental/queryConfigurationMessage.c
	gcc $(CCFLAGS) -o ./Build/queryConfigurationMessage.o ./src/message/experimental/queryConfigurationMessage.c

./Build/reportServicesMessage.o : ./src/message/experimental/reportServicesMessage.c
	gcc $(CCFLAGS) -o ./Build/reportServicesMessage.o ./src/message/experimental/reportServicesMessage.c

./Build/queryVksFeatureClassMetadataMessage.o : ./src/message/experimental/worldModel/queryVksFeatureClassMetadataMessage.c
	gcc $(CCFLAGS) -o ./Build/queryVksFeatureClassMetadataMessage.o ./src/message/experimental/worldModel/queryVksFeatureClassMetadataMessage.c

./Build/reportVksBoundsMessage.o : ./src/message/experimental/worldModel/reportVksBoundsMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVksBoundsMessage.o ./src/message/experimental/worldModel/reportVksBoundsMessage.c

./Build/reportVksObjectsMessage.o : ./src/message/experimental/worldModel/reportVksObjectsMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVksObjectsMessage.o ./src/message/experimental/worldModel/reportVksObjectsMessage.c

./Build/queryVksBoundsMessage.o : ./src/message/experimental/worldModel/queryVksBoundsMessage.c
	gcc $(CCFLAGS) -o ./Build/queryVksBoundsMessage.o ./src/message/experimental/worldModel/queryVksBoundsMessage.c

./Build/queryVksObjectsMessage.o : ./src/message/experimental/worldModel/queryVksObjectsMessage.c
	gcc $(CCFLAGS) -o ./Build/queryVksObjectsMessage.o ./src/message/experimental/worldModel/queryVksObjectsMessage.c

./Build/createVksObjectsMessage.o : ./src/message/experimental/worldModel/createVksObjectsMessage.c
	gcc $(CCFLAGS) -o ./Build/createVksObjectsMessage.o ./src/message/experimental/worldModel/createVksObjectsMessage.c

./Build/reportVksObjectsCreationMessage.o : ./src/message/experimental/worldModel/reportVksObjectsCreationMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVksObjectsCreationMessage.o ./src/message/experimental/worldModel/reportVksObjectsCreationMessage.c

./Build/deleteVksObjectsMessage.o : ./src/message/experimental/worldModel/deleteVksObjectsMessage.c
	gcc $(CCFLAGS) -o ./Build/deleteVksObjectsMessage.o ./src/message/experimental/worldModel/deleteVksObjectsMessage.c

./Build/reportVksFeatureClassMetadataMessage.o : ./src/message/experimental/worldModel/reportVksFeatureClassMetadataMessage.c
	gcc $(CCFLAGS) -o ./Build/reportVksFeatureClassMetadataMessage.o ./src/message/experimental/worldModel/reportVksFeatureClassMetadataMessage.c

./Build/setVelocityStateMessage.o : ./src/message/command/platform/setVelocityStateMessage.c
	gcc $(CCFLAGS) -o ./Build/setVelocityStateMessage.o ./src/message/command/platform/setVelocityStateMessage.c

./Build/setGlobalWaypointMessage.o : ./src/message/command/platform/setGlobalWaypointMessage.c
	gcc $(CCFLAGS) -o ./Build/setGlobalWaypointMessage.o ./src/message/command/platform/setGlobalWaypointMessage.c

./Build/setDiscreteDevicesMessage.o : ./src/message/command/platform/setDiscreteDevicesMessage.c
	gcc $(CCFLAGS) -o ./Build/setDiscreteDevicesMessage.o ./src/message/command/platform/setDiscreteDevicesMessage.c

./Build/setWrenchEffortMessage.o : ./src/message/command/platform/setWrenchEffortMessage.c
	gcc $(CCFLAGS) -o ./Build/setWrenchEffortMessage.o ./src/message/command/platform/setWrenchEffortMessage.c

./Build/setGlobalVectorMessage.o : ./src/message/command/platform/setGlobalVectorMessage.c
	gcc $(CCFLAGS) -o ./Build/setGlobalVectorMessage.o ./src/message/command/platform/setGlobalVectorMessage.c

./Build/setTravelSpeedMessage.o : ./src/message/command/platform/setTravelSpeedMessage.c
	gcc $(CCFLAGS) -o ./Build/setTravelSpeedMessage.o ./src/message/command/platform/setTravelSpeedMessage.c

./Build/setEmergencyMessage.o : ./src/message/command/core/setEmergencyMessage.c
	gcc $(CCFLAGS) -o ./Build/setEmergencyMessage.o ./src/message/command/core/setEmergencyMessage.c

./Build/requestComponentControlMessage.o : ./src/message/command/core/requestComponentControlMessage.c
	gcc $(CCFLAGS) -o ./Build/requestComponentControlMessage.o ./src/message/command/core/requestComponentControlMessage.c

./Build/setComponentAuthorityMessage.o : ./src/message/command/core/setComponentAuthorityMessage.c
	gcc $(CCFLAGS) -o ./Build/setComponentAuthorityMessage.o ./src/message/command/core/setComponentAuthorityMessage.c

./Build/shutdownMessage.o : ./src/message/command/core/shutdownMessage.c
	gcc $(CCFLAGS) -o ./Build/shutdownMessage.o ./src/message/command/core/shutdownMessage.c

./Build/activateServiceConnectionMessage.o : ./src/message/command/core/activateServiceConnectionMessage.c
	gcc $(CCFLAGS) -o ./Build/activateServiceConnectionMessage.o ./src/message/command/core/activateServiceConnectionMessage.c

./Build/confirmComponentControlMessage.o : ./src/message/command/core/confirmComponentControlMessage.c
	gcc $(CCFLAGS) -o ./Build/confirmComponentControlMessage.o ./src/message/command/core/confirmComponentControlMessage.c

./Build/standbyMessage.o : ./src/message/command/core/standbyMessage.c
	gcc $(CCFLAGS) -o ./Build/standbyMessage.o ./src/message/command/core/standbyMessage.c

./Build/createServiceConnectionMessage.o : ./src/message/command/core/createServiceConnectionMessage.c
	gcc $(CCFLAGS) -o ./Build/createServiceConnectionMessage.o ./src/message/command/core/createServiceConnectionMessage.c

./Build/setTimeMessage.o : ./src/message/command/core/setTimeMessage.c
	gcc $(CCFLAGS) -o ./Build/setTimeMessage.o ./src/message/command/core/setTimeMessage.c

./Build/suspendServiceConnectionMessage.o : ./src/message/command/core/suspendServiceConnectionMessage.c
	gcc $(CCFLAGS) -o ./Build/suspendServiceConnectionMessage.o ./src/message/command/core/suspendServiceConnectionMessage.c

./Build/releaseComponentControlMessage.o : ./src/message/command/core/releaseComponentControlMessage.c
	gcc $(CCFLAGS) -o ./Build/releaseComponentControlMessage.o ./src/message/command/core/releaseComponentControlMessage.c

./Build/clearEmergencyMessage.o : ./src/message/command/core/clearEmergencyMessage.c
	gcc $(CCFLAGS) -o ./Build/clearEmergencyMessage.o ./src/message/command/core/clearEmergencyMessage.c

./Build/resetMessage.o : ./src/message/command/core/resetMessage.c
	gcc $(CCFLAGS) -o ./Build/resetMessage.o ./src/message/command/core/resetMessage.c

./Build/confirmServiceConnectionMessage.o : ./src/message/command/core/confirmServiceConnectionMessage.c
	gcc $(CCFLAGS) -o ./Build/confirmServiceConnectionMessage.o ./src/message/command/core/confirmServiceConnectionMessage.c

./Build/rejectComponentControlMessage.o : ./src/message/command/core/rejectComponentControlMessage.c
	gcc $(CCFLAGS) -o ./Build/rejectComponentControlMessage.o ./src/message/command/core/rejectComponentControlMessage.c

./Build/resumeMessage.o : ./src/message/command/core/resumeMessage.c
	gcc $(CCFLAGS) -o ./Build/resumeMessage.o ./src/message/command/core/resumeMessage.c

./Build/terminateServiceConnectionMessage.o : ./src/message/command/core/terminateServiceConnectionMessage.c
	gcc $(CCFLAGS) -o ./Build/terminateServiceConnectionMessage.o ./src/message/command/core/terminateServiceConnectionMessage.c

./Build/selectCameraMessage.o : ./src/message/command/environment/selectCameraMessage.c
	gcc $(CCFLAGS) -o ./Build/selectCameraMessage.o ./src/message/command/environment/selectCameraMessage.c

./Build/jausMessage.o : ./src/message/jausMessage.c
	gcc $(CCFLAGS) -o ./Build/jausMessage.o ./src/message/jausMessage.c

./Build/jausUnsignedLong.o : ./src/type/jausUnsignedLong.c
	gcc $(CCFLAGS) -o ./Build/jausUnsignedLong.o ./src/type/jausUnsignedLong.c

./Build/jausByte.o : ./src/type/jausByte.c
	gcc $(CCFLAGS) -o ./Build/jausByte.o ./src/type/jausByte.c

./Build/jausTime.o : ./src/type/jausTime.c
	gcc $(CCFLAGS) -o ./Build/jausTime.o ./src/type/jausTime.c

./Build/jausShort.o : ./src/type/jausShort.c
	gcc $(CCFLAGS) -o ./Build/jausShort.o ./src/type/jausShort.c

./Build/jausFloat.o : ./src/type/jausFloat.c
	gcc $(CCFLAGS) -o ./Build/jausFloat.o ./src/type/jausFloat.c

./Build/jausDouble.o : ./src/type/jausDouble.c
	gcc $(CCFLAGS) -o ./Build/jausDouble.o ./src/type/jausDouble.c

./Build/jausLong.o : ./src/type/jausLong.c
	gcc $(CCFLAGS) -o ./Build/jausLong.o ./src/type/jausLong.c

./Build/jausUnsignedShort.o : ./src/type/jausUnsignedShort.c
	gcc $(CCFLAGS) -o ./Build/jausUnsignedShort.o ./src/type/jausUnsignedShort.c

./Build/jausWorldModelVectorObject.o : ./src/type/jausWorldModelVectorObject.c
	gcc $(CCFLAGS) -o ./Build/jausWorldModelVectorObject.o ./src/type/jausWorldModelVectorObject.c

./Build/jausUnsignedInteger.o : ./src/type/jausUnsignedInteger.c
	gcc $(CCFLAGS) -o ./Build/jausUnsignedInteger.o ./src/type/jausUnsignedInteger.c

./Build/jausType.o : ./src/type/jausType.c
	gcc $(CCFLAGS) -o ./Build/jausType.o ./src/type/jausType.c

./Build/jausInteger.o : ./src/type/jausInteger.c
	gcc $(CCFLAGS) -o ./Build/jausInteger.o ./src/type/jausInteger.c

./Build/jausWorldModelFeatureClass.o : ./src/type/jausWorldModelFeatureClass.c
	gcc $(CCFLAGS) -o ./Build/jausWorldModelFeatureClass.o ./src/type/jausWorldModelFeatureClass.c

./Build/jausEventLimit.o : ./src/type/jausEventLimit.c
	gcc $(CCFLAGS) -o ./Build/jausEventLimit.o ./src/type/jausEventLimit.c

./Build/jausPayloadInterface.o : ./src/jausPayloadInterface.c
	gcc $(CCFLAGS) -o ./Build/jausPayloadInterface.o ./src/jausPayloadInterface.c

./Build/jausService.o : ./src/jausService.c
	gcc $(CCFLAGS) -o ./Build/jausService.o ./src/jausService.c

./Build/jausArray.o : ./src/jausArray.c
	gcc $(CCFLAGS) -o ./Build/jausArray.o ./src/jausArray.c

./Build/pointLla.o : ./src/pointLla.c
	gcc $(CCFLAGS) -o ./Build/pointLla.o ./src/pointLla.c
