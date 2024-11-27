#include <iostream>     // cout, endl
#include <vector>       // vector
#include <conio.h>      // _kbhit, getch
#include <windows.h>    // GetStdHandle, SetConsoleTextAttribute
#include <sstream>      // stringstream

// defines for version
#ifndef VERSION_MAJOR
#define VERSION_MAJOR 1
#endif
#ifndef VERSION_MINOR
#define VERSION_MINOR 3
#endif

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

void print_christmas_tree(){
    colored_cout("\t\t     *\n", green);
    colored_cout("\t\t    ***\n", red);
    colored_cout("\t\t   *****\n", bright_green);
    colored_cout("\t\t  *******\n", bright_red);
    colored_cout("\t\t *********\n", green);
    colored_cout("\t\t***********\n", red);
    colored_cout("\t\t     *  \n", bright_green);
    change_text_color(bright_white);
}

void print_banner(){
    print_christmas_tree();
    std::cout << "You are running secret santa roulette software version " << get_version();
    std::cout << "made by TheStandardGuy (www.youtube.com/@tsg_ita)." << std::endl;
    std::cout << "First you add the partecipants to the secret sant (no limits on how many can partecipates).";
    std::cout << "Then you start the ruolette.\nMake your partecipants stop the roulette and choice if they want ";
    std::cout << "another secret-pair or not. Enjoy it!" << std::endl;
}

char ask_until_yes_or_no(const std::string& question){
    char answer{};
    while(yes != answer && no != answer){
        std::cout << question << " (y/n): ";
        answer = get_keyboard_input();
    }
    std::cout << answer << std::endl;
    return answer;
}

char ask_until_ret_or_esc(const std::string& question){
    char answer{};
    while(esc != answer && enter != answer){
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

void erase_previous_row(const int n_rows = 0){
    if(0 == n_rows){
        std::cout << "\033[1A";
    } else {
        std::string s{};
        s += "\033[" + std::to_string(n_rows) + "A";
        std::cout << s;
    }
    std::cout << "\x1b[2K";
}

int main() {
    change_text_color(bright_white);
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
    std::string eraser_line_string{"\x1b[2K"};    

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
        erase_previous_row();
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
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        erase_previous_row(2);
        // std::cout << "\033[2A"; //\033[F";   // goes two rows above         
        for(std::size_t i{0u}; i < 42u; ++i){
            colored_cout("*", get_next_color());
        }
        std::cout << std::endl;
        std::cout << "\x1b[2K"; // delete the whole row        
        change_text_color(bright_white);
        if(no == answer){
            secret_santa_partecipants.erase(it_santa);
            it_santa = secret_santa_partecipants.begin();
            if(secret_santa_partecipants.size() > 0){
                std::cout << "To stop the roulette press any key." << std::endl;
            }
        } else {
            std::cout << "To stop the roulette press any key." << std::endl;
        }
    }
    if(esc != answer){
        colored_cout("Wish you a very happy Christmas!!!", pair_color);
        change_text_color(bright_white);
        // std::cout << std::endl;
    }
    
    return 0;
}