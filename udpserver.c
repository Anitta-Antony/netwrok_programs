#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{

int client_sock,socket_desc,client_size,flag=1;
struct sockaddr_in server_addr,client_addr;
char server_msg[2000],client_msg[2000];
int n_msg[10];

socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(socket_desc<0)
{
printf("socketnotcreated\n");
return -1;

}


server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(2004);
server_addr.sin_addr.s_addr=INADDR_ANY;

if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
{
printf("cant bind\n");
return -1;
}
printf("done with binding\n");
client_size=sizeof(client_addr);
while(flag==1)
{
memset(client_msg,'\0',sizeof(client_msg));
memset(server_msg,'\0',sizeof(server_msg));


if(recvfrom(socket_desc,client_msg,sizeof(client_msg),0,(struct sockaddr*)&client_addr,&client_size)<0)
{
printf("cant recieve\n");
return -1;
}
printf("client msg=%s\n",client_msg);
if(strcmp(client_msg,"exit\n")==0)
{
flag=0;
break;
}



if(recvfrom(socket_desc,&n_msg,sizeof(n_msg),0,(struct sockaddr*)&client_addr,&client_size)<0){
printf("cant recieve\n");
return -1;
}

printf("n msg=%d %d\n",n_msg[1],n_msg[2]);


printf("enter msg\n");
fgets(server_msg,sizeof(server_msg),stdin);

if(sendto(socket_desc,server_msg,sizeof(server_msg),0,(struct sockaddr*)&client_addr,client_size)<0){
printf("cant send\n");

return -1;
}
if(strcmp(server_msg,"exit\n")==0)
{
flag=0;
break;
}

}
close(socket_desc);
return 0;




}
