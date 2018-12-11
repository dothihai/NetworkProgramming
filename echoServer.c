#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "transcript.c"
#define MAXLINE 40960 /*max text line length*/
#define SERV_PORT 40000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

#include "string-constant.h"


void clear(char * s){
  memset(s, 0, strlen(s));
}


int main (int argc, char **argv)
{
  char * response = (char*) calloc(0, MAXLINE * sizeof(Transcript));
  int responseLength;
 int listenfd, connfd, n;
 pid_t childpid;
 socklen_t clilen;
 char buf[MAXLINE];
 struct sockaddr_in cliaddr, servaddr;
	

readFileTranscript("transcript.txt");
readFileSubject("subject.txt");


 //creation of the socket
 listenfd = socket (AF_INET, SOCK_STREAM, 0);
 //read file contain time table

 //preparation of the socket address 
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);
	
 bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
 listen (listenfd, LISTENQ);
	
 printf("%s\n","Server running...waiting for connections.");
 readFileAccount("account.txt");
	
 for ( ; ; ) {
	
  clilen = sizeof(cliaddr);
  connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
  if(fork()==0){
  printf("%s\n","Received request...");
				
  while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
   printf("%s","String received from and resent to the client:");
   buf[n] = 0; // Get actual request
   puts(buf);
   char action = buf[0];
   char *message = buf+2;
   Account acc;
   switch(action){
    case SEND_USER_ACTION:{
      strcpy(acc.mssv,message);
      clear(response);
      sprintf(response, "%c_%s", LOGIN_RESPONSE_ACTION, OK);
      printf("%s\n",response );
      responseLength = strlen(response);
      send(connfd,response, responseLength,0);
    }
    break;
    case SEND_PASSWORD_ACTION:{
      strcpy(acc.password,message);
      int check = checkLogin(acc);
      clear(response);
      sprintf(response, "%c_%s", LOGIN_RESPONSE_ACTION, check?SUCCESS:FAILED);
      responseLength = strlen(response);
      send(connfd, response, responseLength, 0);
    }
    break;
    case SEND_USERNAME_ACTION:{
      clear(response);
      sprintf(response, "%c_%s", SEND_USERNAME_ACTION, accountLogin.name);
      responseLength = strlen(response);
      send(connfd, response, responseLength, 0);
    }
    break;
    case GET_SUBJECT:{
        if (strcmp(buf, GET_ALL_SUBJECT_MARK_TABLE) == 0)
        {
          clear(response);
          char temp[MAXLINE];
          sprintf(temp, "%c_", SEND_ALL);
          getTableSubjectOfStudent(acc.mssv,NULL, temp+2);
          printf("%s\n", "getAllSubject");
          send(connfd, temp, strlen(temp), 0);
        }else {
          char * id_subject = buf+5;
          clear(response);
          char temp[MAXLINE];
          sprintf(temp, "%c_", SEND_SUBJECT);
          getTableSubjectOfStudent(acc.mssv,id_subject, temp+2);
          printf("%s-%s\n", "get", id_subject);
          send(connfd, temp, strlen(temp), 0);
        }
    }
    break;
   }
  }
			
 if (n < 0) {
  perror("Read error"); 
  exit(1);
 }
 close(connfd);
	
 }
}
 //close listening socket
 close (listenfd); 
}