#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <iostream>
#include <map>

namespace game {
    class Authenticator {
        std::map<std::string, std::string> user_pass_map;

    public:
        Authenticator(const char *secret_path);
        bool Auth(std::string username, std::string password);
    };
}

#endif
