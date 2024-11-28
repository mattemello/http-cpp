#include <algorithm>
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

int takeFromHead(std::string buffer, int start) {

    int position = start;

    while(buffer[position] != ' ' || buffer[position] != '\n') {
        position++;
    }

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
        recv(client, buffer, sizeof(buffer), 0);

        if(strcmp(buffer, ":q") == 0) {
            close(socketServer);
            break;
        }

        std::string sendBack = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        send(client, sendBack.c_str(), sendBack.length(), 0);

        //int method = takeFromHead(buffer, 0);
        //int where = takeFromHead(buffer, method);
        //int prot = takeFromHead(buffer, where);

        //std::cout<<"here"<<std::endl;
        //std::string meth = takeTheString(buffer, 0, method);
        //std::string path = takeTheString(buffer, method, where);
        //std::string protocol = takeTheString(buffer, where, prot);

        //if (meth.compare("GET") == 0 && path.compare("/") == 0 && protocol.compare("HTTP/1.1") == 0) {

        //}
    }



    return 0;

}
