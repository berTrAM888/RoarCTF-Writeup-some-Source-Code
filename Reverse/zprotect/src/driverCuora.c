#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <asm/fcntl.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/dirent.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DEV 0

static int arr1[64] = {0x2e, 0x2e, 0x2e, 0x42, 0x47, 0x53, 0x55, 0x60, 0x60, 0x67, 0x66, 0x6d, 0x6c, 0x6e, 0x71, 0x73, 0x75};

static int arr2[64] = {0xa3, 0x86, 0xfe, 0x40, 0xe6, 0x7e, 0xb6, 0x7e, 0x3e, 0x48, 0x1d, 0x54, 0x30, 0x35, 0xf1, 0x82, 0x4c, 0xea, 0xba, 0xc0, 0x0e, 0xe3, 0x56, 0xf3, 0x36, 0x7f, 0x84, 0x8e, 0x43, 0x6d, 0x00, 0xf9, 0xcf, 0x7d};

static int arr3[64] = {0xc9, 0x9b, 0x0c, 0xf7, 0x8d, 0x14, 0x98, 0x14, 0x10, 0x77, 0x22, 0xb6, 0xf0, 0xa0, 0xdc, 0xdb, 0x37, 0x4d, 0x58, 0xef, 0x13, 0xbd, 0x96, 0xbc, 0x90, 0x04, 0xbb, 0x1b, 0xc7, 0x25, 0xf3, 0x5c, 0xfe, 0x24};

static unsigned char var1[64];

typedef struct
{
	int len;
	int content_num[64];
}content;

static struct task_struct* sleep_tsk0;
static struct task_struct* sleep_tsk1;
static struct task_struct* sleep_tsk2;
static struct task_struct* sleep_tsk3;
static struct task_struct* sleep_tsk4;
static struct task_struct* sleep_tsk5;
static struct task_struct* sleep_tsk6;
static struct task_struct* sleep_tsk7;
static struct task_struct* sleep_tsk8;
static struct task_struct* sleep_tsk9;
static struct task_struct* sleep_tskA;
static struct task_struct* sleep_tskB;
static struct task_struct* sleep_tskC;
static struct task_struct* sleep_tskD;
static struct task_struct* sleep_tskE;
static struct task_struct* sleep_tskF;
static struct task_struct* sleep_tsk10;
static struct task_struct* init_main_tsk0;
static struct task_struct* init_main_tsk1;

int var2[64];

int var3;

int var4;


void func1(unsigned char *arg1,unsigned char *arg2)
{
	int i;
	unsigned char tmp[4];
	tmp[0] = 0;
	for(i=0;i< 8;i++)
	{
		if(arg2[0]& (1 << i))
		{
            tmp[0]|=1<<(7-i);
		}
	}
	arg1[0] = tmp[0];

}

void func2(unsigned int *arg1,unsigned int *arg2)
{
    int i;
    unsigned int tmp[4];
    tmp[0] = 0;
    for(i=0;i< 32;i++)
    {
        if(arg2[0]& (1 << i))
        {
            tmp[0]|=1<<(15 - i);
        }
    }
    arg1[0] = tmp[0];
}

unsigned int func3(unsigned char *arg1, unsigned int arg2)
{
    int i;
    unsigned int wCRCin = 0xFFFFFFFF;
    unsigned int wCPoly = 0x04C11DB7;
    unsigned int wChar = 0;
    while (arg2--)
    {
        wChar = *(arg1++);
        func1((unsigned char *)&wChar,(unsigned char *)&wChar);
        wCRCin ^= (wChar << 24);
        for(i = 0;i < 8;i++)
        {
            if(wCRCin & 0x80000000)
                wCRCin = (wCRCin << 1) ^ wCPoly;
            else
                wCRCin = wCRCin << 1;
        }
    }
    func2(&wCRCin,&wCRCin);
    return (wCRCin ^ 0xFFFFFFFF) ;
}

int func4(char* arg1, char* arg2)
{
    static unsigned char Buff[64];
    struct file *filep;
    loff_t pos;
    memset(Buff, 0x00, sizeof(Buff));
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
    filep = filp_open(arg1, O_RDONLY, 0);
    if(IS_ERR(filep))
    {
        return -1;
    }
    pos = filep->f_pos;
    vfs_read(filep, Buff, sizeof(Buff), &pos);
    filep->f_pos = pos;
    set_fs(old_fs);
    filp_close(filep, 0);
	strcpy(arg2,Buff);
	return 0;
}

int func5(char* s)
{
	char buf[64];
	int i, j;
	for (i = 0, j = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\n')
			continue;
		buf[j++] = s[i];
	}
	buf[j] = '\0';
	strcpy(s, buf);
	return 0;
}

static int func6(void* arg)
{
    int var;
    var = arg - 0x0;
    msleep(var * 10);
    var2[var3] = var;
    var3++;
    return 0;
}

static int func7(void* data)
{
	int i;
	printk(KERN_INFO "[Cuora_init function INFO] The init mission is completed.");
	msleep(9000);
	printk(KERN_INFO "[Cuora_init function INFO] The init function is executed.");
	return 0;
}

static int func8(void* arg)
{
	char* temp_content = arg;
	var4 = func3(arg, 0x11);
	printk("[Cuora_init function INFO] Completion calculation.");
	return 0;
}

int func9(int* arg1, int arg2)
{
	char temp;
	int i,j;
	for(i=0; i<arg2; i++)
	{
		for(j=0; j<(arg2-i);j++)
		{
			if(arg1[j] > arg1[j+1])
			{
                temp = arg1[j];
				arg1[j] = arg1[j+1];
				arg1[j+1] = temp;
			}
		}
	}
	return 0;
}

int funcA(int* arg1, int arg2)
{
	int i;
	for(i=0;i<arg2;i++)
	{
		arg1[i] = arg1[i]^1;
	}
	return 0;
}


static int Cuora_init(void)
{
	printk(KERN_ALERT "driverCuora init\n");

	char* ivar1;
	content ivar2;
	ivar1 = "/home/ppprocce/ssooor";
	int ivar3;
	ivar3  = func4(ivar1, var1);
	if(ivar3 != 0)
	{
        return -1;
	}

	int i;
	ivar2.len = strlen(var1)-1;
	for(i=0;i<(strlen(var1)-1);i++)
	{
		ivar2.content_num[i] = var1[i] -0x00;
	}

	var3 = 0;
	sleep_tsk0 = kthread_run(func6, ivar2.content_num[0], "s0");
	if (IS_ERR(sleep_tsk0))
	{
		return -1;
	}

	sleep_tsk1 = kthread_run(func6, ivar2.content_num[1], "s1");
	if (IS_ERR(sleep_tsk1))
	{
		return -1;
	}

	sleep_tsk2 = kthread_run(func6, ivar2.content_num[2], "s2");
	if (IS_ERR(sleep_tsk2))
	{
		return -1;
	}

	sleep_tsk3 = kthread_run(func6, ivar2.content_num[3], "s3");
	if (IS_ERR(sleep_tsk3))
	{
		return -1;
	}

	sleep_tsk4 = kthread_run(func6, ivar2.content_num[4], "s4");
	if (IS_ERR(sleep_tsk4))
	{
		return -1;
	}

	sleep_tsk5 = kthread_run(func6, ivar2.content_num[5], "s5");
	if (IS_ERR(sleep_tsk5))
	{
		return -1;
	}

	sleep_tsk6 = kthread_run(func6, ivar2.content_num[6], "s6");
	if (IS_ERR(sleep_tsk6))
	{
		return -1;
	}

	sleep_tsk7 = kthread_run(func6, ivar2.content_num[7], "s7");
	if (IS_ERR(sleep_tsk7))
	{
		return -1;
	}

	sleep_tsk8 = kthread_run(func6, ivar2.content_num[8], "s8");
	if (IS_ERR(sleep_tsk8))
	{
		return -1;
	}

	sleep_tsk9 = kthread_run(func6, ivar2.content_num[9], "s9");
	if (IS_ERR(sleep_tsk9))
	{
		return -1;
	}

	sleep_tskA = kthread_run(func6, ivar2.content_num[10], "sA");
	if (IS_ERR(sleep_tskA))
	{
		return -1;
	}

	sleep_tskB = kthread_run(func6, ivar2.content_num[11], "sB");
	if (IS_ERR(sleep_tskB))
	{
		return -1;
	}
    
	sleep_tskC = kthread_run(func6, ivar2.content_num[12], "sC");
	if (IS_ERR(sleep_tskC))
	{
		return -1;
	}

	sleep_tskD = kthread_run(func6, ivar2.content_num[13], "sD");
	if (IS_ERR(sleep_tskD))
	{
		return -1;
	}

	sleep_tskE = kthread_run(func6, ivar2.content_num[14], "sE");
	if (IS_ERR(sleep_tskE))
	{
		return -1;
	}

	sleep_tskF = kthread_run(func6, ivar2.content_num[15], "sF");
	if (IS_ERR(sleep_tskF))
	{
		return -1;
	}
	

	sleep_tsk10 = kthread_run(func6, ivar2.content_num[16], "s10");
	if (IS_ERR(sleep_tsk10))
	{
		return -1;
	}

	init_main_tsk0 = kthread_run(func7, NULL, "m0");
	if (IS_ERR(init_main_tsk0))
	{
		return -1;
	}

	init_main_tsk1 = kthread_run(func8, var1, "m2");
	if (IS_ERR(init_main_tsk1))
    {
        return -1;
    }
    
	return 0;
}

static void Cuora_exit(void)
{
	int i;
	func9(var2, 0x10);
	funcA(var2, 0x11);

	for(i=0;i<0x11;i++)
	{
		if(var2[i] != arr1[i])
		{
			return -1;
		}
	}
	printk("[Cuora_exit function INFO] I didn't expect you to guess the path, just a little,go forward!");
	if(var4 != 0x5a9e037c)
	{
		return -1;
	}
	printk("[Cuora_exit function INFO] Keep moving forward!");

	func5(var1);
	unsigned char evar1[64];
    strcpy(evar1, var1);
    strcat(evar1, var1);
	
	unsigned char evar2[64];
	int evar3;
    evar3  = func4(var1, evar2);
    if(evar3 != 0)
    {
        return -1;
    }
	func5(evar2);

	unsigned char evar4[64];
	unsigned char evar5[64];

	for(i=0;i<strlen(evar2);i++)
	{
		evar4[i] = (evar2[i] ^ 0x55) + (evar1[i] ^ 0xAA);
		evar5[i] = (evar2[i] ^ 0xAA) + (evar1[i] ^ 0x55);
		evar4[i] = (evar4[i] / 4) | (evar5[i] * 64);
		evar5[i] = (evar5[i] * 4) | (evar5[i] / 64);
	}

	for(i=0;i<strlen(evar2);i++)
    {
        if(evar4[i] != arr2[i])
        {
                return -1;
        }
        if(evar5[i] != arr3[i])
        {
            return -1;
        }
    }
	printk(KERN_ALERT "Congratulations! driverCuora exit\n");
    return 0;
}


module_init(Cuora_init);
module_exit(Cuora_exit);
