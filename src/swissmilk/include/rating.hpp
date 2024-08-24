#pragma once

#include "utils.hpp"

enum class SmDevelopmentCoefficientK {
    K10 = 10,
    K15 = 15,
    K20 = 20,
    K30 = 30,
    K40 = 40
};

enum class SmRatingType { Classical, Rapid, Blitz };

enum class SmGameResult { Win = 2, Draw = 1, Lose = 0 };

f32 expected_score_again_player_rating_based(f32 rating_one, f32 rating_two);