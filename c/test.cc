#include<iostream>
#include<vector>
#include<string>
#include <stdio.h>
#include<stdlib.h>  //atexit函数所属头文件
using namespace std;
void init(void) __attribute__((constructor));
void init(void){
    printf("before enter main!\n");
}
void exit_func(void){
    printf("after leave main!\n");
}
int main(void){
    void *m = malloc(5);
    atexit(exit_func);
    printf("hello world!\n");
}
