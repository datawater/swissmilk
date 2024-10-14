#include "../src/include/swissmilk.hpp"
#include "tests.h"

#define WORKSHY_ASSERT(expression) \
    do {\
        if (!(expression))\
            return new_result_error(nullptr);\
    } while(0)

result_t test_try_guess_k() {
    SmPlayer player_underage = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 1800,
        SmFideTitle::from_string("WCM"), 2010, 0, SmRatingType::Classical);

    SmPlayer player_rapid =
        SmPlayer("Underage Player", SmFederation::from_string("NON"), 2050,
                 SmFideTitle::from_string("WCM"), 2010, 0, SmRatingType::Rapid);

    SmPlayer player_under_2400 = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2399,
        SmFideTitle::from_string("WCM"), 2000, 0, SmRatingType::Classical);

    SmPlayer player_over_2400 = SmPlayer(
        "Underage Player", SmFederation::from_string("NON"), 2401,
        SmFideTitle::from_string("WCM"), 2010, 0, SmRatingType::Classical);

    WORKSHY_ASSERT(40 == (int)player_underage.get_k());
    WORKSHY_ASSERT(20 == (int)player_rapid.get_k());
    WORKSHY_ASSERT(20 == (int)player_under_2400.get_k());
    WORKSHY_ASSERT(10 == (int)player_over_2400.get_k());
    
    return new_result_ok();
}