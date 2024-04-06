#include "minmax.h"

Minmax::Minmax(uint8_t d) {
    depth = d;
}


bool Minmax::touch_border(uint64_t b_board, uint64_t w_board) {
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
    uint64_t board = (b_board | w_board);
    if ((board & 0xff818181818181ff) != 0) {
        return true;
    }
    return false;
}

int Minmax::evaluate_value(uint64_t b_board, uint64_t w_board) {
    int evaluation = 0;
    bool on_border = touch_border(b_board, w_board);
    std::array<uint64_t, 2> board = {b_board, w_board};
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

tuple<int, int> Minmax::min_max(
        uint8_t turn_, uint64_t b_board, uint64_t w_board,
        uint8_t depth_, int pre_evaluation) {
    int evaluation = evaluate_value(b_board, w_board);

    if (depth_ == 0) {
        return forward_as_tuple(evaluation, -1);
    }

    vector<uint8_t> candidates = BitBoard::reversible_area_list(turn_, b_board, w_board);
    int next_evaluation;
    int max_evaluation = -2147483647;
    int min_evaluation = 2147483647;
    uint64_t new_black_board;
    uint64_t new_white_board;

    int selected = -1;

    if (BitBoard::turn_playable(turn_, b_board, w_board)) {
        for (auto candidate : candidates) {
            tie(new_black_board, new_white_board) = BitBoard::simulate_play(
                turn_, EXP2[candidate], b_board, w_board);
            int state = BitBoard::judge_game(new_black_board, new_white_board);
            if (state == 3) {  // If the game continues
                if (player_clr == turn_) {
                    next_evaluation = get<0>(min_max(
                        (uint8_t) (turn_ ^ 1), new_black_board, new_white_board,
                        (uint8_t) (depth_-1), max_evaluation
                        ));
                } else {
                    next_evaluation = get<0>(min_max(
                        (uint8_t) (turn_ ^ 1), new_black_board, new_white_board,
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
                    return forward_as_tuple(next_evaluation, candidate);
                }
            } else {
                if (pre_evaluation > next_evaluation) {
                    return forward_as_tuple(next_evaluation, candidate);
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
                (uint8_t) (turn_ ^ 1), b_board, w_board,
                (uint8_t) (depth_-1), max_evaluation
                );
        } else {
            return min_max(
                (uint8_t) (turn_ ^ 1), b_board, w_board,
                (uint8_t) (depth_-1), min_evaluation
                );
        }
    }
    if (player_clr == turn_) {
        return forward_as_tuple(max_evaluation, selected);
    } else {
        return forward_as_tuple(min_evaluation, selected);
    }
}

tuple<int, int> Minmax::min_max_debug(
        uint8_t turn_, uint64_t b_board, uint64_t w_board,
        uint8_t depth_, int pre_evaluation) {
    int evaluation = evaluate_value(b_board, w_board);

    vector<uint8_t> candidates = BitBoard::reversible_area_list(turn_, b_board, w_board);
    int next_evaluation;
    int max_evaluation = -2147483647;
    int min_evaluation = 2147483647;
    uint64_t new_black_board;
    uint64_t new_white_board;

    cout << "min_max(" << (int) turn_ <<  ", " << b_board <<  ", " << w_board;
    cout <<  ", " << (int) depth_ << ", " << pre_evaluation << ")" << endl;
    cout << "candidate(";
    for (auto candidate : candidates) {
        cout << (int) candidate << ", ";
    }
    cout << ")" << endl;
    cout << "Evaluation = " << evaluation << endl;

    if (depth_ == 0) {
        return forward_as_tuple(evaluation, -1);
    }

    int selected = -1;

    if (BitBoard::turn_playable(turn_, b_board, w_board)) {
        for (auto candidate : candidates) {
            tie(new_black_board, new_white_board) = BitBoard::simulate_play(
                turn_, EXP2[candidate], b_board, w_board);
            cout << "Put on " << (int) candidate << " -> (";
            cout << new_black_board << ", " << new_white_board << ")" << endl;
            int state = BitBoard::judge_game(new_black_board, new_white_board);
            if (state == 3) {  // If the game continues
                if (player_clr == turn_) {
                    cout << "Call min_max on status3." << endl;
                    next_evaluation = get<0>(min_max_debug(
                        (uint8_t) (turn_ ^ 1), new_black_board, new_white_board,
                        (uint8_t) (depth_-1), max_evaluation
                        ));
                } else {
                    cout << "Call min_max on status3." << endl;
                    next_evaluation = get<0>(min_max_debug(
                        (uint8_t) (turn_ ^ 1), new_black_board, new_white_board,
                        (uint8_t) (depth_-1), min_evaluation
                        ));
                }
            } else if (state == 2) {
                cout << "Status draw." << endl;
                next_evaluation = 0;
            } else if (state == player_clr) {
                cout << "Status win." << endl;
                next_evaluation = 2147483646;
            } else {
                cout << "Status lose." << endl;
                next_evaluation = -2147483646;
            }

            // alpha-bata method (pruning)
            if (player_clr == turn_) {
                if (next_evaluation > pre_evaluation) {
                    cout << "Alpha: next_evaluation > pre_evaluation (";
                    cout << next_evaluation << ", " << pre_evaluation << ")" << endl;
                    return forward_as_tuple(next_evaluation, candidate);
                }
            } else {
                if (pre_evaluation > next_evaluation) {
                    cout << "Beta: pre_evaluation > next_evaluation (";
                    cout << pre_evaluation << ", " << next_evaluation << ")" << endl;
                    return forward_as_tuple(next_evaluation, candidate);
                }
            }

            cout << "Check: (next, min, max) = (";
            cout << next_evaluation << ", " << min_evaluation << ", " << max_evaluation << ")" << endl;
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
            cout << "Skip" <<  endl;
            return min_max_debug(
                (uint8_t) (turn_ ^ 1), b_board, w_board,
                (uint8_t) (depth_-1), max_evaluation
                );
        } else {
            cout << "Skip" <<  endl;
            return min_max_debug(
                (uint8_t) (turn_ ^ 1), b_board, w_board,
                (uint8_t) (depth_-1), min_evaluation
                );
        }
    }
    if (player_clr == turn_) {
        cout << "Final: depth = " << (int) depth_ << ", evaluation = ";
        cout << max_evaluation << ", candidate = " << (int) selected << endl;
        return forward_as_tuple(max_evaluation, selected);
    } else {
        cout << "Final: depth = " << (int) depth_ << ", evaluation = ";
        cout << max_evaluation << ", candidate = " << (int) selected << endl;
        return forward_as_tuple(min_evaluation, selected);
    }
}

uint8_t Minmax::move(const BitBoard& board) {
    tuple <uint64_t, uint64_t> boards = board.return_board();
    uint8_t turn = board.return_turn();
    player_clr = turn;
    uint8_t select;
    select = std::get<1>(
        min_max(turn, std::get<0>(boards), std::get<1>(boards), depth, 2147483647));

    if (select == 255) {
        min_max_debug(turn, std::get<0>(boards), std::get<1>(boards), depth, 2147483647);
        cout << "Selected: " << (int) select << " from (turn: " << (int) turn;
        cout << ", black: " << std::get<0>(boards);
        cout << ", white: " << std::get<1>(boards) << ")" << endl;
    }
    return select;
    // return std::get<1>(
    //     min_max(turn, std::get<0>(boards), std::get<1>(boards), depth, 2147483647));
}