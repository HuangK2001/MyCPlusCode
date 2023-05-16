#include <QCoreApplication>
#include <pcap.h>
#include <Packet32.h>
#include <time.h>
#include <iostream>
#define lib_pcap_pcap_h
using namespace std;

typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
} ip_address;

typedef struct ip_header{
    u_char ver_ihl;
    u_char tos;
    u_char tlen;
    u_short identification;
    u_char flags_fo;
    u_char ttl;
    u_char protp;
    u_short crc;
    ip_address saddr;
    ip_address daddr;
    u_int op_pad;
} ip_header;

typedef struct udp_header{
    u_short sport;
    u_short dport;
    u_short len;
    u_short crc;
} udp_header;


void packet_handler(u_char *param,const struct pcap_pkthdr *header,const uchar *pkt_data)
{
    struct tm *ltime;
    char timestr[16];
    ip_header *ih;
    udp_header *uh;
    int ip_len;
    u_short sport, dport;
    time_t local_tv_sec;
    local_tv_sec=header->ts.tv_sec;
    ltime=localtime (&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S",ltime);
    printf ("%s.%.6d len: %d ",timestr, header->ts.tv_usec,header->len);
    ih = (ip_header *) (pkt_data + 14);
    ip_len = (ih->ver_ihl &0xf)* 4;
    uh = (udp_header *)((char*)ih +ip_len);

    sport= ntohs( uh->sport );
    dport =ntohs ( uh->dport );
    printf(" %d.%d. %d.%d.%d-> %d.%d. %d.%d. %d \n",
           ih->saddr.byte1,
           ih->saddr.byte2,
           ih->saddr.byte3,
           ih->saddr.byte4,
           sport,
           ih->daddr.byte1,
           ih->daddr.byte2,
           ih->daddr.byte3,
           ih->daddr.byte4,
           dport);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    pcap_if_t *alldevs;
    pcap_if_t *d;
    int inum;
    int i=0;
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
    u_int netmask;
    char packet_filter[]="ip and udp";
    struct bpf_program fcode;
    if(pcap_findalldevs(&alldevs,errbuf))
    {
        cout<<stderr<<" pcap_findalldecs 函数调用错误 "<<errbuf<<endl;
        return 1;
    }
    for(d=alldevs;d;d=d->next)
    {
        cout<<++i<<d->name<<endl;
        if(d->description)
        {
            cout<<d->description<<endl;
        }
        else
        {
            cout<<" 没有可以的描述符 "<<endl;
        }
    }
    if(i==0)
    {
        cout<<" 无法找到网路接口！请确认WinPcap已安装！"<<endl;
    }
    cout<<"请输入待捕获数据的网卡编号："<<endl;
    cin>>inum;
    if(inum<1||inum>i)
    {
        cout<<" Adapter number out of range. "<<endl;
        pcap_freealldevs(alldevs);
        return -1;
    }
    for (d=alldevs,i=0;i<inum-1;d=d->next,i++);
    {
        adhandle=pcap_open_live(d->name,65536,1,1000,errbuf);
    }
    if(adhandle==NULL)
    {
        cout<<stderr<<" 无法打开网卡，WinPcap不支持 "<<d->name<<endl;
        pcap_freealldevs(alldevs);
        return -1;
    }
    if(pcap_datalink(adhandle)!=DLT_EN10MB)
    {
        cout<<stderr<<" 本程序只在以太网中环境下使用 "<<endl;
        pcap_freealldevs(alldevs);
        return -1;
    }
    if(d->addresses!=NULL)
    {
        netmask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
    }
    else
    {
        netmask=0xffffff;
    }
    if(pcap_compile(adhandle,&fcode,packet_filter,1,netmask)<0)
    {
        cout<<stderr<<" 无法编译过滤规则，请检查语法的正确性 "<<endl;
        pcap_freealldevs(alldevs);
        return -1;
    }
    if(pcap_setfilter(adhandle,&fcode)<0)
    {
        cout<<stderr<<" 设置过滤器错误 "<<endl;
        pcap_freealldevs(alldevs);
        return -1;
    }
    cout<<" Listening on..."<<d->description<<endl;
    pcap_loop(adhandle,0,packet_handler,NULL);
    return 0;

    return a.exec();
}
