/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _COMMUNICATE_H_RPCGEN
#define _COMMUNICATE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct joinserver_1_argument {
	char *IP;
	int ProgID;
	int ProgVers;
};
typedef struct joinserver_1_argument joinserver_1_argument;

struct leaveserver_1_argument {
	char *IP;
	int ProgID;
	int ProgVers;
};
typedef struct leaveserver_1_argument leaveserver_1_argument;

struct join_1_argument {
	char *IP;
	int Port;
};
typedef struct join_1_argument join_1_argument;

struct leave_1_argument {
	char *IP;
	int Port;
};
typedef struct leave_1_argument leave_1_argument;

struct subscribe_1_argument {
	char *IP;
	int Port;
	char *Article;
};
typedef struct subscribe_1_argument subscribe_1_argument;

struct unsubscribe_1_argument {
	char *IP;
	int Port;
	char *Article;
};
typedef struct unsubscribe_1_argument unsubscribe_1_argument;

struct publish_1_argument {
	char *Article;
	char *IP;
	int Port;
};
typedef struct publish_1_argument publish_1_argument;

struct publishserver_1_argument {
	char *Article;
	char *IP;
	int Port;
};
typedef struct publishserver_1_argument publishserver_1_argument;

#define COMMUNICATE_PROG 0x13131344
#define COMMUNICATE_VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define JoinServer 1
extern  bool_t * joinserver_1(char *, int , int , CLIENT *);
extern  bool_t * joinserver_1_svc(char *, int , int , struct svc_req *);
#define LeaveServer 2
extern  bool_t * leaveserver_1(char *, int , int , CLIENT *);
extern  bool_t * leaveserver_1_svc(char *, int , int , struct svc_req *);
#define Join 3
extern  bool_t * join_1(char *, int , CLIENT *);
extern  bool_t * join_1_svc(char *, int , struct svc_req *);
#define Leave 4
extern  bool_t * leave_1(char *, int , CLIENT *);
extern  bool_t * leave_1_svc(char *, int , struct svc_req *);
#define Subscribe 5
extern  bool_t * subscribe_1(char *, int , char *, CLIENT *);
extern  bool_t * subscribe_1_svc(char *, int , char *, struct svc_req *);
#define Unsubscribe 6
extern  bool_t * unsubscribe_1(char *, int , char *, CLIENT *);
extern  bool_t * unsubscribe_1_svc(char *, int , char *, struct svc_req *);
#define Publish 7
extern  bool_t * publish_1(char *, char *, int , CLIENT *);
extern  bool_t * publish_1_svc(char *, char *, int , struct svc_req *);
#define PublishServer 8
extern  bool_t * publishserver_1(char *, char *, int , CLIENT *);
extern  bool_t * publishserver_1_svc(char *, char *, int , struct svc_req *);
#define Ping 9
extern  bool_t * ping_1(CLIENT *);
extern  bool_t * ping_1_svc(struct svc_req *);
extern int communicate_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define JoinServer 1
extern  bool_t * joinserver_1();
extern  bool_t * joinserver_1_svc();
#define LeaveServer 2
extern  bool_t * leaveserver_1();
extern  bool_t * leaveserver_1_svc();
#define Join 3
extern  bool_t * join_1();
extern  bool_t * join_1_svc();
#define Leave 4
extern  bool_t * leave_1();
extern  bool_t * leave_1_svc();
#define Subscribe 5
extern  bool_t * subscribe_1();
extern  bool_t * subscribe_1_svc();
#define Unsubscribe 6
extern  bool_t * unsubscribe_1();
extern  bool_t * unsubscribe_1_svc();
#define Publish 7
extern  bool_t * publish_1();
extern  bool_t * publish_1_svc();
#define PublishServer 8
extern  bool_t * publishserver_1();
extern  bool_t * publishserver_1_svc();
#define Ping 9
extern  bool_t * ping_1();
extern  bool_t * ping_1_svc();
extern int communicate_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_joinserver_1_argument (XDR *, joinserver_1_argument*);
extern  bool_t xdr_leaveserver_1_argument (XDR *, leaveserver_1_argument*);
extern  bool_t xdr_join_1_argument (XDR *, join_1_argument*);
extern  bool_t xdr_leave_1_argument (XDR *, leave_1_argument*);
extern  bool_t xdr_subscribe_1_argument (XDR *, subscribe_1_argument*);
extern  bool_t xdr_unsubscribe_1_argument (XDR *, unsubscribe_1_argument*);
extern  bool_t xdr_publish_1_argument (XDR *, publish_1_argument*);
extern  bool_t xdr_publishserver_1_argument (XDR *, publishserver_1_argument*);

#else /* K&R C */
extern bool_t xdr_joinserver_1_argument ();
extern bool_t xdr_leaveserver_1_argument ();
extern bool_t xdr_join_1_argument ();
extern bool_t xdr_leave_1_argument ();
extern bool_t xdr_subscribe_1_argument ();
extern bool_t xdr_unsubscribe_1_argument ();
extern bool_t xdr_publish_1_argument ();
extern bool_t xdr_publishserver_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

typedef struct SocketInfomation {
    struct sockaddr_in clientAddr;
    struct sockaddr_in serverAddr;
    int serverSocket;
    int clientSocket;
    int myPort;
    int serverPort;
    char *serverIP;
} SocketInfo;

#define MY_IP "127.0.0.1"

#endif /* !_COMMUNICATE_H_RPCGEN */
