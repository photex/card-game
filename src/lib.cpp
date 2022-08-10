
// I wouldn't typically use iostreams for logging in a library
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <random>
#include <utility>

#include "cardgame.h"

#include <assert.h>

#define DEBUG_OUTPUT

bool round_t::cards_remaining() const
{
    return !player1_hand.empty() && !player2_hand.empty();
}

std::pair<int, int> round_t::draw_next()
{
    auto result = std::make_pair(player1_hand.back(), player2_hand.back());

    player1_hand.pop_back();
    player2_hand.pop_back();

    return result;
}

round_result_t round_t::results() const
{
    auto result = round_result_t::draw;
    if (cards_remaining()) {
        result = round_result_t::in_progress;
    } else if (player1_score > player2_score) {
        result = round_result_t::player1;
    } else if (player1_score < player2_score) {
        result = round_result_t::player2;
    }
    return result;
}

void round_t::print_score() const
{
    std::cout << "Score: P1 (" << player1_score << ") vs P2 (" << player2_score << ")\n\n";
}

template <typename T>
void print_cards(T const& cards, char const* msg)
{
#ifdef DEBUG_OUTPUT
    std::cout << "## " << msg << ":\n## ";
    for (auto const& card : cards) {
        std::cout << std::setw(3) << card;
    }
    std::cout << "\n"
              << std::endl;
#endif
}

deck_t create_deck()
{
    // Instructions were:
    // "We start with the deck of 52 cards, each uniquely numbered from 1 to 53"
    // So, card I'm just setting the last card to 53 instead of 52.

    deck_t deck;
    std::iota(deck.begin(), deck.end(), 1);
    deck[DECK_SIZE - 1] = 53;

    print_cards(deck, "Initial Deck");

    return deck;
}

void shuffle_deck(deck_t& deck)
{
    std::mt19937 generator { std::random_device {}() };
    std::shuffle(deck.begin(), deck.end(), generator);
    print_cards(deck, "Shuffled Deck");
}

void deal_cards(deck_t const& deck, player_hand_t& player1,
    player_hand_t& player2)
{
    uint32_t step = 0;
    for (auto const& card : deck) {
        if (step % 2) {
            player1.push_back(card);
        } else {
            player2.push_back(card);
        }

        step++;
    }

    assert(player1.size() == MAX_HAND_SIZE);

    assert(player2.size() == MAX_HAND_SIZE);
}

void play_round(deck_t const& deck)
{
    round_t round;

    deal_cards(deck, round.player1_hand, round.player2_hand);

    print_cards(round.player1_hand, "Player 1 Hand");
    print_cards(round.player2_hand, "Player 2 Hand");

    while (round.cards_remaining()) {
        const auto [player1_draw, player2_draw] = round.draw_next();
        if (player1_draw > player2_draw) {
            round.player1_score++;
        } else {
            round.player2_score++;
        }
    }

    round.print_score();

    switch (round.results()) {
    case round_result_t::in_progress: {
        std::cerr << "Round finished but is still in progress?" << std::endl;
    } break;
    case round_result_t::player1: {
        std::cout << "Player 1 Wins!";
    } break;
    case round_result_t::player2: {
        std::cout << "Player 2 Wins!";
    } break;
    case round_result_t::draw: {
        std::cout << "Draw!";
    } break;
    }

    std::cout << std::endl;
}
