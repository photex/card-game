#include "cardgame.h"

int main(int argc, char* argv[])
{
    int result = 0;

    player_hand_t player1, player2;
    auto deck = create_deck();

    shuffle_deck(deck);

    play_round(deck);

    return result;
}
