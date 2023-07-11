# linux 套接字的基本函数
**step1 调用socket函数创建套接字**
```c
int socket(int domain,int type,int protocol)
/*
 * 其中domian表示IP地址类型，常用的有 AF_INET 和 AF_INET6。AF_INET 表示 IPv4 地址，例如 127.0.0.1；AF_INET6 表示 IPv6 地址，例如 1030::C9B4:FF12:48AA:1A2B。
 * 你也可以使用 PF 前缀，PF 是“Protocol Family”的简写，它和 AF 是一样的。例如，PF_INET 等价于 AF_INET，PF_INET6 等价于 AF_INET6。
 * type 为数据传输方式/套接字类型，常用的有 SOCK_STREAM（流格式套接字/面向连接的套接字） 和 SOCK_DGRAM（数据报套接字/无连接的套接字）
 * protocol:0表示自动选择
 * */
```
**step2 调用bind函数分配ip地址和端口号**
```c
//给创建好的套接字分配IP地址和端口号
//成功时返回0，失败时返回-1
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
/*
 * sockfd:上面创建的套接字的返回值
 * myaddr:结构体，具体如下
 * //创建sockaddr_in结构体变量
struct sockaddr_in serv_addr;
memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
serv_addr.sin_family = AF_INET;  //使用IPv4地址
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
serv_addr.sin_port = htons(1234);  //端口
 * */
```
**step3 调用listen使套接字可以接受请求**
```c
//将套接字转化为可接受连接的状态
//成功时返回0，失败时返回-1
int listen(int sockfd, int backlog);
/*
 *sockfd:监听的端口号
 * backlog：请求队列的最大长度
 * */
```
**Step4 调用accept函数接受请求**
```c
//受理连接请求
//成功时返回0，失败时返回-1
int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
/*
 * sockfd:socket创建的套接字
 * addr：客户端网络套接字地址
 * addrlen：地址长度
 * */
```
accept() 返回一个新的套接字来和客户端通信，addr 保存了客户端的IP地址和端口号，而 sock 是服务器端的套接字，大家注意区分。后面和客户端通信时，要使用这个新生成的套接字，而不是原来服务器端的套接字。