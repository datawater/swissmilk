#include <iostream>

#include "swissmilk/federations.hpp"
#include "swissmilk/swissmilk.hpp"
#include "swissmilk/title.hpp"

int main() {
    std::cout << "Hello, World!\n";

    SmPlayer player =
        SmPlayer("Datas Doppelgänger", SmFederation::from_string("USA"), 3850,
                 SmFideTitle::from_string("WCM"));
    std::cout << player << "\n";

    return 0;
}