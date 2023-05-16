#include "socketframe.h"
#include "winsock2.h"
#include<cstdio>
#define MAXLINE 200
SocketFrame::SocketFrame()
{

}
int udp_server_fun_echo(SOCKET s)
{
    int iResult = 0;
    struct sockaddr_in cliaddr;
    int addrlen = sizeof( sockaddr_in );
    char recvline[MAXLINE];
    do{
        memset(recvline,0,MAXLINE);
        iResult = recvfrom(s,recvline,MAXLINE,0,(SOCKADDR *)&cliaddr,&addrlen);
        if(iResult > 0)
        {
            printf("服务器端接收到数据%s\n",recvline);
            iResult = sendto(s,recvline,iResult,0,(SOCKADDR *)&cliaddr,addrlen);
            if(iResult == SOCKET_ERROR)
            {
                printf("sendto 函数调用错误，错误号：%ld\n",WSAGetLastError());
                iResult = -1;
            }
            else
                printf("服务器端发送数据%s\n",recvline);
        }
        else
        {
            printf("recvfrom 函数调用错误，错误号：%d\n",WSAGetLastError());
            iResult = -1;
        }
    }while(iResult > 0);
    return iResult;
}

int SocketFrame::start_up(void)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int iResult;

    // 使用 MAKEWORD(lowbyte, highbyte) 宏，在Windef.h 中声明
    wVersionRequested = MAKEWORD(2, 2);

    iResult = WSAStartup(wVersionRequested, &wsaData);
    if (iResult != 0) {
        //告知用户无法找到合适可用的Winsock DLL
        printf("WSAStartup 函数调用错误，错误号： %d\n",  WSAGetLastError());
        return -1;
    }

    // 确认WinSock Dll支持版本2.2
    // 注意，如果DLL支持的版本比2.2更高，根据用户调用前的需求，仍然返回2.2版本号，存储于wsaData.wVersion

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        // 告知用户无法找到可用的WinSock DLL.
        printf("无法找到可用的Winsock.dll版本\n");
        WSACleanup();
        return -1;
    }
    return 0;
}

int SocketFrame::clean_up(void)
{
    int iResult;
    iResult = WSACleanup();
    if (iResult == SOCKET_ERROR){
        // WSACleanup调用失败
        printf("WSACleanup 函数调用错误，错误号： %d\n",WSAGetLastError());
        return -1;
    }
    return 0;
}

int SocketFrame::quit(SOCKET s)
{
    int iResult=0;
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR){
        printf("closesocket 函数调用错误，错误号：%d\n", WSAGetLastError());
        return -1;
    }
    iResult = clean_up();
    return iResult;
}

int SocketFrame::set_address(char * hname, char * sname, struct sockaddr_in * sap, char * protocol)
{
    struct servent *sp;
    struct hostent *hp;
    char *endptr;
    unsigned short port;
    unsigned long ulAddr = INADDR_NONE;


    //对地址结构socketaddr_in初始化为0，并设置地址族为AF_INET
    memset( sap,0, sizeof( *sap ) );
    sap->sin_family = AF_INET;

    if ( hname != NULL )
    {
        //如果hname不为空，假定给出的hname为点分十进制表示的数字地址，转换地址为sockaddr_in类型
        ulAddr = inet_addr(hname);
        if ( ulAddr == INADDR_NONE || ulAddr == INADDR_ANY) {
            //printf("inet_addr 函数调用错误，错误号： %d\n", WSAGetLastError());
            //调用错误，表明给出的是主机名，调用gethostbyname获得主机地址
            hp = gethostbyname( hname );
            if ( hp == NULL ) {
                printf("未知的主机名，错误号： %d\n", WSAGetLastError());
                return -1;
            }
            sap->sin_addr = *( struct in_addr * )hp->h_addr;
        }
        else
            sap->sin_addr.S_un.S_addr=ulAddr;
    }
    else
        //如果调用者没有指定一个主机名或地址，则设置地址为通配地址INADDR_ANY
        sap->sin_addr.s_addr = htonl( INADDR_ANY );
    //尝试转换sname为一个整数
    port = (unsigned short )strtol( sname, &endptr, 0 );
    if ( *endptr == '\0' )
    {
        //如果成功则转换为网络字节顺序
        sap->sin_port = htons( port );
    }
    else
    {
        //如果失败，则假定是一个服务名称，通过调用getservbyname获得端口号
        sp = getservbyname( sname, protocol );
        if ( sp == NULL ) {
            printf("未知的服务，错误号： %d\n", WSAGetLastError());
            return -1;
        }
        sap->sin_port = sp->s_port;
    }
    return 0;
}

SOCKET SocketFrame::udp_server( char *hname, char *sname )
{
    sockaddr_in local;
    SOCKET ServerSocket;
    const int on = 1;
    int iResult = 0;

    //为服务器的本地地址local设置用户输入的IP和端口号
    if (set_address( hname, sname, &local, "udp" ) !=0 )
        return -1;

    //创建套接字
    ServerSocket = socket( AF_INET, SOCK_DGRAM, 0 );
    if (ServerSocket == INVALID_SOCKET) {
        printf("socket 函数调用错误，错误号： %ld\n", WSAGetLastError());
        clean_up();
        return -1;
    }

    //设置服务器地址可重用选项
    iResult = setsockopt( ServerSocket, SOL_SOCKET, SO_REUSEADDR, ( char * )&on, sizeof( on ));
    if ( iResult == SOCKET_ERROR){
        printf("setsockopt函数调用错误，错误号： %d\n", WSAGetLastError());
        quit(ServerSocket);
        return -1;
    }

    //绑定服务器地址
    iResult = bind( ServerSocket, (struct sockaddr *) & local, sizeof (local));
    if (iResult == SOCKET_ERROR) {
        printf("bind 函数调用错误，错误号： %d\n", WSAGetLastError());
        quit(ServerSocket);
        return -1;
    }

    return ServerSocket;
}
