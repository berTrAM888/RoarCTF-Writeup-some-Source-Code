#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utility.h"

void ctf_init(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(300);
}

int read_char(char *buff, int size){
    return read_until(buff, size, '\n');
}

int read_int(){
    char number[8];
    read_char(number, 8);
    return atoi(number);
}

int read_until(char *buff, int size, char end_char){
    int res, i;

    for(i = 0; i < size; ++i){
        res = read(STDIN_FILENO, buff + i, 1);
        if(res != 1){
            exit(-1);
        }
        if(buff[i] == end_char){
            buff[i] = '\0';
            return i;
        }
    }

    buff[size - 1] = '\0';
    return size - 1;
}

