#include <iostream>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>

using namespace std;

struct Vector2 {
	float x;
	float y;
};
Vector2* newPosition = new Vector2;
Vector2 position;

void main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Server Window");
	sf::Event e;

	/* We initialise the ENet library, and double-check this has worked. We then
	declare a few library specific variables.*/
	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;
	ENetPacket* dataPacket;

	/* set the address values to essentially be a local host */

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	/*create the server. We pass in the pointer to the address variable,
	the maximum number of clients, channles and BW*/
	server = enet_host_create(&address, 32, 2, 0, 0);

	/* Now we check server initialisation*/
	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}

	while (window.isOpen())
	{
		window.pollEvent(e);

		if (e.type == sf::Event::Closed) {
			window.close();

		}

		/*This while loop checks to see ifthe server has any events to respond to. 
		We can use the event type to determine how to respond to a given event*/
		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";

				//store some data about this peerfor as long as it remains in scope using the "data" variable. */
				enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				cout << "Packet received!\n";
				memcpy(newPosition, enetEvent.packet->data, enetEvent.packet->dataLength);
				cout << newPosition->x << "," << newPosition->y << "\n";
				position.x = newPosition->x;
				position.y = newPosition->y;
				dataPacket = enet_packet_create(&position, sizeof(Vector2), ENET_PACKET_FLAG_RELIABLE);
				enet_host_broadcast(server, 0, dataPacket);
				break;
			
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
			}
		}

		if (e.type == sf::Event::KeyPressed)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

		}

		window.clear(sf::Color::Blue);
		window.display();
	}

	//destroy the ENet Host instance, and deinitialize the library on shutdown. 
	delete newPosition;
	enet_host_destroy(server);
	atexit(enet_deinitialize);
}