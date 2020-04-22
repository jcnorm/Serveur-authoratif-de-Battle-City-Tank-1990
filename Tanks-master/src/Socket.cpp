#include <stdio.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <iostream>
#include "Socket.h"
#include <string.h> 

void Socket::Connect()
{
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    // Filling server information 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    //Timeout on recv settings
    struct timeval recv_timeout;
    recv_timeout.tv_sec = 0;
    recv_timeout.tv_usec = 200;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,&recv_timeout,sizeof(recv_timeout)) < 0) {
        perror("Socket timeout option couldn't be set");
    }

    //Polling options
    fds[0].fd = sock;
    fds[0].events = POLLIN;
} 

std::string Socket::VerifyGameState(std::string message){

    //If last call timed out and received the message in the meantime
    if (missedLastResponse){
        if(poll(fds, 1, 50) > 0)
            recvfrom(sock, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &serv_addr, 
                (socklen_t*)sizeof(serv_addr)); 
        missedLastResponse = false;
    }

    memset(buffer, 0, sizeof(buffer));

    sendto(sock, (const char *)message.c_str(), message.size(), 
        MSG_CONFIRM, (const struct sockaddr *) &serv_addr,  
            sizeof(serv_addr)); 

    recvfrom(sock, (char *)buffer, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &serv_addr, 
            (socklen_t*)sizeof(serv_addr)); 

    //If recv timed out
    if(errno == EAGAIN || errno == EWOULDBLOCK)
        missedLastResponse = true;

    return std::string(buffer);
}  

void Socket::Close(){
    close(sock); 
}