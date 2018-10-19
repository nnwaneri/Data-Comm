#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


int main(int argc, char *argv[]){
    rintf("----------------------------------------\n");
    printf("Data Communication & Network Programming\n");
    printf("Norah Nwaneri\n");
    printf("----------------------------------------\n");
    int socklen_t sid,clen;
    char buffer[1024];
    struct sockaddr_in saddr,caddr;int n;if(argc<2){
	fprintf(stderr,"ERROR: port is not given \n");
	exit(1);
    }
    sid=socket(AF_INET,SOCK_DGRAM,0);
    if(sid<0) 
	perror("socket_create");
    bzero((char*)&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(atoi(argv[1]));
    saddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sid,(struct    sockaddr *)&saddr,sizeof(saddr))<0)
	perror("socket_bind");
    clen=sizeof(caddr);
    bzero(buffer,1024);
    n=recvfrom(sid,buffer,1023,0,(struct sockaddr*)&caddr,&clen);
    if(n<0) 
	perror("receive");
    printf("The msg is %s", buffer);
    close(sid);
    return 0;
}
