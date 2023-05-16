#include <QCoreApplication>
#include "winsock2.h"
#include "socketframe.h"
#include "cstdio"
#define ECHOPORT "6000"

int udp_client_fun_echo(FILE *fp,SOCKET s,SOCKADDR *servaddr,int servlen);
int main(int argc, char *argv[])
{
    SocketFrame frame;
    int iResult;
    SOCKET ClientSocket;
    sockaddr_in servaddr;
    char server_ip[] = "127.0.0.1"; //��������̨�����ַ�ķ�����ֱ�����ַ�����ָ����ַ
//    if(argc != 2)
//    {
//        printf("usage��EchoUDPClient <IPaddress>");
//        return -1;
//    }
    frame.start_up();
    ClientSocket = frame.udp_client(server_ip,ECHOPORT,true);
    if(ClientSocket == -1)
    {
        return -1;
    }
    printf("�ͻ��������ɹ�������������ַ���...\n");
    if(frame.set_address(server_ip,ECHOPORT,&servaddr,"udp") != 0)
    {
        return 0;
    }
    iResult = udp_client_fun_echo(stdin,ClientSocket,(SOCKADDR *)&servaddr,sizeof(sockaddr_in));
    if(iResult == -1)
        printf("��ǰ������̳���\n");
    frame.quit(ClientSocket);
    return iResult;
}
