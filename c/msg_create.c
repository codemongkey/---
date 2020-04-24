//创建一个消息队列，在创建时指定队列的最大消息数和每个消息的最大大小
//本程序使用说明：
//./create -e 路径名
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h> //包含ftok()
#include <fcntl.h>   //包含getopt() 及相关的外部变量
#include <stdio.h>
#include <stdlib.h>
 
int 
main(int argc, char** argv)
{
    int c, flags ;
    int mqid ; //消息队列id
 
    flags = IPC_CREAT|0600 ; //设置消息队列的标记
    //从命令行读取 队列的最大消息数 消息的最大大小
    while ((c = getopt(argc, argv, "e")) != -1)
    {
        switch(c)
        {
        case 'e':
            flags |= IPC_EXCL ; //排他性创建：若已存在此名的消息队列，则返回错误
            break;
        }
    }
 
    //若用户没有指定选项
    if (optind != argc -1)
       puts("请按格式输入：[-e] [-m maxmsg] [-z msgsize] <name>") ;
 
    //创建消息队列
    mqid = msgget(ftok(argv[optind], 0), flags) ;
    printf("optind=%d,mqid=%d.\n",optind,mqid); 
    exit(0) ;
}
