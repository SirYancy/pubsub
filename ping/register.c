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

#define COMMUNICATE_PROG 0x13131344
#define COMMUNICATE_VERSION 1

#define SERVER "128.101.35.147"
#define PORT 5105
#define BUFLEN 512

struct sockaddr_in si_me, si_server;
int s;
socklen_t slen = sizeof(si_me);

char *buf, *message;

void Register(char *message);
void Deregister(char *message);
char *GetList(char *message);

int main(void)
{
    buf = (char *)malloc(BUFLEN * sizeof(char));
    message = (char *)malloc(BUFLEN * sizeof(char));

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


    printf("getsockname\n");

    if(getsockname(s, (struct sockaddr *) &si_me, &slen) < 0) {
        perror("getsockname()");
        exit(1);
    }

    printf("Registering\n");

    sprintf(buf, "Register;RPC;%s;%d;%d;%d%c", 
            inet_ntoa(si_me.sin_addr), 
            ntohs(si_me.sin_port),
            COMMUNICATE_PROG,
            COMMUNICATE_VERSION,
            '\0');

    printf("Buffer: %s\n", buf);

    Register(buf);

    printf("Geting List\n");

    sprintf(buf, "GetList;RPC;%s;%d%c",
            inet_ntoa(si_me.sin_addr), 
            ntohs(si_me.sin_port),
            '\0');

    printf("Buffer: %s\n", buf);

    GetList(buf);

    printf("GetList: %s\n", message);

    printf("Deregistering\n");

    sprintf(buf, "Deregister;RPC;%s;%d%c", 
            inet_ntoa(si_me.sin_addr), 
            ntohs(si_me.sin_port),
            '\0');

    printf("Buffer: %s\n", buf);

    Deregister(buf);
}

/**
 * ["Register;RPC;IP;Port;ProgramID;Version"]
 */
void Register(char *message){
    if(sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_server, slen) < 0) {
        perror("Register");
        exit(1);
    }
}

/**
 * ["Deregister,RPC,IP,Port"]
 */
void Deregister(char *message){
    if(sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_server, slen) < 0) {
        perror("Deregister");
        exit(1);
    }
}

/**
 * ["GetList;RPC;IP;Port"]
 */
char *GetList(char *to_message){
    if(sendto(s, to_message, strlen(message), 0, (struct sockaddr *) &si_server, slen) < 0) {
        perror("GetList sendto()");
        exit(1);
    }

    printf("Message sent\n");

    char *result = (char *)malloc(BUFLEN*sizeof(char));

    printf("Attempting to receive...\n");

    if(recvfrom(s, result, BUFLEN, 0, (struct sockaddr *) &si_server, &slen) < 0) {
        perror("GetList recvfrom()");
    }

    return result;
}

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

