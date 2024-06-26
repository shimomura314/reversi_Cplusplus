#include "bitboard.h"

BitBoard::BitBoard() {
    board_log.emplace_back(
        Boards{0x0000000810000000, 0x0000001008000000});
}

uint8_t BitBoard::bit_count(uint64_t x) {
    /*
    Count the number of bit awaking.

    Parameters
    ----------
    x : uint64_t
        An unsigned 64-bit integer which represents the location of disk.

    Returns
    -------
    uint64_t
        The number of bits in the integer.

    Notes
    -----
    This method uses the "population count" algorithm to count
    the number of bits in an integer.
    It works by first distributing the bits by 2-bit,
    then adding the upper and lower bits at each level
    until the entire 64-bit integer is summed up.

    Examples
    --------
    >>> game = OthelloBoard()
    >>> game._bit_count(0x0000000810000000ULL)
    3
    */
    // Distributing by 2-bit, express the number of bits using 2-bit.
    x -= (x >> 1) & 0x5555555555555555ULL;
    // Upper 2-bit + lower 2-bit.
    x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
    // Upper 4-bit + lower 4-bit.
    x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    // Upper 8-bit + lower 8-bit.
    x += x >> 8;
    // Upper 16-bit + lower 16-bit.
    x += x >> 16;
    // Upper 32-bit + lower 32-bit.
    x += x >> 32;
    return uint8_t(x & 0x0000007f);
    // return __builtin_popcountll(x);
}

uint64_t BitBoard::check_surround(uint64_t x, uint8_t direction) {
    /*
    Check neighbor disk is reversible or not.

    Parameters
    ----------
    put_loc : uint64_t
        The location where the player puts their disk represented
        as a 64-bit unsigned integer.
    direction : int
        An integer representing the direction to check.
        It should be an integer in the range [0, 7].
        0: upper, 1: upper right, 2: right, 3: lower right,
        4: lower,5: lower left, 6: left, 7: upper left.
    */
    
    if (direction == 0) {  // Upper
        return (x << 8) & 0xffffffffffffff00;
    } else if (direction == 1){  // Upper right
        return (x << 7) & 0x7f7f7f7f7f7f7f00;
    } else if (direction == 2){  // Right
        return (x >> 1) & 0x7f7f7f7f7f7f7f7f;
    } else if (direction == 3){  // Lower right
        return (x >> 9) & 0x007f7f7f7f7f7f7f;
    } else if (direction == 4){  // Lower
        return (x >> 8) & 0x00ffffffffffffff;
    } else if (direction == 5){  // Lower left
        return (x >> 7) & 0x00fefefefefefefe;
    } else if (direction == 6){  // Left
        return (x << 1) & 0xfefefefefefefefe;
    }
    // Upper left
    return (x << 9) & 0xfefefefefefefe00;
}

std::tuple<uint8_t, uint8_t> BitBoard::count_disks(BitBoard::Boards boards) {
    /*
    Counts the number of disks on the board for each player.

    Parameters
    ----------
    b_board, w_board : uint64_t, optional
        The bitboard representing the black/white player's disks.
        If not given, the internal board of the instance is used.

    Returns
    -------
    Tuple[int, int]
        A tuple with the number of disks for the players, respectively.
    */
    return std::forward_as_tuple(
        bit_count(boards.black), bit_count(boards.white));
}

uint64_t BitBoard::reversible_area(
        uint8_t turn_, BitBoard::Boards boards) {
    /*
    Calculate the reversible area of the board for the given turn.

    Parameters
    ----------
    turn : unsigned char
        The turn to calculate the reversible area for.
    b_board, w_board : uint64_t
        The boards represented as a 64-bit integer.
        Defaults to 0.

    Returns
    -------
    reversible : uint64_t
        The reversible area of the board for the given turn.
    */
    uint64_t board[2] = {boards.black, boards.white};
    uint64_t blank_board = ~(boards.black | boards.white);
    uint64_t horiz_brd = board[turn_ ^ 1] & 0x7e7e7e7e7e7e7e7e;
    uint64_t vert_brd = board[turn_ ^ 1] & 0x00ffffffffffff00;
    uint64_t all_border = board[turn_ ^ 1] & 0x007e7e7e7e7e7e00;

    // Upper
    uint64_t one_rv = horiz_brd & (board[turn_] << 1);
    one_rv |= horiz_brd & (one_rv << 1);
    one_rv |= horiz_brd & (one_rv << 1);
    one_rv |= horiz_brd & (one_rv << 1);
    one_rv |= horiz_brd & (one_rv << 1);
    one_rv |= horiz_brd & (one_rv << 1);
    uint64_t reversible = blank_board & (one_rv << 1);

    // Lower
    one_rv = horiz_brd & (board[turn_] >> 1);
    one_rv |= horiz_brd & (one_rv >> 1);
    one_rv |= horiz_brd & (one_rv >> 1);
    one_rv |= horiz_brd & (one_rv >> 1);
    one_rv |= horiz_brd & (one_rv >> 1);
    one_rv |= horiz_brd & (one_rv >> 1);
    reversible |= blank_board & (one_rv >> 1);

    // Left
    one_rv = vert_brd & (board[turn_] << 8);
    one_rv |= vert_brd & (one_rv << 8);
    one_rv |= vert_brd & (one_rv << 8);
    one_rv |= vert_brd & (one_rv << 8);
    one_rv |= vert_brd & (one_rv << 8);
    one_rv |= vert_brd & (one_rv << 8);
    reversible |= blank_board & (one_rv << 8);

    // Right
    one_rv = vert_brd & (board[turn_] >> 8);
    one_rv |= vert_brd & (one_rv >> 8);
    one_rv |= vert_brd & (one_rv >> 8);
    one_rv |= vert_brd & (one_rv >> 8);
    one_rv |= vert_brd & (one_rv >> 8);
    one_rv |= vert_brd & (one_rv >> 8);
    reversible |= blank_board & (one_rv >> 8);

    // Upper right
    one_rv = all_border & (board[turn_] << 7);
    one_rv |= all_border & (one_rv << 7);
    one_rv |= all_border & (one_rv << 7);
    one_rv |= all_border & (one_rv << 7);
    one_rv |= all_border & (one_rv << 7);
    one_rv |= all_border & (one_rv << 7);
    reversible |= blank_board & (one_rv << 7);

    // Upper left
    one_rv = all_border & (board[turn_] << 9);
    one_rv |= all_border & (one_rv << 9);
    one_rv |= all_border & (one_rv << 9);
    one_rv |= all_border & (one_rv << 9);
    one_rv |= all_border & (one_rv << 9);
    one_rv |= all_border & (one_rv << 9);
    reversible |= blank_board & (one_rv << 9);

    // Lower right
    one_rv = all_border & (board[turn_] >> 9);
    one_rv |= all_border & (one_rv >> 9);
    one_rv |= all_border & (one_rv >> 9);
    one_rv |= all_border & (one_rv >> 9);
    one_rv |= all_border & (one_rv >> 9);
    one_rv |= all_border & (one_rv >> 9);
    reversible |= blank_board & (one_rv >> 9);

    // Lower left
    one_rv = all_border & (board[turn_] >> 7);
    one_rv |= all_border & (one_rv >> 7);
    one_rv |= all_border & (one_rv >> 7);
    one_rv |= all_border & (one_rv >> 7);
    one_rv |= all_border & (one_rv >> 7);
    one_rv |= all_border & (one_rv >> 7);
    reversible |= blank_board & (one_rv >> 7);
    return reversible;
}

std::vector<uint8_t> BitBoard::reversible_area_list(
        uint8_t turn_, Boards boards) {
    uint64_t reversible = reversible_area(turn_, boards);
    std::vector<uint8_t> candidates;
    for (uint8_t i = 0; i < 64; ++i) {
        if (reversible & exp2[i]) {
            candidates.push_back(i);
        }
    }
    return candidates;
}

bool BitBoard::is_reversible(
        uint64_t put_loc, uint8_t turn_, Boards boards) {
    /*
    Check if the put_loc is reversible for the given turn.

    Parameters
    ----------
    turn : unsigned char
        Current player's turn. `0` for black, `1` for white.
    put_loc : uint64_t
        The bitboard position to check reversibility.
    b_board, w_board : uint64_t, optional
        Bitboard representing the player's pieces on the board.
        Default is `0`.

    Returns
    -------
    bool
        `True` if the put_loc is reversible, `False` otherwise.
    */
    return (put_loc & reversible_area(turn_, boards)) == put_loc;
}

bool BitBoard::turn_playable(uint8_t turn_, Boards boards) {
    /*
    Return wheather you can put disk or not.

    Parameters
    ----------
    turn : unsigned char
        The turn of the player to check. 0 for black, 1 for white.
    black_board, white_board : uint64_t, optional
        Bitboards representing the stones.
        Defaults to 0, in which case the current boards of the game will be used.
    
    Returns
    -------
    np.bool_
        True if the player has a valid move to make, False otherwise.
    */
    return reversible_area(turn_, boards) != 0;

}

int BitBoard::judge_game(Boards boards) {
    /*
    Determines the outcome of the game based on the current state of the board.

    Parameters
    ----------
    player : int, optional
        The score of the current player, defaults to 0.
    opponent : int, optional
        The score of the opposing player, defaults to 0.

    Returns
    -------
    bool
        Returns True if the game is over, otherwise False.
    */
    uint64_t black, white;
    uint8_t count_b, count_w;
    black = reversible_area(0, boards);
    white = reversible_area(1, boards);
    std::tie(count_b, count_w) = count_disks(boards);
    if (black == 0 && white == 0) {
        if (count_b == count_w) {
            return 2;
        } else if (count_b > count_w) {
            return 0;
        } else {
            return 1;
        }
    }
    return 3;
}

BitBoard::Boards BitBoard::return_board() const {
    /*
    Returns the current board of the game.

    Returns
    -------
    board : tuple of uint64_t
        A tuple of the black board and white board.
    */
    return BitBoard::boards_state;
}

uint8_t BitBoard::return_turn() const {
    /*
    Returns the current turn of the game.

    Returns
    -------
    int
        An integer representing the current turn,
        where 0 represents the black and 1 represents the white.
    */
    return turn;
}

uint8_t BitBoard::return_result() const {
    /*
    Returns the game result.

    Returns
    -------
    int
        0: Black
        1: White
        2: Draw
        3: Start
    */
    return result;
}

std::array<int, 64> BitBoard::display_board() const {
    /*
    Calculate 2-dimensional arrays to be used for board display.

    Returns
    -------
    list
        A list of lists with dimensions 8 x 8 where 1 represents a black disk,
        -1 represents a white disk, and 0 represents an empty cell.
    */
    BitBoard::Boards copied_boards = return_board();
    uint64_t b_board, w_board;
    std::array<int, 64> board_list;

    b_board = copied_boards.black;
    w_board = copied_boards.white;
    for (uint8_t i = 0; i < 8; ++i){
        for (uint8_t j = 0; j < 8; ++j){
            if (b_board & 1) {
                board_list[i + j*8] = 0;
            } else if (w_board & 1) {
                board_list[i + j*8] = 1;
            } else {
                board_list[i + j*8] = 2;
            }
            b_board = b_board >> 1;
            w_board = w_board >> 1;
        }
    }
    return board_list;
}

void BitBoard::load_board(Boards boards) {
    /*
    Updates the game board with the provided black and white board configurations.

    Parameters
    ----------
    b_board, w_board : int
        The bitboard configuration of the black/white player.

    Returns
    -------
    None
    */
    boards_state = boards;
}

void BitBoard::load_state() {
    /*
    Load the current game state with the given board configuration and board history.

    Parameters
    ----------
    b_board : uint64_t
        The bitboard representing the black player's pieces.
    w_board : uint64_t
        The bitboard representing the white player's pieces.
    board_log : list
        The list of previous board states.
    board_back : list
        The list of next board states.

    Returns
    -------
    None
    */
    load_board({status.GS_b_board, status.GS_w_board});
    board_log = status.GS_board_log;
    board_back = status.GS_board_back;
}

void BitBoard::save_state(){
    /*
    Returns the current board of the game.

    Returns
    -------
    board : tuple of uint64_t
        A tuple of the black board and white board.
    */
    status = {
        boards_state.black, boards_state.white, board_log, board_back,
    };
}

bool BitBoard::undo_turn() {
    /*
    Undo the last turn.

    Returns:
        bint: True if successful, False otherwise.
    */
    if (board_log.size() < 2) {
        return false;
    }

    BitBoard::Boards lastBoard;

    lastBoard = board_log.back();
    board_back.push_back(lastBoard);
    board_log.pop_back();
    lastBoard = board_log.back();
    board_back.push_back(lastBoard);
    board_log.pop_back();
    lastBoard = board_log.back();
    load_board({lastBoard.black, lastBoard.white});
    return true;
}

bool BitBoard::redo_turn() {
    /*
    Redo the last undoed turn.

    Returns:
    - True if the board was advanced successfully.
    - False if there is no board to advance.
    */
    if (board_back.empty()) {
        return false;
    }

    BitBoard::Boards lastBoard;

    lastBoard = board_back.back();
    board_log.push_back(lastBoard);
    board_back.pop_back();
    lastBoard = board_back.back();
    board_log.push_back(lastBoard);
    board_back.pop_back();
    load_board({lastBoard.black, lastBoard.white});
    return true;
}

BitBoard::Boards BitBoard::simulate_play(
        uint8_t turn, uint64_t put_loc, Boards boards) {
    /*

    Simulates a play of Othello by updating the current board state.

    Parameters
    ----------
    turn : int
        The player who is making the play. 0 for black, 1 for white.
    put_loc : uint64_t
        The location where the player puts their disk represented
        as a 64-bit unsigned integer.
    black_board, white_board : uint64_t, optional
        Bitboard representing player's discs.
        Default is 0, which means use the internal state of the board.

    Returns
    -------
    tuple of uint64_t
        A tuple of updated black and white bitboards after the player's move.
    */
    uint64_t board[2] = {boards.black, boards.white};
    uint64_t reverse_bit = 0;
    uint64_t reverse_bit_;
    uint64_t border_bit;

    for (uint8_t direction = 0; direction < 8; ++direction){
        reverse_bit_ = 0;
        border_bit = check_surround(put_loc, direction);
        while (border_bit & board[turn ^ 1]) {
            reverse_bit_ |= border_bit;
            border_bit = check_surround(border_bit, direction);
        }
        // If player's disk is opposite side.
        if (border_bit & board[turn]) {
            reverse_bit |= reverse_bit_;
        }
    }
    board[turn] ^= (put_loc | reverse_bit);
    board[turn ^ 1] ^= reverse_bit;

    return {board[0], board[1]};
}

void BitBoard::play_turn(uint8_t put_loc) {
    /*
    Play a turn with the given location on the board.

    Parameters
    ----------
    put_loc : int
        Location to put the piece on the board, from 0 to 63.

    Raises
    ------
    AssertionError
        If the input value is not within 0 to 63.
    ValueError
        If the input value is not reversible.

    Returns
    -------
    None
    */
    if (put_loc > 63) {
        throw std::out_of_range("put_loc must be between 0 and 63.");
    }

    // cdef uint64_t put_loc_ = 1i64 << put_loc
    uint64_t put_loc_ = exp2[put_loc];
    BitBoard::Boards next_boards_state;

    // If input value is not valid, raise an error.
    if (!is_reversible(put_loc_, turn, boards_state)) {
        throw std::invalid_argument("Move is not reversible.");
    }

    next_boards_state = simulate_play(
        turn, put_loc_, boards_state);

    // Update boards.
    load_board(next_boards_state);
    pass_cnt[turn] = 0;
    turn ^= 1;

    // Update log
    board_log.push_back(next_boards_state);
    board_back.clear();
}

void BitBoard::skip_turn() {
    pass_cnt[turn] += 1;
    turn ^= 1;
}

void BitBoard::update_count() {
    /*
    Update the number of disks on the board for each player.

    Returns
    -------
        count_player : int
            The number of disks for the current player.
        count_opponent : int
            The number of disks for the opponent.
    */
    uint8_t cnt_black, cnt_white;
    std::tie(cnt_black, cnt_white) = count_disks(boards_state);
    count_black = cnt_black;
    count_white = cnt_white;
}

void BitBoard::auto_mode(bool automode) {
    /*
    Set automatic mode.

    Parameters
    ----------
    automode : bool, optional
        Automatic mode on/off flag, by default True
    */
    human_ai = automode;
}
