#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "udp.h"
#include <errno.h>

bool InitServer(int port, int *sockDesc, struct sockaddr_in *sockAddr) {
    // creating socket
    if ((*sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
	fprintf(stderr, "Error creating server socket: %s\n", strerror(errno));
        return false;
    }

    // Initialize
    memset((struct sockaddr *)sockAddr, 0, sizeof(*sockAddr));

    sockAddr->sin_family = AF_INET;
    sockAddr->sin_port = htons(port);
    sockAddr->sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*sockDesc, (struct sockaddr *)sockAddr, sizeof(struct sockaddr_in)) < 0){
        fprintf(stderr, "Error binding: %s\n", strerror(errno));
        return false;
    }

    return true;
}

bool InitClient(char *IP, int port, int *sockDesc, struct sockaddr_in *sockAddr) {
    // Creating socket
    if ((*sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        fprintf(stderr, "Error creating client socket: %s\n", strerror(errno));
	return false;
    }

    // Initialize
    memset((struct sockaddr *)sockAddr, 0, sizeof(*sockAddr));

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
    //printf("Sending to: %s:%d\n", inet_ntoa(sockAddr->sin_addr), ntohs(sockAddr->sin_port));
    if (sendto(sockDesc, buffer, strlen(buffer), 0, (struct sockaddr *) sockAddr, sizeof(struct sockaddr_in)) < 0) {
        fprintf(stderr, "Error sending: %s\n", strerror(errno));
	return false;
    }

    return true;
}

int RecvFrom(int sockDesc, struct sockaddr_in *sockAddr, char *buffer) {
    memset(buffer, '\0', MAX_BUFFER);
    int sockLen = sizeof(struct sockaddr_in);
    int len = recvfrom(sockDesc, buffer, MAX_BUFFER - 1, 0, (struct sockaddr *) sockAddr, &sockLen);

    if (len < 0) {
        fprintf(stderr, "Error receiving: %s\n", strerror(errno));
	return -1;
    }

    return len;
}
