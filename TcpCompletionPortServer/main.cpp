#include <QCoreApplication>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<iostream>
using namespace std;
#define MAXDATASIZE 200
#define SERVERPORT 6000

typedef struct
{
    OVERLAPPED OverLappe;
    WSABUF DataBuf;
    char buffer[MAXDATASIZE];
    DWORD BytesSEND, BytesRECV;
}PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

typedef struct
{
    SOCKET Sock;
}PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
    HANDLE CompletionPort = (HANDLE)CompletionPortID;
    DWORD BytesTransferred;
    LPOVERLAPPED OverLapp;
    LPPER_IO_OPERATION_DATA PerIOData;
    LPPER_HANDLE_DATA PerHandleData;
    DWORD SendBytes, RecvBytes, Flags;

    while (true)
    {
        BOOL Ret = GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,
                                             (PULONG_PTR)&PerHandleData, (LPOVERLAPPED*)&PerIOData, INFINITE);
        if (Ret == 0)
        {
            cout << "GetQueuedCompletionStatus() failed with error " << GetLastError() << endl;
            return 0;
        }
        if (BytesTransferred == 0)
        {
            cout << "Closing socket " << PerHandleData->Sock << endl;
            if (closesocket(PerHandleData->Sock) == 0)
            {
                cout << "closesocket() failed with error " << GetLastError() << endl;
                return 0;
            }
            GlobalFree(PerHandleData);
            GlobalFree(PerIOData);
            continue;
        }
        if (PerIOData->BytesRECV == 0)
        {
            PerIOData->BytesRECV = BytesTransferred;
            PerIOData->BytesSEND = 0;
        }
        else
        {
            PerIOData->BytesSEND += BytesTransferred;
        }
        if (PerIOData->BytesRECV > PerIOData->BytesSEND)
        {
            ZeroMemory(&(PerIOData->OverLappe), sizeof(OVERLAPPED));
            PerIOData->DataBuf.buf = PerIOData->buffer + PerIOData->BytesSEND;
            PerIOData->DataBuf.len = PerIOData->BytesRECV - PerIOData->BytesSEND;
            Ret = WSASend(PerHandleData->Sock, &(PerIOData->DataBuf), 1,
                          &SendBytes, 0, &(PerIOData->OverLappe), NULL);
            if (Ret == SOCKET_ERROR)
            {
                if (WSAGetLastError() != ERROR_IO_PENDING)
                {
                    cout << "WSASend() failed with error " << WSAGetLastError() << endl;
                    return 0;
                }
            }
        }
        else
        {
            PerIOData->BytesRECV = 0;
            Flags = 0;
            ZeroMemory(&(PerIOData->OverLappe), sizeof(OVERLAPPED));
            PerIOData->DataBuf.len = MAXDATASIZE;
            PerIOData->DataBuf.buf = PerIOData->buffer;
            Ret = WSARecv(PerHandleData->Sock, &(PerIOData->DataBuf), 1, &RecvBytes,
                          &Flags, &(PerIOData->OverLappe), NULL);
            if (Ret == SOCKET_ERROR)
            {
                if (WSAGetLastError() != ERROR_IO_PENDING)
                {
                    cout << "WSARecv() failed with error " << WSAGetLastError() << endl;
                    return 0;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DWORD Ret;
    WSADATA wsadata;
    WSAStartup(0x0202, &wsadata);
    HANDLE CompletionPort;
    CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (CompletionPort == NULL)
    {
        cout << "CreateIoCompletionPort() failed with error " << GetLastError() << endl;
        WSACleanup();
        return -1;
    }

    DWORD ThreadID;
    SYSTEM_INFO SystemInfo;
    GetSystemInfo(&SystemInfo);
    for (int i = 0; i < SystemInfo.dwNumberOfProcessors * 2; ++i)
    {
        HANDLE ThreadHandle;
        ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort, 0, &ThreadID);
        if (ThreadHandle == NULL)
        {
            cout << "CreateThread() failed with error " << GetLastError() << endl;
            WSACleanup();
            return -1;
        }
        CloseHandle(ThreadHandle);
    }

    SOCKET sockListen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sockListen == INVALID_SOCKET)
    {
        cout << "WSASocket() failed with error " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(SERVERPORT);
    local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    Ret = bind(sockListen, (SOCKADDR*)&local, sizeof(local));
    if (Ret == SOCKET_ERROR)
    {
        cout << "bind() failed with error " << WSAGetLastError() << endl;
        closesocket(sockListen);
        WSACleanup();
        return -1;
    }

    Ret = listen(sockListen, 3);
    if (Ret == SOCKET_ERROR)
    {
        cout << "listen() failed with error " << WSAGetLastError() << endl;
        closesocket(sockListen);
        WSACleanup();
        return -1;
    }

    cout << "Server listening..." << endl;
    SOCKET sockAccept;
    LPPER_HANDLE_DATA PerHandleData;
    LPPER_IO_OPERATION_DATA PerIoData;
    DWORD Flags, BytesRecv;
    WSABUF wsaData;
    while (true)
    {
        sockAccept = WSAAccept(sockListen, NULL, NULL, NULL, 0);
        if (sockAccept == INVALID_SOCKET)
        {
            cout << "WSAAccept() failed with error " << WSAGetLastError() << endl;
            closesocket(sockListen);
            WSACleanup();
            return -1;
        }
        cout << "WSAAccept() accept successfully, socketID: " << sockAccept<<"\n";
        PerHandleData = (LPPER_HANDLE_DATA)GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
        if (PerHandleData == NULL)
        {
            cout << "GlobalAlloc() failed with error " << GetLastError() << endl;
            closesocket(sockListen);
            WSACleanup();
            return -1;
        }
        PerHandleData->Sock = sockAccept;
        if (CreateIoCompletionPort((HANDLE)sockAccept, CompletionPort, (DWORD)PerHandleData, 0) == NULL)
        {
            cout << "CreateIoCompletionPort() failed with error " << GetLastError() << endl;
            closesocket(sockListen);
            closesocket(sockAccept);
            WSACleanup();
            return -1;
        }

        PerIoData = (LPPER_IO_OPERATION_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_OPERATION_DATA));
        if (PerIoData == NULL)
        {
            cout << "GlobalAlloc() failed with error " << GetLastError() << endl;
            closesocket(sockListen);
            closesocket(sockAccept);
            WSACleanup();
            return -1;
        }
        ZeroMemory(&(PerIoData->OverLappe), sizeof(OVERLAPPED));
        PerIoData->DataBuf.buf = PerIoData->buffer;
        PerIoData->DataBuf.len = MAXDATASIZE;
        PerIoData->BytesRECV = 0;
        PerIoData->BytesSEND = 0;
        Flags = 0;

        Ret = WSARecv(sockAccept, &(PerIoData->DataBuf), 1, &BytesRecv, &Flags,
                      &(PerIoData->OverLappe), NULL);
        if (Ret == SOCKET_ERROR)
        {
            if (WSAGetLastError() != ERROR_IO_PENDING)
            {
                cout << "WSARecv() failed with error " << WSAGetLastError() << endl;
                closesocket(sockListen);
                closesocket(sockAccept);
                WSACleanup();
                return -1;
            }
        }
    }
    closesocket(sockListen);
    WSACleanup();
    return 0;


    return a.exec();
}

