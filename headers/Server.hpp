#include <enet/enet.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <tuple>

class Server
{
private:
    ENetHost *server;
    ENetPeer *peer;
    
public:
    Server(int port,const char *addressIP,int nConnections);
    ~Server();
    auto Poll();
    void Send(const char *message);

};

Server::Server(int port, const char *addressIP,int nConnections)
{
    // Initialize ENet
    if (enet_initialize() != 0) {
        fprintf(stderr, "Failed to initialize ENet.\n");
    }

    // Create an address structure for the server to listen on
    ENetAddress address;
     enet_address_set_host (& address, addressIP);
    address.port = port;

    // Create the server host
    ENetHost* server = enet_host_create(&address, nConnections, 2, 0, 0);
    if (server == nullptr) {
        fprintf(stderr, "Failed to create server host.\n");
    }
}

Server::~Server()
{
    enet_host_destroy(server);
    enet_deinitialize;
}

auto Server::Poll()
{
    ENetEvent event;
    if (enet_host_service(server, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                    peer = event.peer;
                    enet_uint8 *data = 0;
                    return std::make_tuple(1, data);
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("Received a packet from client %u: %s\n", event.peer->connectID, event.packet->data);
                    enet_uint8 *data = event.packet->data;
                    enet_packet_destroy(event.packet);
                    return std::make_tuple(2, data);
                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%x:%u disconnected.\n", event.peer->address.host, event.peer->address.port);
                    enet_uint8 *data = 0;
                    return std::make_tuple(3, data);
                default:
                    enet_uint8 *data = 0;
                    return std::make_tuple(0, data);
            }
        }
}

void Server::Send(const char *message)
{
    ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}