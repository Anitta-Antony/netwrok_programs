#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(void)
{
	int socket_desc;
	struct sockaddr_in client_addr,server_addr;
	int server_msg,client_msg;
	
  socket_desc=socket(AF_INET,SOCK_STREAM,0);
  if(socket_desc<0)
  {
  printf("couldnt create socket\n");
  return -1;
  }
  
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(2002);
  server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  
 if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
  {
  printf("error while coonectong\n");
  	return -1;
  }
  while(1){
  
 scanf("%d",&client_msg);
  
  if(send(socket_desc,&client_msg,sizeof(client_msg),0)<0){
  printf("error in sending\n");
  	return -1;
  }
  if(recv(socket_desc,&server_msg,sizeof(server_msg),0)<0){
  printf("error in recieving\n");
  	return -1;
  }
  printf("msg from server is %d\n",server_msg);
  }
 close(socket_desc);
return 0;
}
