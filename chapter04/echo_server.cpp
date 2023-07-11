//
// Created by dgy on 23-7-11.
//
#include <cstring>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#define BUF_SIZE 1024
void error_handling(char *message);
int main(int argc,char *argv[]){
    int serv_sock,clnt_sock;
    char message[BUF_SIZE];
    int str_len,i;
    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    if (argc!=2){
        printf("usage:%s <port><IP>\n",argv[0]);
        exit(1);
    }
    serv_sock= socket(AF_INET,SOCK_STREAM,0);
    int opt=1;//设置端口复用
    setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&opt, sizeof(int));
    if (serv_sock==-1){
        char *sock_error=(char *)"socket error";
        error_handling(sock_error);
    }
    memset(&serv_adr,0, sizeof(serv_adr));
    serv_adr.sin_addr.s_addr= htonl(INADDR_ANY);
    serv_adr.sin_port= htons(atoi(argv[1]));
    serv_adr.sin_family=AF_INET;
    if (bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        char *bind_error=(char *)"bind error";
        error_handling(bind_error);
    }

    if (listen(serv_sock,5)==-1){
        char *listen_error=(char *)"listen error";
        error_handling(listen_error);
    }

    clnt_adr_sz=sizeof(clnt_adr);
    for (int i = 0; i < 5; ++i) {
        clnt_sock= accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        if(clnt_sock==-1){
            char *accept=(char *)"accept error";
            error_handling(accept);
        }

        else
            printf("connect client %d \n",i+1);
        while((str_len= read(clnt_sock,message,BUF_SIZE))!=0)
            write(clnt_sock, message,str_len);
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}