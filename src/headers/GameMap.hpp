#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include "Room.hpp"

class GameMap{
    public:
        GameMap();
        GameMap(int n);
        void init_gmap();
        void print_gmap();
        std::vector<Room> gmap;
    private:
        void randomize_map(int);
        int checker;
};

inline void connect_room(std::vector<Room>&,int,int);
inline bool already_connected(std::vector<Room>&,int,int);

#endif
