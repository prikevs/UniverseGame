#include "universe_map.h"

#include <iostream>
using namespace std;

int main() {
    game::UniverseMap universe(25);
    game::Position position(1, 1);
    game::User user;
    cout << universe.AddUser(user, position) << endl;
    cout << "---------" << endl;
    cout << universe.GetUserDisplayMap(user, 2) << endl;
}
