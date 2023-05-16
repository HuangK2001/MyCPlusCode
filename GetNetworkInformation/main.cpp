#include <QCoreApplication>
#include <winsock2.h>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WORD wdVersion = MAKEWORD(2, 2);
    WSADATA wdSockMsg;
    int nRes = WSAStartup(wdVersion, &wdSockMsg);
    char hostname[50];
    if(gethostname(hostname,sizeof(hostname)))
    {
        printf("gethostname() Error:%u\n",WSAGetLastError());
        return 0;
    }
    printf("以下信息由gethostname()函数获得：\n");
    printf("Local host name:%s\n",hostname);

    PHOSTENT pHostent;
    pHostent = gethostbyname(hostname);
    if(pHostent == NULL)
    {
        printf("gethostname() Error:%u\n",WSAGetLastError());
        return 0;
    }
    printf("以下信息由gethostbyname()函数获得：\n");
    printf("name:%s\naliases:%s\naddrtype:%d\nlength:%d\n",
           pHostent->h_name,pHostent->h_aliases,pHostent->h_addrtype,pHostent->h_length);
    SOCKADDR_IN sa;
    for (int n = 0;pHostent->h_addr_list[n];n++)
    {
        memcpy(&sa.sin_addr.s_addr,pHostent->h_addr_list[n],pHostent->h_length);
        printf("Address:%s\n",inet_ntoa(sa.sin_addr));
    }

    PPROTOENT pProtoent;
    pProtoent = getprotobyname("tcp");
    if(pProtoent == NULL)
    {
        printf("getprotobyname() Error:%u\n",WSAGetLastError());
        return 0;
    }
    printf("以下信息由getprotobyname()函数获得：\n");
    printf("name:%s\nproto:%d\n",pProtoent->p_name,pProtoent->p_proto);
    for(int n = 0;pProtoent->p_aliases[n];n++)
    {
        printf("aliases:%s\n",pProtoent->p_aliases[n]);
    }

    servent *server_info;
    server_info = getservbyname("www",NULL);
    printf("以下信息由getservbyname()函数获得：\n");
    if(server_info != NULL)
    {
        printf("s_name:%s\n",server_info->s_name);
        for(int i = 0;server_info->s_aliases[i] != NULL;i++)
        {
            printf("s_aliases:%s\n",server_info->s_aliases[i]);
        }
        printf("s_port:%d\n",ntohs((u_short)server_info->s_port));
        printf("s_port:%d\n",server_info->s_proto);
    }
    WSACleanup();
    return a.exec();
}
