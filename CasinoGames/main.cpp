//
//  main.cpp
//  CasinoGames
//
//  Created by Maksim Sharoika on 2021-07-10.
//

#include <stdlib.h>
#include <iostream>
#include "games.hpp"

bool game_on = true;
int game_choice = -1;
int money = 100;

using namespace std;

int main() {
    srand(unsigned((time(NULL))));
    // introduction message
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "--------------------------- Welcome to Maximo-Casino ---------------------------" << endl;
    cout << "------------------------ You Have $"<< money << " to Gamble With --------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    // game logic
    while (game_on == true && money != 0)
    {
        cout << "Please enter the # associated with the game you would like to play, enter 0 to leave." << endl;
        cout << "1. BlackJack" << endl;
        cout << "0. Leave" << endl;
        cout << "Your choice... ";
        cin >> game_choice;
        if (game_choice == 0)
        {
            game_on = false;
        }
        if (game_choice == 1)
        {
            money = blackjack(money);
            cout << "You have returned from backjack with $" << money << "." << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
        }
    }
    // game end
    if (money < 1)
    {
        cout << "You lost all your money - come back when you have more." << endl;
    }
    cout << "Thank you for playing! - Maxino-Casino." << endl;
    return 0;
}
