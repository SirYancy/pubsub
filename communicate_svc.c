/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "communicate.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static bool_t *
_joinserver_1 (joinserver_1_argument *argp, struct svc_req *rqstp)
{
	return (joinserver_1_svc(argp->IP, argp->ProgID, argp->ProgVers, rqstp));
}

static bool_t *
_leaveserver_1 (leaveserver_1_argument *argp, struct svc_req *rqstp)
{
	return (leaveserver_1_svc(argp->IP, argp->ProgID, argp->ProgVers, rqstp));
}

static bool_t *
_join_1 (join_1_argument *argp, struct svc_req *rqstp)
{
	return (join_1_svc(argp->IP, argp->Port, rqstp));
}

static bool_t *
_leave_1 (leave_1_argument *argp, struct svc_req *rqstp)
{
	return (leave_1_svc(argp->IP, argp->Port, rqstp));
}

static bool_t *
_subscribe_1 (subscribe_1_argument *argp, struct svc_req *rqstp)
{
	return (subscribe_1_svc(argp->IP, argp->Port, argp->Article, rqstp));
}

static bool_t *
_unsubscribe_1 (unsubscribe_1_argument *argp, struct svc_req *rqstp)
{
	return (unsubscribe_1_svc(argp->IP, argp->Port, argp->Article, rqstp));
}

static bool_t *
_publish_1 (publish_1_argument *argp, struct svc_req *rqstp)
{
	return (publish_1_svc(argp->Article, argp->IP, argp->Port, rqstp));
}

static bool_t *
_publishserver_1 (publishserver_1_argument *argp, struct svc_req *rqstp)
{
	return (publishserver_1_svc(argp->Article, argp->IP, argp->Port, rqstp));
}

static bool_t *
_ping_1 (void  *argp, struct svc_req *rqstp)
{
	return (ping_1_svc(rqstp));
}

static void
communicate_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		joinserver_1_argument joinserver_1_arg;
		leaveserver_1_argument leaveserver_1_arg;
		join_1_argument join_1_arg;
		leave_1_argument leave_1_arg;
		subscribe_1_argument subscribe_1_arg;
		unsubscribe_1_argument unsubscribe_1_arg;
		publish_1_argument publish_1_arg;
		publishserver_1_argument publishserver_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case JoinServer:
		_xdr_argument = (xdrproc_t) xdr_joinserver_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _joinserver_1;
		break;

	case LeaveServer:
		_xdr_argument = (xdrproc_t) xdr_leaveserver_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _leaveserver_1;
		break;

	case Join:
		_xdr_argument = (xdrproc_t) xdr_join_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _join_1;
		break;

	case Leave:
		_xdr_argument = (xdrproc_t) xdr_leave_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _leave_1;
		break;

	case Subscribe:
		_xdr_argument = (xdrproc_t) xdr_subscribe_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _subscribe_1;
		break;

	case Unsubscribe:
		_xdr_argument = (xdrproc_t) xdr_unsubscribe_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _unsubscribe_1;
		break;

	case Publish:
		_xdr_argument = (xdrproc_t) xdr_publish_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _publish_1;
		break;

	case PublishServer:
		_xdr_argument = (xdrproc_t) xdr_publishserver_1_argument;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _publishserver_1;
		break;

	case Ping:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) _ping_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

#include "udp.h"

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

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;
    pthread_t udp_thread;

	pmap_unset (COMMUNICATE_PROG, COMMUNICATE_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, COMMUNICATE_PROG, COMMUNICATE_VERSION, communicate_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (COMMUNICATE_PROG, COMMUNICATE_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, COMMUNICATE_PROG, COMMUNICATE_VERSION, communicate_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (COMMUNICATE_PROG, COMMUNICATE_VERSION, tcp).");
		exit(1);
	}

//    pthread_create(&udp_thread, NULL, udp_thread_func, NULL);

    svc_run ();
    pthread_join(udp_thread, NULL);
    fprintf (stderr, "%s", "svc_run returned");
    exit (1);
    /* NOTREACHED */
}
