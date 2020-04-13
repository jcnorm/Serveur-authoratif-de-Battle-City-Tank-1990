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
    
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Socket timeout option couldn't be set");
    }
} 

[[nodiscard]] Gamestate Socket::SendGameState(Gamestate state){
    auto message = state.ToString();

    sendto(sock, (const char *)message.c_str(), message.size(), 
        MSG_CONFIRM, (const struct sockaddr *) &serv_addr,  
            sizeof(serv_addr)); 

    int n = recvfrom(sock, (char *)buffer, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &serv_addr, 
            (socklen_t*)sizeof(serv_addr)); 

    std::cout << "Buffer received: " << std::string(buffer) << std::endl;
    memset(buffer, 0, sizeof(buffer));
    
    return Gamestate(std::string(buffer));
}  

void Socket::Close(){
    close(sock); 
}