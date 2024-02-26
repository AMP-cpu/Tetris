#include <enet/enet.h>
#include <cstdio>
#include <iostream>

class Server
{
private:
    ENetHost *server;
    ENetPeer *peer;
    
public:
    Server(int port, const char *addressIP,int nConnections);
    ~Server();
    void Poll();
    void Send(std::string message);

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
    fprintf(stderr, "Server created.\n");

    // Create the server host
    server = enet_host_create(&address, nConnections, 2, 0, 0);
    if (server == nullptr) {
        fprintf(stderr, "Failed to create server host.\n");
    }
}

Server::~Server()
{
    enet_host_destroy(server);
    enet_deinitialize;
}

void Server::Poll()
{
    ENetEvent event;
    if (enet_host_service(server, &event, 1000) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                    //peer = event.peer;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("i");
                    printf("Received a packet from client %u: %s\n", event.peer->connectID, event.packet->data);
                    enet_packet_destroy (event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%x:%u disconnected.\n", event.peer->address.host, event.peer->address.port);
                    break;
                default:
                    break;
            }
        }
}

void Server::Send(std::string message)
{
    ENetPacket* packet = enet_packet_create(message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}