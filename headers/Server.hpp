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
    std::tuple<int,const char*> Poll();
    void Send(const char *message);
};

Server::Server(int port, const char *addressIP, int nConnections)
{
    // Initialize ENet
    if (enet_initialize() != 0) {
        fprintf(stderr, "Failed to initialize ENet.\n");
    }
    
    // Create an address structure for the server to listen on
    ENetAddress address;
    enet_address_set_host(&address, addressIP);
    address.port = port;

    // Create the server host
    server = enet_host_create(&address, nConnections, 2, 0, 0); // Assign to class member, not local variable
    if (server == nullptr) {
        fprintf(stderr, "Failed to create server host.\n");
    }
}

Server::~Server()
{
    enet_host_destroy(server);
    enet_deinitialize();
}

std::tuple<int, const char*> Server::Poll()
{
    ENetEvent event;
    int eventType = 0;
    const char *data = nullptr;
        
    if (server && enet_host_service(server, &event, 1000) > 0) { // Check if server is valid
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                peer = event.peer;
                eventType = 1;
                data = "0";
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf("Received a packet from client %u: %s\n", event.peer->incomingPeerID, event.packet->data); // Use incomingPeerID
                data = reinterpret_cast<char*>(event.packet->data);
                enet_packet_destroy(event.packet);
                eventType = 2;
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%x:%u disconnected.\n", event.peer->address.host, event.peer->address.port);
                eventType = 3;
                data = "0";
                break;
            default:
                printf("teste");
                data = "0";
                break;
        }
    }

    return std::make_tuple(eventType, data);
}

void Server::Send(const char *message)
{
    if (peer) { // Ensure peer is valid
        ENetPacket* packet = enet_packet_create(message, strlen(message) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }
}