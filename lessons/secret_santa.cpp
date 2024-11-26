#include <iostream>
#include <map>
#include <conio.h>

int get_keyboard_input(){
    while(!_kbhit){}
    return getch();
}

int main() {
    constexpr char esc{27};
    constexpr char ret{13};

    std::map<int, std::string> secret_santa_map {
        {21, "jack"}, {22, "cami"}, {666, "mango"},
        {42, "david"}, {3, "leti"}, {17, "valerio"},
        {4, "gonzo"}, {432, "dario"}, {325, "irene"},
        {73, "fulvia"}, {94, "hamza"}, {11, "luca"}
    };    

    std::cout << "Perss enter to start secret santa roulette, exit to terminate." << std::endl;
    char answer = (ret == get_keyboard_input()) ? 'y' : [](){ 
        std::cout << "You are a f*****g grinch!!!";
        return esc;}();
    while('y' == answer){
        auto it = secret_santa_map.begin();
        while(get_keyboard_input && answer != 'n'){
            std::cout << "\b\b\b";
            std::cout << it->first;
            if(++it == secret_santa_map.end()){
                it = secret_santa_map.begin();
            }
        }
        answer = esc; // esc in ASCII
        std::cout << "\b\b\b";
        std::cout << "Your pair-santa is: "<< it->first << " ~ " << it->second << "!!!" << std::endl;
        std::cout << "Do you want to change your pair-santa and retry the roulette? y/n" << std::endl;
        answer = get_keyboard_input();
        while('y' != answer && 'n' != answer){
            std::cout << "Do you want to change your pair-santa and retry the roulette? y/n" << std::endl;
            answer = get_keyboard_input();
        }
    }
    if(esc != answer){
        std::cout << "Wish you a very happy christmas!!!" << std::endl;
    }
    
    return 0;
}