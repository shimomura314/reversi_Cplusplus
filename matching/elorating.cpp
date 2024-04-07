#include "elorating.h"

EloRating::EloRating() {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Constructor: File was not found." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        float value;
        if (iss >> key >> value) {
            rating[key] = value;
        }
    }
    std::cout << "Constructor: File found." << std::endl;
    file.close();
}

EloRating::~EloRating() {
    save();
}


void EloRating::update(
        const std::string& member1, const std::string& member2,
        const int game_number, const float cnt_mbr1_win) {
    int cnt_mbr2_win = game_number - cnt_mbr1_win;

    if (rating.find(member1) == rating.end()) {
        rating[member1] = INIT_RATING;
    }
    if (rating.find(member2) == rating.end()) {
        rating[member2] = INIT_RATING;
    }


    float pre_prblty_1 = 1.0f / (
        std::pow(10, (rating[member2] - rating[member1]) / 400.0f) + 1.0f);
    float pre_prblty_2 = 1.0f / (
        std::pow(10, (rating[member1] - rating[member2]) / 400.0f) + 1.0f);
    float expected_win_1 = pre_prblty_1 * game_number;
    float expected_win_2 = pre_prblty_2 * game_number;

    rating[member1] = rating[member1] + K * ((float) cnt_mbr1_win - expected_win_1);
    rating[member2] = rating[member2] + K * ((float) cnt_mbr2_win - expected_win_2);
}

void EloRating::reset() {
    rating.clear();
}

void EloRating::save() {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
        return;
    }

    for (const auto& pair : rating) {
        file << pair.first << " " << pair.second << "\n";
    }
    file.close();
}

void EloRating::print() {
    for (const auto& pair : rating) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
