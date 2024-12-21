#include <cmath>
#include <cstdio>
#include <ctime>
#include <numeric>

#include "include/player.hpp"
#include "include/rating.hpp"
#include "include/utils.hpp"

static const i16 p_to_dp_table[] = {
    -800, -677, -589, -538, -501, -470, -444, -422, -401, -383, -366, -351,
    -336, -322, -309, -296, -284, -273, -262, -251, -240, -230, -220, -211,
    -202, -193, -184, -175, -166, -158, -149, -141, -133, -125, -117, -110,
    -102, -95,  -87,  -80,  -72,  -65,  -57,  -50,  -43,  -36,  -29,  -21,
    -14,  -7,   0,    7,    14,   21,   29,   36,   43,   50,   57,   65,
    72,   80,   87,   95,   102,  110,  117,  125,  133,  141,  149,  158,
    166,  175,  184,  193,  202,  211,  220,  230,  240,  251,  262,  273,
    284,  296,  309,  322,  336,  351,  366,  383,  401,  422,  444,  470,
    501,  538,  589,  677,  800};

// FIXME: This ignores dropping bellow 2400.
//  K = 10 once a player's published rating has reached 2400 and remains at that
//  level subsequently, even if the rating drops below 2400.
SmDevelopmentCoefficientK SmPlayer::try_guess_k(SmRatingType type) {
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

    if (type == SmRatingType::Rapid || type == SmRatingType::Blitz) {
        return SmDevelopmentCoefficientK::K20;
    }

    if (current_year - birth_year <= 18 && this->rating < 2300) {
        return SmDevelopmentCoefficientK::K40;
    }

    if (this->rating < 2400) {
        return SmDevelopmentCoefficientK::K20;
    }

    if (this->rating >= 2400) {
        return SmDevelopmentCoefficientK::K10;
    }

#ifdef DEBUG
    fprintf(stderr, "Couldn't guess K value. Defaulting to 40.");
#endif

    return SmDevelopmentCoefficientK::K40;
}

f32 expected_score_again_player_rating_based(f32 rating_one, f32 rating_two) {
    // D_rating = 10 ** ((R_opponent - R_player) / 400)
    // E = 1 / (1 + D_rating)

    f32 rating_diff = rating_two - rating_one;

    // Clamp rating diff to 400 so Rating diff / 400 doesn't go over 1
    if (rating_diff > 400.0 || rating_diff < -400) {
        rating_diff = 400.0;
    }

    f32 rating_diff_scaled = std::pow(10, rating_diff / 400.0);
    f32 expected_score = 1.0f / (1.0f + rating_diff_scaled);

    return expected_score;
}

f32 SmPlayer::expected_score_against_player(SmPlayer* other) {
    return expected_score_again_player_rating_based(this->rating,
                                                    other->rating);
}

f32 SmPlayer::rating_change_after_game(SmPlayer* other, SmGameResult result) {
    // D_r = K * (S - E);

    f32 expected_score = this->expected_score_against_player(other);
    // Round expected score to the 100th.
    // (IDK, the FIDE calculator does it, so do I)
    expected_score = static_cast<int>(expected_score * 100.0f) / 100.0f;

    f32 score = static_cast<f32>(result) / 2.0;
    f32 k = static_cast<f32>(this->k);

    return k * (score - expected_score);
}

// https://en.wikipedia.org/wiki/Performance_rating_(chess)#Calculation
f32 SmPlayerInTournament::calculate_performance_rating_binary_search(
    f32 epsilon) {
    f32 low = 0.0f;
    f32 high = 4000.0f;
    f32 mid = 0.0f;

    auto history = this->history->get_rounds();
    f32 actual_score = std::accumulate(
        history->begin(), history->end(), 0.0f, [&](f32 sum, const auto& x) {
            return sum + expected_score_again_player_rating_based(
                             this->get_rating(), x.second->get_rating());
        });

    while ((high - low) > epsilon) {
        mid = (high + low) / 2;
        f32 expected_score_mid = std::accumulate(
            history->begin(), history->end(), 0.0f,
            [&](f32 sum, const auto& x) {
                return sum + expected_score_again_player_rating_based(
                                 mid, x.second->get_rating());
            });

        if (expected_score_mid < actual_score) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return mid;
}

// https://handbook.fide.com/chapter/B022017
f32 SmPlayerInTournament::calculate_performance_rating_fide() {
    auto history = this->history->get_rounds();

    f32 average = std::accumulate(history->begin(), history->end(), 0.0f,
                                  [&](f32 sum, const auto& x) {
                                      return sum + x.second->get_rating();
                                  }) /
                  history->size();

    return average + p_to_dp_table[static_cast<u16>(this->score / 2 /
                                                    history->size() * 100)];
}