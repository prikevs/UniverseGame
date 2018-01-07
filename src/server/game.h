#ifndef GAME_H
#define GAME_H

#include <string>

namespace game {
    enum SpotType {
        Spot = 0,
        Mineral,
        Player,
        Unknown,
    };

    enum Direction {
        Up,
        Down,
        Left,
        Right,
    };

    struct Position {
        int x, y;

        Position(int x, int y) : x(x), y(y) {}
        Position() {}
    };

    struct User {
        int userid;
        int score;
        Position position;
        std::string username;
        bool is_gm;
    };
}

#endif
