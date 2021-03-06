// Server side C/C++ program to demonstrate Socket programming
// This is only set to work with IPV4 and TCP
// Build and run. go to browser and type localhost:8080 to see message
// or use  curl -X GET "localhost:8080"
// review socket.h for function usage


#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[]){
    
    //declare address struct and option variable
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;
    
       
    // Creating socket file descriptor
    /*int sockfd = socket(domain, type, protocol)
    
    domain:
        AF_LOCAL - also known as AF_UNIX used to same host operations
        AF_INET - used with IPV4
            ---in this case we can use LOCALHOST:PORT#
    type:
        SOCK_STREAM - TCP
        SOCK_DGRAM - UDP

    
    */
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
       
    // Set socket options.
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt));

    //here we set the values of sockaddr_in to declare the PORT
    //later we have to cast it to sockaddr for the function use
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // prepare for connections on socket
    listen(server_fd, 3);

    // wait for connection and open a new socket when it arrives
    int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);

    //send hello world message
    //sends N bytes of the message buffer
    char *message = "Hello World\n";
    send(new_socket , message , strlen(message) , 0 );
   
    return 0;
}
