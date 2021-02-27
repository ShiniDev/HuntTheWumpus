#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Game.hpp"
#include <string>

inline bool is_an_integer(const std::string& s){
    for(int i = 0; i < s.size(); i++){
        if(!isdigit(s[i]))return false;
    }
    return true;
}

inline void to_lower_string(std::string& s){
    for(int i = 0; i < s.size(); i++){
        if(!isalpha(s[i]))continue;
        s[i] = tolower(s[i]);
    }
}

inline void p_player_rooms(const GameMap& g,const Player& p){
    std::cout << g.gmap[p.get_room_num()-1].rooms[0] << ", " << g.gmap[p.get_room_num()-1].rooms[1] << ", ";
    std::cout << "and " << g.gmap[p.get_room_num()-1].rooms[2];
}

#endif
