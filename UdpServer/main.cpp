#include <QCoreApplication>
#include "winsock2.h"
#define ECHOPORT "6000"
#include "socketframe.h"
int udp_server_fun_echo(SOCKET s);
int main(int argc, char *argv[])
{
    SocketFrame frame;
    int iResult = 0;
    SOCKET ServerSocket;
//    if(argc != 1)
//    {
//        printf("usage��EchoTCPServer");
//        return -1;
//    }
    frame.start_up();
    ServerSocket = frame.udp_server(NULL,ECHOPORT);
    if(ServerSocket == -1)
    {
        return -1;
    }
    printf("������׼���û������...\n");
    for(;;) {
        iResult = udp_server_fun_echo(ServerSocket);
        if(iResult == -1)
            printf("��ǰ������̳���\n");
    }
    frame.quit(ServerSocket);
    return 0;
}












