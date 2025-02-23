#include "lesson.h"

#if SECRET_SANTA_ACTIVE

#include <iostream>     // cout, endl
#include <map>          // map
#include <vector>       // vector
#include <conio.h>      // _kbhit, getch
#include <windows.h>    // GetStdHandle, SetConsoleTextAttribute
#include <sstream>

#define VERSION_MAJOR 0
#define VERSION_MINOR 2

int get_keyboard_input(){
    while(!_kbhit()){}
    return getch();
}

void consume_keyboard_input(){
    getch();
}

void change_text_color(const int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

template <typename Streamable> 
void colored_cout(Streamable s, int color){
    change_text_color(color);
    std::cout << s;
}

std::string get_version(){
    std::stringstream ss;
    ss << VERSION_MAJOR << "." << VERSION_MINOR;
    return ss.str();
}

void print_banner(){
    std::cout << "You runned secret santa roulette software version " << get_version() << std::endl;
}

void lesson::run() {
    print_banner();
    constexpr char esc{27};
    constexpr char ret{13};
    constexpr int green{2};
    constexpr int red{4};
    constexpr int bright_green{10};
    constexpr int bright_red{12};
    constexpr int bright_white{15};
    int last_console_color{bright_white};

    std::map<int, std::string> secret_santa_map {
        {21, "jack"}, {22, "cami"}, {666, "mango"},
        {42, "david"}, {3, "leti"}, {17, "valerio"},
        {4, "gonzo"}, {432, "dario"}, {325, "irene"},
        {73, "fulvia"}, {94, "hamza"}, {11, "luca"}
    };    
    std::vector<int> console_colors{bright_red, bright_green, red, green};

    std::cout << "Press enter to start secret santa roulette, esc to terminate." << std::endl;
    char answer = (ret == get_keyboard_input()) ? 'y' : [](){ 
        colored_cout("You are a f", bright_green);
        colored_cout("*", bright_red);
        colored_cout("*", bright_green);
        colored_cout("*", bright_red);
        colored_cout("*", bright_green);
        colored_cout("*", bright_red);
        colored_cout("g grinch!!!", bright_green);
        return esc;}();
    while('y' == answer){
        auto it_santa = secret_santa_map.begin();
        auto it_console_color = console_colors.begin();
        while(!_kbhit()){
            change_text_color(*it_console_color);
            std::cout << "\b\b\b";
            std::cout << it_santa->first;
            if(++it_santa == secret_santa_map.end()){
                it_santa = secret_santa_map.begin();
            }
            if(++it_console_color == console_colors.end()){
                it_console_color = console_colors.begin();
            }
        }
        consume_keyboard_input();
        colored_cout("\b\b\bYour pair-santa is: ", bright_white);
        colored_cout(it_santa->first, *it_console_color);
        colored_cout(" ~ ", bright_white);
        colored_cout( it_santa->second, *it_console_color);
        change_text_color(bright_white);
        std::cout << "!!!" << std::endl;
        std::cout << "Do you want to change your pair-santa and retry the roulette? y/n" << std::endl;
        answer = get_keyboard_input();
        while('y' != answer && 'n' != answer){
            std::cout << "Do you want to change your pair-santa and retry the roulette? y/n" << std::endl;
            answer = get_keyboard_input();
        }
        last_console_color = *it_console_color;
    }
    if(esc != answer){
        colored_cout("Wish you a very happy christmas!!!", last_console_color);
        change_text_color(bright_white);
        std::cout << std::endl;
    }
    
}

#endif