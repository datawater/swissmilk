#pragma once

#include <cassert>
#include <unordered_set>

#include "player.hpp"
#include "utils.hpp"

class Tournament {
   private:
    std::unordered_set<SmPlayerInTournament*> players;
    u8 amount_of_rounds;

   public:
    SM_DEFINE_GETTER_SETTER(u8, amount_of_rounds)
    SM_DEFINE_GETTER(std::unordered_set<SmPlayerInTournament*>, players)

    inline void add_player_to_tournament(SmPlayer* player) {
        assert(player != nullptr);

        // if (std::binary_search(this->players.begin(), this->players.end(), ))
    }
};