#include <algorithm>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(3010);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    

    bind(socketServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    while(true) {

        listen(socketServer, 5);

        int client = accept(socketServer, nullptr, nullptr);

        char buffer[1024] = {0};
        recv(client, buffer, sizeof(buffer), 0);

        if(strcmp(buffer, ":q") == 0) {
            close(socketServer);
            break;
        }

        std::cout << buffer <<std::endl;
        std::cout << "the message " << buffer << std::endl;

    }



    return 0;

}
