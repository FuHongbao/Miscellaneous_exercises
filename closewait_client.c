/*************************************************************************
	> File Name: closewait_client.c
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月20日 星期二 19时01分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "common_n.h"
#define PORT 9521

int main() {
    int x;
    char *ip = "192.168.2.62";
    for (int i = 0; i < 10; i++) {
        x = i;
        pid_t pid = fork();
        if (pid == 0) break;
    }
    while (1) {
        int sockfd = socket_connect(PORT, ip);
        char buff[1024] = {0};
        recv(sockfd, buff, sizeof(buff), 0);
        recv(sockfd, buff, sizeof(buff), 0);
        sleep(100);
    }
    return 0;
}

