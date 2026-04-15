#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <cstring>

void * handleClientFunction (void *clientFdPtr) {
    
    int clientFd = *((int *)clientFdPtr);
    free(clientFdPtr);

    char buffer[4096] = {0};
    
    ssize_t bytesRead = read(clientFd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Read Failed");
    } else if (bytesRead > 0){
        buffer[bytesRead] = '\0';
        std::cout << "Request Received\n" << buffer << std::endl;
    }

    const char *buf =   "HTTP/1.1 200 OK\r\n"
                        "Content-Length: 19\r\n"
                        "\r\n"
                        "Hello from server!\n";    

    write(clientFd, buf, strlen(buf));
    
    close(clientFd);

    return NULL;
}

int main () {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        perror("Socket Failed");
        return -1;
    }

    sockaddr_in server = {0};
    server.sin_port = htons(9999);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;

    int b = bind(sfd, (sockaddr *)&server, sizeof(server));
    if (b == -1) {
        perror("Bind Failed");
        return -1;
    }

    int queueSize = 20;
    int l = listen(sfd, queueSize);
    if (l == -1) {
        perror("Listen Failed");
        return -1;
    }

    std::cout << "Server Listening at port 9999" << std::endl;

    while (1) {

        sockaddr_in client = {0};
        socklen_t clientSize = sizeof(client);
        int clientFd = accept(sfd, (sockaddr *)&client, &clientSize);
        if (clientFd == -1) {
            perror("Accept Failed");
            continue;
        }

        pthread_t threadId;

        int *clientFdCopyPtr = (int *)malloc(sizeof(int));
        *clientFdCopyPtr = clientFd;

        int p = pthread_create(&threadId, NULL, handleClientFunction, (void *)clientFdCopyPtr);
        if (p != 0) {
            perror("Thread Creation Failed");
            free(clientFdCopyPtr);
            close(clientFd);
            continue;
        }

        pthread_detach(threadId);

    }

    close(sfd);

    return 0;
}
