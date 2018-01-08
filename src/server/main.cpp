#include "game_server.h"
#include "authenticator.h"

#include <unistd.h>
#include <iostream>
#include <string>

namespace game {
    int GameServer::StartServer(int argc, char* argv[]) {
        int port = 9999;
        const char *host = "127.0.0.1";
        const char *secret_path = "secrets.txt";

        int c;
        while((c = getopt(argc, argv, "p:h:s:")) != -1) {
            switch(c) {
            case 'h':
                if (optarg) host = optarg;
            case 'p':
                if (optarg) port = std::atoi(optarg);
            case 's':
                if (optarg) secret_path = optarg;
            }
        }

        Authenticator authenticator(secret_path);



        return 0;
    }
}
