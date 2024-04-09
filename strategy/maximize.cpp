#include "maximize.h"

uint8_t Maximize::move(const BitBoard& board) {
    /*
    A strategy to try to maximize the number of disks you have.

    Attributes
    ----------
    None

    Methods
    -------
    put_disk(othello):
        Given an Othello game board, finds all the legal moves and chooses a random move that maximizes the number of
        disks owned by the current player.

    Parameters
    ----------
    othello : instance of the Othello class
        The current game state

    Returns:
    --------
    int : the index of the chosen move
    */
    BitBoard::Boards present_boards;
    present_boards = board.return_board();
    uint8_t turn = board.return_turn();
    std::vector<uint8_t> candidates = board.reversible_area_list(turn, present_boards);
    std::vector<uint8_t> max_strategy;
    uint8_t max_merit = 0;

    BitBoard::Boards new_boards;
    std::tuple<uint8_t, uint8_t> counter;
    uint8_t myNum;

    for (auto candidate: candidates) {
        new_boards = board.simulate_play(turn, candidate, present_boards);
        counter = board.count_disks(new_boards);
        if (turn == 0) {
            myNum = std::get<0>(counter);
        } else {
            myNum = std::get<1>(counter);
        }

        if (max_merit < myNum) {
            max_merit = myNum;
            max_strategy.clear();
            max_strategy.push_back(candidate);
        } else if (max_merit == myNum) {
            max_strategy.push_back(candidate);
        }
    }
    return max_strategy[rand() % max_strategy.size()];
}