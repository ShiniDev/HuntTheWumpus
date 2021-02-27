#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <fstream>

#include "Player.hpp"
#include "GameMap.hpp"
#include "Utilities.hpp"

class Game{
    public:
        Game();

        GameMap initialize_gamemap();
        Player initialize_player();

        void output_to_file();
        void initialize_mobs();
        void start();
    private:
        GameMap g;
        Player p;
};

#endif
