//
//  blackjack.hpp
//  CasinoGames
//
//  Created by Maksim Sharoika on 2021-07-11.
//

#ifndef blackjack_hpp
#define blackjack_hpp

// casino functions
int get_input(int, int);
void spacer();

// black-jack function
int blackjack(int money);

// blackjack sub-functions
void restart_cards(int[], int[]);
int get_bet(int);
void generate_cards(int[], int[]);

int ask_player_move();

int calculate_dealer_hand(int, int[]);
int calculate_player_hand(int, int[]);

void inform_player_cards(int, int[]);
void inform_dealer_cards(int, int[]);

void inform_player_total(int);
void inform_dealer_total(int);

int standoff(int, int, int, int);
int bust(int, int, int, int);
int end_game(int, int, int, int);

bool play_again(bool);

#endif /* blackjack_hpp */
