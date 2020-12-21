#ifndef __MY_MULTIPLAYER_H__
#define __MY_MULTIPLAYER_H__

#include <enet.h>
#include "my_player.h"

/*
	@breif runs enet_initialize and checks for an error.
	@return a Uint8 true if succeeded, false if error
*/
Uint8 multiplayer_init();

/*
	@brief initializes a server host.
*/
Uint8 multiplayer_server_create(ENetAddress *addr, ENetHost **host, int port);

/*
	@brief initializes a client host and begins connection to peer
*/
Uint8 multiplayer_client_create(ENetAddress *addr, ENetHost **host, ENetPeer **peer, ENetEvent *eve, int port, const char *ip);

/*
	@brief updates the host based on whether it is a client or server. Manages events recieved.
*/
void multiplayer_host_service(Uint8 isserver, ENetHost **host, ENetEvent *eve, Vector3D *recieve, Vector3D *send);

#endif