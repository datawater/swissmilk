#include <cmath>
#include <ctime>

#include "player.hpp"
#include "rating.hpp"

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

    u16 current_year = 1900 + localtime->tm_year;
    u16 birth_year = this->get_birth_year();

    if (current_year - birth_year < 18 && this->rating < 2300) {
        return DevelopmentCoefficientK::K40;
    }

    if (type == RatingType::Rapid || type == RatingType::Blitz) {
        return DevelopmentCoefficientK::K20;
    }

    if (this->rating < 2400) {
        return DevelopmentCoefficientK::K20;
    }

    if (this->rating >= 2400) {
        return DevelopmentCoefficientK::K10;
    }

    return DevelopmentCoefficientK::K40;
}

f32 SmPlayer::expected_score_against_player(SmPlayer* other) {
    // D_rating = 10 ** ((R_opponent - R_player) / 400)
    // E = 1 / (1 + D_rating)

    f32 delta_rating = std::powf(10, (other->rating - this->rating) / 400);

    return 1.0 / (1.0 + delta_rating);
}

f32 SmPlayer::rating_change_after_game(SmPlayer* other, GameResult result) {
    // D_r = K * (S - E);

    return ((double)static_cast<int>(this->k)) *
           (((double)static_cast<int>(result)) / 2.0 -
            this->expected_score_against_player(other));
}