// 套接字
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// UNIX/LINUX STD
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    // 创建套接字
    // 1.协议族，通讯使用的协议族，AF_INET表示IPv4协议族
    // 2.套接字类型，SOCK_STREAM表示流式套接字，SOCK_DGRAM表示数据报套接字
    // 3.协议，0表示使用默认协议
    // 返回值：成功返回套接字描述符，失败返回-1
    int s_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 设置套接字参数：端口/地址复用，解决端口冲突或改变问题
    int opt = 1;
    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // struct sockaddr addr;            // 通用
    struct sockaddr_in addr;            // TCP/IP协议族
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;          // 协议族
    // addr.sin_port = 2000;        // 端口号，tode:大小端问题
    addr.sin_port = htons(2000);        // 端口号，htons将主机字节序转换为网络字节序
    // addr.sin_addr.s_addr = INADDR_ANY;  // IP地址，INADDR_ANY表示任意地址
    addr.sin_addr.s_addr = htonl(INADDR_ANY);   // host to net long 主机字节序转换为网络字节序
    // 套接字绑定服务端地址
    bind(s_fd, (struct sockaddr *)&addr, sizeof(addr));
    
    // 监听套接字，等待客户端连接，初始化一个请求队列，最大长度为5
    listen(s_fd, 5);
    printf("server is running...\n");

    // 接收客户端连接请求，阻塞等待客户端连接
    while (1)
    {
        // 建立连接，返回一个新的套接字描述符，用于与客户端通信
        int c_fd = accept(s_fd, NULL, NULL);
        printf("client connected, fd: %d\n", c_fd);
        // 读写
        char buf[128];
        while (1)
        {
        memset(buf, 0, sizeof(buf));
        read(c_fd, buf, 128);
        if (!strncmp(buf, "bye", 3))
        {
            break;
        }
        
        printf("rece:%s\n", buf);
        //
        char msg[] = "bye\n";
        write(c_fd, msg, sizeof(msg));
        }
        
        
        
        close(c_fd);
    }



    close(s_fd);
    return 0;
}

