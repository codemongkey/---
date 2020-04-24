//删除一个队列，我们以IPC_RMID命令调用msgctl
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
 
int 
main(int argc, char** argv)
{
    int mqid ;
 
    if (argc != 2)
        puts("usage:remove <pathname>") ;
 
    mqid = msgget(ftok(argv[1], 0), 0) ;
    msgctl(mqid, IPC_RMID, NULL) ;
    exit(0) ;
}
