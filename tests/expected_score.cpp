#include <iostream>
#include <string>

#include "../src/swissmilk/include/swissmilk.hpp"

int main() {
    SmPlayer player_underage = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2050,
        SmFideTitle::from_string("WCM"), 0, 2010, SmRatingType::Classical);

    SmPlayer player_under_2400 = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2399,
        SmFideTitle::from_string("WCM"), 0, 2000, SmRatingType::Classical);

    std::cout << player_underage.expected_score_against_player(
                     &player_under_2400)
              << "\n";
}