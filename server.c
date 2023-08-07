#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
	int socket_desc, client_sock, client_size;
	struct sockaddr_in server_addr, client_addr;
	char server_msg[2000], client_msg[2000];


	// Clean buffers:

	memset(server_msg, '\0', sizeof(server_msg));
	memset(client_msg, '\0', sizeof(client_msg));


	// Create socket:

	socket_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_desc < 0){
		printf("Error while creating socket\n");
		return -1;
	}
	printf("Socket created successfully\n");


	// Set port and IP:
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2002);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//bind port and ip
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("couldnt bind to the port");
		return -1;
	}
	
	
	//listening for incoming connections
	if(listen(socket_desc,1)<0){
	printf("error while listening");
	return -1;
	}printf("listeninf\n");
	
	//accepting a coonection
	client_size=sizeof(client_addr);
	client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
	if(client_sock<0){
	printf("cant accept");
	return -1;
	}
	 printf("client connected at %s and port %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	 
	 
	 //rec
         if(recv(client_sock,client_msg,sizeof(client_msg),0)<0){
         printf("couldnt recieve\n");
    		return -1;
    }
    printf("client msg:%s\n",client_msg);
    
    char rev[20];
    int i;
    strcpy(rev,client_msg);
    int l=strlen(client_msg)-1;
    printf("%d",l);
    char tmp;
    for(i=0;i<l/2;i++)
    {
	tmp=client_msg[i];
	client_msg[i]=client_msg[l-i-1];
	client_msg[l-i-1]=tmp;
   
 
    }
    
    
   
   
    if(strcmp(rev,client_msg)==0)
    {
  
    strcpy(server_msg, "is a palindrome.");
    }
    else
    {
    strcpy(server_msg, "not a palindrome.");
    }
    
    
    
    
    	 
	

	// Respond to client:
	
	if (send(client_sock,server_msg,strlen(server_msg),0) < 0){
	printf("Can't send\n");
	return -1;
	}

	// Closing the socket:
	close(client_sock);
	close(socket_desc);
	return 0;
}


