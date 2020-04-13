#include <cassert>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//#pragma comment(lib,"Ws2_32.lib")

using port_type = unsigned short;
enum { TAILLE_TRAME = 256 };

struct ChargeurSockets
{
    ChargeurSockets()
    {
        WSADATA wsaData;
        assert(WSAStartup(MAKEWORD(2, 2), &wsaData) == 0);
    }
    ~ChargeurSockets()
    {
        WSACleanup();
    }
};

SOCKET creer_socket(port_type port)
{
    SOCKET sck = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    assert(sck != INVALID_SOCKET);
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    assert(bind(sck, reinterpret_cast<const sockaddr*>(&addr), sizeof(sockaddr_in)) != SOCKET_ERROR);
    unsigned long non_bloquant = 1;
    assert(ioctlsocket(sck, FIONBIO, &non_bloquant) == 0);
    return sck;
}


bool envoyer_message(SOCKET sck, const std::string& msg, const sockaddr_in& dest)
{
    assert(msg.size() <= TAILLE_TRAME);
    char tampon[TAILLE_TRAME] = {};
    copy(begin(msg), end(msg), tampon);
    int nb_emis = sendto(
        sck, tampon + 0, TAILLE_TRAME, 0,
        reinterpret_cast<const sockaddr*>(&dest), sizeof(dest)
        );
    if (!nb_emis)
        return false; // fermeture propre de l'homologue
    if (nb_emis == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        if (err != WSAEWOULDBLOCK) return false;
    }
    return true;
}

int recevoir_message(SOCKET sck, char* dest, int capacite, unsigned int& adresse, port_type& port)
{
    sockaddr_in de;
    int deLg = sizeof(de);
    int nb_recus = recvfrom(
        sck, dest, capacite, 0,
        reinterpret_cast<sockaddr*>(&de), &deLg
        );
    // nb_recus == 0 est possible car nous sommes non-bloquants
    if (nb_recus == SOCKET_ERROR)
    {
        int err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) return 0;
    }
    else
    {
        adresse = ntohl(de.sin_addr.s_addr);
        port = ntohs(de.sin_port);
    }
    return nb_recus;
}

void CreateConnection()
{
    const port_type PORT_CLIENT = 0; // whatever
    const port_type PORT_SERVEUR = 7878;
    ChargeurSockets chargeur;
    SOCKET sck = creer_socket(PORT_CLIENT);
    // on veut écrire à 127.0.0.1, port PORT_SERVEUR
    const std::string DESTINATAIRE = "127.0.0.1";
    //unsigned int destinataire = (127 << 24) | (0 << 16) | (0 << 8) | (1 << 0);
    sockaddr_in dest = {};
    dest.sin_family = AF_INET;
    InetPton(AF_INET, DESTINATAIRE.c_str(), &dest.sin_addr.s_addr);
    //dest.sin_addr.s_addr = htonl(destinataire);
    dest.sin_port = htons(PORT_SERVEUR);
    // on y va
    int nb_paquets = 0;
    for (;;)
    {
        stringstream sstr;
        sstr << "J'aime mon prof! (paquet #" << ++nb_paquets << ")";
        if (!envoyer_message(sck, sstr.str(), dest)) break;

        char tampon[TAILLE_TRAME] = { };
        unsigned int adresse;
        port_type port;
        auto nb_recus = recevoir_message(sck, tampon, TAILLE_TRAME, adresse, port);
        if (nb_recus == SOCKET_ERROR) break;
        if (nb_recus)
            cout << "Message recu: \"" << tampon << "\"" << endl;
    }
    closesocket(sck);
}
