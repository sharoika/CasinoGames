//
//  main.cpp
//  CasinoGames
//
//  Created by Maksim Sharoika on 2021-07-10.
//

#include <stdlib.h>
#include <iostream>
#include "blackjack.hpp"

// contant for spacer
const int spacer_length = 80;

// function pre-call
int get_input(int, int);
void spacer();

using namespace std;

int main() {
    // variable declarations
    bool game_on = true;
    int money = 100;
    // random seed generation
    srand(unsigned((time(NULL))));
    // introduction message
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------- Welcome to Maximo-Casino ---------------------------" << endl;
    cout << "------------------------ You Have $"<< money << " to Gamble With --------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    
    // game logic
    while (game_on == true && money > 0)
    {
        int game_choice = 0;
        // choice menu of games
        cout << "Please enter the # associated with the game you would like to play, enter 1 to leave." << endl;
        cout << "1. BlackJack" << endl;
        cout << "0. Leave" << endl;
        cout << "Your choice... ";
        
        game_choice = get_input(0, 1);
        
        // leave the casino option
        if (game_choice == 0)
        {
            game_on = false;
        }
        
        // leave blackjack option
        if (game_choice == 1)
        {
            money = blackjack(money);
            cout << "You have returned from backjack with $" << money << "." << endl;
            spacer();
        }
    }
    
    // game end
    if (money <= 0)
    {
        cout << "You lost all your money - come back when you have more." << endl;
    }
    spacer();
    cout << "You are leaving with $" << money << "." << endl;
    cout << "Thank you for playing! - Maxino-Casino." << endl;
    spacer();
    return 0;
}

// space function
void spacer()
{
    for(int i = 0; i < spacer_length; i++)
    {
        cout << "-";
    }
    cout << endl;
}

// input function
int get_input(int low_range, int high_range)
{
    int input;
    while(true)
    {
        cin >> input;
        if (!cin)
        {
            cout << "Invalid response - please try again... ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if(input < low_range || input > high_range)
        {
            cout << "Invalid response - please try again... ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
      }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    return input;
}
    
