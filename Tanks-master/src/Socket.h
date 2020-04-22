#ifndef SOCKET_H
#define SOCKET_H
#include "gamestate.h"
#include <string>
#include <arpa/inet.h> 
#include <poll.h>

struct Socket{
private:
    const static int MAXLINE = 4096; 
    int sock = 0; 
    char buffer[MAXLINE] = {0};
    struct sockaddr_in serv_addr; 
    const int PORT = 8080;
    bool missedLastResponse = false;
    struct pollfd fds[1];
public:
    void Connect();
    std::string VerifyGameState(std::string message);
    void Close();
};

#endif