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
            printf("�������˽��յ�����%s\n",recvline);
            iResult = sendto(s,recvline,iResult,0,(SOCKADDR *)&cliaddr,addrlen);
            if(iResult == SOCKET_ERROR)
            {
                printf("sendto �������ô��󣬴���ţ�%ld\n",WSAGetLastError());
                iResult = -1;
            }
            else
                printf("�������˷�������%s\n",recvline);
        }
        else
        {
            printf("recvfrom �������ô��󣬴���ţ�%d\n",WSAGetLastError());
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

    // ʹ�� MAKEWORD(lowbyte, highbyte) �꣬��Windef.h ������
    wVersionRequested = MAKEWORD(2, 2);

    iResult = WSAStartup(wVersionRequested, &wsaData);
    if (iResult != 0) {
        //��֪�û��޷��ҵ����ʿ��õ�Winsock DLL
        printf("WSAStartup �������ô��󣬴���ţ� %d\n",  WSAGetLastError());
        return -1;
    }

    // ȷ��WinSock Dll֧�ְ汾2.2
    // ע�⣬���DLL֧�ֵİ汾��2.2���ߣ������û�����ǰ��������Ȼ����2.2�汾�ţ��洢��wsaData.wVersion

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        // ��֪�û��޷��ҵ����õ�WinSock DLL.
        printf("�޷��ҵ����õ�Winsock.dll�汾\n");
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
        // WSACleanup����ʧ��
        printf("WSACleanup �������ô��󣬴���ţ� %d\n",WSAGetLastError());
        return -1;
    }
    return 0;
}

int SocketFrame::quit(SOCKET s)
{
    int iResult=0;
    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR){
        printf("closesocket �������ô��󣬴���ţ�%d\n", WSAGetLastError());
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


    //�Ե�ַ�ṹsocketaddr_in��ʼ��Ϊ0�������õ�ַ��ΪAF_INET
    memset( sap,0, sizeof( *sap ) );
    sap->sin_family = AF_INET;

    if ( hname != NULL )
    {
        //���hname��Ϊ�գ��ٶ�������hnameΪ���ʮ���Ʊ�ʾ�����ֵ�ַ��ת����ַΪsockaddr_in����
        ulAddr = inet_addr(hname);
        if ( ulAddr == INADDR_NONE || ulAddr == INADDR_ANY) {
            //printf("inet_addr �������ô��󣬴���ţ� %d\n", WSAGetLastError());
            //���ô��󣬱�����������������������gethostbyname���������ַ
            hp = gethostbyname( hname );
            if ( hp == NULL ) {
                printf("δ֪��������������ţ� %d\n", WSAGetLastError());
                return -1;
            }
            sap->sin_addr = *( struct in_addr * )hp->h_addr;
        }
        else
            sap->sin_addr.S_un.S_addr=ulAddr;
    }
    else
        //���������û��ָ��һ�����������ַ�������õ�ַΪͨ���ַINADDR_ANY
        sap->sin_addr.s_addr = htonl( INADDR_ANY );
    //����ת��snameΪһ������
    port = (unsigned short )strtol( sname, &endptr, 0 );
    if ( *endptr == '\0' )
    {
        //����ɹ���ת��Ϊ�����ֽ�˳��
        sap->sin_port = htons( port );
    }
    else
    {
        //���ʧ�ܣ���ٶ���һ���������ƣ�ͨ������getservbyname��ö˿ں�
        sp = getservbyname( sname, protocol );
        if ( sp == NULL ) {
            printf("δ֪�ķ��񣬴���ţ� %d\n", WSAGetLastError());
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

    //Ϊ�������ı��ص�ַlocal�����û������IP�Ͷ˿ں�
    if (set_address( hname, sname, &local, "udp" ) !=0 )
        return -1;

    //�����׽���
    ServerSocket = socket( AF_INET, SOCK_DGRAM, 0 );
    if (ServerSocket == INVALID_SOCKET) {
        printf("socket �������ô��󣬴���ţ� %ld\n", WSAGetLastError());
        clean_up();
        return -1;
    }

    //���÷�������ַ������ѡ��
    iResult = setsockopt( ServerSocket, SOL_SOCKET, SO_REUSEADDR, ( char * )&on, sizeof( on ));
    if ( iResult == SOCKET_ERROR){
        printf("setsockopt�������ô��󣬴���ţ� %d\n", WSAGetLastError());
        quit(ServerSocket);
        return -1;
    }

    //�󶨷�������ַ
    iResult = bind( ServerSocket, (struct sockaddr *) & local, sizeof (local));
    if (iResult == SOCKET_ERROR) {
        printf("bind �������ô��󣬴���ţ� %d\n", WSAGetLastError());
        quit(ServerSocket);
        return -1;
    }

    return ServerSocket;
}
