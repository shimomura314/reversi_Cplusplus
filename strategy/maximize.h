#ifndef MAXIMIZE_H
#define MAXIMIZE_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

#include <iostream>
#include <vector>

class Maximize : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board);
};

#endif  // #ifndef MAXIMIZE_H