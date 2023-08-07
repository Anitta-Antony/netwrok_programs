#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int prime(int num)
{
	int d=0;int result=0;
	while(num!=0)
	{
	d=num%10;
	d=d*d*d;
	
	num=num/10;
	result=result+d;
	}
	return result;	

}

int main(void)
{
	int socket_desc,client_sock,client_size;
	struct sockaddr_in client_addr,server_addr;
	int server_msg,client_msg;
	
  socket_desc=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(socket_desc<0)
  {
  printf("couldnt create socket\n");
  return -1;
  }
  
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(2002);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
  {
  	printf("couldnt bind to the port\n");
  	return -1;
  }
  
  if(listen(socket_desc,1)<0)
  {
  	printf("error while listening\n");
  	return -1;
  }
  printf("listening\n");
  
  client_size=sizeof(client_addr);
  
  client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
  if(client_sock<0)
  {
  printf("error while coonectong\n");
  	return -1;
  }
  printf("connected at ip and port %s and %i\n",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port));
  
  while(1){
  if(recv(client_sock,&client_msg,sizeof(client_msg),0)<0){
  printf("error in recieving\n");
  	return -1;
  }
  server_msg=prime(client_msg);
  
  printf("msg from client is %d\n",client_msg);
  if(send(client_sock,&server_msg,sizeof(server_msg),0)<0)
  {
  printf("error in sending\n");
  	return -1;
  }
  if(client_msg==0)
  {
  return 0;
  }
  }
  
  close(client_sock);
	close(socket_desc);
	return 0;
  
  
	
	
}


