#include <iostream>
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
void error_handling(char *message);
int main(int argc,char *argv[]) {
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_size;
    char message[]="hello world!";
    if(argc!=2){
        printf("usage:%s<port>\n",argv[0]);
        exit(1);
    }
    /*
     * 创建套接字，但这个套接字并不是真正的服务器的套接字
     * */
    serv_sock= socket(PF_INET,SOCK_STREAM,0);
    if (serv_sock==-1)
        error_handling("socket() error!");
    memset(&serv_addr,0,sizeof (serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr= htonl(INADDR_ANY);//自动分配
    serv_addr.sin_port= htons(atoi(argv[1]));//命令行中输入的第一个字符
/*
 * 初始化结构体变量，完成套接字的分配
 * */
    if (bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof (serv_addr))==-1)
        error_handling("bind() error");
    if (listen(serv_sock,5)==-1)
        error_handling("listen() error");
    clnt_addr_size=sizeof (clnt_addr);
    /*
     * 请求建立连接
     * */
    clnt_sock= accept(serv_sock,(struct sockaddr*)& clnt_addr,&clnt_addr_size);
    if (clnt_sock==-1)
        error_handling("accept() error");
    /*
     * 向客户端传输数据
     * */
    write(clnt_sock,message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
void error_handling(char *message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
