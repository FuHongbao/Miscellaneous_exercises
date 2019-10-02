/*************************************************************************
	> File Name: qiuhe_3.cpp
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年07月05日 星期五 11时49分40秒
 ************************************************************************/

#include "common_n.h"
#include <stdio.h>
#include <pthread.h>
#define INE 10
int sum = 0, now = 0;
pthread_mutex_t met;
void *to_count(void *) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&met);
        now++;
        sum += now;
        pthread_mutex_unlock(&met);
    }
}


int main() {
    for (int i = 0; i < INE; i++) {
        pthread_t pth;
        pthread_create (&pth, NULL, to_count, NULL);
    }    
    sleep(2);
    printf("ans = %d\n", sum);
    return 0;
}

