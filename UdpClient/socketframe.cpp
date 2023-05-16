#include "socketframe.h"
#include "winsock2.h"
#include "cstdio"
#define MAXLINE 200
SocketFrame::SocketFrame()
{

}
int udp_client_fun_echo(FILE *fp,SOCKET s,SOCKADDR *servaddr,int servlen)
{
    int iResult;
    char sendline[MAXLINE],recvline[MAXLINE];
    memset(sendline,0,MAXLINE);
    memset(recvline,0,MAXLINE);
    while(fgets(sendline,MAXLINE,fp)!=NULL)
    {
        if( *sendline == 'Q')
        {
            printf("input end!\n");
            return 0;
        }
        iResult = sendto(s,sendline,strlen(sendline),0,(SOCKADDR *)servaddr,servlen);
        if(iResult == SOCKET_ERROR)
        {
            printf("sendto 函数调用错误，错误号：%ld\n",WSAGetLastError());
            return -1;
        }
        printf("\r\n客户端发送数据：%s \r\n",sendline); //错误点：误写成了recvline

        memset(recvline,0,MAXLINE);
        iResult = recvfrom(s,recvline,MAXLINE,0,NULL,NULL);
        if(iResult > 0)
        {
            printf("客户端接收到数据：%s \r\n",recvline);
        }
        else {
            printf("recvfrom 函数调用错误，错误号：%d\n",WSAGetLastError());
            break;
        }
        memset(sendline,0,MAXLINE);
    }
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
    if (iResult == SOCKET_ERROR) {
        // WSACleanup调用失败
        printf("WSACleanup 函数调用错误，错误号： %d\n",  WSAGetLastError());
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

SOCKET SocketFrame::udp_client( char *hname, char *sname, BOOL flag)
{
    struct sockaddr_in peer;
    SOCKET ClientSocket;
    int iResult = -1;

    //指明服务器的地址peer为用户输入的IP和端口号
    if (set_address( hname, sname, &peer, "udp" ) ==1 )
        return -1;

    //创建套接字
    ClientSocket = socket( AF_INET, SOCK_DGRAM, 0 );
    if (ClientSocket == INVALID_SOCKET) {
        printf("socket 函数调用错误，错误号： %ld\n", WSAGetLastError());
        clean_up();
        return -1;
    }

    if( flag == TRUE)
    {
        //连接模式
        //请求向服务器建立连接
        iResult = connect(ClientSocket, ( struct sockaddr * )&peer, sizeof( peer ) );
        if (iResult == SOCKET_ERROR){
            printf("connect 函数调用错误，错误号： %d\n", WSAGetLastError());
            quit(ClientSocket);
            return -1;
        }
    }

    return ClientSocket;
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
