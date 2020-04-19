#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <iostream>
#include "Validator.h"
//#include <chrono>

#define PORT     8080
#define MAXLINE 4096

int sockfd;

//To simplify signal handling
typedef void Sigfunc(int);
Sigfunc *signal(int,Sigfunc *);

void HandleSignals(int no){
    switch(no){
        case SIGINT:    std::cout << "Received the SIGINT signal" << std::endl;
                        break;

        case SIGTSTP:   std::cout << "Received the SIGTSTP signal" << std::endl;
                        break;
    }

    std::cout << "Closing down server" << std::endl;
    close(sockfd);

    exit(0);
}

void InitializeSignalHandlers(){
    signal(SIGTSTP,HandleSignals) ;
    signal(SIGINT,HandleSignals) ;
}

void InitializeSocket(sockaddr_in& servaddr, sockaddr_in& cliaddr){
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    InitializeSignalHandlers();

    InitializeSocket(servaddr, cliaddr);
    
    socklen_t len = sizeof(cliaddr);
    int n;
    Validator validator{};

    while(true){
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    &len);

        //auto pre = std::chrono::high_resolution_clock::now();

        auto newGamestate = validator.ValidateMessage(std::string(buffer));

        // auto post = std::chrono::high_resolution_clock::now();
        
        // std::cout << "Time to validate: "
        //     << std::chrono::duration_cast<std::chrono::microseconds>(post - pre).count()
        //     << " us." << std::endl;

        sendto(sockfd, newGamestate.c_str(), newGamestate.size(),
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                len);
    }

    return 0;
}