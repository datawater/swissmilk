#include <iostream>
#include <string>

#include "../src/swissmilk/swissmilk.hpp"

int main() {
    SmPlayer player_underage =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2050,
                 SmFideTitle::from_string("WCM"), 2010, RatingType::Classical);

    SmPlayer player_under_2400 =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2399,
                 SmFideTitle::from_string("WCM"), 2000, RatingType::Classical);

    std::cout << player_underage.expected_score_against_player(
                     &player_under_2400)
              << "\n";
}