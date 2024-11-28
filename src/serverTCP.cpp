#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

std::size_t takeFromHead(std::string buffer, size_t start) {

    std::size_t position = buffer.find(' ', start);


    return position;
}

std::string takeTheString(std::string buffer, int start, int final){
    return buffer.substr(start, final);
}

int main() {

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(3010);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    

    if(bind(socketServer, (struct sockaddr*)&serverAddress, sizeof(serverAddress))){
        std::perror("blind failed");
        exit(1);

    }

    while(true) {

        listen(socketServer, 5);

        int client = accept(socketServer, nullptr, nullptr);

        char buffer[1024] = {0};
        ssize_t byte_buffer = recv(client, buffer, sizeof(buffer), 0);

        if(strcmp(buffer, ":q") == 0) {
            close(socketServer);
            break;
        }

        std::string request(buffer, byte_buffer);

        std::size_t fmeth = takeFromHead(request, 0);
        std::string method = request.substr(0, fmeth);
        std::size_t where = takeFromHead(request, fmeth+1);
        std::string path = request.substr(fmeth+1, where - fmeth - 1);

        std::cout << path << std::endl;

         if (method == "GET"){
            std::string sendBack = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            send(client, sendBack.c_str(), sendBack.length(), 0);
        } else {
            std::string sendBack = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/html\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
            send(client, sendBack.c_str(), sendBack.length(), 0);
        }

    }



    return 0;

}
