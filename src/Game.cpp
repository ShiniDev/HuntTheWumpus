#include "headers/Game.hpp"

Game::Game(){
    p = initialize_player();
    g = initialize_gamemap();
    g.init_gmap();
}

GameMap Game::initialize_gamemap(){
    std::cout << "\n<Map Settings>\n\n";
    std::cout << "Map Size (Even number between 4 to 500): ";
    std::string s;
    int n;
    while(true){
        std::cin >> s;
        if(!is_an_integer(s)){
            std::cout << "Integer only\n";
            continue;
        }
        n = std::stoi(s);
        if(n<4||n>500){
            std::cout << "Number cannot be less than 4 or greater than 500\n";
            continue;
        }
        if(n%2!=0){
            std::cout << "Number must be an even number\n";
            continue;
        }
        std::cout << "Your chosen map size is " << n << "\n";
        std::cout << "Final?(y/n)\n";
        std::cin >> s;
        to_lower_string(s);
        if(s=="yes"||s=="y")break;
    }
    GameMap g(n);
    return g;
}

Player Game::initialize_player(){
    std::string s;
    std::cout << "\n<Player Initialization>\n\n";
    while(true){
        std::cout << "Player name: ";
        std::cin >> s;
        std::cout << "Final?(y/n)\n";
        std::string s2;
        std::cin >> s2;
        to_lower_string(s2);
        if(s2=="yes"||s2=="y")break;
    }
    Player p(s);
    return p;
}

void Game::initialize_mobs(){
    for(int i = 0; i < 3;i++){
        int r = rand()%(g.gmap.size()-1);
        if(g.gmap[r].player==true||g.gmap[r].pit==true||g.gmap[r].bat==true||g.gmap[r].wump==true){
            i--;
            continue;
        }
        if(i==0&&g.gmap.size()!=4)g.gmap[r].bat=true; //Bat is disabled if there are 4 rooms
        else if(i==1)g.gmap[r].pit=true;
        else if(i==2)g.gmap[r].wump=true;
    }
    for(int i = 0; i < g.gmap.size()/10&&g.gmap.size()>10; i++){	//The ratio is 1:10 for pits
        int r = rand()%(g.gmap.size()-1);
        if(g.gmap[r].player==true||g.gmap[r].pit==true||g.gmap[r].bat==true||g.gmap[r].wump==true){
            i--;
            continue;
        }
        g.gmap[r].pit=true;
    }
    for(int i = 0;i < g.gmap.size()/15&&g.gmap.size()>15; i++){
        int r = rand()%(g.gmap.size()-1);
        if(g.gmap[r].player==true||g.gmap[r].pit==true||g.gmap[r].bat==true||g.gmap[r].wump==true){
            i--;
            continue;
        }
        g.gmap[r].bat=true;
    }
}

void Game::start(){
    srand(time(NULL));
    p.player_move(rand()%(g.gmap.size()-1)+1);
    g.gmap[p.get_room_num()-1].player=true;
    initialize_mobs();
    std::cout << "\nWelcome to Hunt the Wumpus!\n\n";
    std::cout << "Your job is to slay the wumpus using bow and arrow.\n";
    std::cout << "In addition to the wumpush, the cave has two hazards: bottomless pits and giant bats.\n";
    std::cout << "If you enter a room with a bottomless pit, it's the end of the game for you.\n";
    std::cout << "If you enter a room with a bat, the bat picks you up and drops you into another room.\n";
    std::cout << "If you enter the room with the wumpus or he enters yours, he eats you.\n";
    std::cout << "When you enter a room you will be told if a hard is nearby:\n";
    std::cout << "\t\"I smell the wumpus\": it's in an adjoining room.\n";
    std::cout << "\t\"I feel a breeze\": One of the adjoining rooms is a bottomless pit.\n";
    std::cout << "\t\"I hear a bat\": A giant bat is in an adjoining room.\n";
    std::cout << "Commands: m for move, s for shoot, h for help, e for exit\n\n";
    char ch;
    bool bd,pd,wd;
    while(p.is_alive()){
        bd = false;
        pd = false;
        wd = false;
        std::cout << "You are in room " << p.get_room_num() << "; there are tunnels to ";
        p_player_rooms(g,p);
        std::cout << '\n';
        for(int i = 0; i < 3; i++){
            if(g.gmap[g.gmap[p.get_room_num()-1].rooms[i]-1].pit==true&&!pd){
                std::cout << "\n\"I feel a breeze\"\n";
                pd = true;
            }
            if(g.gmap[g.gmap[p.get_room_num()-1].rooms[i]-1].bat==true&&!bd){
                std::cout << "\n\"I hear a bat\"\n";
                bd = true;
            }
            if(g.gmap[g.gmap[p.get_room_num()-1].rooms[i]-1].wump==true&&!wd){
                std::cout << "\n\"I smell the wumpus\"\n";
                wd = true;
            }
        }
        std::cout << "\n; move or shoot? ";
        std::cin >> ch;
        if(isalpha(ch))ch = tolower(ch);	//Checks first if its a letter, to avoid error
        if(ch=='m'){
            int n;
            std::string s;		//Important to restrict erroneus input
            std::cin >> s;
            if(!is_an_integer(s)){
                std::cout << "\nInteger only\n\n";
            }else {
                n = std::stoi(s);
                bool valid_room = false;
                for(int i = 0; i < g.gmap[p.get_room_num()-1].rooms.size(); i++){
                    if(g.gmap[p.get_room_num()-1].rooms[i]==n){
                        valid_room = true;
                        break;
                    }
                }
                if(!valid_room){
                    std::cout << "\nInvalid room number on move command\n\n";
                    continue;
                }
                std::cout << "\n<Action> Moved to room " << n << "\n\n";
                g.gmap[p.get_room_num()-1].player=false;
                p.player_move(n);
                g.gmap[p.get_room_num()-1].player=true;
                if(g.gmap[p.get_room_num()-1].pit==true){
                    std::cout << "\nYou fall to the bottomless pit!...\n";
                    std::cout << "It's been 8 hours since you've fall and you're still falling\n";
                    std::cout << "It's been a full week since you've fall, no wonder they call it the bottomless pit\n";
                    std::cout << "You died\n\n";
                    p.died();
                    continue;
                }
                if(g.gmap[p.get_room_num()-1].wump==true){
                    std::cout << "\nYou've stepped into the Wumpus's lair!...\n";
                    std::cout << "The Wumpus wakes up then proceeds to eat you!\n";
                    std::cout << "You died\n\n";
                    p.died();
                    continue;
                }
                if(g.gmap[p.get_room_num()-1].bat==true){
                    std::cout << "\nYou encounted a bat!...\n";
                    while(true){
                        int r = rand()%(g.gmap.size()-1);
                        g.gmap[p.get_room_num()-1].player = false;
                        if(g.gmap[r].player==true||g.gmap[r].pit==true||g.gmap[r].bat==true||g.gmap[r].wump==true){
                            continue;
                        }
                        p.player_move(r);
                        g.gmap[p.get_room_num()-1].player = true;
                        break;
                    }
                    std::cout << "The bat took you to a different room!\n\n";
                }
            }
        }else if(ch=='s'){
            std::string s;
            int n;
            std::cin >> s;
            if(!is_an_integer(s)){
                std::cout << "\nInteger Only\n\n";
                continue;
            }
            n = std::stoi(s);
            bool valid_room = false;
            for(int i = 0; i < g.gmap[p.get_room_num()-1].rooms.size(); i++){
                if(g.gmap[p.get_room_num()-1].rooms[i]==n){
                    valid_room = true;
                    break;
                }
            }
            if(!valid_room){
                std::cout << "\nInvalid room number on shoot command\n\n";
                continue;
            }
            if(g.gmap[n-1].wump==true){
                g.gmap[n-1].wump = false;
                std::cout << "\nYou've shot and killed the Wumpus!\n";
                std::cout << "You've won the game!, the wumpus is no more\n\n";
                break;
            }
            if(g.gmap[n-1].bat==true){
                g.gmap[n-1].bat = false;
                std::cout << "\nYou've shot and killed a bat\n\n";
            }else std::cout << "You've miss your shot!\n";
            bool wumpus_nearby = false;
            int wumpus_room;
            for(int i = 0; i < 3; i++){
                if(g.gmap[g.gmap[p.get_room_num()-1].rooms[i]-1].wump==true){
                    wumpus_room = g.gmap[p.get_room_num()-1].rooms[i];
                    wumpus_nearby = true;
                    break;
                }
            }
            if(wumpus_nearby){
                g.gmap[wumpus_room-1].wump = false;
                std::cout << "\nYou've startled the wumpus!\n";
                int r = rand()%3;
                wumpus_room = g.gmap[wumpus_room-1].rooms[r];
                g.gmap[wumpus_room-1].wump = true;
                if(g.gmap[wumpus_room-1].player == true){
                    std::cout << "The wumpus move unto your room!\n";
                    std::cout << "The wumpus is very mad!, it then proceeds to devour you!\n";
                    std::cout << "You died\n\n";
                    break;
                }
            }
        }else if(ch=='h'){
            std::cout << "m to move eg. m14 - move to room 14\n";
            std::cout << "s to shoot eg. s12 - shoot room 12\n";
            std::cout << "h for help\n";
            std::cout << "e to exit\n\n";
            continue;
        }else if(ch=='e'){
            std::cout << "\nThank You, " << p.get_name() << " for playing!\n\n";
            break;
        }else{
            std::cout << "Invalid command, use h to see the available commands\n\n";
            continue;
        }
    }
    output_to_file();
}

void Game::output_to_file(){
    std::ofstream ofs;
    ofs.open("src/data/Map.txt",std::ios_base::out);
    ofs << "<Legend>\n";
    ofs << "P = Player\n";
    ofs << "W = Wumpus\n";
    ofs << "U = Pit\n";
    ofs << "^ = Bat\n\n";
    ofs << "   ";
    for(int i = 0; i < 10; i++){
        ofs << " " << i << " ";
    }
    for(int i = 0; i < g.gmap.size(); i++){
        if(i%10==0){
            ofs << "\n";
            if(i<9)ofs << "00" << i;
            else if(i < 99) ofs << "0" << i;
            else ofs << i;
        }
        if(g.gmap[i].bat==true)ofs << "|^|";
        else if(g.gmap[i].pit==true)ofs << "|U|";
        else if(g.gmap[i].player==true)ofs << "|P|";
        else if(g.gmap[i].wump==true)ofs << "|W|";
        else ofs << "| |";
    }
    ofs.close();
}
