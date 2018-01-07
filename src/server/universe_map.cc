#include "universe_map.h"

#include <iostream>
#include <vector>
#include <string>

namespace game {
    bool UniverseMap::CheckBoundary(const Position& position) {
        if (position.x < 0 || position.x >= this->map_size ||
                position.y < 0 || position.y >= this->map_size) {
            return false;
        }

        return true;
    }

    Position UniverseMap::GetAvailablePosition() {
        // TODO: get available positon
        return Position();
    }

    UniverseMap::UniverseMap(int n) : map_size(n) {
        this->universe_spots = std::vector<std::vector<Point> >(n, 
                std::vector<Point>(n, Point()));
    }

    UniverseMap::Result UniverseMap::AddUser(
            const User& user, const Position& position) {
        if (!this->CheckBoundary(position)) {
            return UniverseMap::OutOfBoundary;
        }

        User new_user = user;

        // Initialize position
        new_user.position = position;

        Point& point = this->universe_spots[new_user.position.y][new_user.position.x];
        point.spot_type = Player;

        if (this->user_map.find(user.userid) != user_map.end()) {
            return UniverseMap::UserExists;
        }

        this->user_map.insert(std::pair<int, User>(new_user.userid, new_user));
        return UniverseMap::Success;
    }

    UniverseMap::Result UniverseMap::RemoveUser(const User &user) {
        // Check boundary
        if (!this->CheckBoundary(user.position)) {
            return UniverseMap::OutOfBoundary;
        }

        // Set point to empty spot.
        Point& point = this->universe_spots[user.position.y][user.position.x];
        point.spot_type = Spot;

        if (this->user_map.find(user.userid) == user_map.end()) {
            return UniverseMap::UserNotExists;   
        }

        this->user_map.erase(user.userid);
        return UniverseMap::Success;
    }

    UniverseMap::Result UniverseMap::Move(const User &user, Direction direction) {
        if (this->user_map.find(user.userid) == this->user_map.end()) {
            return UniverseMap::UserNotExists; 
        }

        User& u = this->user_map[user.userid];
        Position temp_pos = u.position;
        switch(direction) {
        case Up:temp_pos.y++; break;
        case Down:temp_pos.y--; break;
        case Left:temp_pos.x--; break;
        case Right:temp_pos.x++; break;
        }

        // Check boundary
        if (!this->CheckBoundary(user.position)) {
            return UniverseMap::OutOfBoundary;
        }

        Point& point = this->universe_spots[u.position.y][u.position.x];
        Point& temp_point = this->universe_spots[temp_pos.y][temp_pos.x];

        switch(temp_point.spot_type) {
        case Unknown:
        case Player:
            // if some one occupied.
            return Conflict;
        case Mineral:
            // add score
            u.score++;
            break;
        case Spot:
            break;
        }

        // move user to current spot (temp_point)
        temp_point.spot_type = Player;

        // set origin point to empty spot
        point.spot_type = Spot;

        // set user
        u.position = temp_pos;

        return UniverseMap::Success; 
    }

	std::string UniverseMap::ToString() {
        std::string result = "";
        for(int i = this->map_size - 1; i >= 0; --i) {
        	for(int j = 0; j < this->map_size; ++j) {
            	Point& point = this-> universe_spots[i][j];
				switch(point.spot_type) {
				case Spot: result += "o"; break;
			    case Mineral: result += "m"; break;
                case Player: result += "p"; break;
                case Unknown: result += "x"; break;
				}
            }
            result += "\n";
        }

        return result;
    }

    std::string UniverseMap::GetUserDisplayMap(const User& user, int n) {
        if (this->user_map.find(user.userid) == this->user_map.end()) {
            return ToString();
        }

        std::vector<std::vector<char> > m(this->map_size, 
                std::vector<char>(this->map_size, 'o'));

        for(int i = 0; i < this->map_size; ++i) {
            for(int j = 0; j < this->map_size; ++j) {
                char temp = 'x';
                Point& point = this-> universe_spots[i][j];
                switch(point.spot_type) {
				case Spot: temp = 'o'; break;
			    case Mineral: temp = 'm'; break;
                case Player: temp = 'p'; break;
                case Unknown: temp = 'x'; break;
                }

                m[i][j] = temp;
            }
        }

        User& u = user_map[user.userid];
        int x_begin = u.position.x - n;
        x_begin = x_begin < 0 ? 0 : x_begin;

        int x_end = u.position.x + n;
        x_end = x_end >= this->map_size ? map_size : x_end;

        int y_begin = u.position.y - n;
        y_begin = y_begin < 0 ? 0 : y_begin;

        int y_end = u.position.y + n;
        y_end = y_end >= this->map_size ? map_size : y_end;

        for(int i = 0; i < y_begin; ++i) {
            for(int j = 0; j < this->map_size; ++j) {
                m[i][j] = 'x';
            }
        }

        for(int i = y_begin; i <= y_end; ++i) {
            for(int j = 0; j < x_begin; ++j) {
                m[i][j] = 'x';
            }

            for(int j = x_end+1; j < this->map_size; ++j) {
                m[i][j] = 'x';
            }
        }

        for(int i = y_end+1; i < this->map_size; ++i) {
            for(int j = 0; j < this->map_size; ++j) {
                m[i][j] = 'x';
            }
        }

        std::string result = "";
        for(int i = this->map_size-1; i >= 0; --i) {
            for(int j = 0; j < this->map_size; ++j) {
                result += m[i][j];
            }

            result += "\n";
        }

        return result;
    }
}

