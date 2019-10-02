/*************************************************************************
	> File Name: tongxun2.c
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年06月05日 星期三 18时35分30秒
 ************************************************************************/
#include "common.h"
#include <pthread.h>
#define PORT 8881

int ip[20]={40,89,66,73,103,80,88,91,79,142,70,77,81,82,84};

struct Message{
    char name[20];
    char message[1024];
};

int socket_create(int port) {
    int listen_socket;
    struct sockaddr_in my_addr;
    if( (listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        return -1;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listen_socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0){
        return -1;
    }
    listen(listen_socket, 20);
    return listen_socket;
}
void *do_send(){
    char addr_ip[20]={0};
    struct Message msg;
    int socketfd;
    while (1) {
        for(int i = 0; i < 15; i++) {
            sprintf(addr_ip,"192.168.2.%d",ip[i]);
            if ((socketfd = socket_connect(PORT,addr_ip)) < 0){
                perror("socket_connect");
                continue;
            }
            strcpy(msg.name, "FuHongbao");
            strcpy(msg.message, "tomato\n");
            send(socketfd, &msg,sizeof(msg),0);
            memset(&msg, 0, sizeof(msg));
            struct timeval timeout = {3, 0};
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
            recv(socketfd, &msg,sizeof(msg), 0);
            printf("%s ---> %s\n",msg.name, msg.message);
            sleep(10);
        }
    }
}

void *do_recv(void *arg) {
    int *socketfd = (int *)arg;
    struct Message msg;
    
    int k = recv(*socketfd, &msg, sizeof(msg), 0);
    printf ("%s ---> %s\n",msg.name,msg.message);
    strcpy(msg.name, "FuHongbao");
    send(*socketfd, &msg, sizeof(msg), 0);
    close(*socketfd);
}

int main() {
    int server_listen;
    pthread_t send_t;

    if((server_listen = socket_create(PORT)) < 0) {
       perror("socket_connect"); 
    }
   // pthread_create(&send_t, NULL,do_send,NULL);

    while (1) {
        int socket_accept;
        pthread_t con_t;
        if ((socket_accept = accept(server_listen, NULL, NULL)) < 0 ){
            perror("accept");
            continue;
        }
        pthread_create(&con_t,NULL,do_recv,(void *)&socket_accept);
    }
    pthread_join(send_t,NULL);
    return 0;
}

