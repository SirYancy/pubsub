//#include "communicate.h"
#include <stdio.h>
#include <stdlib.h>
//#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

#define SERVER "128.101.35.147"
#define PORT 5105
#define BUFLEN 512

void Register(char *message);
void Deregister(char *message);
char *GetList(char *message);

/*
void *udp_thread_func(void *udp_args) {
    int clientSocket;
    struct sockaddr_in myAddr, clientAddr;
    char buffer[MAX_BUFFER];

    printf("In udp thread ...\n");

    if (!InitServer(5678, &clientSocket, &myAddr)) {
        // Initialize server failed
        printf("Server init fail\n");
    }
    printf("Server initialized\n");

    memset((char *)&clientAddr, '\0', sizeof(clientAddr));

    RecvFrom(clientSocket, &clientAddr, buffer);

    printf("%s\n", buffer);
    printf("%d %d\n", ntohs(clientAddr.sin_port), inet_ntoa(clientAddr.sin_addr));

    while (true) {
        SendTo(clientSocket, &clientAddr, "XXX");
        sleep(2);
    }
}
*/

int main(void)
{
    struct sockaddr_in si_me, si_server;
    int s;

    char buf[BUFLEN];
    char message[BUFLEN];

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset((char *) &si_server, 0, sizeof(si_server));
    si_server.sin_family = AF_INET;
    si_server.sin_port = htons(PORT);

    memset((char *) &si_me, 0, sizeof(si_server));
    si_me.sin_family = AF_INET;
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    si_me.sin_port = htons(0);

    printf("server\n");

    if (inet_aton(SERVER, &si_server.sin_addr) == 0){
        perror("inet_aton");
        exit(1);
    }

    printf("binding\n");

    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) < 0) {
        perror("bind()");
        exit(1);
    }

    printf("connecting\n");

    if(connect(s, (struct sockaddr *) &si_server, sizeof(si_server)) < 0) {
        perror("connect()");
        exit(1);
    }

    socklen_t *slen;

    printf("getsockname\n");

    if(getsockname(s, (struct sockaddr *) &si_me, slen) < 0) {
        perror("getsockname()");
        exit(1);
    }

    printf("printing\n");

    printf("Bound to IP: %s, PORT: %d", inet_ntoa(si_me.sin_addr), ntohs(si_me.sin_port));
}

/**
 * ["Register;RPC;IP;Port;ProgramID;Version"]
 */
void Register(char *message){}

/**
 * ["Deregister,RPC,IP,Port"]
 */
void Deregister(char *message){}

/**
 * ["GetList;RPC;IP;Port"]
 */
char *GetList(char *message){}
