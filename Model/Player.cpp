#include "Player.hpp"
#include <iostream>

Player::Player()
{
    // nie powinno sie zdarzyc
}
Player::Player(unsigned s)
{
    seat = s;
    cash_in_game = 0;
    cash_available = START_BUDGET;
    bet_this_turn = 0;
    is_playing = false;
    is_active = false;
    all_in = false;
    //left = false;
	if(s==0)
		name = "Red";
	else
		name = "Blue";
}
void Player::bet(unsigned cash, unsigned& update_bet_this_turn)
{
    std::cout<< name << " betting " << cash << "\n";
    cash_available -= cash;
    cash_in_game += cash;
    bet_this_turn += cash;
    //aktualizacja aktualnej stawki zakladu
    update_bet_this_turn = std::max(update_bet_this_turn,bet_this_turn);
}