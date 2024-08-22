#include <cmath>
#include <cstdio>
#include <ctime>

#include "player.hpp"
#include "rating.hpp"
#include "utils.hpp"

// FIXME: This ignores dropping bellow 2400.
//  K = 10 once a player's published rating has reached 2400 and remains at that
//  level subsequently, even if the rating drops below 2400.
DevelopmentCoefficientK SmPlayer::try_guess_k(RatingType type) {
    // K = 40 for a player new to the rating list until he has completed events
    // with at least 30 games
    //
    // K = 20 as long as a player's rating remains under
    // 2400.
    //
    // K = 10 once a player's published rating has reached 2400 and
    // remains at that level subsequently, even if the rating drops below 2400.
    //
    // K = 40 for all players until their 18th birthday, as long as their rating
    // remains under 2300. K = 20 for RAPID and BLITZ ratings all players.

    std::time_t time = std::time(nullptr);
    std::tm* const localtime = std::localtime(&time);

    if (localtime == NULL) {
        SM_ERROR("Couldn't get local time");
    }

    u16 current_year = 1900 + localtime->tm_year;
    u16 birth_year = this->get_birth_year();

    if (type == RatingType::Rapid || type == RatingType::Blitz) {
        return DevelopmentCoefficientK::K20;
    }

    if (current_year - birth_year < 18 && this->rating < 2300) {
        return DevelopmentCoefficientK::K40;
    }

    if (this->rating < 2400) {
        return DevelopmentCoefficientK::K20;
    }

    if (this->rating >= 2400) {
        return DevelopmentCoefficientK::K10;
    }

#ifdef DEBUG
    fprintf(stderr, "Couldn't guess K value. Defaulting to 40.");
#endif

    return DevelopmentCoefficientK::K40;
}

f32 SmPlayer::expected_score_against_player(SmPlayer* other) {
    // D_rating = 10 ** ((R_opponent - R_player) / 400)
    // E = 1 / (1 + D_rating)

    f32 rating_diff = other->rating - this->rating;

    // Clamp rating diff to 400 so Rating diff / 400 doesn't go over 1
    if (rating_diff > 400.0) {
        rating_diff = 400.0;
    }

    f32 rating_diff_scaled = std::pow(10, rating_diff / 400.0);
    f32 expected_score = 1.0f / (1.0f + rating_diff_scaled);

    return expected_score;
}

f32 SmPlayer::rating_change_after_game(SmPlayer* other, GameResult result) {
    // D_r = K * (S - E);

    f32 expected_score = this->expected_score_against_player(other);
    // Round expected score to the 100th.
    // (IDK, the FIDE calculator does it, so do I)
    expected_score = static_cast<int>(expected_score * 100.0f) / 100.0f;

    f32 score = static_cast<f32>(result) / 2.0;
    f32 k = static_cast<f32>(this->k);

    return k * (score - expected_score);
}