# include <iostream>
# include <fstream>
# include <string>
# include <list>
# include <vector>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <stdio.h>
#include <cstdio>

using namespace std;

void create_file(string username, string password);
void verify(string username, string password);
void right_password(string username, int money, string password);
void wrong_password(void);
void game_selection(int money, string username, string password);
void trump (int money, string username, string password);
int get_house_card(int suit, int card, int house_hand[4][6]);
void update_money(int money, string username, string password);
std::fstream& GotoLine(std::fstream& file, unsigned int num);
std::array <int, 13> ranomizelist(std::array<int, 13> list);
const char string_to_char(const char* a, const char* b);

string get_user_card(int suit, int card, int user_hand[4][6]);
string house_card_get(int suit, int card, int user_hand[4][6]);


class file_info{
    public:
        string username;
        string password;
};
int starting_money = 300;

int main(){
    char t;
    file_info file;
    cout <<"Would you like to login or register a oBoonkero's casino account? \nL for login, R for regist or press Q to exit\n";
    cin >> t;

    switch(t){
        case 'L':
        {
        cout << "\nPlease enter your loging information for oBoonkero Casino";
        cout << "\n username: ";
        cin >> file.username;
        cout << "\n password: ";
        cin >> file.password;
        verify(file.username, file.password);
        break;
        }
        case 'R':
        {
        string ur;
        string pr;
        cout << "\nPlease enter the following information that you would like to use";
        cout << "\nusername: ";
        cin >> ur;
        cout << "\npassword: ";
        cin >> pr;
        create_file(ur, pr);
        break;
        }

        case 'Q':
        exit(EXIT_SUCCESS);
        break;
        
        default:
        cout << "\n the following character inputed was not recognized. \nPlease try again";
        main();
        break;
    }

}

void create_file(string username, string password){
    ofstream MyFile(username + ".txt");

    if (MyFile.is_open()){
        MyFile << password;
        MyFile << "\n";
        MyFile << starting_money;
    }
    MyFile.close();
    main();

}

void verify(string username, string password){
    ifstream file(username + ".txt", ios::in);
    string ps;
    string ab;
    if (file.is_open()){
        getline(file, ps);
        getline(file, ab);
        file.close();

    }
    else{
        cout << "Idk you fucked up";
    }
    if (ps == password){
        right_password(username, std::stoi(ab), password);

    }
    else {
        wrong_password();

    }
    
    
}
void wrong_password(){
    cout << "Sorry the username and/or password is incorrect\n";
    main();
}

void right_password(string username, int money, string password){
    cout << "Congratulations you have succesfully logged in! \n";
    cout << "You currently have: $";
    cout << money;
    game_selection(money, username, password);

}

void game_selection(int money, string username, string password){
    char user;
    cout << "\nPlease select a game below by typing out the first letter of the game (capitalized) \n";
    cout << "Trump(not actually trump btw), press E for explanation of game, or press Q to quit \n";
    cin >> user;
    switch(user)
    {
    case 'T':
        trump(money, username, password);
        break;
    case 'E':
        cout << "Just choose a suite likes hearts or diamond by typing the first letter of sutie like S for spades. \nThen choose a number from zero to five in order to get a random card. If your card is higher than the houses card then you win.";
        game_selection(money, username, password);
    case 'Q':
        exit(EXIT_SUCCESS);
        break;

    default:
        cout << "\nThat character is incorrect make sure that you have capitalized";
        game_selection(money, username, password);
        break;
    }
}
class games{
    public:
    int user_suit;
};
void trump(int money, string username, string password){
    file_info file;
    games game;

    int delta_money;
    int houseWs;
    int userWs;
    char user_suit;
    int user_suit_int;
    int usercard;

    

    std::array<int, 13> cardset = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

    std::array <int, 13> hearts;
    hearts = ranomizelist(cardset);
    std::array <int, 13> diamonds; 
    diamonds = ranomizelist(cardset);
    std::array <int, 13> clubs;
    clubs = ranomizelist(cardset);
    std::array <int, 13> spades;
    spades = ranomizelist(cardset);

    int user_hand[4][6];
    int house_hand[4][6];

    int housecard;
    int bet_amount; 
    cout << "How much money would you like to bet on this game\n" << "$";
    cin >> bet_amount; 
    if (bet_amount > money){
        cout << "You do not have enough money to proceed with that bet" << "\n You only have $" << money;
        game_selection(money, username, password);
    }

    

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 6; j++){
            switch (i){
                case 0:
                    user_hand[i][j] = hearts[j];
                    break;
                case 1:
                    user_hand[i][j] = diamonds[j];
                    break;
                case 2:
                    user_hand[i][j] = clubs[j];
                    break;
                case 3:
                    user_hand[i][j] = spades[j];
                    break;
            }
        }
        
    }
    for (int i = 0; i < 4; i++){
        for (int j = 7; j < 12; j++){
            switch (i){
                case 0:
                    house_hand[i][j-7] = hearts[j];
                    break;
                case 1:
                    house_hand[i][j-7] = diamonds[j];
                    break;
                case 2:
                    house_hand[i][j-7] = clubs[j];
                    break;
                case 3:
                    house_hand[i][j-7] = spades[j];
                    break;
            }
        }
        
    }
    
    

    /*cout << "\nYour hand is: \n";

    for (int i = 0; i < 4; i++){
        switch (i){
            case 0:
                cout << "Hearts: ";
                break;
            case 1:
                cout << "Diamonds: ";
                break;
            case 2:
                cout << "Clubs: ";
                break;
            case 3:
                cout << "Spades: ";
                break;
        }
        for (int j = 0; j < 6; j++){
            switch(user_hand[i][j]){
                case 2:
                    cout << "two";
                    break;
                case 3:
                    cout << "three";
                    break;
                case 4:
                    cout << "four";
                    break;
                case 5:
                    cout << "five";
                    break;
                case 6:
                    cout << "six";
                    break;
                case 7:
                    cout << "seven";
                    break;  
                case 8:
                    cout << "eight";
                    break;
                case 9:
                    cout << "nine";
                    break;  
                case 10:
                    cout << "ten";
                    break;
                case 11:
                    cout << "jack";
                    break;
                case 12:
                    cout << "queen";
                    break;
                case 13:
                    cout << "king";
                    break;
                case 14:
                    cout << "ace";
                    break;
            
            }
            cout << ", ";
        }
        cout << "\n";
    }*/

    
    cout << "Please choose a suit by entering the first letter of suit:  ";
    cin >> user_suit;
    switch(user_suit){
        case 'H':
            game.user_suit = 0;
            break;
        case 'D':
            game.user_suit = 1;
            break; 
        case 'C':
            game.user_suit = 2;
            break;
        case 'S':
            game.user_suit = 3;
            break;
        default:
            cout << "That is not a valid suit please try again\n";
            trump(money, username, password);
            break;
    }
    
    cout << "Please choose a number between 0-5 to get your card\n";
    cin >> usercard;
    housecard = get_house_card(game.user_suit, usercard, house_hand);
    


    if (user_hand[game.user_suit][usercard] > housecard){
        delta_money = money + bet_amount;
        cout << "Your card was:" << get_user_card(game.user_suit, usercard, user_hand) << "\n";
        cout << "The house card was:" << house_card_get(game.user_suit, usercard, house_hand) << "\n";
        cout << "You won! You now have $" << delta_money << "\n";
        update_money(delta_money, username, password);
    }
    else if (user_hand[game.user_suit][usercard] < housecard){
        delta_money = money - bet_amount;
        cout << "You lost! You now have $" << delta_money << "\n";
        update_money(delta_money, username, password);
    }
    else{
        cout << "You tied! You now have $" << money << "\n";
    }
}



int get_house_card(int suit, int card, int house_hand[4][6]){
    return house_hand[suit][card];

}
        



string get_user_card(int suit, int card, int user_hand[4][6]){

    string a;
    string b;
    switch (suit){
        case 0:
            a = "Hearts";
            break;
        case 1:
            a = "Diamonds";
            break;
        case 2:
            a = "Clubs";
            break;
        case 3:
            a = "Spades";
            break;
    }
    switch (user_hand[suit][card]){
        case 2:
            b = "two";
            break;
        case 3:
            b = "three";
            break;
        case 4:
            b = "four";
            break;
        case 5:
            b = "five";
            break;
        case 6:
            b = "six";
            break;
        case 7:
            b = "seven";
            break;  
        case 8:
            b = "eight";
            break;
        case 9:
            b = "nine";
            break;  
        case 10:
            b = "ten";
            break;
        case 11:
            b = "jack";
            break;
        case 12:
            b = "queen";
            break;
        case 13:
            b = "king";
            break;
        case 14:
            b = "ace";
            break;
    }

    return b+" of "+a;

}

string house_card_get(int suit, int card, int user_hand[4][6]){

    string a;
    string b;
    switch (suit){
        case 0:
            a = "Hearts";
            break;
        case 1:
            a = "Diamonds";
            break;
        case 2:
            a = "Clubs";
            break;
        case 3:
            a = "Spades";
            break;
    }
    switch (user_hand[suit][card]){
        case 2:
            b = "two";
            break;
        case 3:
            b = "three";
            break;
        case 4:
            b = "four";
            break;
        case 5:
            b = "five";
            break;
        case 6:
            b = "six";
            break;
        case 7:
            b = "seven";
            break;  
        case 8:
            b = "eight";
            break;
        case 9:
            b = "nine";
            break;  
        case 10:
            b = "ten";
            break;
        case 11:
            b = "jack";
            break;
        case 12:
            b = "queen";
            break;
        case 13:
            b = "king";
            break;
        case 14:
            b = "ace";
            break;
    }

    return b+" of "+a;

}

        
    
    
    std::array <int, 13> ranomizelist(std::array<int, 13> list){

        //https://www.cplusplus.com/reference/algorithm/shuffle/
        // obtain a time-based seed:
    

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (list.begin(), list.end(), std::default_random_engine(rand()));
    


    return list;
    }



void update_money(int money, string username, string password){
    string a = username + ".txt";
    const char* file_name = a.c_str();

    if( remove(file_name) != 0 )
    perror( "Error deleting file" );
    else
    puts( "File successfully deleted" );


    ofstream file(file_name);
    if (file.is_open()){
        file << password;
        file << "\n";
        file << money;
    }
    file.close();
    game_selection(money, username, password);

}

