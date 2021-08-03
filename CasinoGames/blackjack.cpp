//
//  blackjack.cpp
//  CasinoGames
//
//  Created by Maksim Sharoika on 2021-07-11.
//

// including the header file
#include "blackjack.hpp"

// creating constant varibles
const int max_card_number = 21;

// main BlackJack function
int blackjack(int money)
{
    bool blackjack_game = true;
    int player_card[max_card_number];
    int dealer_card[max_card_number];
    
    spacer();
    cout << "----------------------------- Welcome to BlackJack -----------------------------" << endl;
    cout << "------------------------ You Have $"<< money << " to Gamble With --------------------------" << endl;
    spacer();
    
    // BlackJack game logic
    while(blackjack_game == true)
    {
        // setting up BlackJack round
        restart_cards(player_card, dealer_card);
        int bet = 0;
        int dealer_hand = 0;
        int player_hand = 0;
        int player_move = 1;
        
        // Request Bet from Player
        bet = get_bet(money);
        money = money - bet;
        generate_cards(player_card, dealer_card);
        
        // Dealer's Section
        spacer();
        cout << "Dealer's Hand: "<< endl;
        cout << "Card #1: " << "###" << endl;
        cout << "Card #2: " << dealer_card[1] << endl;
        spacer();
        
        // player move logic
        for(int i = 2; player_hand < 22 && player_move == 1; i++)
        {
            player_hand = calculate_player_hand(i, player_card);
            inform_player_cards(i, player_card);
            inform_player_total(player_hand);
            money = bust(player_hand, dealer_hand, money, bet);
            if(player_hand < 22)
            {
            player_move = ask_player_move();
            }
        }
        
        // dealer move logic
        if(player_hand < 22)
        {
            int dealer_card_number = 2;
            dealer_hand = calculate_dealer_hand(dealer_card_number, dealer_card);
            for(int i = 2; dealer_hand < 17; i++)
            {
                dealer_hand = calculate_dealer_hand(i+1, dealer_card);
                dealer_card_number++;
            }
            dealer_hand = calculate_dealer_hand(dealer_card_number, dealer_card);
            inform_dealer_cards(dealer_card_number, dealer_card);
            inform_dealer_total(dealer_hand);
            money = bust(player_hand, dealer_hand, money, bet);
        }
        
        // end game logic
        if(dealer_hand < 22 && player_hand < 22)
        {
            money = end_game(money, bet, player_hand, dealer_hand);
        }
        
        // play again logic
        if(money > 0)
        {
            blackjack_game = play_again(blackjack_game);
        }
        else
        {
            blackjack_game = false;
        }
        
    }
    return money;
}

void restart_cards(int player_card[], int dealer_card[])
{
    for(int i = 0; i < max_card_number; i++)
    {
        dealer_card[i] = 0;
        player_card[i] = 0;
    }
}

int get_bet(int money)
{
    int local_bet;
    cout << "You currently have: $" << money << endl;
    cout << "How much would you like to bet... $";
    local_bet = get_input(0, money);
    return local_bet;
}

void generate_cards(int player_card[], int dealer_card[])
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

int ask_player_move()
{
    int input;
    cout << "What would you like your move to be?" << endl;
    cout << "1. Hit " << endl;
    cout << "2. Stand" << endl;
    cout << "Please enter the numerical value associated... ";
    input = get_input(1, 2);
    spacer();
    return input;
}

int calculate_dealer_hand(int number_of_hits, int dealer_card[])
{
    int dealer_hand = 0;
    for(int i = 0; i < number_of_hits; i++)
    {
        dealer_hand = dealer_hand + dealer_card[i];
    }
    return dealer_hand;
}

int calculate_player_hand(int number_of_hits, int player_card[])
{
    int player_hand = 0;
    for(int i = 0; i < number_of_hits; i++)
    {
        player_hand = player_hand + player_card[i];
    }
    return player_hand;
}


void inform_player_cards(int current_cards, int player_card[])
{
    cout << "Your have hit " << current_cards - 2 << " time(s)." << endl;
    cout << "Player's Hand: " << endl;
    for(int i = 0; i < current_cards; i++)
    {
        cout << "Card #" << i+1 << ": " << player_card[i] << endl;
    }
}

void inform_dealer_cards(int current_cards, int dealer_card[])
{
    cout << "Dealer has hit " << current_cards - 2 << " time(s)." << endl;
    cout << "Dealer's Hand: " << endl;
    for(int i = 0; i < current_cards; i++)
    {
        cout << "Card #" << i+1 << ": " << dealer_card[i] << endl;
    }
}

void inform_dealer_total(int dealer_hand)
{
    cout << "The dealer's total card value is: " << dealer_hand << endl;
    spacer();
}

void inform_player_total(int player_hand)
{
    cout << "Your player's card value is: " << player_hand << endl;
    spacer();
}

int standoff(int money, int bet, int player_hand, int dealer_hand)
{
    if (player_hand == 21)
    {
        cout << "Both are BlackJacks money returned.";
        money = money + bet;
    }
    else
    {
        cout << "Dealer wins because no one has blackjacks.";
        money = money;
    }
    return money;
}

int bust(int player_hand, int dealer_hand, int money, int bet)
    {
    if(player_hand > 21)
    {
        cout << "PLAYER BUSTED." << endl;
        money = money;
        cout << "You now have $" << money << "." << endl;
        spacer();
    }
    if(dealer_hand > 21)
    {
        cout << "DEALER BUSTED." << endl;
        money = money + 2*bet;
        cout << "You now have $" << money << "." << endl;
        spacer();
    }
    return money;
}

int end_game(int money, int bet, int player_hand, int dealer_hand)
{
    if(player_hand == dealer_hand)
    {
        cout << "Your and the dealer have a 'Stand Off'" << endl;
        money = standoff(money, bet, player_hand, dealer_hand);
    }
    else if(player_hand < dealer_hand)
    {
        cout << "DEALER WINS." << endl;
    }
    else if(player_hand > dealer_hand)
    {
        cout << "PLAYER WINS." << endl;
        money = money + 2*bet;
    }
    cout << "You now have $" << money << "." << endl;
    spacer();
    return money;
}

bool play_again(bool blackjack_game)
{
    cout << "Would you like to play again?" << endl;
    cout << "1. Yes" << endl;
    cout << "0. No" << endl;
    cout << "Please enter numerical value...";
    blackjack_game = get_input(0, 1);
    spacer();
    return blackjack_game;
}
