#ifndef ERORATING_H
#define ERORATING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>

class EloRating
{
private:
    constexpr static int INIT_RATING = 1600;
    constexpr static int K = 16;
    const std::string filename = "./matching/elorating.txt";
    std::unordered_map<std::string, float> rating;

public:
    EloRating();
    ~EloRating();
    void update(
        const std::string& member1, const std::string& member2,
        const int game_number, const float cnt_mbr1_win);
    void reset();
    void save();
    void print();
};

#endif  // #ifndef ERORATING_H