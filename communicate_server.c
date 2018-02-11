/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <string.h>
#include <stdio.h>
#include <string.h>
#include "communicate.h"

#define MAXSUBSCRIBERS 5
#define MAXSTRING 120

typedef struct SubNode
{
    char *ip;
    int port;
    char subscriptions[100][MAXSTRING];
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

bool_t *
join_1_svc(char *IP, int Port,  struct svc_req *rqstp)
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
	/*
	 * insert server code here
	 */

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

	/*
	 * insert server code here
	 */

	return &result;
}

bool_t add_subscriber(char *ip, int port)
{
    if(numSubs >= MAXSUBSCRIBERS){
        return 0;
    }

    SubNode *n = (SubNode*)malloc(sizeof(SubNode));
    
    n->ip = malloc(strlen(ip) * sizeof(char));
    strcpy(n->ip, ip);
    n->port = port;
    n->next = NULL;

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
            free(current);
            numSubs--;
            return 1;
        }
    }

    return 0;

}

bool_t publishing(char *ip, int port, char *Article)
{
	int j = 0;
	char *type;
	while ((type = strsep(&Article, ";")) != NULL)
	{ 
		if (j == 3 && !strcmp(type, "")) //if contents field is empty 
		{
			printf("Illegal to publish this article\n");
			return 0;
		}
		j++;
	}
	
	// TODO: Insert logic to broadcast to all clients

	return 1;

}

bool_t subscribing(char *ip, int port, char *Article)
{
	int i; 
	int j = 0;
	int p = 0;
	SubNode *current = subList; 
	char *type; 
	
	for (i = 0; i < numSubs; i++) // go through all the clients to look for right one
	{
		if (!strcmp(current->ip, ip) && current->port == port)
		{
			while ((type = strsep(&Article, ";")) != NULL)
			{ 
				if (strcmp(type, ""))
				{  
					if (p == 3 && j == 0) { // if only contents exist return 0
						printf("Illegal article");
						return 0;
					}
					strcpy(current->subscriptions[j], type);
					j++;
				}
				p++;
			}	
			if (j == 0) // if nothing, return 0
			{ 
				printf("Illegal article");
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

			while ((type = strsep(&Article, ";")) != NULL) 
			{
				for (s = 0; s < 100; s++)
				{
					if (!strcmp(current->subscriptions[s], type) && strcmp(type, ""))
					{	
						u++;
						strcpy(current->subscriptions[s], "");
					} 
				}
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

