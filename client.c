#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr,client_addr;
	char server_msg[2000],client_msg[2000];
	
   //clean buffers
	memset(server_msg,'\0',sizeof(server_msg));
	memset(client_msg,'\0',sizeof(client_msg));
	
    //create socket
	
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc<0){
	printf("socket not created");
	return -1;
	}
	
  //set ip and port
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2002);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
   //connect
   
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
	printf("unable to connect");
	return -1;
	
        }
        
   //get user input
   
   printf("enter the msg\n");
   fgets(client_msg,sizeof(client_msg),stdin);
   
   
   //sending msg to server
   
   if(send(socket_desc,client_msg,strlen(client_msg),0)<0)
    {
    	printf("sending unsuccesful");
    	return -1;		
    }
    
    //recieving msg
    
    if(recv(socket_desc,server_msg,sizeof(server_msg),0)<0)
    {
     printf(" cant recieve\n");
    return -1;
    }
    printf("server response:%s\n",server_msg);
   
    close(socket_desc);
    return 0;
    }

   

	
	
	
	
		


