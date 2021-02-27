#ifndef ROOM_HPP
#define ROOM_HPP
#include <vector>
struct Room{
    Room();
    bool bat;
    bool pit;
    bool wump;
    bool player;
    int id;
    std::vector<int> rooms;
};

#endif
