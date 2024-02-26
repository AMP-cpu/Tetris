#include "../headers/Server.hpp"
#include "../headers/Client.hpp"
#include <cstdio>
#include <iostream>


int main() {
    Server server = Server(1234,  "localhost", 2);

    while (true)
    {

        server.Poll();
    }
    


}