#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

    int clientSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAdd;

    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(3010);
    serverAdd.sin_addr.s_addr = INADDR_ANY;

    connect(clientSock, (struct sockaddr*)&serverAdd, sizeof(serverAdd));

    const char* hello = ":q";
    send(clientSock, hello, strlen(hello), 0);
    std::cout << hello << std::endl;

    close(clientSock);

    return 0;

}
