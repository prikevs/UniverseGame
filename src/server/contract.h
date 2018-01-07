#ifndef CONTRACT_H
#define CONTRACT_H

namespace contract {

    const int MAXMSG = 1024;

    const int MAXUSERNAME = 32;
    const int MAXPASSWORD = 32;

    const int MAXREGMSG = MAXMSG - 4;
    const int MAPSIZE = MAXMSG - 4 - 4 - 4 - 8;

    enum OpType {
        Register,
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
    };

    enum RegRes {
        True,
        False, 
    };

    enum OpRes {
        Success,

        OutOfBoundary,
        Conflict,
    };

    struct OpReq {
        OpType op;
        char[MAXUSERNAME] username; 
        char[MAXPASSWORD] password;
    };

    struct RegResp {
        RegRes result;
        char[MAXREGMSG];
    };

    struct Position {
        int x, y;
    };

    struct OpResp {
        OpRes result;
        int score;
        int map_size;
        Position position;
        char[MAPSIZE];
    };

}

#endif
