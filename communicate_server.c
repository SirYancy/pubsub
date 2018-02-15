/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "communicate.h"
#include "udp.h"

#define MAXSUBSCRIBERS 5
#define MAXSTRING 120
#define SERVERPORT 8888 

int serverSocket = -1;
struct sockaddr_in serverAddr;
bool_t initialized = -1;

typedef struct SubNode
{
    char *ip;
    int port;
    char subscriptions[100][MAXSTRING];
    int subs;
    struct sockaddr_in *clientAddr;
    struct SubNode *next;
} SubNode;

static SubNode * subList;
static int numSubs = 0;

void setup_list(int cap);
void list_subscribers();
void print_sub(SubNode *n);
bool_t add_subscriber(char *ip, int port);
bool_t remove_subscriber(char *ip, int port);
bool_t subscribing(char *ip, int port, char *Article);
bool_t unsubscribing(char *ip, int port, char *Article);
bool_t publishing(char *ip, int port, char *Article);


    bool_t *
join_1_svc(char *IP, int Port, struct svc_req *rqstp)
{
    static bool_t  result;

    result = add_subscriber(IP, Port);

    printf("Added client. Result: %d, IP: %s, Port: %d\n", result, IP, Port);

    list_subscribers();

    return &result;
}

    bool_t *
leave_1_svc(char *IP, int Port,  struct svc_req *rqstp)
{
    static bool_t  result;

    result = remove_subscriber(IP, Port);

    if(result)
        printf("Removed client. Result: %d, IP: %s, Port: %d\n", result, IP, Port);
    else
        printf("Failed to remove client. Result: %d, IP: %s, Port: %d\n", result, IP, Port);

    return &result;
}

    bool_t *
subscribe_1_svc(char *IP, int Port, char *Article,  struct svc_req *rqstp)
{
    static bool_t  result;
    result = subscribing(IP, Port, Article);

    if (result)
    {
        printf("Client subscribed. Article: %s\n", Article);
    }
    else
    {
        printf("Client failed to subscribe\n");
    }
    //	list_subscribers();
    return &result;
}

    bool_t *
unsubscribe_1_svc(char *IP, int Port, char *Article,  struct svc_req *rqstp)
{
    static bool_t  result;
    result = unsubscribing(IP, Port, Article);
    if (result)
    {
        printf("Client unsubscribed from Article: %s\n", Article);
    }
    else
    {
        printf("Client failed to unsubscribe\n");
    }

    return &result;
}

    bool_t *
publish_1_svc(char *Article, char *IP, int Port,  struct svc_req *rqstp)
{
    static bool_t  result;
    result = publishing(IP, Port, Article);
    if (result)
    {
        printf("New published article: %s\n", Article);
    }
    else
    {
        printf("Failed to publish article\n");
    }

    return &result;
}

    bool_t *
publishserver_1_svc(char *Article, char *IP, int Port,  struct svc_req *rqstp)
{
    static bool_t  result;

    /*
     * insert server code here
     */

    return &result;
}

    bool_t *
ping_1_svc(struct svc_req *rqstp)
{
    static bool_t  result;

    printf("Ping Received from client\n");
    result = 1;

    return &result;
}

bool_t add_subscriber(char *ip, int port)
{
    if(numSubs >= MAXSUBSCRIBERS){
        return 0;
    }

    SubNode *n = (SubNode*)malloc(sizeof(SubNode));

    n->ip = malloc((strlen(ip)+1) * sizeof(char));
    strcpy(n->ip, ip);
    n->port = port;
    n->next = NULL;

    n->subs = 0;
    //n->clientSocket = socket;
    n->clientAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    memset((char *)n->clientAddr, '\0', sizeof(struct sockaddr_in));

    /*Configure settings in address struct*/
    (n->clientAddr)->sin_family = AF_INET;
    (n->clientAddr)->sin_port = htons(port);
    (n->clientAddr)->sin_addr.s_addr = inet_addr(ip);

    if(subList == NULL){
        subList = n;
        numSubs++;
        return 1;
    }
    SubNode *current = subList;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = n;
    numSubs++;
    /* if (!InitClient(ip, port, &(n->clientSocket), n->clientAddr))
       {
       printf("Addsub failed to initialise client");
       } */
    return 1;

    //TODO ensure there are no duplicates?
}

bool_t remove_subscriber(char *ip, int port)
{
    SubNode *current = subList;

    if (!strcmp(current->ip, ip) && current->port == port)
    {
        subList = current->next;
        free(current->ip);
        free(current->clientAddr);
        free(current);
        numSubs--;
        return 1;
    }

    SubNode *tmp;
    int i;

    for(i = 0; i < numSubs-1; i++)
    {
        tmp = current;
        current = current->next;
        if (!strcmp(current->ip, ip) && current->port == port)
        {
            tmp->next = current->next;
            free(current->ip);
            free(current->clientAddr);
            free(current);
            numSubs--;
            return 1;
        }
    }

    return 0;

}

bool_t publishing(char *ip, int port, char *Article)
{
    int i, s, e = 0;
    char *type;
    SubNode *current = subList;
    bool_t send;
    char toSend[strlen(Article)];
    strcpy(toSend, Article);
    char *token;
    char toCheck[strlen(Article)];
    strcpy(toCheck, Article);
    printf("Article: %s\n", toSend);

    if(initialized < 0)
    {
        printf("Server init\n");
        if (!InitServer(SERVERPORT, &serverSocket, &serverAddr))
        {
            printf("couldn't initialise server\n");
        }
        else
        {
            printf("Initialized server\n");
            initialized = 1;
        }
    }
    int p = 0;
    while ((token = strsep(&Article, ";")) != NULL)
    {
	if (!strcmp(token, ""))
	{
	    if (p == 3) {
	       printf("no contents\n");
	       return 0;
	    }
	    e++;
	}
	else if (p == 3 && e == 3)
	{
	    printf("no first 3 fields\n");
	    return 0;
	}
	p++;
    }

    for (i = 0; i < numSubs; i++)
    {
        send = 0;
        int j = 0;
        int e = 0;
	type = strtok(toCheck, ";");
	while (type != NULL)
        {
            for (s = 0; s < 100; s++) // go through subscriptions, and check if it matches a field in article
            {
                if (!strcmp(type, current->subscriptions[s]) && strcmp(type, ""))
                {
                    send = 1;
                    break;
                }
            }
            j++;
	    type = strtok(NULL, ";");
        }
        
	if (j == 0) 
	{
	    printf("Illegal article\n");
	    return 0;
	}
        if (send == 1)
        {
            if (!SendTo(serverSocket, current->clientAddr, toSend))
            {
                printf("couldn't send to client\n");
                return 0;
            }
        }
        current = current->next;
    }

    return 1;
}

bool_t subscribing(char *ip, int port, char *Article)
{
    int i;
    int j = 0;
    int p = 0;
    SubNode *current = subList;
    char *type;
    type = strtok(Article, ";");

    for (i = 0; i < numSubs; i++) // go through all the clients to look for right one
    {
	p = 0;
	j = 0;
        if (!strcmp(current->ip, ip) && current->port == port)
        {
            while (type != NULL)
            {
                if (strcmp(type, ""))
                {
                    if (p == 3) { // if contents exist return 0
                        printf("contents exist Illegal article\n");
                        return 0;
                    }
                    strcpy(current->subscriptions[j], type);
	            current->subs = current->subs + 1;
                    j++;
                }
		p++;
		type = strtok(NULL, ";");
            }
        
        if (j == 0) // if nothing, return 0
        {
            printf("nothing in article\n");
            return 0;
        }
        //return 1;

        	return 1;
	}
        current = current->next;
    }
    return 0;
}

bool_t unsubscribing(char *ip, int port, char *Article)
{
    int i = 0;
    int s = 0;
    int p = 0;
    int u  = 0;

    SubNode *current = subList;

    for (i = 0; i < numSubs; i++)
    {
        if (!strcmp(current->ip, ip) && current->port == port)
        {
            char *type;
            char subs[100][MAXSTRING];
            type = strtok(Article, ";");
            while (type != NULL)
            {
                for (s = 0; s < 100; s++)
                {
                    if (!strcmp(current->subscriptions[s], type) && strcmp(type, ""))
                    {
                        u++;
                        strcpy(current->subscriptions[s], "");
                        current->subs = current->subs - 1;
                    }
                }
                type = strtok(NULL, ";");
            }

            if (u == 0)
            {
                return 0;
            }
            /*for (p = 0; p <100; p++)
              {
              printf("client %s subscribed to %s\n", current->ip, current->subscriptions[p]);
              } */
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void print_sub(SubNode *n)
{
    printf("IP: %s, Port: %d\n", n->ip, n->port);
}

void list_subscribers()
{
    SubNode *n = subList;
    while(n != NULL)
    {
        print_sub(n);
        n = n->next;
    }
}

    bool_t *
joinserver_1_svc(char *IP, int ProgID, int ProgVers,  struct svc_req *rqstp)
{
    static bool_t  result;

    // TODO: Later

    return &result;
}

    bool_t *
leaveserver_1_svc(char *IP, int ProgID, int ProgVers,  struct svc_req *rqstp)
{
    static bool_t  result;

    // TODO later

    return &result;
}
