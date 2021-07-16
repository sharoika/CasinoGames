//
//  games.cpp
//  CasinoGames
//
//  Created by Maksim Sharoika on 2021-07-11.
//

#include "games.hpp"

bool blackjack_game = true;

const int max_card_number = 21;

int player_card[max_card_number];
int dealer_card[max_card_number];
int dealer_hand = 0;
int player_hand = 0;

int player_move = 1;

int bet;

void restart();
int get_bet(int);
void generate_cards();

int calculate_dealer_hand(int);
int calculate_player_hand(int);

int dealer_card_number = 2;

void inform_player_cards(int);
void inform_dealer_cards(int);

void inform_player_total();
void inform_dealer_total();

void ask_player_move();

bool check_bust();
int end_game(int, int);

bool play_again(bool);

int blackjack(int money)
{
    // introduction message
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "----------------------------- Welcome to BlackJack -----------------------------" << endl;
    cout << "------------------------ You Have $"<< money << " to Gamble With --------------------------" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    while(blackjack_game == true)
    {
        restart();
        bet = get_bet(money);
        money = money - bet;
        generate_cards();
        
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Dealer's Hand: "<< endl;
        cout << "Card #1: " << "###" << endl;
        cout << "Card #2: " << dealer_card[1] << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        
        for(int i = 2; player_hand < 22 && player_move == 1; i++)
        {
            player_hand = calculate_player_hand(i);
            inform_player_cards(i);
            inform_player_total();
            if(check_bust() == false)
            {
                cout << "--------------------------------------------------------------------------------" << endl;
                ask_player_move();
                cout << "--------------------------------------------------------------------------------" << endl;
            }
        }
        if(player_hand < 22)
        {
            dealer_hand = calculate_dealer_hand(dealer_card_number);
            for(int i = 2; dealer_hand < 17; i++)
            {
                dealer_hand = calculate_dealer_hand(i+1);
                dealer_card_number++;
            }
            dealer_hand = calculate_dealer_hand(dealer_card_number);
            inform_dealer_cards(dealer_card_number);
            inform_dealer_total();
            check_bust();
            cout << "--------------------------------------------------------------------------------" << endl;
        }
        if(dealer_hand < 22 && player_hand < 22)
        {
            money = end_game(money, bet);
        }
        if(money > 0)
        {
            blackjack_game = play_again(blackjack_game);
        }
        if(money == 0 || money < 0)
        {
            cout << "You ran out of money broke boy." << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            blackjack_game = false;
        }
    }
    return money;
}

void restart()
{
    dealer_card_number = 2;
    dealer_hand = 0;
    player_hand = 0;
    player_move = 1;
    for(int i = 0; i < max_card_number; i++)
    {
        dealer_card[i] = 0;
        player_card[i] = 0;
    }
}

int get_bet(int money)
{
    cout << "You currently have: $" << money << endl;
    cout << "How much would you like to bet... $";
    cin >> bet;
    if(bet < money)
    {
        money = money - bet;
    }
    else if(bet > money)
    {
        cout << "You dont have that much, try again" << endl;
        bet = get_bet(money);
    }
    return bet;
}

void generate_cards()
{
    for(int i = 0; i < max_card_number; i++)
    {
        player_card[i] = ((rand() % 13) + 1);
        dealer_card[i] = ((rand() % 13) + 1);
        if(player_card[i] > 10)
        {
            player_card[i] = 10;
        }
        if(dealer_card[i] > 10)
        {
            dealer_card[i] = 10;
        }
    }
}

int calculate_dealer_hand(int number_of_hits)
{
    dealer_hand = 0;
    for(int i = 0; i < number_of_hits; i++)
    {
        dealer_hand = dealer_hand + dealer_card[i];
    }
    return dealer_hand;
}

int calculate_player_hand(int number_of_hits)
{
    player_hand = 0;
    for(int i = 0; i < number_of_hits; i++)
    {
        player_hand = player_hand + player_card[i];
    }
    return player_hand;
}


void inform_player_cards(int current_cards)
{
    cout << "Your have hit " << current_cards - 2 << " time(s)." << endl;
    cout << "Player's Hand: " << endl;
    for(int i = 0; i < current_cards; i++)
    {
        cout << "Card #" << i+1 << ": " << player_card[i] << endl;
    }
}

void inform_dealer_cards(int current_cards)
{
    cout << "Dealer has hit " << current_cards - 2 << " time(s)." << endl;
    cout << "Dealer's Hand: " << endl;
    for(int i = 0; i < current_cards; i++)
    {
        cout << "Card #" << i+1 << ": " << dealer_card[i] << endl;
    }
}

void inform_dealer_total()
{
    cout << "The dealer's total card value is: " << dealer_hand << endl;
}

void inform_player_total()
{
    cout << "Your player's card value is: " << player_hand << endl;
}

void ask_player_move()
{
    cout << "What would you like your move to be?" << endl;
    cout << "1. Hit " << endl;
    cout << "2. Stand" << endl;
    cout << "Please enter the numerical value associated... ";
    cin >> player_move;
}

bool check_bust()
{
    if(player_hand > 21)
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Player has busted." << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return true;
    }
    if(dealer_hand > 21)
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "Dealer has busted." << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        return true;
    }
    return false;
}

int end_game(int money, int bet)
{
    if(player_hand == dealer_hand)
    {
        cout << "Your and the dealer have a 'Stand Off'" << endl;
        cout << "Your money have been returned" << endl;
        money = money + bet;
    }
    else if(player_hand < dealer_hand)
    {
        cout << "DEALER WINS" << endl;
    }
    else if(player_hand > dealer_hand)
    {
        cout << "PLAYER WINS" << endl;
        money = money + 2*bet;
    }
    cout << "You now have $" << money << "." << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    return money;
}

bool play_again(bool blackjack_game)
{
    cout << "Would you like to play again?" << endl;
    cout << "1. Yes" << endl;
    cout << "0. No" << endl;
    cout << "Please enter numerical value...";
    cin >> blackjack_game;
    cout << "--------------------------------------------------------------------------------" << endl;
    return blackjack_game;
}
