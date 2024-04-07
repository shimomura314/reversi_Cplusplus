#include "matching.h"


std::uint8_t set_match(
        const std::string& strategy1, const std::string& strategy2) {
    Othello game = Othello();
    game.change_strategy(strategy1, true);
    game.change_strategy(strategy2, false);
    game.auto_mode();

    std::tuple<bool, bool> result;

    while (1) {
        result = game.process_game();
        if (game.return_result() != 3) {
            break;
        }
    }
    return game.return_result();
}

int main() {
    int REPEAT = 2;
    std::vector<std::string> strategies = {
        "random",
        "maximize",
        "minimize",
        "minmax",
        "minmax4",
        "minmax6",
    };
    std::vector<std::pair<std::string, std::string>> parameters;
    EloRating rating = EloRating();

    for (int i = 0; i < REPEAT; ++i) {
        for (size_t j = 0; j < strategies.size(); ++j) {
            for (size_t k = 0; k < strategies.size(); ++k) {
                if (j != k) {
                    parameters.push_back(std::make_pair(
                        strategies[j], strategies[k]));
                }
            }
        }
    }

    std::cout << "Matching start." << std::endl;
    for (auto parameter : parameters) {
        uint8_t rslt = set_match(parameter.first, parameter.second);
        if (rslt == 0) {
            rating.update(parameter.first, parameter.second, 1, 1);
            std::cout << parameter.first << " vs " << parameter.second;
            std::cout << " finished, won by first." << std::endl;
        } else if (rslt == 1) {
            rating.update(parameter.first, parameter.second, 1, 0);
            std::cout << parameter.first << " vs " << parameter.second;
            std::cout << " finished, won by second." << std::endl;
        } else if (rslt == 1) {
            rating.update(parameter.first, parameter.second, 1, 0.5f);
            std::cout << parameter.first << " vs " << parameter.second;
            std::cout << " finished, draw." << std::endl;
        }
    }

    rating.print();
    rating.save();

    return 0;
}
