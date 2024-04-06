#ifndef MINIMIZE_H
#define MINIMIZE_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

#include <iostream>
#include <vector>

class Minimize : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board);
};

#endif  // #ifndef MINIMIZE_H