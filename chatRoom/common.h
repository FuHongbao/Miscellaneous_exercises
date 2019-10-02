/*************************************************************************
	> File Name: common.h
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年06月02日 星期日 17时10分55秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>

int socket_connect(int port, char *host) {
  int sockfd;
  struct sockaddr_in dest_addr;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket() error");
    return -1;
  }

  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;   //地址族
  dest_addr.sin_port = htons(port);  //端口转为网络字节序（htons）
  dest_addr.sin_addr.s_addr = inet_addr(host);//ipv4 32位无符号整型(网络字节序)

  //DBG("Connetion TO %s:%d\n",host,port);
  //fflush(stdout);
  if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
    //perror("connect() error");
    //DBG("connect() error : %s!\n", strerror(errno));
    return -1;
  }
  return sockfd;  //已经建立好连接的套接字

}

    
#endif
