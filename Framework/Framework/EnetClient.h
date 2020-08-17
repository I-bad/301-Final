#pragma once
#include <enet\enet.h>
#include <iostream>

class EnetClient
{
public:
	EnetClient() {}
	~EnetClient() {}
	
	// initialising the enet library and connecting to the server
	void connectToServer(int port);
	// destroy the ENet client instance, and deinitialize the library on shutdown. 
	void destroyEnetClient();
	//poll for events to respond to and use the event type to repsond
	void listenToServer();
	//populate the packet we made earlier and braocast it to the server
	void SendMovementPacket(const float x, const float y);

private:
	/*library specific variables. An address (which represents the
	client address), a Host (which represents the client, i.e. this software
	instance), and an arbitrary Event. ENet is an event-driven library so we
	can poll for specifc events. peer to store information about the server they're
	connecting to.*/
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;
	ENetPacket* dataPacket;

	/*below is the data structure that we will be using to represent 2d position
	we declare this newPosition variable on
	the heap. It's where the data from our received packet is going to be stored
	and the vector 2 position is the packet we will populate and braodcast to the server*/
	struct Vector2 {
		float x;
		float y;
	};
	Vector2* newPosition = new Vector2;
	Vector2 position;
};
	