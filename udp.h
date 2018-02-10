#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFFER 1024

#define SERVER_PORT 5678
#define CLIENT_PORT 6789

bool InitServer(int port, int *sockDesc, struct sockaddr_in *sockAddr);
bool InitClient(char *IP, int port, int *sockDesc, struct sockaddr_in *sockAddr);
void Destroy(int sockDesc);

bool SendTo(int sockDesc, struct sockaddr_in *sockAddr, char *buffer);
int RecvFrom(int sockDesc, struct sockaddr_in *sockAddr, char *buffer);

