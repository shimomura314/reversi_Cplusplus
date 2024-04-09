#ifndef STRATEGY_H
#define STRATEGY_H

#include "../bitboard/bitboard.h"
#include "basestrategy.h"
#include "random.h"
#include "maximize.h"
#include "minimize.h"
#include "minmax.h"

#include <memory>
#include <string>

class BitOthello;

class Strategy 
{
private:
    std::unique_ptr<BaseStrategy> strategy_;
public:
    Strategy(const std::string& strategy = "random");
    void set_strategy(const std::string& strategy);
    uint8_t move(const BitBoard& board);
};

#endif  // #ifndef STRATEGY_H