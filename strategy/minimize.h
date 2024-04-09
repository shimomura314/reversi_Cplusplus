#ifndef MINIMIZE_H
#define MINIMIZE_H

#include "basestrategy.h"
#include "../bitboard/bitboard.h"

class Minimize : public BaseStrategy
{
private:
public:
    uint8_t move(const BitBoard& board) override;
};

#endif  // #ifndef MINIMIZE_H