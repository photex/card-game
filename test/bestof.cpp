#include <cassert>
#include <iomanip>
#include <iostream>

#include "cardgame.h"

const int MATCH_COUNT = 7;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    int result = 0;

    assert(MATCH_COUNT % 2 != 0);

    auto best_of = (MATCH_COUNT / 2) + (MATCH_COUNT % 2);

    // We start with the deck of 52 cards
    auto deck = create_deck();

    int p1_wins = 0;
    int p2_wins = 0;
    int draws = 0;

    int rounds_played = 0;
    while (rounds_played < MATCH_COUNT) {
        shuffle_deck(deck);

        auto match_result = play_match(deck);
        switch (match_result) {
        case match_result_t::player1:
            p1_wins++;
            break;
        case match_result_t::player2:
            p2_wins++;
            break;
        case match_result_t::draw:
            draws++;
            continue;
        default:
            break;
        }
        rounds_played++;

        if (p1_wins >= best_of || p2_wins >= best_of) {
            break;
        }
    }

    assert(p1_wins != p2_wins);

    std::cout << "\n\n\n------------------------------------" << std::endl;
    std::cout << "Rounds played: " << rounds_played << std::endl;
    std::cout << "P1 (" << std::setw(2) << p1_wins << ") : (" << std::setw(2) << p2_wins << ") P2 -\t";

    if (p1_wins > p2_wins) {
        std::cout << "Player 1 wins the series!";
    } else {
        std::cout << "Player 2 wins the series!";
    }
    std::cout << std::endl;

    return result;
}
