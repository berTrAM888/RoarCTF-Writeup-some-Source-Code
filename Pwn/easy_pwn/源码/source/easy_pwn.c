#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "error.h"
#include "errno.h"
//gcc -z noexecstack -fstack-protector-all -z now -fPIE -pie -s -o easy_pwn easy_pwn.c
struct tickets
{
int flag;
int size;
void *ticket_start;
};
struct tickets a[20];
//char *buf;
void init() {
	setvbuf(stdin, 0, 2, 0);
	setvbuf(stdout, 0, 2, 0);
    memset(a,0,sizeof(struct tickets)*20);
	alarm(0x3c);
}
int menu(){
    puts("Note system");
    puts("1. create a note");
    puts("2. write note");
    puts("3. drop the note");
    puts("4. show the note");
    puts("5. exit");
    return printf("choice: ");
}


int getchoice(int n){
    int x=scanf("%d",&n);
    if(n>256||n<0) return 10;
    return n;
}

int GET_TICKET(){
    int i;
    int size;
    void *start;
    for(i=0;i<=15;i++){
        if(!a[i].flag){
            printf("size: ");
            size=getchoice(size);
            if(size>0){
                if(size>4096)
                    size=4096;
                start=calloc(size,1);
                if(!start)
                    exit(-1);
                a[i].flag=1;
                a[i].size=size;
                a[i].ticket_start=start;
                int ptr=(long long)a[i].ticket_start&0xfff;
                printf("the index of ticket is %d \n",i);
            }
            return i;
        }
    }
}

int content(char *a1,int a2){
    __int64_t c;
    ssize_t d;
    if(!a2)
        return 0;
    c=0;
    while(c<a2){
        d=read(0,&a1[c],a2-c);
        if(d>0)
            c+=d;           
    }
    return c;
}

int getsize(int a,int b){
    if(a>b)
        return b;
    int c=(b-a==10)?a+1:a;
    return c;
}

int PALY_GANE(){
    int b;
    int size;
    int index;
    printf("index: ");
    b=getchoice(b);
    index=b;
    if(b>=0&&b<=15){
        b=a[b].flag;
        if(b==1){
            printf("size: ");
            b=getchoice(b);
            size=getsize(a[index].size,b);
            if(b>0){
                printf("content: ");
                b=content(a[index].ticket_start,size);
            }
        }
    }
    return b;
}

int GAME_OVER(){
    __int64_t res;
    int e;
    printf("index: ");
    res=getchoice(res);
    e=res;
    if(res>=0&&res<=15){
        res=a[res].flag;
        if(res==1){
            a[e].flag=0;
            a[e].size=0;
            free(a[e].ticket_start);
            a[e].ticket_start=NULL;
        }
    }
    return res;
}

int outputs(char *a1,int a2){
    __int64_t c;
    ssize_t d;
    if(!a2)
        return 0;
    c=0;
    while(c<a2){
        d=write(1,&a1[c],a2-c);
        if(d>0)
            c+=d;        
    }
    return c;
}
int LOOK_GANE(){
    int s;
    int f;
    printf("index: ");
    s=getchoice(s);
    f=s;
    if(s>=0&&s<=15){
        s=a[s].flag;
        if(s==1){
            printf("content: ");
            s=outputs(a[f].ticket_start,a[f].size);
        }
    }
    return s;
}

int main(){
    init();
    while(1){
        menu();
        int n;
        n=getchoice(n);
        switch(n){
            case 1:
                GET_TICKET();
                break;
            case 2:
                puts("Tell me the secret about you!!");
                PALY_GANE();
                break;
            case 3:
                GAME_OVER();
                break;
            case 4:
                LOOK_GANE();
                break;
            case 5:
                return 0;
            default :
                puts("Wrong try again!!");
                continue;
        }
    }
}
