#include "cardgame.h"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    int result = 0;

    // We start with the deck of 52 cards
    auto deck = create_deck();

    // The deck is shuffled
    shuffle_deck(deck);

    play_match(deck);

    return result;
}
