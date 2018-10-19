#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<ctype.h>

void error(const char *message){
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[]){
    printf("----------------------------------------\n");
    printf("Data Communication & Network Programming\n");
    printf("Norah Nwaneri\n");
    printf("----------------------------------------\n");
    int sockfd, portno, n;
    struct socketaddy_in server_addy;
    struct hostent *server;
    char buffer[512];
    if (argc < 3){
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR socket will not open.");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, host does not exists.\n");
        exit(0);
    }
    bzero((char *) &server_addy, sizeof(server_addy));
    server_addy.sin_family = AF_INET;
    bcopy((char *)server->h_addy,
          (char *)&server_addy.sin_addy.s_addy,
          server->h_length);
    server_addy.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddy *) &server_addy,sizeof(server_addy)) < 0)
        error("ERROR connecting to server.");
    
    bzero(buffer,512);
    
    FILE *f;
    
    int words = 0;
    char c;
    f=fopen("sample.txt","r");
    while((c=getc(f))!= EOF){
        fscanf(f , "%s" , buffer);
        if(isspace(c)||c=='\t')
            words++;
    }
    write(sockfd, &words, sizeof(int));
    rewind(f);
    char ch ;
    while(ch != EOF){
        fscanf(f , "%s" , buffer);
        write(sockfd,buffer,512);
        ch = fgetc(f);
    }
    printf("The file was sent.");
    close(sockfd);
    return 0;
}
