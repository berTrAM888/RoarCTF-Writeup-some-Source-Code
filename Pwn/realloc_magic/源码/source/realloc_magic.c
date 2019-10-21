#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* realloc_ptr;
unsigned int lock;

int get_int()
{
    char buf[0x10];
    read(0,buf,0xf);
    return atoi(buf);
}


void re()
{
    puts("Size?");
    unsigned int size = get_int();
    realloc_ptr = realloc(realloc_ptr,size);
    puts("Content?");
    read(0,realloc_ptr,size);
    puts("Done");
}

void fr()
{
    free(realloc_ptr);
    puts("Done");
}

void ba()
{
    if(lock)
        exit(-1);
    lock = 1;
    realloc_ptr = 0;
    puts("Done");
}

void menu()
{
    puts("====================");
    puts("1. realloc");
    puts("2. free");
    puts("3. exit");
    write(1,">> ",3);
}

void init()
{
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    alarm(60);
}


int main()
{
    init();
    while(1)
    {
        menu();
        int c = get_int();
        switch(c)
        {
            case 1:
                re();
                break;
            case 2:
                fr();
                break;
            case 666:
                ba();
                break;
            default:
                puts("invalid choice");
        }
    }
    return 0;
}
