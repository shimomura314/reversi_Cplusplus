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

std::tuple<bool, bool> Othello::process_game() {
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

    BitBoard::Boards present_boards;
    present_boards = return_board();
    uint8_t turn = return_turn();

    result = judge_game(present_boards);

    if (result != 3) {
        return std::forward_as_tuple(true, true);
    }

    if (!turn_playable(turn, present_boards)) {
        skip_turn();
        return std::forward_as_tuple(false, false);
    }

    if ((player_clr != turn) || ((player_clr == turn) && (human_ai))) {
        if (turn == 0) {
            uint64_t select = black_strategy -> move(*this);
            play_turn(select);
        } else {
            uint64_t select = white_strategy -> move(*this);
            play_turn(select);
        }        
        return std::forward_as_tuple(false, true);
    } else {
        return std::forward_as_tuple(false, false);
    }
}
