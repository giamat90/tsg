#include <iostream>     // cout, endl
#include <map>          // map
#include <vector>       // vector
#include <conio.h>      // _kbhit, getch
#include <windows.h>    // GetStdHandle, SetConsoleTextAttribute
#include <sstream>      // stringstream

#define VERSION_MAJOR 1
#define VERSION_MINOR 1

// very important keys
constexpr char esc{27};
constexpr char enter{13};
constexpr char yes{'y'};
constexpr char no{'n'};
// console colors
constexpr int green{2};
constexpr int red{4};
constexpr int bright_green{10};
constexpr int bright_red{12};
constexpr int bright_white{15};

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

char ask_until_yes_or_no(const std::string& question){
    char answer{};
    while(yes != answer && no != answer){
        std::cout << question << " (y/n)" << std::endl;
        answer = get_keyboard_input();
    }
    return answer;
}

char ask_until_ret_or_esc(const std::string& question){
    char answer{};
    while( esc != answer && enter != answer){
        std::cout << question << std::endl;
        answer = get_keyboard_input();
    }
    return answer;
}

void insult(){
    colored_cout("You are a f", bright_green);
    colored_cout("*", bright_red);
    colored_cout("*", bright_green);
    colored_cout("*", bright_red);
    colored_cout("*", bright_green);
    colored_cout("*", bright_red);
    colored_cout("g grinch", bright_green);
    colored_cout("!", bright_red);
    colored_cout("!", bright_green);
    colored_cout("!", bright_red);
    change_text_color(bright_green);
}

int main() {
    print_banner();
    char answer = ask_until_yes_or_no("Do you want to organize a secret santa?");
    if(no == answer){
        insult();
        return 1;
    }
    // Add partecipants
    std::vector<std::string> secret_santa_partecipants{};
    std::string partecipant{};
    int max_name_len_partecipant{};    
    answer = ask_until_yes_or_no("Do you want add a secret santa partecipant?");
    while('y' == answer){
        std::cout << "Write the partecipant's name and press enter" << std::endl;
        if(std::getline(std::cin, partecipant)){
            secret_santa_partecipants.emplace_back(partecipant);
            if(max_name_len_partecipant < partecipant.size()){
                max_name_len_partecipant = partecipant.size();
            }
        }
        answer = ask_until_yes_or_no("Do you want add a secret santa partecipant?");
    }
    std::string eraser_string(max_name_len_partecipant, '\b');    

    // Start the roulette
    std::vector<int> console_colors{bright_red, bright_green, red, green};
    int pair_color{bright_white};
    answer = ask_until_ret_or_esc("Press enter to start secret santa roulette, esc to terminate.");
    if(esc == answer){
        insult();
        return 1;
    }
    std::cout << "To stop the roulette press any key." << std::endl;
    while((secret_santa_partecipants.size() > 0)){
        auto it_santa = secret_santa_partecipants.begin();
        auto it_console_color = console_colors.begin();
        while(!_kbhit()){
            change_text_color(*it_console_color);
            std::cout << eraser_string;
            std::cout << *it_santa;
            if(++it_santa == secret_santa_partecipants.end()){
                it_santa = secret_santa_partecipants.begin();
            }
            if(++it_console_color == console_colors.end()){
                it_console_color = console_colors.begin();
            }
        }
        // throw way the keyboard input
        consume_keyboard_input();
        std::cout << eraser_string;
        colored_cout("Your pair-santa is: ", bright_white);
        colored_cout(*it_santa, *it_console_color);
        pair_color = *it_console_color;
        auto get_next_color = [&](){ return ++it_console_color == console_colors.end() ? *(it_console_color = console_colors.begin()) : *it_console_color;};
        colored_cout("!", get_next_color());
        colored_cout("!", get_next_color());
        colored_cout("!", get_next_color());
        std::cout << std::endl;
        change_text_color(bright_white);
        answer = ask_until_yes_or_no("Do you want to change your pair-santa and retry the roulette?");
        if(no == answer){
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            std::cout << "\033[F\033[F";
            std::cout << "******************************************" << std::endl;
            std::cout << "Do you want to change your pair-santa and retry the roulette?" << std::endl;
            secret_santa_partecipants.erase(it_santa);
            it_santa = secret_santa_partecipants.begin();
        }
    }
    if(esc != answer){
        colored_cout("Wish you a very happy Christmas!!!", pair_color);
        change_text_color(bright_white);
        std::cout << std::endl;
    }
    
    return 0;
}