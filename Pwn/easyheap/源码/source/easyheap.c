#include <malloc.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void *set=NULL;
size_t random_num =0;
void *chunk=NULL;
size_t ops = 0x10;
size_t twice = 3;
char username[0x28]="\0";
char info[0x30];

void banner(){
    puts("                                            88                                           ");
    puts("                                            88                                           ");
    puts("                                            88                                           ");
    puts(" ,adPPYba, ,adPPYYba, ,adPPYba, 8b       d8 88,dPPYba,   ,adPPYba, ,adPPYYba, 8b,dPPYba, ");
    puts("a8P_____88 \"\"     `Y8 I8[    \"\" `8b     d8' 88P'    \"8a a8P_____88 \"\"     `Y8 88P'    \"8a");
    puts("8PP\"\"\"\"\"\"\" ,adPPPPP88  `\"Y8ba,   `8b   d8'  88       88 8PP\"\"\"\"\"\"\" ,adPPPPP88 88       d8");
    puts("\"8b,   ,aa 88,    ,88 aa    ]8I   `8b,d8'   88       88 \"8b,   ,aa 88,    ,88 88b,   ,a8\"");
    puts(" `\"Ybbd8\"' `\"8bbdP\"Y8 `\"YbbdP\"'     Y88'    88       88  `\"Ybbd8\"' `\"8bbdP\"Y8 88`YbbdP\"' ");
    puts("                                    d8'                                       88         ");
    puts("                                   d8'                                        88         ");
}

void handler(){
    puts("time out!");
    exit(0);
}

void menu(){
    signal(SIGALRM, handler);
    alarm(0x3c);
    puts("1.add");
    puts("2.dele");
    puts("3.show");
    puts("4.exit");
    printf(">> ");
}

void add(){
    char buf[0x8];
    int ret=0;
    int size = 0;
    if(ops<=0){
        puts("chunk filled!\n");
        puts("everything has a price");
        return;
    }
    else{
        puts("input the size");
        ret = read(0,buf,0x8);
        if(ret<0){
            puts("read error");
            exit(0);
        }
        size = atol(buf);
        if(size<=0x80){
            chunk = malloc(size);
            puts("please input your content");
            ret = read(0,chunk,size);
            if(ret<0){
            puts("read error");
            exit(0);
            }
        }
        else{
            puts("invaild size");
            exit(0);
        }
    }
    ops--;
}

void dele(){
    free(chunk);
}

void show(){
    if(random_num == 0xdeadbeefdeadbeef){
        puts((char *)chunk);
        puts("everything has a price");
        //if (!mallopt(1, 0))
        //    exit(0);
        close(1);
        close(2);
    }
}

void gift(){
    int choice=0;
    int ret=0;
    char buf[8];
    if(twice){
        puts("build or free?");
        ret = read(0,buf,8);
        if(ret<0){
            puts("read error");
            exit(0);
        }
        choice = atoi(buf);
        if(choice==1){
            set = calloc(0xa0, 1);
            puts("please input your content");
            ret = read(0,set,0xa0);
            if(ret<0){
                puts("read error");
                exit(0);
            }
        }
        else if(choice==2){
            free(set);
        }
        else{
            puts("invaild choice");
        }
    }
    else{
        puts("everything has a price");
    }
    twice--;
}

int main(){
    int choice=0;
    int ret=0;
    size_t no=0;

    setvbuf(stdin,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stderr,0,2,0);

    no = open("/dev/random",O_RDONLY);
    if(no==-1){
        puts("open file error!");
        exit(0);
    }
    ret = read(no,&random_num,8);
    if(ret<0){
        puts("read error");
        exit(0);
    }
    close(no);

    banner();

    printf("please input your username:");
    ret = read(0,username,0x20);
    if(ret<0){
        puts("read error");
        exit(0);
    }
    printf("please input your info:");
    ret = read(0,info,0x20);

    if(ret<0){
        puts("read error");
        exit(0);
    }
    while(1){
        menu();
        ret = scanf("%d",&choice);
        if(ret<0){
            puts("scanf error");
            exit(0);
        }
        if(choice==1){
            add();
        }
        else if(choice==2){
            dele();
        }
        else if(choice==3){
            show();
        }
        else if(choice==4){
            break;
        }
        else if(choice==666){
            gift();
        }
        else{
            continue;
        }
    }
    return 0;
}