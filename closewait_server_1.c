/*************************************************************************
	> File Name: closewait_server_1.c
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年08月20日 星期二 19时55分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "common_n.h"
#define PORT 8520

int main() {
    int sockfd = socket_create(PORT);
    while(1) {
        int newfd = accept(sockfd, NULL, NULL);
    }
    
    return 0;
}


