#include <stdio.h>
#include "udp.h"

bool InitServer(int port, int *sockDesc, struct sockaddr_in *sockAddr) {
    // creating socket
    if ((*sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("Error creating socket\n");
        return false;
    }

    // Initialize
    memset((char *)sockAddr, '\0', sizeof(struct sockaddr_in));

    sockAddr->sin_family = AF_INET;
    sockAddr->sin_port = htons(port);
    sockAddr->sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*sockDesc, (struct sockaddr *)sockAddr, sizeof(struct sockaddr_in)) < 0){
        printf("Error binding\n");
        return false;
    }

    return true;
}

bool InitClient(char *IP, int port, int *sockDesc, struct sockaddr_in *sockAddr) {
    // Creating socket
    if ((*sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("Error creating socket\n");
        return false;
    }

    // Initialize
    memset((char *)sockAddr, '\0', sizeof(struct sockaddr_in));

    /*Configure settings in address struct*/
    sockAddr->sin_family = AF_INET;
    sockAddr->sin_port = htons(port);
    sockAddr->sin_addr.s_addr = inet_addr(IP);

    return true;
}

void Destroy(int sockDesc) {
    close(sockDesc);
}

bool SendTo(int sockDesc, struct sockaddr_in *sockAddr, char *buffer) {
    if (sendto(sockDesc, buffer, strlen(buffer), 0, (struct sockaddr *) sockAddr, sizeof(struct sockaddr_in)) < 0) {
        printf("Error sending\n");
        return false;
    }

    return true;
}

int RecvFrom(int sockDesc, struct sockaddr_in *sockAddr, char *buffer) {
    memset(buffer, '\0', MAX_BUFFER);
    int sockLen = sizeof(struct sockaddr_in);
    int len = recvfrom(sockDesc, buffer, MAX_BUFFER - 1, 0, (struct sockaddr *) sockAddr, &sockLen);

    if (len < 0) {
        printf("Error receiving\n");
        return -1;
    }

    return len;
}
