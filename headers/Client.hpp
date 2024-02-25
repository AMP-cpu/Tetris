#include <enet/enet.h>
#include <cstdio>
#include <iostream>

class Client
{
private:
    ENetHost *client;
    ENetPeer *peer;
    
public:
    Client();
    ~Client();
    void Connect(int port, char *addressIP);
    void Poll();
    void Send(std::string message);

};

Client::Client()
{
    // Initialize ENet
    if (enet_initialize() != 0) {
        fprintf(stderr, "Failed to initialize ENet.\n");
    }

    // Create the client host
    client = enet_host_create(NULL, 1, 2, 0, 0);    
    if (Client::client == nullptr) {
        fprintf(stderr, "Failed to create server host.\n");
    }
}

Client::~Client()
{
    enet_host_destroy(client);
    enet_deinitialize;
}

void Client::Connect(int port, char *addressIP)
{
    // Create an address structure for the server to listen on
    ENetAddress address;
    enet_address_set_host (& address, addressIP);
    address.port = port;

    ENetEvent event;

    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == nullptr) {
        fprintf(stderr, "Failed to initiate connection to the server.\n");
    }

    printf("Connecting to the server...\n");

    if (enet_host_service(client, &event, 5000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("Connected to the server!\n");
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                fprintf(stderr, "Connection to the server failed: %p\n", event.peer->data);
                enet_peer_reset(peer);
                enet_host_destroy(client);
            default:
                break;
        }
    } else {
        fprintf(stderr, "Connection to the server timed out.\n");
        enet_peer_reset(peer);
        enet_host_destroy(client);
    }
}

void Client::Poll()
{
    ENetEvent event;
    if (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("A new client connected from %x:%u.\n", event.peer->address.host, event.peer->address.port);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("Received a packet from server %u: %s\n", event.peer->connectID, event.packet->data);

                    

                    enet_packet_destroy(event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%x:%u disconnected.\n", event.peer->address.host, event.peer->address.port);
                    break;
                default:
                    break;
            }
        }

}

void Client::Send(std::string message)
{
    ENetPacket* packet = enet_packet_create(message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}