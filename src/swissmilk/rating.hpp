#pragma once

enum class DevelopmentCoefficientK {
    K10 = 10,
    K15 = 15,
    K20 = 20,
    K30 = 30,
    K40 = 40
};

enum class RatingType { Classical, Rapid, Blitz };

enum class GameResult { Win = 2, Draw = 1, Lose = 0 };