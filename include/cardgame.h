#pragma once

#include <array>
#include <cstdint>
#include <vector>

const int DECK_SIZE = 52;
const int MAX_HAND_SIZE = DECK_SIZE / 2;

using deck_t = std::array<int, DECK_SIZE>;
using player_hand_t = std::vector<int>;

enum class match_result_t {
    in_progress,
    player1,
    player2,
    draw,
};

struct match_t {
    uint32_t player1_score = 0;
    uint32_t player2_score = 0;

    player_hand_t player1_hand;
    player_hand_t player2_hand;

    bool cards_remaining() const;

    std::pair<int, int> draw_next();

    match_result_t results() const;

    void print_score() const;
};

deck_t create_deck();

void shuffle_deck(deck_t&);

void deal_cards(deck_t const& deck, player_hand_t& player1, player_hand_t& player2);

void play_match(deck_t const& deck);
