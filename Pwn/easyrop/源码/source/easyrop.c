//gcc -O0 -Wl,-z,relro,-z,now   -fno-stack-protector  easyrop.c -o easyrop -no-pie
#include <signal.h> 
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdio.h>
#include <seccomp.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <linux/filter.h>
#include <linux/seccomp.h>

#define MAX_FILE 1000

    char path = '\0';

typedef struct item
{
    char d_name[256];
    char dir_name[256];
} file_item;

char chr[2];
size_t pathsize=0;
file_item files[MAX_FILE];

typedef struct item_info
{
    unsigned int i_node;
    char permission[16];
    short owner;
    short group;
    off_t size;
    time_t mod_time;
    nlink_t link_num;
    char name[256];
} info;

int is_detail;
int size_of_path;
int terminalWidth;

void set_secommp(){
    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
    struct sock_filter sfi[] ={
        {0x20,0x00,0x00,0x00000004},
        {0x15,0x00,0x05,0xc000003e},
        {0x20,0x00,0x00,0x00000000},
        {0x35,0x00,0x01,0x40000000},
        {0x15,0x00,0x02,0xffffffff},
        {0x15,0x01,0x00,0x0000003b},
        {0x06,0x00,0x00,0x7fff0000},
        {0x06,0x00,0x00,0x00000000}
    };
    struct sock_fprog sfp = {8, sfi};
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &sfp);
}

void handler()
{
    fprintf(stdout,"Time out!\n");
    fflush(stdout);
    exit(0);
}

void go()
{
    signal(SIGALRM, handler);
    alarm(0x3c);
}

const char *uid_to_name(short uid)
{
    struct passwd *pw_ptr;

    if ((pw_ptr = getpwuid(uid)) == NULL)
        return "Unknown";
    else
        return pw_ptr->pw_name;
}

const char *gid_to_name(short gid)
{
    struct group *grp_ptr;

    if ((grp_ptr = getgrgid(gid)) == NULL)
        return "Unknown";
    else
        return grp_ptr->gr_name;
}

int cmp(const void *a, const void *b)
{
    return strcasecmp((*(file_item *)a).d_name, (*(file_item *)b).d_name);
}

void getWidth()
{
    struct winsize wbuf;
    terminalWidth = 80;
    if (isatty(STDOUT_FILENO))
    {
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wbuf) == -1 || wbuf.ws_col == 0)
        {
            char *tp;
            if (tp = getenv("COLUMNS"))
                terminalWidth = atoi(tp);
        }
        else
            terminalWidth = wbuf.ws_col;
    }
    return;
}

void get_dir_detail(const char *dirname)
{
    DIR *dir;
    struct dirent *drt;
    int cur = 0;
    dir = opendir(dirname);
    if (dir == NULL)
    {
        perror("Read directroy Error.");
        return;
    }
    while ((drt = readdir(dir)) != NULL)
    {
        file_item *cur_node = files + cur;
        if ((strcmp(drt->d_name, ".") == 0) || (strcmp(drt->d_name, "..") == 0))
            continue;

        if (drt->d_name[0] == '.')
            continue;

        size_of_path++;
        cur++;
        if (cur >= MAX_FILE)
        {
            fwrite("Too many files!\n",1,17,stderr);
            exit(-1);
        }

        snprintf(cur_node->d_name,sizeof(drt->d_name),"%s",drt->d_name);
        snprintf(cur_node->dir_name,sizeof(dirname),"%s",dirname);
        strcat(cur_node->dir_name, drt->d_name);
    }
    closedir(dir);
}

void getPermission(mode_t st_mode, char *permission)
{
    unsigned int mask = 0700;
    static const char *perm[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    char type;
    if (S_ISREG(st_mode))
        type = '-';
    else if (S_ISDIR(st_mode))
        type = 'd';
    else if (S_ISCHR(st_mode))
        type = 'c';
    else if (S_ISLNK(st_mode))
        type = 'l';
    else
        type = '?';
    permission[0] = type;
    int i = 3;
    char *ptr = permission + 1;
    while (i > 0)
    {
        *ptr++ = perm[(st_mode & mask) >> (i - 1) * 3][0];
        *ptr++ = perm[(st_mode & mask) >> (i - 1) * 3][1];
        *ptr++ = perm[(st_mode & mask) >> (i - 1) * 3][2];
        i--;
        mask >>= 3;
    }
}

void print_file_info(info *file_info)
{
    unsigned fsize = file_info->size;
    char ftime[64];
    strcpy(ftime, ctime(&file_info->mod_time));
    ftime[strlen(ftime) - 1] = '\0';

    int i = 8;
    fprintf(stdout,"%10s ", file_info->permission);
    fprintf(stdout,"%3i", file_info->link_num);
    fprintf(stdout,"%14s", uid_to_name(file_info->owner));
    fprintf(stdout,"%14s ", gid_to_name(file_info->group));
    fprintf(stdout,"%8u ", fsize);
    fprintf(stdout,"%26s ", ftime);
    fprintf(stdout,"%s \n", file_info->name);
}

void search_file_info()
{

    struct stat file_stat;
    int cur = 0;
    info file_info;

    while (cur < size_of_path)
    {
        file_item *cur_node = files + cur;
        memset(file_info.permission, '\0', sizeof(file_info.permission));
        if (stat(cur_node->dir_name, &file_stat) == -1)
        {
            fprintf(stdout,"Can't get the information of the file.\n");
            continue;
        }
        getPermission(file_stat.st_mode, file_info.permission);
        file_info.owner = file_stat.st_uid;
        file_info.group = file_stat.st_gid;
        file_info.mod_time = file_stat.st_atime;
        file_info.size = file_stat.st_size;
        file_info.i_node = file_stat.st_ino;
        file_info.link_num = file_stat.st_nlink;
        strcpy(file_info.name, cur_node->d_name);
        print_file_info(&file_info);
        cur++;
    }
}

int init(char *pathname)
{
    char error[0x100];
    size_of_path = 0;
    struct stat file_stat;
    if (stat(pathname, &file_stat) == -1)
    {
        snprintf(error, sizeof(error), "%s", "Can't get the information of the given path.\n");
        fwrite(error,1,46,stdout);
        return 0;
    }
    if (S_ISREG(file_stat.st_mode))
    {
        size_of_path = 1;
        char *base_name = basename(pathname);
        strcpy(files[0].d_name, base_name);
        strcpy(files[0].dir_name, pathname);
        return 1;
    }
    if (S_ISDIR(file_stat.st_mode))
    {
        if (pathname[strlen(pathname) - 1] != '/')
        {
            char *ptr = pathname + strlen(pathname);
            *ptr++ = '/';
            *ptr = 0;
        }
        get_dir_detail(pathname);
        return 1;
    }
}

void print_simple()
{
    int max_len = 0;
    int num_in_row = 0;
    int num_in_col = 0;
    getWidth();
    int i = 1;
    max_len = strlen(files[0].d_name);
    while (i < size_of_path)
    {
        int cur_len = strlen(files[i].d_name);
        max_len = max_len > cur_len ? max_len : cur_len;
        i++;
    }
    max_len += 2;
    num_in_row = terminalWidth / max_len;
    if (size_of_path % num_in_row == 0)
        num_in_col = size_of_path / num_in_row;
    else
        num_in_col = size_of_path / num_in_row + 1;
    i = 0;
    while (i < num_in_col)
    {
        int j;
        for (j = 0; j < num_in_row; ++j)
        {
            file_item *cur = files + i + j * num_in_col;
            fprintf(stdout,"%-*s", max_len, cur->d_name);
        }
        fprintf(stdout,"\n");
        i++;
    }
}

void banner()
{
    puts("  ,ggg,     ,gggg,gg    ,g,     gg     gg   ,gggggg,    ,ggggg,   gg,gggg,   ");
    puts(" i8\" \"8i   dP\"  \"Y8I   ,8'8,    I8     8I   dP\"\"\"\"8I   dP\"  \"Y8gggI8P\"  \"Yb  ");
    puts(" I8, ,8I  i8'    ,8I  ,8'  Yb   I8,   ,8I  ,8'    8I  i8'    ,8I  I8'    ,8i ");
    puts(" `YbadP' ,d8,   ,d8b,,8'_   8) ,d8b, ,d8I ,dP     Y8,,d8,   ,d8' ,I8 _  ,d8' ");
    puts("888P\"Y888P\"Y8888P\"`Y8P' \"YY8P8PP\"\"Y88P\"8888P      `Y8P\"Y8888P\"   PI8 YY88888P");
    puts("                                     ,d8I'                        I8         ");
    puts("                                   ,dP'8I                         I8         ");
    puts("                                  ,8\"  8I                         I8         ");
    puts("                                  I8   8I                         I8         ");
    puts("                                  `8, ,8I                         I8         ");
    puts("                                   `Y8P\"                          I8         ");
}

int main(int argc, char *argv[])
{
    char byte;
    is_detail = 0;
    char initpath[0x400];
    size_t pos;
    size_t cnt;
    go();
    banner();
    fwrite(">> ", 1, 3, stdout);
    fflush(stdout);
    cnt = 0;
    while (!feof(stdin))
    {
        byte = fgetc(stdin);
        if (byte == '\n')
        {
            break;
        }
        pos = cnt++;
        initpath[pos] = byte;
    }
    initpath[cnt] = '\0';
    if (init(initpath))
    {
        qsort(files, size_of_path, sizeof(files[0]), cmp);
        search_file_info();
    }
    else
    {
        fflush(stdout);
        set_secommp();
        return 0;
    }
}