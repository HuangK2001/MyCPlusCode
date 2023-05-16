#ifndef SOCKETFRAME_H
#define SOCKETFRAME_H
#include "winsock2.h"
class SocketFrame
{
public:
    SocketFrame();
    int udp_server_fun_echo(SOCKET s);
    int start_up(void);
    int quit(SOCKET s);
    int clean_up(void);
    SOCKET udp_server( char *hname, char *sname );
    int set_address(char * hname, char * sname, struct sockaddr_in * sap, char * protocol);
};

#endif // SOCKETFRAME_H
