#ifndef BASESTRATEGY_H
#define BASESTRATEGY_H

#include <iostream>
#include "../bitboard/bitboard.h"

class BaseStrategy {
public:
    virtual ~BaseStrategy() {}
    virtual uint8_t move(const BitBoard& board) = 0;
};

#endif  // #ifndef BASESTRATEGY_H