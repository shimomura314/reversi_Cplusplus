#include "othello.h"

Othello::Othello(uint8_t color) {
    change_player(color);
    black_strategy = new Strategy();
    white_strategy = new Strategy();
}

Othello::~Othello() {
    delete black_strategy;
    delete white_strategy;
}

uint8_t Othello::return_player_clr() const {
    return player_clr;
}

void Othello::change_strategy(const std::string& strategy, bool is_player) {
    /*
    Change strategy for player or opponent.

    Parameters
    ----------
    strategy : str
        Name of the strategy to be used.
    color : uint8_t
        Whether the player's strategy should be changed, by default False.
    */
    if ((is_player && (player_clr == 0)) || (!is_player && (player_clr == 1))) {
        black_strategy -> set_strategy(strategy);
    } else {
        white_strategy -> set_strategy(strategy);
    }
}

void Othello::change_player(uint8_t color) {
    player_clr = color;
}

tuple<bool, bool> Othello::process_game() {
    /*
    Process the game by updating the count, judging whether the game is over,
    and making a move by the player or the CPU, depending on whose turn it is.

    Returns
    -------
    finished, updated : Tuple[bint, bint]
        A tuple representing if the game has ended
        and if a turn was played.
    */
    update_count();

    uint64_t b_board, w_board;
    tie(b_board, w_board) = return_board();
    uint8_t turn = return_turn();

    result = judge_game(b_board, w_board);

    if (result != 3) {
        return forward_as_tuple(true, true);
    }

    if (!turn_playable(turn, b_board, w_board)) {
        skip_turn();
        return forward_as_tuple(false, false);
    }

    if ((player_clr != turn) || ((player_clr == turn) && (human_ai))) {
        if (turn == 0) {
            uint64_t select = black_strategy -> move(*this);
            play_turn(select);
        } else {
            uint64_t select = white_strategy -> move(*this);
            play_turn(select);
        }        
        return forward_as_tuple(false, true);
    } else {
        return forward_as_tuple(false, false);
    }
}

int main() {
}

// PYBIND11_MODULE(my_module, module) {
//     module.def("Main", &main); // 関数のバインド
// }