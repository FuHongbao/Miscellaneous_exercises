/*************************************************************************
	> File Name: tongxun2.c
	> Author: victoria 
	> Mail: 1105847344@qq.com
	> Created Time: 2019年06月05日 星期三 18时35分30秒
 ************************************************************************/
#include "common.h"
#include <pthread.h>
#define PORT 8881

//int ip[20]={40,89,66,73,103,80,88,91,79,142,70,77,81,82,84};

struct Message{
    char name[20];
    char message[1024];
    char file_name[100];
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
/*void *do_send(){
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
            memset(&msg, 0, sizeof(msg));
            strcpy(msg.name, "FuHongbao");
            printf("请输入要发送的文件名：");
            char fname[100],ffname[100];
            scanf("%s",fname);
            getchar();
            sprintf(ffname,"./%s",fname);
            printf("%s\n",ffname);
            FILE *file;
            file = fopen(ffname, "r+");
            char tmp_char[100];
            while ((fread(tmp_char, sizeof(char),1,file)) != 0) {
                strcat(msg.message, tmp_char);
            }
            fclose(file);
            strcpy(msg.file_name, fname);
            send(socketfd, &msg,sizeof(msg),0);
            memset(&msg, 0, sizeof(msg));
            struct timeval timeout = {3, 0};
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
            recv(socketfd, &msg,sizeof(msg), 0);
            printf("%s ---> %s\n",msg.name, msg.message);
            sleep(10);
        }
    }
}*/

void *do_recv(void *arg) {
    int *socketfd = (int *)arg;
    struct Message msg;
    
    while(1){
        memset(&msg, ' ', sizeof(msg));
        int k = recv(*socketfd, &msg, sizeof(msg), 0);
        if(k <= 0) break;
        printf ("%s 向您发送了一个文件\n",msg.name);
        char fname[100];
        FILE *recv_file;
        sprintf(fname,"/home/victoria/haizei/%s",msg.file_name);
        recv_file = fopen(fname, "wb+");
        char mess[1024];
        strcpy(mess, msg.message);
        fwrite(mess, sizeof(char), strlen(mess), recv_file);
        fclose(recv_file);
    }
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

