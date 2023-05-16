#include <QCoreApplication>
#include <stdio.h>
#include "winsock2.h"
#include <mstcpip.h>
#define DEFAULT_BUFLEN 65535
#define DEFAULT_NAMELEN 512

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WSADATA wsaData;
    SOCKET SnifferSocket = INVALID_SOCKET;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    struct hostent *local;
    char HostName[DEFAULT_NAMELEN];
    struct in_addr addr;
    struct sockaddr_in LocalAddr, RemoteAddr;
    int addrlen = sizeof(struct sockaddr_in);
    int in=0,i=0;
    DWORD dwBufferLen[10];
    DWORD Optval= 1 ;
    DWORD dwBytesReturned = 0 ;

    // 初始化套接字
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //创建原始套接字
    printf( "创建原始套接字...\n");
    SnifferSocket = socket ( AF_INET, SOCK_RAW, IPPROTO_IP);
    if (SnifferSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //获取本机名称
    memset( HostName, 0, DEFAULT_NAMELEN);
    iResult = gethostname( HostName, sizeof(HostName));
    if ( iResult ==SOCKET_ERROR) {
        printf("gethostname failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //获取本机可用IP
    local = gethostbyname( HostName);
    printf ("\n本机可用的IP地址为：\n");
    if( local ==NULL)
    {
        printf("gethostbyname failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    while (local->h_addr_list[i] != 0) {
        addr.s_addr = *(u_long *) local->h_addr_list[i++];
        printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
    }

    printf ("\n请选择捕获数据待使用的接口号：");
    scanf( "%d", &in);
    memset( &LocalAddr, 0, sizeof(LocalAddr));
    memcpy( &LocalAddr.sin_addr.S_un.S_addr, local->h_addr_list[in-1], sizeof(LocalAddr.sin_addr.S_un.S_addr));
    LocalAddr.sin_family = AF_INET;
    LocalAddr.sin_port=0;

    //绑定本地地址
    iResult = bind( SnifferSocket, (struct sockaddr *) &LocalAddr, sizeof(LocalAddr));
    if( iResult == SOCKET_ERROR){
        printf("bind failed with error: %ld\n", WSAGetLastError());
        closesocket(SnifferSocket);
        WSACleanup();
        return 1;
    }
    printf(" \n成功绑定套接字和 #%d 号接口地址\n", in);

    //设置套接字接收命令
    iResult = WSAIoctl(SnifferSocket, SIO_RCVALL , &Optval, sizeof(Optval),  &dwBufferLen, sizeof(dwBufferLen), &dwBytesReturned , NULL , NULL );
    if ( iResult == SOCKET_ERROR ){
        printf("WSAIoctl failed with error: %ld\n", WSAGetLastError());
        closesocket(SnifferSocket);
        WSACleanup();
    }

    //开始接收数据
    printf(" \n开始接收数据:\n");
    do
    {
        //接收数据
        iResult = recvfrom( SnifferSocket, recvbuf, DEFAULT_BUFLEN, 0 ,(struct sockaddr *)&RemoteAddr,&addrlen);
        if (iResult > 0)
            printf ("\n接收到来自\t%s\t\t的数据包，长度为 %d",inet_ntoa(RemoteAddr.sin_addr),iResult );
        else
            printf("recvfrom failed with error: %ld\n", WSAGetLastError());
    } while(iResult > 0);
    return 0;
    return a.exec();
}
