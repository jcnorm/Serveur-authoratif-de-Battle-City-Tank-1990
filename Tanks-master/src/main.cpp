/**
 * \mainpage
 * \par Tanks
 * Gra w czołgi wzorowana na Battle City / Tank 1990 umożliwiająca grę przez jednego lub dwóch graczy
 * \author Krystian Kałużny
 * \date 12.05.215
 * \version 1.0
 * \par Kontakt:
 * \a k.kaluzny141@gmail.com
*/

#include "app.h"

int main( int argc, char* args[] )
{
    bool server_verification = false;
    if (argc > 1 && strcmp(args[1],"-valid")==0 )
        server_verification = true;

    App app;
    app.run(server_verification);

    return 0;
}
