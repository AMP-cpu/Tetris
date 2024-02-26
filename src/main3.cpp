#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include <cstdio>
#include <iostream>


int main() {
    Client client = Client();

    client.Connect(1234,  "localhost");
    client.Poll();



    const char *message = "h";

    client.Send(message);



    while(true)
    {
        client.Poll();
        client.Send(message);
    }
    


}