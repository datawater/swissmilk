#include "../src/include/swissmilk.hpp"
#include "tests.h"

result_t test_expected_score() {
    SmPlayer player_underage = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2050,
        SmFideTitle::from_string("WCM"), 0, 2010, SmRatingType::Classical);

    SmPlayer player_under_2400 = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2399,
        SmFideTitle::from_string("WCM"), 0, 2000, SmRatingType::Classical);

    auto e = player_underage.expected_score_against_player(&player_under_2400);
    e = ((int)(e * 1e+5)) * 1e-5;

    if (e != 0.11826f) {
        return new_result_error(nullptr);
    }

    return new_result_ok();
}