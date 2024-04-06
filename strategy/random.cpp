#include "random.h"

uint8_t Random::move(const BitBoard& board) {
    uint64_t b_board, w_board;
    tie(b_board, w_board) = board.return_board();
    uint8_t turn = board.return_turn();

    vector<uint8_t> candidates = board.reversible_area_list(turn, b_board, w_board);
    return candidates[rand() % candidates.size()];
}