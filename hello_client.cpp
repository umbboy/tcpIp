//
// Created by dgy on 23-7-11.
//
#include <iostream>
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
void error_handling(char *message);
int main(int argc,char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    if (argc!=3)
    {
        /*
         *  _exit() ：退出程序；
            exit（0）：运行正常退出程序；
            exit（1）：运行异常退出程序；
            return（）：返回函数，若在主函数中，则会退出函数并返回值。
         * */
        printf("usage :%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    sock= socket(PF_INET,SOCK_STREAM,0);
    if (sock==-1)
        error_handling("socket() error");
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_port= htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr= inet_addr(argv[1]);
    serv_addr.sin_family=PF_INET;
    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
        error_handling("connect error!");
    str_len= read(sock,message, sizeof(message)-1);
    if (str_len==-1)
        error_handling("read error");
    printf("message from server:%s \n",message);
    close(sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}