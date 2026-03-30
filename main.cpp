#include <iostream>
#include <sys/socket.h> // socket
#include <cstdio> // perror
#include <unistd.h> // close
#include <netinet/in.h>


int main () {
    
    int sockedFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockedFileDescriptor == -1) {
        perror("Socket Failed"); // perror("My Message with the meaning of the errno and not the number or errno itself.")
        return -1;
    }

    sockaddr_in s = {0};
    s.sin_family = AF_INET;
    s.sin_port = htons(9999);
    s.sin_addr.s_addr = INADDR_ANY;

    int b = bind(sockedFileDescriptor, (sockaddr *)&s, sizeof(s));
    if (b == -1) {
        perror("Bind Failed");
        return -1;
    }
    
    int backLogSize = 3;
    int l = listen(sockedFileDescriptor, backLogSize);
    if (l == -1) {
        perror("Listen Failed");
        return -1;
    }
    
    sockaddr_in clientSockAddr = {0};
    socklen_t clientSize = sizeof(clientSockAddr);    
    int acceptFileDescriptor = accept(sockedFileDescriptor, (sockaddr *)&clientSockAddr, &clientSize);
    if (acceptFileDescriptor == -1) {
        perror("Accept Failed");
        return -1;
    }

    char buffer[4096];
    size_t bytesRead = read(acceptFileDescriptor, buffer, 4096);
    if (bytesRead == -1) {
        perror("Read Failed/Device Disconnected");
        return -1;
    }

    std::cout << buffer << std::endl;

    close(sockedFileDescriptor);

    return 0;
}