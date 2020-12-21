#include "my_multiplayer.h"
#include "simple_logger.h"

Uint8 multiplayer_init()
{
	if (enet_initialize() != 0)
	{
		slog("error initializing enet");
		return false;
	}
	atexit(enet_deinitialize);
	return true;
}

Uint8 multiplayer_server_create(ENetAddress *addr, ENetHost **host, int port)
{
	addr->host = ENET_HOST_ANY;
	addr->port = port;

	*host = enet_host_create(addr, 8, 1, 0, 0); //8 connections maximum, 1 channel, no bandwith limits
	
	if (*host == NULL)
	{
		slog("Error creating server");
		return false;
	}
	else
	{
		return true;
	}
}

Uint8 multiplayer_client_create(ENetAddress *addr, ENetHost **host, ENetPeer **peer, ENetEvent *eve, int port, const char *ip)
{
	enet_address_set_host(addr, ip);
	addr->port = port;

	*host = enet_host_create(NULL, 1, 1, 0, 0);
	if (*host == NULL)
	{
		slog("Error creating client");
		return false;
	}

	*peer = enet_host_connect(*host, addr, 1, 0);
	if (*peer == NULL)
	{
		slog("No available peers");
		return false;
	}
	else
	{
		if (enet_host_service(*host, eve, 5000) > 0
			&& eve->type == ENET_EVENT_TYPE_CONNECT)
		{
			slog("Connected to %s:%d", ip, port);
			return true;
		}
		else
		{
			slog("Connection to %s:%d failed", ip, port);
			enet_peer_reset(*peer);
			return false;
		}
	}
}

void multiplayer_host_service(Uint8 isserver, ENetHost **host, ENetEvent *eve)
{
	if (isserver)
	{
		while (enet_host_service(*host, eve, 0) > 0)
		{
			if (eve->type == ENET_EVENT_TYPE_CONNECT)
			{
				slog("A new client connected from %x:%u",
					eve->peer->address.host,
					eve->peer->address.port);
			}
			else if (eve->type == ENET_EVENT_TYPE_RECEIVE)
			{
				//recieve = event.packet->data;
				//recievepos.x = recieve->x;
				//recievepos.y = recieve->y;
				//recievepos.z = recieve->z;

				//temp_player->position.x = recievepos.x;
				//temp_player->position.y = recievepos.y;
				//temp_player->position.z = recievepos.z;

				//pack = enet_packet_create(send, sizeof(Vector3D), ENET_PACKET_FLAG_RELIABLE);
				//enet_peer_send(event.peer, 0, pack);
			}
			else if (eve->type == ENET_EVENT_TYPE_DISCONNECT)
			{
				slog("Client %x:%u has disconnected",
					eve->peer->address.host,
					eve->peer->address.port);
				//Set data to NULL
			}
		}
	}
	else
	{
		while (enet_host_service(*host, eve, 0) > 0)
		{
			if (eve->type == ENET_EVENT_TYPE_RECEIVE)
			{
				//recieve = event.packet->data;
				//recievepos.x = recieve->x;
				//recievepos.y = recieve->y;
				//recievepos.z = recieve->z;

				//temp_player->position.x = recievepos.x;
				//temp_player->position.y = recievepos.y;
				//temp_player->position.z = recievepos.z;
			}
		}
	}
}
