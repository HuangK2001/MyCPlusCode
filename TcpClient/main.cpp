#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
//����Ĭ�ϵĻ��������ȺͶ˿ں�
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
    // ��ʼ���׽���
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    printf("TCP �ͻ���������...\n");
    if (iResult != 0) {
        printf("WSAStartupʧ��,�����: %d\n", iResult);
        return 1;
    }
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // ������������ַ�Ͷ˿ں�
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("��ȡ��ַ��Ϣʧ��,�����: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // �������ӷ�������ַ��ֱ���ɹ�
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // �����׽���
        ConnectSocket = socket(AF_INET,SOCK_STREAM, IPPROTO_IP);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("�׽���ʧ��,�����: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

         SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //�趨��������IP��ַ��"127.0.0.1"�Ǳ��ػ�·��ַ
    //���ܱ�����������û�������������������IP��������
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000); //�˿ں�Ҫ��������˱���һ��
    iResult = connect(ConnectSocket,(SOCKADDR *)&addrSrv,sizeof(SOCKADDR));


        // ���������������
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
        printf("�޷����ӵ�������!\n");
        WSACleanup();
        return 1;
    }

    // ���ͻ������еĲ�������
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("����ʧ��,�����: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    printf("�����ֽ���: %ld\n", iResult);
    printf("��������:\n%s\n",sendbuf);
    // ���ݷ��ͽ���������shutdown()�����������ٷ������ݣ���ʱ�ͻ����Կ��Խ�������
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("�ر�ʧ��,�����: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // �����������ݣ�ֱ���������ر�����
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
        {
            printf("\n�յ�Server�˻������ݣ�\n");
            printf("%s\n",recvbuf);
            printf("\n�����յ��ֽ���: %d\n", iResult);
        }

        else if ( iResult == 0 )
            printf("���ӹر�\n");
        else
            printf("����ʧ��,�����: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    // �ر��׽���
    closesocket(ConnectSocket);
    // �ͷ���Դ
    WSACleanup();
    return 0;
}
