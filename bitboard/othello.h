#ifndef OTHELLO_H
#define OTHELLO_H

#include "bitboard.h"
#include "../strategy/strategy.h"

#include <string>

class Othello : public BitBoard
{
private:
    Strategy* black_strategy;
    Strategy* white_strategy;
public:
    Othello(uint8_t color = 0);
    ~Othello();

    uint8_t player_clr = 0;
    uint8_t return_player_clr() const;
    void change_strategy(const std::string& strategy, bool is_player = false);
    void change_player(uint8_t color);
    tuple<bool, bool> process_game();
};

#endif  // #ifndef OTHELLO_H