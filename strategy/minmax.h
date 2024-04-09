#ifndef MINMAX_H
#define MINMAX_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

class Minmax : public BaseStrategy
{
private:
    constexpr static std::array<int, 64> EVAL_TBL1 = {
        30,  -12,   0,  -1,  -1,   0, -12,  30,
        -12, -15,  -3,  -3,  -3,  -3, -15, -12,
        0,    -3,   0,  -1,  -1,   0,  -3,   0,
        -1,   -3,  -1,  -1,  -1,  -1,  -3,  -1,
        -1,   -3,  -1,  -1,  -1,  -1,  -3,  -1,
        0,    -3,   0,  -1,  -1,   0,  -3,   0,
        -12, -15,  -3,  -3,  -3,  -3, -15, -12,
        30,  -12,   0,  -1,  -1,   0, -12,  30,
    };
    constexpr static std::array<int, 64> EVAL_TBL2 = {
        120, -20,  20,   5,   5,  20, -20, 120,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        20,   -5,  15,   3,   3,  15,  -5,  20,
        5,    -5,   3,   3,   3,   3,  -5,   5,
        5,    -5,   3,   3,   3,   3,  -5,   5,
        20,   -5,  15,   3,   3,  15,  -5,  20,
        -20, -40,  -5,  -5,  -5,  -5, -40, -20,
        120, -20,  20,   5,   5,  20, -20, 120,
    };

    // High speed computation
    constexpr static std::array<uint64_t, 64> EXP2 = {
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
    uint8_t depth;
    uint8_t player_clr;

    bool touch_border(BitBoard::Boards boards);
    int evaluate_value(BitBoard::Boards boards);
    std::tuple<int, int> min_max(
        uint8_t turn_, BitBoard::Boards boards,
        uint8_t depth_, int pre_evaluation);
    std::tuple<int, int> min_max_debug(
        uint8_t turn_, BitBoard::Boards boards,
        uint8_t depth_, int pre_evaluation);
public:
    Minmax(uint8_t d = 2);
    uint8_t move(const BitBoard& board);
};

#endif  // #ifndef MINMAX_H