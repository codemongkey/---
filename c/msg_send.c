//向消息队列发送消息(把一个指定了长度和类型的消息放置到某个队列中)
//我们必须在不同进程中约定好 标识消息队列的 路径名和工程ID，
//可把此两者放置到一个头文件中，让用消息队列通信的进程代码都包含此头文件。
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> //包含ftok
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/fcntl.h>
 
#define MSG_W 0200
#define BUF_SIZE 512
 
typedef struct msgbuf
{
    long mtype ;
    char mdata[BUF_SIZE] ;
} mymsg_t ;
 
int 
main(int argc, char** argv)
{
    int            mqid ;    //消息队列的描述符
    size_t         msglen ;  //消息的长度
    long           msgtype ; //消息的类型
    mymsg_t*  ptr ;     //消息结构的指针
 
    //用户未按格式输入
    if (argc != 3)
        puts("usage: send <pathname> <type>") ;
 
    msgtype = atoi(argv[2]) ;
 
    //获取已存在消息队列的描述符
    mqid = msgget(ftok(argv[1], 0), MSG_W) ;
 
    //构造一条消息
    ptr = calloc(sizeof(long) + msglen, sizeof(char)) ;
    ptr->mtype = msgtype ;
    snprintf(ptr->mdata, BUF_SIZE, "Hi,Boy~") ;
	printf("mqid=%d\n",mqid);
 
    //发送消息
    msglen = strlen(ptr->mdata) ;
    msgsnd(mqid, ptr, msglen, 0) ;
 
   exit(0) ;
}
