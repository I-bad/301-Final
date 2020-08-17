#include "EnetClient.h"
#include <iostream>

void EnetClient::connectToServer(int port)
{
	if (enet_initialize() != 0) { std::cout << "Enet failed to initialise!" << "\n\n"; } // enet init check
	client = enet_host_create(NULL, 1, 2, 0, 0); // create client insatnce - address, clients, channels, bandwidth
	if (client == NULL) { std::cout << "Client failed to initialise!" << "\n\n"; } // client init check
	enet_address_set_host(&address, "localhost"); //setting the host we will connect to 
	address.port = port; // the port if the host
	peer = enet_host_connect(client, &address, 2, 0); // connect to the host - who, where, channel, GD
	if (peer == NULL) { std::cout << "No available peers for initializing an ENet connection.\n"; } //if we cant connect
}

void EnetClient::listenToServer() 
{
	while (enet_host_service(client, &enetEvent, 0) > 0) //While we are connected to server and hit the recieve event, cout a message saying so
	{
		switch (enetEvent.type) {
		case ENET_EVENT_TYPE_RECEIVE:
			std::cout << "The server thinks you are at..\n";
			memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength); // populate the vecotr on the heap with the data values being recieved 
			std::cout << newPosition->x << "," << newPosition->y << "\n";
			break;
		}
	}
}

void EnetClient::destroyEnetClient() // cleanly shutodwn by deleting the vector on the heap and shutting down host and library
{
	delete newPosition;
	enet_host_destroy(client);
	atexit(enet_deinitialize); 
}

void EnetClient::SendMovementPacket(const float x, const float y) // populate position vector with the flaot from our charecter and send them to server
{
	position.x = x;
	position.y = y;
	dataPacket = enet_packet_create(&position, sizeof(Vector2), ENET_PACKET_FLAG_RELIABLE); // ref to vec 2, size of data, status of packet
	enet_host_broadcast(client, 0, dataPacket); // who, chanel. data
}
