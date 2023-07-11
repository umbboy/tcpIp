//
// Created by dgy on 23-7-11.
//
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#define buf_size 1024
void error_handling(char *message);
/*
 * argc表示程序运行时发送给main函数的命令行参数的个数（包括可执行程序以及传参）。
argv[]是字符指针数组，它的每个元素都是字符指针，指向命令行中每个参数的第一个字符。
 * */
int main(int argc,char *argv[]){
    int sock;
    char message[buf_size];
    int str_len;
    struct sockaddr_in serv_adr;
    if (argc!=3){
        printf("usage :%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    sock= socket(AF_INET,SOCK_STREAM,0);
    if (sock==-1){
        char *sock_error=(char *)"sock error";
        error_handling(sock_error);
    }
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_port= htons(atoi(argv[2]));
    serv_adr.sin_addr.s_addr= inet_addr(argv[1]);
    serv_adr.sin_family=AF_INET;//地址族ipv4
    if (connect(sock,(struct sockaddr *)&serv_adr,sizeof (serv_adr))==-1){
        char *connnect_error=(char *)"connet error";
        error_handling(connnect_error);
    }
    else
        puts("connected.......");
    while(1){
        fputs("input message(Q to quit):",stdout);
        fgets(message,buf_size,stdin);
        if (!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
            break;
        write(sock,message, strlen(message));
        str_len= read(sock,message,buf_size-1);
        message[str_len]=0;
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