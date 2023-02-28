#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>      // for gethostname() 
#include <arpa/inet.h>   // for IP address structures and functions 

int main(){
    int	sock, msgsock;  // Sockets are integer file descriptors on Linux 
    struct	sockaddr_in	name, caller;
    char	buf[4096]; //as used in my 2048 lab
    int	size, length, checkFail, k;
    size = sizeof(buf) - 1;  /* Default size */
    

    /* Create the listen socket. This is a TCP socket, so use SOCK_STREAM 
     * Exit if the socket cannot be created */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        perror("receiver: socket() failed. ");
        return (-1);
    }
    
    /* Bind the socket to an IP address and port. We will use the IP address
     * INADDR_ANY, which tells the system to assign the IP address, and the
     * port number 0, which tells the system to assign a random port number.
     *
     * First we have to set the fields in the sockaddr_in object "name" and then
     * we can call bind(). Again, exit if bind() fails. */
    name.sin_family = AF_INET;         // TCP/IP family 
    //name.sin_addr.s_addr = INADDR_ANY; /* INADDR_ANY = assigned by system */
    name.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // should give me 127.0.0.1 but might need inet_addr("127.0. 0.1")
    name.sin_port = htons(0);	         // 0 = assigned by system 
    checkFail = bind(sock,(struct sockaddr *)&name,sizeof name);
    if (checkFail < 0)
    {
        perror("receiver: bind() failed. ");
        return (-1);
    }

    /* In order to use vcsend to send data to this program, we need to know
     * what port number the system just assigned this program. So this segment
     * calls getsockname() to update the sockaddr_in object "name" with the
     * system assigned values and then print that info to the screen. */
    length = sizeof name;
    checkFail = getsockname(sock, (struct sockaddr *)&name, (socklen_t *)&length);
    if (checkFail < 0)
    {
        perror("receiver: getsockname() failed. ");
        return (-1);
    }

    sleep(1);
    printf("\nreceiver: process id: %d ", (int)getpid());
    printf("\nreceiver: IP address: %d.%d.%d.%d",
            (ntohl(name.sin_addr.s_addr) & 0xff000000) >> 24,
            (ntohl(name.sin_addr.s_addr) & 0x00ff0000) >> 16,
            (ntohl(name.sin_addr.s_addr) & 0x0000ff00) >>  8,
            (ntohl(name.sin_addr.s_addr) & 0x000000ff));
    printf("\nreceiver: port number: %hu", ntohs(name.sin_port));
    printf("\n");
    fflush(stdout);

    listen(sock,5);		/* up to 5 clients can connect. only 1st is accepted */
    k = sizeof caller;
    while(1)
    {
        msgsock = accept(sock, (struct sockaddr *)&caller, (socklen_t *)&k);

        /* We only reach this point when there is an error or a client. We can 
        * check the value of msgsock (the data socket) to see which has happened */

        int running = 0;
        if (msgsock == -1)
        {
            printf("receiver: accept() failed. ");
        }
        checkFail = recv(msgsock, buf, size, 0);
        if(checkFail < 0){
            printf("error ocurred");
        }
        printf("%s",buf);
        //msg to send
        char response[255];
        
        //char responde200[] = "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: 1354\n\n<html>\n<body>\n<h1>Happy New Millennium!</h1>\n(more file contents)\n . \n . \n .\n</body>\n</html>";
        char body[] = "<html>\n<body>\n<h1>Happy New Millennium!</h1>\n(more file contents)\n . \n . \n .\n</body>\n</html>";
        int bodysize = sizeof(body);
        char header[] = "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: ";
        snprintf(response,sizeof(response),"%s%d\n\n%s",header,bodysize,body);
        //send
        //send(msgsock, response, sizeof(body)+sizeof(header)+1,0);
        char okresponse[] = "HTTP/1.0 200 OK\n\n";
        send(msgsock,okresponse,sizeof(okresponse)+1,0);
        close(msgsock);
    }  
    return 0;
}
