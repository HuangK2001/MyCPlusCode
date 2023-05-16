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
            printf("sendto �������ô��󣬴���ţ�%ld\n",WSAGetLastError());
            return -1;
        }
        printf("\r\n�ͻ��˷������ݣ�%s \r\n",sendline); //����㣺��д����recvline

        memset(recvline,0,MAXLINE);
        iResult = recvfrom(s,recvline,MAXLINE,0,NULL,NULL);
        if(iResult > 0)
        {
            printf("�ͻ��˽��յ����ݣ�%s \r\n",recvline);
        }
        else {
            printf("recvfrom �������ô��󣬴���ţ�%d\n",WSAGetLastError());
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
    if (iResult == SOCKET_ERROR) {
        // WSACleanup����ʧ��
        printf("WSACleanup �������ô��󣬴���ţ� %d\n",  WSAGetLastError());
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

SOCKET SocketFrame::udp_client( char *hname, char *sname, BOOL flag)
{
    struct sockaddr_in peer;
    SOCKET ClientSocket;
    int iResult = -1;

    //ָ���������ĵ�ַpeerΪ�û������IP�Ͷ˿ں�
    if (set_address( hname, sname, &peer, "udp" ) ==1 )
        return -1;

    //�����׽���
    ClientSocket = socket( AF_INET, SOCK_DGRAM, 0 );
    if (ClientSocket == INVALID_SOCKET) {
        printf("socket �������ô��󣬴���ţ� %ld\n", WSAGetLastError());
        clean_up();
        return -1;
    }

    if( flag == TRUE)
    {
        //����ģʽ
        //�������������������
        iResult = connect(ClientSocket, ( struct sockaddr * )&peer, sizeof( peer ) );
        if (iResult == SOCKET_ERROR){
            printf("connect �������ô��󣬴���ţ� %d\n", WSAGetLastError());
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
