#ifndef MAXIMIZE_H
#define MAXIMIZE_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

class Maximize : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board) override;
};

#endif  // #ifndef MAXIMIZE_H