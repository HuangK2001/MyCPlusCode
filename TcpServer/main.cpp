#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_BUFLEN 512    //Ĭ�ϻ���������Ϊ512
#define DEFAULT_PORT "6000"  //Ĭ�Ϸ������˿ں�Ϊ27015
int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL;
    struct addrinfo hints;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    // ��ʼ�� Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartupʧ��,�����: %d\n", iResult);
        return 1;
    }
    ZeroMemory(&hints, sizeof(hints));

    //����IPv4��ַ�壬��ʽ�׽��֣�TCPЭ��
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // ������������ַ�Ͷ˿ں�
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 )
    {
         printf("��ȡ��ַ��Ϣʧ��,�����: %d\n", iResult);
         WSACleanup();
         return 1;
    }

    // Ϊ�������ӵķ����������׽���
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(ListenSocket == INVALID_SOCKET)
    {
        printf("�׽���ʧ��,�����: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Ϊ�׽��ְ󶨵�ַ�Ͷ˿ں�
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("��ʧ��,�����: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    // ������������
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("����ʧ��,�����: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    printf("TCP����˿�����...\n");
    // ���ܿͻ����������󣬷��������׽���ClientSocket
    ClientSocket = accept(ListenSocket,NULL,NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("ͬ������ʧ�ܣ������: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // �ڱ���Ҫ�����׽��ֵ�������ͷŸ��׽���
    closesocket(ListenSocket);

    // �����������ݣ�ֱ���Է��ر�����
    do
    {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0)
        {


            //���1���ɹ����յ�����
            printf("�յ��ֽ���: %d\n", iResult);
            //�������������ݻ��͸��ͻ���
            iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR)
            {
                printf("����ʧ�ܣ������: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("�����ֽ���: %d\n", iSendResult);
        }
        else if (iResult == 0)
        {
            //���2�����ӹر�
            printf("���ӹر�...\n");
        }
        else
        {
            //���3�����շ�������
            printf("����ʧ��,�����: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    } while (iResult > 0);
    //shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("�ر�ʧ��,�����: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
    return 0;
}
