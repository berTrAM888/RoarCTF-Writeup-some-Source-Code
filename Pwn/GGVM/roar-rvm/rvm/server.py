#!/usr/bin/python
from subprocess import Popen,STDOUT,PIPE
from binascii import hexlify,unhexlify
from os import urandom,remove
import sys

def check(sss):
	try:
		if(sss.find('sh')!=-1 or sss.find('$')!=-1):
			raise Exception("INVALID SUBSTR");
		return unhexlify(sss)
	except Exception,e:
		print(str(Exception)+str(e))
		return "WRONG"
while(True):
	print("GIVE ME YOUR MACHINE CODE IN HEX SUCH AS 61616161")
	get = raw_input().strip()
	ss = check(get)
	if(ss=="WRONG"):
		print("INVALID CODE WITH `sh`")
		pass
	else:
		try:
			filename = hexlify(urandom(8))
			filename = "./tmp/"+filename
			f = open(filename,"wb")
			f.write(ss)
			f.close()
			argv = ["/home/rvm/rvm",filename]
			#print(argv)
			io = Popen(args = argv,shell=False,stdin=PIPE,stdout=PIPE)
			print io.stdout.readline()
			print io.stdout.readline()

			io.stdin.flush()
			io.stdout.flush()
			sys.stdin.flush()
			sys.stdout.flush()
			exit()
		except Exception,e:
			print(str(Exception)+str(e))
			remove(filename)
			io.terminate()
			exit()



