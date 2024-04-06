#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <list>
#include <deque>
#include <tuple>
#include <vector>
#include <algorithm>

// #include <pybind11/pybind11.h>

using namespace std;

class Strategy;

class BitBoard
{
private:
    // Board status
    constexpr static uint8_t BLACK = 0;
    constexpr static uint8_t WHITE = 1;
    uint64_t black_board = 0x0000000810000000;
    uint64_t white_board = 0x0000001008000000;

    // Game status
    uint8_t turn = 0;
    uint64_t reversible = 0;
    uint8_t count_black = 0;
    uint8_t count_white = 0;
    int pass_cnt[2] = {0, 0};

    // Logger
    std::deque<std::pair<uint64_t, uint64_t>> board_log;
    std::deque<std::pair<uint64_t, uint64_t>> board_back;

    // High speed computation
    constexpr static uint64_t exp2[64]{
        0x1, 0x2, 0x4, 0x8,
        0x10, 0x20, 0x40, 0x80,
        0x100, 0x200, 0x400, 0x800,
        0x1000, 0x2000, 0x4000, 0x8000,
        0x10000, 0x20000, 0x40000, 0x80000,
        0x100000, 0x200000, 0x400000, 0x800000,
        0x1000000, 0x2000000, 0x4000000, 0x8000000,
        0x10000000, 0x20000000, 0x40000000, 0x80000000,
        0x100000000, 0x200000000, 0x400000000, 0x800000000,
        0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000,
        0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000,
        0x100000000000, 0x200000000000, 0x400000000000, 0x800000000000,
        0x1000000000000, 0x2000000000000, 0x4000000000000, 0x8000000000000,
        0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000,
        0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000,
        0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000,
    };
public:
    BitBoard();
    // ~BitBoard();
    struct GameStatus {
        uint64_t GS_b_board;
        uint64_t GS_w_board;
        std::deque<std::pair<uint64_t, uint64_t>> GS_board_log;
        std::deque<std::pair<uint64_t, uint64_t>> GS_board_back;
    };

    uint8_t result = 3;
    bool human_ai = false;
    GameStatus status = {
        black_board, white_board, board_log, board_back,
    };

    // Game rules
    static uint8_t bit_count(uint64_t x);
    static uint64_t check_surround(uint64_t x, uint8_t direction);
    static tuple<uint8_t, uint8_t> count_disks(
        uint64_t b_board, uint64_t w_board);
    static uint64_t reversible_area(
        uint8_t turn_, uint64_t b_board, uint64_t w_board);
    static vector<uint8_t> reversible_area_list(
        uint8_t turn_, uint64_t b_board, uint64_t w_board);
    static bool is_reversible(
        uint64_t put_loc, uint8_t turn_,
        uint64_t b_board, uint64_t w_board);
    static bool turn_playable(
        uint8_t turn_, uint64_t b_board, uint64_t w_board);
    static int judge_game(uint64_t b_board, uint64_t w_board);

    // Change board status
    tuple <uint64_t, uint64_t> return_board() const;
    uint8_t return_turn() const;
    uint8_t return_result() const;
    vector<vector<uint8_t>> display_board() const;
    void load_board(uint64_t b_board, uint64_t w_board);
    void load_state();
    void save_state();
    bool undo_turn();
    bool redo_turn();

    // Functions for play
    static tuple<uint64_t, uint64_t> simulate_play(
        uint8_t turn, uint64_t put_loc,
        uint64_t b_board, uint64_t w_board);
    void play_turn(uint8_t put_loc);
    void skip_turn();
    void update_count();
    void auto_mode(bool automode = true);
};

#endif  // #ifndef BITBOARD_H