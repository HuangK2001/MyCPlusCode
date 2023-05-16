#ifndef SOCKETFRAME_H
#define SOCKETFRAME_H
#include "cstdio"
#include "winsock2.h"
class SocketFrame
{
public:
    SocketFrame();
    int udp_client_fun_echo(FILE *fp,SOCKET s,SOCKADDR *servaddr,int servlen);
    int start_up(void);
    int clean_up(void);
    int quit(SOCKET s);
    SOCKET udp_client( char *hname, char *sname, BOOL flag);
    int set_address(char * hname, char * sname, struct sockaddr_in * sap, char * protocol);
};

#endif // SOCKETFRAME_H
