#include "random.h"

uint8_t Random::move(const BitBoard& board) {
    BitBoard::Boards present_boards;
    present_boards = board.return_board();
    uint8_t turn = board.return_turn();

    std::vector<uint8_t> candidates = board.reversible_area_list(turn, present_boards);
    return candidates[rand() % candidates.size()];
}