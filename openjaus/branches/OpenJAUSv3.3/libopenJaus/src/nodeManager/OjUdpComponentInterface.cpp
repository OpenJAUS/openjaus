#include "OjUdpComponentInterface.h"
#include "ErrorEvent.h"

OjUdpComponentInterface::OjUdpComponentInterface(FileLoader *configData, EventHandler *handler, JausComponentCommunicationManager *cmptMngr)
{
	this->configData = configData;
	this->commMngr = cmptMngr;
	this->eventHandler = handler;
	
	this->systemTree = cmptMngr->getSystemTree();
	this->nodeManager = cmptMngr->getNodeManagerComponent();
	this->type = COMPONENT_INTERFACE;
	this->name = "OpenJAUS UDP Component to Node Manager Interface";
	this->portMap.empty();

	// Open our socket
	this->openSocket();

	// Setup our pThread
	this->setupThread();
}

OjUdpComponentInterface::~OjUdpComponentInterface(void){}

unsigned int OjUdpComponentInterface::getPort(void)
{
	return this->socket->port;
}

bool OjUdpComponentInterface::routeMessage(JausMessage message)
{ 
	// This interface does not transport jaus messages
	// This isn't an "error" because the cmptMngr send JausMessages to all known interfaces for broadcasts
	jausMessageDestroy(message);
	return false;
}

bool OjUdpComponentInterface::sendDatagramPacket(DatagramPacket dgPacket)
{
	return true;
}

void OjUdpComponentInterface::openSocket(void)
{
	// Read Configuration
	this->portNumber = this->configData->GetConfigDataInt("Component_Communications", "OpenJAUS_UDP_Port");
	this->ipAddress = inetAddressGetByString((char *)this->configData->GetConfigDataString("Component_Communications", "OpenJAUS_UDP_IP").c_str());
	if(this->ipAddress == NULL)
	{
		this->ipAddress = inetAddressCreate();
		this->ipAddress->value = INADDR_ANY;
	}

	// Create Component Socket
	this->socket = datagramSocketCreate(this->portNumber, ipAddress);
	if(!this->socket)
	{
		// Error creating our socket
		return;
	}

	// Setup Timeout
	datagramSocketSetTimeout(this->socket, this->configData->GetConfigDataInt("Component_Communications", "OpenJAUS_UDP_Timeout_Sec"));
}

void OjUdpComponentInterface::closeSocket(void)
{
	datagramSocketDestroy(this->socket);
}

void OjUdpComponentInterface::run()
{
	DatagramPacket packet;
	JausAddress address;
	JausAddress lookupAddress;
	int bytesRecv = 0;
	char buf[256] = {0};
	int componentId = 0;
	//int componentMessagePort = 0;
	//int instanceId = 0;
	int commandCode = 0;
	int serviceType = 0;

	packet = datagramPacketCreate();
	packet->bufferSizeBytes = OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES;
	packet->buffer = (unsigned char *) calloc(packet->bufferSizeBytes, 1);
	
	while(this->running)
	{
		bytesRecv = datagramSocketReceive(this->socket, packet);
		if(bytesRecv == OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES)
		{
			// This is to ensure we are using a valid NM pointer (this occurs
			this->nodeManager = ((JausComponentCommunicationManager *)this->commMngr)->getNodeManagerComponent();

			switch(packet->buffer[0])
			{
				case CHECK_IN:
					// System.out.println("ComponentInterface: Received Query JAUS address command from: " + JausComponent.getName(componentId));
					componentId = (packet->buffer[1] & 0xFF);
					if(componentId < JAUS_MINIMUM_COMPONENT_ID || componentId > JAUS_MAXIMUM_COMPONENT_ID)
					{
						sprintf(buf, "Invalid Component Id (%d) trying to check in.", componentId);
						ErrorEvent *e = new ErrorEvent(ErrorEvent::Configuration, __FUNCTION__, __LINE__, buf);
						this->eventHandler->handleEvent(e);
						return;
					}

					address = this->nodeManager->checkInLocalComponent(componentId);
					if(!address || !jausAddressIsValid(address))
					{
						sprintf(buf, "Cannot add local component with Id: %d.", componentId);
						ErrorEvent *e = new ErrorEvent(ErrorEvent::Warning, __FUNCTION__, __LINE__, buf);
						this->eventHandler->handleEvent(e);
						
						// TODO: Send back checkin error reply (no available instance)							
						break;
					}
				
					//componentMessagePort = (packet->buffer[2] & 0xFF) + ((packet->buffer[3] & 0xFF) << 8);

					memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
					packet->buffer[0] = REPORT_ADDRESS;
					packet->buffer[1] = (unsigned char)(address->instance & 0xFF);
					packet->buffer[2] = (unsigned char)(address->component & 0xFF);
					packet->buffer[3] = (unsigned char)(address->node & 0xFF);
					packet->buffer[4] = (unsigned char)(address->subsystem & 0xFF);
					packet->address = this->ipAddress;

					datagramSocketSend(this->socket, packet);
					jausAddressDestroy(address);
					break;

				case CHECK_OUT:
					nodeManager->checkOutLocalComponent(packet->buffer[4], packet->buffer[3], packet->buffer[2], packet->buffer[1]);
					break;
				    
				case VERIFY_ADDRESS:
					lookupAddress = jausAddressCreate();
					lookupAddress->instance = (packet->buffer[1] & 0xFF);
					lookupAddress->component = (packet->buffer[2] & 0xFF);
					lookupAddress->node = (packet->buffer[3] & 0xFF);
					lookupAddress->subsystem = (packet->buffer[4] & 0xFF);						

					memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
					packet->buffer[0] = ADDRESS_VERIFIED;
					if(this->systemTree->hasComponent(lookupAddress))
					{
						packet->buffer[1] = JAUS_TRUE;
					}
					else
					{
						packet->buffer[1] = JAUS_FALSE;
					}
					packet->address = this->ipAddress;

					datagramSocketSend(this->socket, packet);
					jausAddressDestroy(lookupAddress);
					break;
					
				case GET_COMPONENT_ADDRESS_LIST:
					componentId  = packet->buffer[1] & 0xFF;
					//	
					
					address = systemTree->lookUpAddress(JAUS_ADDRESS_WILDCARD_OCTET, JAUS_ADDRESS_WILDCARD_OCTET, componentId, JAUS_ADDRESS_WILDCARD_OCTET);
					memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
					packet->buffer[0] = COMPONENT_ADDRESS_LIST_RESPONSE;
					//		
					if(!address || !jausAddressIsValid(address))
					{
						packet->buffer[1] = (unsigned char)(JAUS_INVALID_INSTANCE_ID & 0xFF);
						packet->buffer[2] = (unsigned char)(JAUS_INVALID_COMPONENT_ID & 0xFF);
						packet->buffer[3] = (unsigned char)(JAUS_INVALID_NODE_ID & 0xFF);
						packet->buffer[4] = (unsigned char)(JAUS_INVALID_SUBSYSTEM_ID & 0xFF);
//						packet->buffer[1] = (unsigned char)(JAUS_INVALID_SUBSYSTEM_ID & 0xFF);
//						packet->buffer[2] = (unsigned char)(JAUS_INVALID_NODE_ID & 0xFF);
//						packet->buffer[3] = (unsigned char)(JAUS_INVALID_COMPONENT_ID & 0xFF);
//						packet->buffer[4] = (unsigned char)(JAUS_INVALID_INSTANCE_ID & 0xFF);
						//if(log.isDebugEnabled())log.debug("Get address for component ID: " + componentId + " returning: 0.0.0.0");
					}
					else
					{
						packet->buffer[1] = (unsigned char)(address->instance & 0xFF);
						packet->buffer[2] = (unsigned char)(address->component & 0xFF);
						packet->buffer[3] = (unsigned char)(address->node & 0xFF);
						packet->buffer[4] = (unsigned char)(address->subsystem & 0xFF);
//						packet->buffer[1] = (unsigned char)(address->subsystem & 0xFF);
//						packet->buffer[2] = (unsigned char)(address->node & 0xFF);
//						packet->buffer[3] = (unsigned char)(address->component & 0xFF);
//						packet->buffer[4] = (unsigned char)(address->instance & 0xFF);
						//if(log.isDebugEnabled())log.debug("Get address for component ID: " + componentId + " returning: " + address);
					}
					packet->address = this->ipAddress;
					datagramSocketSend(this->socket, packet);
					jausAddressDestroy(address);
				break;
					
					

				case LOOKUP_ADDRESS:
					lookupAddress = jausAddressCreate();
					lookupAddress->instance = (packet->buffer[1] & 0xFF);
					lookupAddress->component = (packet->buffer[2] & 0xFF);
					lookupAddress->node = (packet->buffer[3] & 0xFF);
					lookupAddress->subsystem = (packet->buffer[4] & 0xFF);						
					//if(log.isDebugEnabled())log.debug("Looking Up Address: " + address);

					memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
					packet->buffer[0] = LOOKUP_ADDRESS_RESPONSE;
					
					address = systemTree->lookUpAddress(lookupAddress);
					if(address && jausAddressIsValid(address))
					{
						packet->buffer[5] = (unsigned char) JAUS_TRUE;
						//if(log.isDebugEnabled())log.debug("Lookup Address Found: " + address);
					}
					else
					{
						packet->buffer[5] = (unsigned char) JAUS_FALSE;					
						//if(log.isDebugEnabled())log.debug("Lookup Address NOT Found: " + address);
					}
					
					packet->buffer[1] = (unsigned char) (address->instance & 0xFF);
					packet->buffer[2] = (unsigned char) (address->component & 0xFF);
					packet->buffer[3] = (unsigned char) (address->node & 0xFF);
					packet->buffer[4] = (unsigned char) (address->subsystem & 0xFF);
					packet->address = this->ipAddress;
					datagramSocketSend(this->socket, packet);
					jausAddressDestroy(address);
					jausAddressDestroy(lookupAddress);
					break;

				case LOOKUP_SERVICE_ADDRESS:
// 					if(true)
// 					{
// 						sprintf(buf, "Accepted LSA");
// 						sprintf(buf, "LSA value. CC: 0x%02X\n", LOOKUP_SERVICE_ADDRESS);
// 						ErrorEvent *e = new ErrorEvent(ErrorEvent::Warning, __FUNCTION__, __LINE__, buf);
// 						this->eventHandler->handleEvent(e);
// 					}
					lookupAddress = jausAddressCreate();
					lookupAddress->instance = (packet->buffer[1] & 0xFF);
					lookupAddress->component = (packet->buffer[2] & 0xFF);
					lookupAddress->node = (packet->buffer[3] & 0xFF);
					lookupAddress->subsystem = (packet->buffer[4] & 0xFF);
// 				//	lookupAddress->instance(packet->buffer[1] & 0xFF);
// 				//	lookupAddress->component(packet->buffer[2] & 0xFF);
// 				//	lookupAddress->node(packet->buffer[3] & 0xFF);
// 				//	lookupAddress->subsystem(packet->buffer[4] & 0xFF);						
// 				//	
					commandCode = (packet->buffer[5] & 0xFF) + ((packet->buffer[6] & 0xFF) << 8);
					serviceType = (packet->buffer[7] & 0xFF);
// 					//if(log.isDebugEnabled())log.debug("Looking Up Address: " + address);
// 
					memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
					packet->buffer[0] = LOOKUP_SERVICE_ADDRESS_RESPONSE;
					
					address = systemTree->lookUpServiceInSystem(commandCode, serviceType);
					if(address && jausAddressIsValid(address)) 
					//if(subsystemTable.lookUpServiceAddressInSystem(address, commandCode, serviceCommandType))
					{
// 						sprintf(buf, "Got a good address.");
// 						ErrorEvent *e = new ErrorEvent(ErrorEvent::Warning, __FUNCTION__, __LINE__, buf);
// 						this->eventHandler->handleEvent(e);

						packet->buffer[5] = (unsigned char) JAUS_TRUE;
						//if(log.isDebugEnabled())log.debug("Lookup Address Found: " + address);
						packet->buffer[1] = (unsigned char) (address->instance & 0xFF);
						packet->buffer[2] = (unsigned char) (address->component & 0xFF);
						packet->buffer[3] = (unsigned char) (address->node & 0xFF);
						packet->buffer[4] = (unsigned char) (address->subsystem & 0xFF);
						packet->address = this->ipAddress;
					}
					else
					{
// 						sprintf(buf, "Invalid address.");
// 						ErrorEvent *e = new ErrorEvent(ErrorEvent::Warning, __FUNCTION__, __LINE__, buf);
// 						this->eventHandler->handleEvent(e);

						packet->buffer[5] = (unsigned char) JAUS_FALSE;
					}

						datagramSocketSend(this->socket, packet);
					if(address)
					{
						jausAddressDestroy(address);
						jausAddressDestroy(lookupAddress);
					}
					
// 					packet->buffer[1] = (unsigned char) (address->instance & 0xFF);
// 					packet->buffer[2] = (unsigned char) (address->component & 0xFF);
// 					packet->buffer[3] = (unsigned char) (address->node & 0xFF);
// 					packet->buffer[4] = (unsigned char) (address->subsystem & 0xFF);
// 					packet->address = this->ipAddress;
// 					datagramSocketSend(this->socket, packet);
// 					jausAddressDestroy(address);
// 					jausAddressDestroy(lookupAddress);
					break;

				//case InterfaceMessage.NODE_MANAGER_LOOKUP_SERVICE_ADDRESS_LIST:
				//	lookupAddress = jausAddressCreate();
				//	lookupAddress->instance(packet->buffer[1] & 0xFF);
				//	lookupAddress->component(packet->buffer[2] & 0xFF);
				//	lookupAddress->node(packet->buffer[3] & 0xFF);
				//	lookupAddress->subsystem(packet->buffer[4] & 0xFF);						
				//	
				//	commandCode = (packet->buffer[5] & 0xFF) + ((packet->buffer[6] & 0xFF) << 8);
				//	serviceType = (packet->buffer[7] & 0xFF);

				//	memset(packet->buffer, 0, OJ_UDP_INTERFACE_MESSAGE_SIZE_BYTES);
				//	packet->buffer[0] = LOOKUP_SERVICE_ADDRESS_LIST_RESPONSE;

				//	//System.out.println("CmptInterface: Get address for component ID: " + componentId);
				//	//address = subsystemTable.lookupServiceAddressList(address, commandCode, serviceCommandType);
				//	
				//	if(lookupAddress->subsystem == 

				//	if(address == null)
				//	{
				//		replyMessage.getData()[0] = (byte)(0 & 0xff);
				//		replyMessage.getData()[1] = (byte)(0 & 0xff);
				//		replyMessage.getData()[2] = (byte)(0 & 0xff);
				//		replyMessage.getData()[3] = (byte)(0 & 0xff);
				//		replyMessage.getData()[4] = (byte)0;
				//		//System.out.println("CmptInterface: Get address for component ID: " + componentId + " returning: 0.0.0.0");
				//	}
				//	else	
				//	{
				//		replyMessage.getData()[0] = (byte)(address.getInstance() & 0xff);
				//		replyMessage.getData()[1] = (byte)(address.getComponent() & 0xff);
				//		replyMessage.getData()[2] = (byte)(address.getNode() & 0xff);
				//		replyMessage.getData()[3] = (byte)(address.getSubsystem() & 0xff);							
				//		replyMessage.getData()[4] = (byte)1;
				//		//System.out.println("CmptInterface: Get address for component ID: " + componentId + " returning: " + address);
				//	}
				//	
		  //  		replyBuffer = new byte[8];
				//	replyMessage.pack(replyBuffer);
				//	outPacket = new DatagramPacket(replyBuffer, replyBuffer.length, packet.getAddress(), packet.getPort());
				//	socket.send(outPacket);
				//	break;
				    
				default:
					sprintf(buf, "Unknown Interface Message Received. CC: 0x%02X\n", packet->buffer[0]);
					//sprintf(buf, "LSA value. CC: 0x%02X\n", LOOKUP_SERVICE_ADDRESS);
					ErrorEvent *e = new ErrorEvent(ErrorEvent::Warning, __FUNCTION__, __LINE__, buf);
					this->eventHandler->handleEvent(e);
					break;
			}
		}
	}
}

bool OjUdpComponentInterface::processOjNodemanagerInterfaceMessage(char *buffer)
{
	return true;
}

std::string OjUdpComponentInterface::toString()
{
	return this->name;
}

