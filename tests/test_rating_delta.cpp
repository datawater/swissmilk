#include "../src/include/swissmilk.hpp"
#include "tests.h"

result_t test_rating_delta_after_game() {
    SmPlayer player_underage = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2050,
        SmFideTitle::from_string("WCM"), 2010, 0, SmRatingType::Classical);

    SmPlayer player_under_2400 = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2399,
        SmFideTitle::from_string("WCM"), 2000, 0, SmRatingType::Classical);

    auto delta = player_underage.rating_change_after_game(&player_under_2400, SmGameResult::Win);

    if (delta != 35.6f)
        return new_result_error(nullptr);

    return new_result_ok();
}