#include <QCoreApplication>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 6000

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WSADATA wsaData;
    int iResult;
    SOCKET ServerSocket = INVALID_SOCKET;
    SOCKET AcceptSocket = INVALID_SOCKET;
    char recvbuf[DEFAULT_BUFLEN];
    char sendbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int sendbuflen = DEFAULT_BUFLEN;
    sockaddr_in addrClient;
    int addrClientlen = sizeof(sockaddr_in);

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0)
    {
        printf("初始化套接字失败:%d\n",iResult);
        return 1;
    }

    ServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if(ServerSocket == INVALID_SOCKET)
    {
        printf("套接字创建失败:%ld\n",WSAGetLastError());
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN addrServ;
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(DEFAULT_PORT);
    addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    iResult = bind(ServerSocket,(const struct sockaddr*)&addrServ,sizeof (SOCKADDR_IN));
    if(iResult == SOCKET_ERROR)
    {
        printf("绑定套接字失败:%d\n",WSAGetLastError());
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    int iMode = 1;
    iResult = ioctlsocket(ServerSocket,FIONBIO,(u_long*)&iMode);
    if(iResult == SOCKET_ERROR)
    {
        printf("设置非阻塞模式失败:%d\n",WSAGetLastError());
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    iResult = listen(ServerSocket, SOMAXCONN);
    if(iResult == SOCKET_ERROR)
    {
        printf("监听失败!\n");
        closesocket(ServerSocket);
        WSACleanup();
        return -1;
    }
    printf("TCP 服务器启动中...\n");
    int err;

    while (true)
    {
        AcceptSocket = accept(ServerSocket,(sockaddr FAR*)&addrClient,&addrClientlen);
        if(AcceptSocket == INVALID_SOCKET)
        {
            err = WSAGetLastError();
            if(err ==WSAEWOULDBLOCK)
            {
                Sleep(1000);
                continue;
            }
            else
            {
                printf("建立连接失败!\n");
                closesocket(ServerSocket);
                WSACleanup();
                return 1;
            }
        }

        while (true)
        {
            memset(recvbuf,0,recvbuflen);
            iResult = recv(AcceptSocket,recvbuf,recvbuflen,0);
            if(iResult > 0)
            {
                printf("收到Client端内容：\n");
                printf("%s\n",recvbuf);
                printf("\n收到字节数: %d\n",iResult);
                memcpy(sendbuf,recvbuf,sizeof (recvbuf)); //把接收缓冲区数据拷贝到发送缓冲区
                send(AcceptSocket,sendbuf,iResult,0); //把发送缓冲区的数据发送出去，iResult指定要发送的字节数
                printf("\n回射发送字节数: %d\n",iResult);
                continue;
            }
            else if (iResult == 0)
            {
                printf("连接关闭，等待下一次连接...\n");
                closesocket(AcceptSocket);
                break;
            }
            else
            {
                err = WSAGetLastError();
                if(err == WSAEWOULDBLOCK)
                {
                    Sleep(10000);
                    printf("\n当前I/O不满足，等待毫秒轮询");
                    continue;
                }
                else
                {
                    printf("接收失败: %d\n",err);
                    closesocket(AcceptSocket);
                    closesocket(ServerSocket);
                    WSACleanup();
                    return 1;
                }
            }
        }
    }
    closesocket(ServerSocket);
    closesocket(AcceptSocket);
    WSACleanup();
    return 0;
    return a.exec();
}
