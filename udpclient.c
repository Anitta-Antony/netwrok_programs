#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(void){

int socket_desc,flag=1;
struct sockaddr_in server_addr,client_addr;
char server_msg[2000],client_msg[2000];
int n_msg[10];
socklen_t server_addr_len;


socket_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
if(socket_desc<0){
printf("socketnotcreated\n");
return -1;

}

server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(2004);
server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

while(flag==1)
{
memset(client_msg,'\0',sizeof(client_msg));
memset(server_msg,'\0',sizeof(server_msg));


printf("enter msg\n");
fgets(client_msg,sizeof(client_msg),stdin);

if(sendto(socket_desc,client_msg,sizeof(client_msg),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
printf("cant send\n");

return -1;
}
if(strcmp(server_msg,"exit\n")==0)
{
flag=0;
break;
}
printf("enter array\n");
for(int i=0;i<5;i++){
scanf("%d",&n_msg[i]);}

if(sendto(socket_desc,&n_msg,sizeof(n_msg),0,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
printf("cant send\n");

return -1;
}


if(recvfrom(socket_desc,server_msg,sizeof(server_msg),0,(struct sockaddr*)&server_addr,&server_addr_len)<0){
printf("cant recieve\n");
return -1;
}
if(strcmp(server_msg,"exit\n")==0)
{
flag=0;
break;
}
printf("server msg=%s\n",server_msg);
}

close(socket_desc);
return 0;
}
