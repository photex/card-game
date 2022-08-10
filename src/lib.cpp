
#include <iomanip>
#include <iostream>

#include <algorithm>
#include <random>
#include <utility>

#include "cardgame.h"

#include <assert.h>

#define DEBUG_OUTPUT

bool match_t::cards_remaining() const
{
    return !player1_hand.empty() && !player2_hand.empty();
}

std::pair<int, int> match_t::draw_next()
{
    auto result = std::make_pair(player1_hand.back(), player2_hand.back());

    player1_hand.pop_back();
    player2_hand.pop_back();

    return result;
}

match_result_t match_t::results() const
{
    // At the end of the game the player who has the most points wins

    auto result = match_result_t::draw;
    if (cards_remaining()) {
        result = match_result_t::in_progress;
    } else if (player1_score > player2_score) {
        result = match_result_t::player1;
    } else if (player1_score < player2_score) {
        result = match_result_t::player2;
    }
    return result;
}

void match_t::print_score() const
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
    // "We start with the deck of 52 cards, each uniquely numbered from 1 to 53"

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

void play_match(deck_t const& deck)
{
    match_t match;

    // We deal out those cards between the 2 players. Each player gets half the deck.
    deal_cards(deck, match.player1_hand, match.player2_hand);

    print_cards(match.player1_hand, "Player 1 Hand");
    print_cards(match.player2_hand, "Player 2 Hand");

    // Rounds are played until all the cards are discarded.
    while (match.cards_remaining()) {
        // On each turn of the game, both players turn over their topmost card and they compare the value of those cards.
        // The player with the higher valued card "wins" the round and gets a point.
        // The two cards being compared are discarded.

        const auto [player1_draw, player2_draw] = match.draw_next();
        // When each round is played you should print each player's card value along with an indication of which player won that round.
        std::cout << "P1 (" << std::setw(2) << player1_draw << ") : (" << std::setw(2) << player2_draw << ") P2 \t- ";
        if (player1_draw > player2_draw) {
            match.player1_score++;
            std::cout << "Player 1 wins the round.";
        } else {
            match.player2_score++;
            std::cout << "Player 2 wins the round.";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    // "When all rounds are played you should print each player's final score along with an indication of which player won overall."

    match.print_score();

    switch (match.results()) {
    case match_result_t::in_progress: {
        std::cerr << "Match finished but is still in progress?" << std::endl;
    } break;
    case match_result_t::player1: {
        std::cout << "Player 1 Wins!";
    } break;
    case match_result_t::player2: {
        std::cout << "Player 2 Wins!";
    } break;
    case match_result_t::draw: {
        std::cout << "Draw!";
    } break;
    }

    std::cout << std::endl;
}
