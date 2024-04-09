#include "minmax.h"

Minmax::Minmax(uint8_t d) {
    depth = d;
}


bool Minmax::touch_border(BitBoard::Boards boards) {
    /*
    Check if any stone on the board is touching the border.

    Parameters:
    -----------
    black_board : uint64_t
        Bitboard representing the current state of black stones on the board.
    white_board : uint64_t
        Bitboard representing the current state of white stones on the board.

    Returns:
    --------
    int
        Returns 1 if a stone is touching the border, otherwise returns 0.
    */
    uint64_t board = (boards.black | boards.white);
    if ((board & 0xff818181818181ff) != 0) {
        return true;
    }
    return false;
}

int Minmax::evaluate_value(BitBoard::Boards boards) {
    int evaluation = 0;
    bool on_border = touch_border(boards);
    std::array<uint64_t, 2> board = {boards.black, boards.white};
    for (int i = 0; i < 64; ++i) {
        if (on_border) {
            if (EXP2[i] & board[player_clr]){
                evaluation += EVAL_TBL1[i];
            }
            if (EXP2[i] & board[player_clr ^ 1]){
                evaluation -= EVAL_TBL1[i];
            }
        } else {
            if (EXP2[i] & board[player_clr]){
                evaluation += EVAL_TBL2[i];
            }
            if (EXP2[i] & board[player_clr ^ 1]){
                evaluation -= EVAL_TBL2[i];
            }
        }
    }
    return evaluation;
}

std::tuple<int, int> Minmax::min_max(
        uint8_t turn_, BitBoard::Boards boards, uint8_t depth_, int pre_evaluation) {
    int evaluation = evaluate_value(boards);

    if (depth_ == 0) {
        return std::forward_as_tuple(evaluation, -1);
    }

    std::vector<uint8_t> candidates = BitBoard::reversible_area_list(turn_, boards);
    int next_evaluation;
    int max_evaluation = -2147483647;
    int min_evaluation = 2147483647;
    BitBoard::Boards new_boards;

    int selected = -1;

    if (BitBoard::turn_playable(turn_, boards)) {
        for (auto candidate : candidates) {
            new_boards = BitBoard::simulate_play(
                turn_, EXP2[candidate], boards);
            int state = BitBoard::judge_game(new_boards);
            if (state == 3) {  // If the game continues
                if (player_clr == turn_) {
                    next_evaluation = std::get<0>(min_max(
                        (uint8_t) (turn_ ^ 1), new_boards,
                        (uint8_t) (depth_-1), max_evaluation
                        ));
                } else {
                    next_evaluation = std::get<0>(min_max(
                        (uint8_t) (turn_ ^ 1), new_boards,
                        (uint8_t) (depth_-1), min_evaluation
                        ));
                }
            } else if (state == 2) {
                next_evaluation = 0;
            } else if (state == player_clr) {
                next_evaluation = 2147483646;
            } else {
                next_evaluation = -2147483646;
            }

            // alpha-bata method (pruning)
            if (player_clr == turn_) {
                if (next_evaluation > pre_evaluation) {
                    return std::forward_as_tuple(next_evaluation, candidate);
                }
            } else {
                if (pre_evaluation > next_evaluation) {
                    return std::forward_as_tuple(next_evaluation, candidate);
                }
            }

            if (player_clr == turn_) {
                if (next_evaluation > max_evaluation) {
                    max_evaluation = next_evaluation;
                    selected = candidate;
                }
            } else {
                if (min_evaluation > next_evaluation) {
                    min_evaluation = next_evaluation;
                    selected = candidate;
                }
            }
        }
    } else {
        if (player_clr == turn_) {
            return min_max(
                (uint8_t) (turn_ ^ 1), boards,
                (uint8_t) (depth_-1), max_evaluation
                );
        } else {
            return min_max(
                (uint8_t) (turn_ ^ 1), boards,
                (uint8_t) (depth_-1), min_evaluation
                );
        }
    }
    if (player_clr == turn_) {
        return std::forward_as_tuple(max_evaluation, selected);
    } else {
        return std::forward_as_tuple(min_evaluation, selected);
    }
}

std::tuple<int, int> Minmax::min_max_debug(
        uint8_t turn_, BitBoard::Boards boards,
        uint8_t depth_, int pre_evaluation) {
    int evaluation = evaluate_value(boards);

    std::vector<uint8_t> candidates = BitBoard::reversible_area_list(turn_, boards);
    int next_evaluation;
    int max_evaluation = -2147483647;
    int min_evaluation = 2147483647;
    BitBoard::Boards new_boards;

    std::cout << "min_max(" << (int) turn_ <<  ", " << boards.black <<  ", " << boards.white;
    std::cout <<  ", " << (int) depth_ << ", " << pre_evaluation << ")" << std::endl;
    std::cout << "candidate(";
    for (auto candidate : candidates) {
        std::cout << (int) candidate << ", ";
    }
    std::cout << ")" << std::endl;
    std::cout << "Evaluation = " << evaluation << std::endl;

    if (depth_ == 0) {
        return std::forward_as_tuple(evaluation, -1);
    }

    int selected = -1;

    if (BitBoard::turn_playable(turn_, boards)) {
        for (auto candidate : candidates) {
            new_boards = BitBoard::simulate_play(
                turn_, EXP2[candidate], boards);
            std::cout << "Put on " << (int) candidate << " -> (";
            std::cout << new_boards.black << ", " << new_boards.white << ")" << std::endl;
            int state = BitBoard::judge_game(new_boards);
            if (state == 3) {  // If the game continues
                if (player_clr == turn_) {
                    std::cout << "Call min_max on status3." << std::endl;
                    next_evaluation = std::get<0>(min_max_debug(
                        (uint8_t) (turn_ ^ 1), new_boards,
                        (uint8_t) (depth_-1), max_evaluation
                        ));
                } else {
                    std::cout << "Call min_max on status3." << std::endl;
                    next_evaluation = std::get<0>(min_max_debug(
                        (uint8_t) (turn_ ^ 1), new_boards,
                        (uint8_t) (depth_-1), min_evaluation
                        ));
                }
            } else if (state == 2) {
                std::cout << "Status draw." << std::endl;
                next_evaluation = 0;
            } else if (state == player_clr) {
                std::cout << "Status win." << std::endl;
                next_evaluation = 2147483646;
            } else {
                std::cout << "Status lose." << std::endl;
                next_evaluation = -2147483646;
            }

            // alpha-bata method (pruning)
            if (player_clr == turn_) {
                if (next_evaluation > pre_evaluation) {
                    std::cout << "Alpha: next_evaluation > pre_evaluation (";
                    std::cout << next_evaluation << ", " << pre_evaluation << ")" << std::endl;
                    return std::forward_as_tuple(next_evaluation, candidate);
                }
            } else {
                if (pre_evaluation > next_evaluation) {
                    std::cout << "Beta: pre_evaluation > next_evaluation (";
                    std::cout << pre_evaluation << ", " << next_evaluation << ")" << std::endl;
                    return std::forward_as_tuple(next_evaluation, candidate);
                }
            }

            std::cout << "Check: (next, min, max) = (";
            std::cout << next_evaluation << ", " << min_evaluation << ", " << max_evaluation << ")" << std::endl;
            if (player_clr == turn_) {
                if (next_evaluation > max_evaluation) {
                    max_evaluation = next_evaluation;
                    selected = candidate;
                }
            } else {
                if (min_evaluation > next_evaluation) {
                    min_evaluation = next_evaluation;
                    selected = candidate;
                }
            }
        }
    } else {
        if (player_clr == turn_) {
            std::cout << "Skip" <<  std::endl;
            return min_max_debug(
                (uint8_t) (turn_ ^ 1), boards,
                (uint8_t) (depth_-1), max_evaluation
                );
        } else {
            std::cout << "Skip" <<  std::endl;
            return min_max_debug(
                (uint8_t) (turn_ ^ 1), boards,
                (uint8_t) (depth_-1), min_evaluation
                );
        }
    }
    if (player_clr == turn_) {
        std::cout << "Final: depth = " << (int) depth_ << ", evaluation = ";
        std::cout << max_evaluation << ", candidate = " << (int) selected << std::endl;
        return std::forward_as_tuple(max_evaluation, selected);
    } else {
        std::cout << "Final: depth = " << (int) depth_ << ", evaluation = ";
        std::cout << max_evaluation << ", candidate = " << (int) selected << std::endl;
        return std::forward_as_tuple(min_evaluation, selected);
    }
}

uint8_t Minmax::move(const BitBoard& board) {
    BitBoard::Boards present_boards = board.return_board();
    uint8_t turn = board.return_turn();
    player_clr = turn;
    uint8_t select;
    select = std::get<1>(
        min_max(turn, present_boards, depth, 2147483647));

    if (select == 255) {
        min_max_debug(turn, present_boards, depth, 2147483647);
        std::cout << "Selected: " << (int) select << " from (turn: " << (int) turn;
        std::cout << ", black: " << present_boards.black;
        std::cout << ", white: " << present_boards.white << ")" << std::endl;
    }
    return select;
    // return std::get<1>(
    //     min_max(turn, std::get<0>(boards), std::get<1>(boards), depth, 2147483647));
}