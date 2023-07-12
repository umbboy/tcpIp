//
// Created by dgy on 23-7-12.
//
#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "string.h"
#include "unistd.h"
#define buf_size 1024
void error_handling(char *message);
int main(int argc,char *argv[])
{
    int sock;
    char message[buf_size];
    int str_len,recv_len,recv_cnt;
    struct sockaddr_in serv_addr;
    if (argc!=3)
    {
        printf("usage : %s <ip> <port>\n",argv[0]);
        exit(1);//非正常退出
    }
    sock= socket(PF_INET,SOCK_STREAM,0);
    if (sock==-1)
    {
        char *sock_error=(char *)"sock error";
        error_handling(sock_error);
    }
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;//地址族
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);//具体的IP地址
    serv_addr.sin_port= htons(atoi(argv[2]));//端口号
    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        char *connect_error=(char *)"connect error";
        error_handling(connect_error);
    }
    else
        printf("connect........");
    while(1)
    {
        fputs("input message (Q):",stdout);
        fgets(message,buf_size,stdin);
        if (!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
            break;
//        sizeof会将空字符\0计算在内，而strlen不会将空字符\0计算在内。
        str_len= write(sock,message, strlen(message));
        recv_len=0;
        while(recv_len<str_len)
        {
            recv_cnt+= read(sock, &message[recv_len],buf_size-1);
            if (recv_cnt==-1){
                char *error=(char *)"read error";
                error_handling(error);
            }
            recv_len+=recv_cnt;
        }
        message[recv_len]=0;
        printf("message from server:%s",message);
    }
    close(sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}