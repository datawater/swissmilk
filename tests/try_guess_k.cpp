#include <iostream>
#include <string>

#include "../src/swissmilk/swissmilk.hpp"

int main() {
    SmPlayer player_underage =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 1800,
                 SmFideTitle::from_string("WCM"), 2010, RatingType::Classical);

    SmPlayer player_rapid =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2050,
                 SmFideTitle::from_string("WCM"), 2010, RatingType::Rapid);

    SmPlayer player_under_2400 =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2399,
                 SmFideTitle::from_string("WCM"), 2000, RatingType::Classical);

    SmPlayer player_over_2400 =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2401,
                 SmFideTitle::from_string("WCM"), 2010, RatingType::Classical);

    std::cout << std::to_string((int)player_underage.get_k()) << "\n";
    std::cout << std::to_string((int)player_rapid.get_k()) << "\n";
    std::cout << std::to_string((int)player_under_2400.get_k()) << "\n";
    std::cout << std::to_string((int)player_over_2400.get_k()) << "\n";
}