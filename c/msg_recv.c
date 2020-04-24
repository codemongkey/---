//从一个消息队列中读出一个消息， -n命令行选项指定非阻塞 -t命令行选项指定接收的消息类型
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> //包含ftok
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
 
#define MSG_R 0400
#define MSG_BUF_SIZE (512 + sizeof(long))
 
typedef struct msgbuf
{
    long mtype ;
    char mdata[MSG_BUF_SIZE-sizeof(long)] ;
} mymsg_t ;
 
int 
main(int argc, char** argv)
{
    int            c = 0 ;
    int            recvCntlFlag = 0 ;
    int            mqid = 0 ;
    long           msgtype = 0 ;
    ssize_t        recvBytes = 0 ; //已接收的字节数
    struct msgbuf* buf = NULL ;    //存储接收消息的缓冲区的指针   
 
    //读取用户输入的命令行
    while ((c = getopt(argc, argv, "nt:")) != -1)
    {
        switch(c)
        {
        case 'n' :
            recvCntlFlag |= IPC_NOWAIT ;
            break ;
        case 't' :
            msgtype = atol(optarg) ;
            break ;
        }
    }
 
    if (optind != argc-1)
        puts("usage:msgrcv [-n] [-t typeno] <pathname>") ;
 
    //获取要接收队列的id
    mqid = msgget(ftok(argv[optind], 0), MSG_R) ;
 
    //开辟缓冲区 接收消息
    buf = malloc(MSG_BUF_SIZE) ;
    recvBytes = msgrcv(mqid, buf, MSG_BUF_SIZE, msgtype, recvCntlFlag ) ;
 
    //输出消息内容
    printf("recv:%d bytes type=%ld %s",recvBytes, buf->mtype, buf->mdata) ;
    exit(0) ;
}
