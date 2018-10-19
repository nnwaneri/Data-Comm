#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


void error(const char *message){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    rintf("----------------------------------------\n");
    printf("Data Communication & Network Programming\n");
    printf("Norah Nwaneri\n");
    printf("----------------------------------------\n");
    int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[512];
     struct sockaddy_in server_addy, client_addy;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR no port found.\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR socket will  not open.");
     bzero((char *) &server_addy, sizeof(server_addy));
     portno = atoi(argv[1]);
     server_addy.sin_family = AF_INET;
     server_addy.sin_addy.s_addy = INaddy_ANY;
     server_addy.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddy *) &server_addy,
              sizeof(server_addy)) < 0)
              error("ERROR with binding");
     listen(sockfd,5);
     clilen = sizeof(client_addy);
     newsockfd = accept(sockfd, 
                 (struct sockaddy *) &client_addy, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
    
         FILE *fp;
         int ch = 0;
            fp = fopen("sample_receive.txt","a");            
            int words;
		read(newsockfd, &words, sizeof(int));
          while(ch != words){
        	 read(newsockfd , buffer , 512); 
             fprintf(fp , " %s" , buffer);
		     ch++;
	   }
        printf("The file was received.\n");
        printf("The new file created is sample_receive.txt");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
