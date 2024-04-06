#ifndef RANDOM_H
#define RANDOM_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

#include <iostream>
#include <vector>

class Random : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board);
};

#endif  // #ifndef RANDOM_H