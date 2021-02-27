#include "headers/Room.hpp"
Room::Room()
    :bat(false),pit(false),wump(false),player(false),id(-1)
{
    for(int i = 0; i < 3; i++){ //Initialize values to -1
        rooms.push_back(-1);
    }
}
