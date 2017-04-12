


//LIBRARIES USED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>

void negiCheck(char *str);

//FUNCTION TO PARSE FTP & HTTP 


int my_http(int fd)
{
static char* not_found =
  "HTTP/1.1 404 Not Found\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>404 Not Found</h1>\n"
  " </body>\n"
  "</html>\n";
static char* bad_request =
  "HTTP/1.1 400 Bad Request\n"
  "Content-type: text/html\n"
  "\n"
  "<html>\n"
  " <body>\n"
  "  <h1>Bad Request</h1>\n"
  "  <p>This server did not understand your request.</p>\n"
  " </body>\n"
  "</html>\n";

int BUFSIZE=65535,i,urlport,urlport_new,tick,tick1,sockfd1,connectfd,mycheck,sockfd2,connectfd1;
char buffer[BUFSIZE],request[BUFSIZE],response[BUFSIZE],splitline1[BUFSIZE],splitline2[BUFSIZE],splitline2_copy[BUFSIZE], splitline3[BUFSIZE];
char message[1024];
char *hostname;
char hostname1[17];
char *getport;
char fsize[BUFSIZE];
char command[BUFSIZE];
int ip[4];
int p1,p2;
struct hostent* r_server;
struct hostent* r_server1;
struct sockaddr_in remote_addr;
struct sockaddr_in remote_addr1;
memset(&splitline1[0],0,sizeof(splitline1));
memset(&splitline2[0],0,sizeof(splitline2));
memset(&splitline2_copy[0],0,sizeof(splitline2_copy));
memset(&splitline3[0],0,sizeof(splitline3));
bzero((char*)message,1024);
bzero((int*)&ip,sizeof(ip));
bzero((char*)&remote_addr,sizeof(remote_addr));
bzero((char*)request,BUFSIZE);
bzero((char*)response,BUFSIZE);
bzero((char*)buffer,BUFSIZE);
recv(fd,request,BUFSIZE,0);

//BREAKING THE REQUEST FOR FURTHER PARSING
sscanf(request,"%s %s %s",splitline1,splitline2,splitline3);
printf("%s %s %s\n",splitline1,splitline2,splitline3);


//FTP REQUESTS HANDLED HERE

if(((strncmp(splitline1,"GET",3)==0)) &&((strncmp(splitline3,"HTTP/1.1",8)==0)||(strncmp(splitline3,"HTTP/1.0",8)==0))
&& (strncmp(splitline2,"ftp://",6)==0))
{
  {
        strcpy(splitline2_copy,splitline2);
        char* gethttp=strstr(splitline2,"//")+2;
        char* gethttp1=strstr(splitline2_copy,"//")+2;
        char* getpath=strstr(gethttp1,"/");
	char ftppath[BUFSIZE];
	if(getpath==NULL)
    	{
    	getpath="/";
    	}
	sprintf(ftppath,getpath);

//CHECK IF FILE or DIR

void negiCheck(char *str)
{
	if((str && *str && str[strlen(str) - 1] != '/'))
	{
	char* file=getpath;
	char* myStr=ftppath;
	char* count= &myStr[strlen(myStr)];
	bzero((char*)fsize,BUFSIZE);
	while(count>myStr && *count != '/')
	{
	count--;
	if (*count== '/'){
        *count= '\0';
	break;}
	}
	sprintf(fsize,"SIZE %s\r\n",file);
	sprintf(command,"RETR %s\r\n",file);
	}
	else{
	sprintf(ftppath,getpath);
	sprintf(command,"LIST %s\r\n",ftppath);
	}
}

	negiCheck(getpath);
	printf("%s\n",ftppath);


    if((getport=strstr(gethttp,":")) !=NULL)    //PARSING FOR PORT IN URL STARTS HERE
            {
                hostname=strtok(gethttp,"/");
                for(i=0;i<strlen(hostname);i++)
                    {
                        if(hostname[i]==':')
             {
                         mycheck=1;
             break;
             }
                    }
                if(mycheck==1)
                    {
                        hostname=strtok(hostname,"/");
                           hostname=strtok(gethttp,":");
            getport=strstr(gethttp1,":");
            getport=strtok(getport,":");
            getport=strtok(getport,"/");
            urlport=atoi(getport);
                    }
                else
                    {
                        hostname=strtok(gethttp,":");
                        urlport=21;
                    }
                printf("target host:port -> %s:%d\n",hostname,urlport);
            }
else  // IF URL DOESN'T HAVE PORT IN IT
    {
        urlport=21;
        hostname=strtok(gethttp,"/");
        printf("target host:port -> %s:%d\n",hostname,urlport);
    }

//BAD URL CHECK
if ((gethostbyname(hostname))!=NULL)
{
r_server=gethostbyname(hostname);
}
else
{
snprintf(message,sizeof(message),not_found);
send(fd,message,sizeof(message),0); // for HTTP
close(fd);
return -1;
}
bzero((char*)&remote_addr,sizeof(remote_addr));

//SETTING UP REMOTE ADDR
remote_addr.sin_port=htons(urlport);
remote_addr.sin_family=AF_INET;
bcopy((char*)r_server->h_addr,(char*)&remote_addr.sin_addr.s_addr,r_server->h_length);
//INITIALIZING SOCKET
sockfd1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(connectfd=connect(sockfd1,(struct sockaddr*)&remote_addr,sizeof(struct sockaddr))<0)
{
	    snprintf(message,sizeof(message),not_found);
            send(fd,message,sizeof(message),0);
	    return -1;
}
bzero((char*)response,BUFSIZE);
while(1)
        {
         recv(sockfd1,response,BUFSIZE,0);
         if (strstr(response, "220 "))
         break;
        }
printf("%s\n",strstr(response, "220 "));
char *user="USER anonymous\r\n";
char *pass="PASS vn94@njit.edu\r\n";
char *mode="PASV\r\n";
char *type="TYPE A\r\n";
char path[BUFSIZE];

//COMMUNICATING WITH FTP SERVER

bzero((char*)path,BUFSIZE);
sprintf(path,"CWD %s\r\n",ftppath);
char *quit="QUIT\r\n";
    send(sockfd1,user,strlen(user),0);
    while(1)
    {
     recv(sockfd1,response,BUFSIZE,0);
     //printf("%s\n",response);
     if (strstr(response, "331 "))
     break;
    }
printf("%s\n",strstr(response, "331 "));
    send(sockfd1,pass,strlen(pass),0);
    while(1)
        {
         recv(sockfd1,response,BUFSIZE,0);
      //   printf("%s\n",response);
	 if (strstr(response, "230"))
         break;
        }
printf("%s\n",strstr(response, "230"));
        send(sockfd1,mode,strlen(mode),0);
    while(1)
        {
         recv(sockfd1,response,BUFSIZE,0);
     //    printf("%s\n",response);
	 if (strstr(response, "227 "))
         break;
        }
        //HANDLING PASSIVE MODE
	char* temp;
	temp=(strstr(response, "227 "));
	sscanf(temp, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)", &ip[0],&ip[1],&ip[2],&ip[3],&p1,&p2);
            urlport_new= (p1 * 256) + p2;
            sprintf(hostname1,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
            printf("creating data socket on => %s:%d\n",hostname1,urlport_new);
	    r_server1=gethostbyname(hostname1);
            bzero((char*)&remote_addr1,sizeof(remote_addr1));

//SETTING UP REMOTE ADDR
remote_addr1.sin_port=htons(urlport_new);
remote_addr1.sin_family=AF_INET;
bcopy((char*)r_server1->h_addr,(char*)&remote_addr1.sin_addr.s_addr,r_server1->h_length);
//CREATING DATA CONNECTION
sockfd2=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(connectfd1=connect(sockfd2,(struct sockaddr*)&remote_addr1,sizeof(struct sockaddr))<0)
{
            snprintf(message,sizeof(message),not_found);
	    send(fd,message,sizeof(message),0);
	    return -1;
}
else
printf("data socket created successfully on %d\n",urlport_new);
send(sockfd1,command,strlen(command),0);
while (1){
         recv(sockfd1,response,BUFSIZE,0);
     //    printf("%s\n",response);
	 if (strstr(response, "150 "))
         break;
	 else if(strstr(response, "550 "))
	 {
	 snprintf (message, sizeof (message), not_found);
	 send(fd,message, strlen (message),0);
	 send(sockfd1,quit,strlen(quit),0);
	 return -1;
	 }
        }
printf("%s\n",strstr(response, "150 "));
do{
            bzero((char*)buffer,BUFSIZE);
            tick1=recv(sockfd2,buffer,BUFSIZE,0);//RECEIVING RESPONSE FROM REMOTE SERVER
	    if (tick1 == 0)
            break;
            else
            {
            send(fd, "HTTP/1.1 200 OK\n\n", 17, 0);  //SENDING BACK to BROWSER
	        send(fd,buffer,tick1,0);
            }
 }while (1);
bzero((char*)response,BUFSIZE);
 send(sockfd1,quit,strlen(quit),0);
 while (1)
 	{
         recv(sockfd1,response,BUFSIZE,0);
	 if (strstr(response, "221"))
         break;
        }
printf("%s\n",strstr(response, "221"));
}
close(sockfd1);
close(sockfd2);
}


//HTTP REQUESTS HANDLED HERE

else if (((strncmp(splitline1,"GET",3)==0))||((strncmp(splitline1,"POST",4))==0)
&&((strncmp(splitline3,"HTTP/1.1",8)==0)||(strncmp(splitline3,"HTTP/1.0",8)==0))
&&(strncmp(splitline2,"http://",7)==0))
    {
        strcpy(splitline2_copy,splitline2);
        char* gethttp=strstr(splitline2,"//")+2;
        char* gethttp1=strstr(splitline2_copy,"//")+2;
        char* getpath=strstr(gethttp1,"/");
    if(getpath==NULL)
    {
    getpath="/";
    }
     if((getport=strstr(gethttp,":")) !=NULL) 
            {
                hostname=strtok(gethttp,"/");
                for(i=0;i<strlen(hostname);i++)
                    {
                        if(hostname[i]==':')
             {
                         mycheck=1;
             break;
             }
                    }
                if(mycheck==1)
                    {
                        hostname=strtok(hostname,"/");
                           hostname=strtok(gethttp,":");
            getport=strstr(gethttp1,":");
            getport=strtok(getport,":");
            getport=strtok(getport,"/");
            urlport=atoi(getport);
                    }
                else
                    {
                        hostname=strtok(gethttp,":");
                        urlport=80;
                    }
                printf("target host:port -> %s:%d\n",hostname,urlport);
            }
else  // IF URL DOESN'T HAVE PORT IN IT
    {
        urlport=80;
        hostname=strtok(gethttp,"/");
        printf("target host:port -> %s:%d\n",hostname,urlport);
    }

//BAD URL CHECK
if ((gethostbyname(hostname))!=NULL)
r_server=gethostbyname(hostname);
else
{
snprintf (message, sizeof (message), not_found);
send(fd,message,sizeof(message),0);
close(fd);
return -1;
}

//IF URL EXISTS WE MOVE AHEAD TO OPENING SOCKET FOR REMOTE CONNECTION
//CLEARING REMOTE ADDR
bzero((char*)&remote_addr,sizeof(remote_addr));
//SETTING UP REMOTE ADDR
remote_addr.sin_port=htons(urlport);
remote_addr.sin_family=AF_INET;
bcopy((char*)r_server->h_addr,(char*)&remote_addr.sin_addr.s_addr,r_server->h_length);
//INITIALIZING SOCKET
sockfd1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(connectfd=connect(sockfd1,(struct sockaddr*)&remote_addr,sizeof(struct sockaddr))<0)
{
            snprintf (message, sizeof (message), not_found);
	    send(fd,message,sizeof(message),0);
	    return -1;
}
bzero((char*)request,BUFSIZE);
//SENDING REQUEST TO REMOTE SERVER HERE
sprintf(request,"%s %s %s\r\nHost: %s\r\nConnection: close\r\n\r\n",splitline1,getpath,splitline3,hostname);
printf("requesting %s for %s",hostname,request);
tick=send(sockfd1,request,strlen(request),0);
    if(tick<0) //ERROR CHECKING
        perror("Error while sending request\n");
    else
        {
            do
                {
                    bzero((char*)response,BUFSIZE);
                    tick1=recv(sockfd1,response,BUFSIZE,0);//RECEIVING RESPONSE FROM REMOTE SERVER
                    if(!(tick1<=0))
                        send(fd,response,tick1,0); //SENDING RESPONSE BACK TO BROWSER
                    }while(tick1>0);  //WHILE LOOP HANDLES SPLIT SEND REQUESTS
       }
}
else  //IF REQUEST IS NOT HTTP
    {
    snprintf(message, sizeof (message), bad_request);
    //printf("%s\n",message);
    send(fd,message,sizeof(message),0);
    close(fd);
    return -1;
    }
close(sockfd1);//CLOSING OPEN SOCKETS FOR THIS FUNCTION
}

//------- MAIN STARTS HERE ----------//

int main(int argc,char* argv[])
{
int counter,acceptfd;
unsigned int clength;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
if(argc<2)
{
printf("usage: ./proxy <portno> |recommended port:5678|\n");
exit(1);
}
//CLEARING SERVER ADDRESS
bzero((char*) &server_addr, sizeof(server_addr));

//SETTING UP SERVER ADDRESS
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(atoi(argv[1]));
server_addr.sin_addr.s_addr=INADDR_ANY;

//SIGPIPE SIGNAL HANDLING(TO PREVENT WHOLE SERVER FROM TERMINATING
//IN CASE OF ANY UNEXPECTED WRITE TO A CLOSED PIPE)
signal(SIGPIPE, SIG_IGN);

//SERVER SOCKET INITIALIZE
int sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(sockfd<0)
    {
    perror("Socket initialization problem\n");
    exit(1);
    }
//REUSING THE SOCKET ADDRESS
int negi = 1;
if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &negi, sizeof(int)) < 0)
    {
    perror("setsockopt error\n");
    exit(1);
    }
//BIND
int bindfd=bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
if (bindfd<0)
    {
    perror("Binding error\n");
    exit(1);
    }
//SOCKET IS LISTENING FOR CLIENT CONNECTIONS
int listenfd=listen(sockfd,10);
if (listenfd<0)
    {
    perror("Listen Error\n");
    exit(1);
    }
printf("listening for incoming requests now...\n");

//INFINITE LOOP: FOR ACCEPTING NEW CONNECTIONS
while(1)
   {
    clength=sizeof(client_addr);
    bzero((char*) &client_addr, sizeof(client_addr));
    acceptfd=accept(sockfd, (struct sockaddr*) &client_addr, &clength); // ACCEPT CONNECTION
    if(acceptfd<0)
    {
    perror("ERROR while accepting");
    }
   printf("received request...\n");
//CALLING HTTP PARSE FUNCTION
my_http(acceptfd);
close(acceptfd); // CLOSING ACCEPT SOCKET
    }
//  close(acceptfd);
close(sockfd);
}
// -------- END OF CODE ------//
