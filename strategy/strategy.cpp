#include "strategy.h"

Strategy::Strategy(const std::string& strategy) {
    set_strategy(strategy);
}

void Strategy::set_strategy(const std::string& strategy) {
    if (strategy == "random") {
        strategy_ = std::make_unique<Random>();
    } else if (strategy == "maximize") {
        strategy_ = std::make_unique<Maximize>();
    } else if (strategy == "minimize") {
        strategy_ = std::make_unique<Minimize>();
    } else if (strategy == "minmax") {
        strategy_ = std::make_unique<Minmax>(2);
    } else if (strategy == "minmax4") {
        strategy_ = std::make_unique<Minmax>(4);
    } else if (strategy == "minmax6") {
        strategy_ = std::make_unique<Minmax>(6);
    } else {
        throw std::invalid_argument("Unknown strategy");
    }
}

uint8_t Strategy::move(const BitBoard& board) {
    if (!strategy_) {
        throw std::runtime_error("Strategy is not set");
    }
    return strategy_ -> move(board);
}