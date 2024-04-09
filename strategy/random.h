#ifndef RANDOM_H
#define RANDOM_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

class Random : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board) override;
};

#endif  // #ifndef RANDOM_H