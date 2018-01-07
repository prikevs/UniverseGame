#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "game.h"

#include <vector>
#include <map>
#include <string>

namespace game {
    class UniverseMap {
    private:
        struct Point {
            SpotType spot_type;
        };

        std::vector<std::vector<Point> > universe_spots;
        std::map<int, User> user_map;
        int map_size;

        bool CheckBoundary(const Position& position);
        Position GetAvailablePosition();

    public:
        enum Result {
            Success,

            // AddUser
            UserExists,

            // Move
            OutOfBoundary,
            Conflict,

            // RemoveUser
            UserNotExists,
        };

        UniverseMap(int n);

        Result AddUser(const User& user, const Position& position);

        Result RemoveUser(const User &user);

        Result Move(const User &user, Direction direction);

        std::string ToString();

        // for temp use, will do this in another thread.
        std::string GetUserDisplayMap(const User& user, int n);
    };
};

#endif
