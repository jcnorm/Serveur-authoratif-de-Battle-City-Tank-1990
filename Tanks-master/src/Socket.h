#ifndef SOCKET_H
#define SOCKET_H
#include "gamestate.h"
#include <string>
#include <arpa/inet.h> 

struct Socket{
private:
    const static int MAXLINE = 4096; 
    int sock = 0; 
    char buffer[MAXLINE] = {0};
    struct sockaddr_in serv_addr; 
    const int PORT = 8080;
public:
    void Connect();
    [[nodiscard]] Gamestate SendGameState(Gamestate state);
    void Close();
};

#endif