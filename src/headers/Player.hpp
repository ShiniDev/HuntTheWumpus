#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>

class Player{
    public:
        Player()
            :name("null"),arrows(5),room_num(1),alive(true){}
        Player(std::string n)
            :name(n),arrows(5),room_num(1),alive(true){}
        std::string get_name()const{return name;}
        int get_arrows()const{return arrows;}
        int get_room_num()const{return room_num;}
        bool is_alive()const{return alive;}

        void set_arrows(int n){arrows = n;}
        void player_move(int n){room_num = n;}
        void died(){alive = false;}
        void revived(){alive = true;} //Might be useful
    private:
        std::string name;
        int arrows;
        int room_num;
        bool alive;
};

#endif
