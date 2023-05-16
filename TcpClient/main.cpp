#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
//定义默认的缓冲区长度和端口号
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6000"

int __cdecl main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    //char *sendbuf = "This is client: hello world.Send to Non Blocking Server";
    char *sendbuf = "This is client: hello world.Send to Completion Port Server";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    // 初始化套接字
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    printf("TCP 客户端已启动...\n");
    if (iResult != 0) {
        printf("WSAStartup失败,错误号: %d\n", iResult);
        return 1;
    }
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // 解析服务器地址和端口号
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("获取地址信息失败,错误号: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // 尝试连接服务器地址，直到成功
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // 创建套接字
        ConnectSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_IP);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("套接字失败,错误号: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

         SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //设定服务器端IP地址，"127.0.0.1"是本地回路地址
    //不管本地主机上有没有网卡，都可以用这个IP测试网络
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000); //端口号要与服务器端保持一致
    iResult = connect(ConnectSocket,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));


        // 向服务器请求连接
        //iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("无法连接到服务器!\n");
        WSACleanup();
        return 1;
    }

    // 发送缓冲区中的测试数据
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("发送失败,错误号: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    printf("发送字节数: %ld\n", iResult);
    printf("发送内容:\n%s\n",sendbuf);
    // 数据发送结束，调用shutdown()函数声明不再发送数据，此时客户端仍可以接收数据
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("关闭失败,错误号: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // 持续接收数据，直到服务器关闭连接
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
        {
            printf("\n收到Server端回射内容：\n");
            printf("%s\n",recvbuf);
            printf("\n回射收到字节数: %d\n", iResult);
        }

        else if ( iResult == 0 )
            printf("连接关闭\n");
        else
            printf("连接失败,错误号: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    // 关闭套接字
    closesocket(ConnectSocket);
    // 释放资源
    WSACleanup();
    return 0;
}
