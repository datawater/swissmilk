#pragma once

#include <algorithm>
#include <cassert>
#include <set>

#include "player.hpp"

class Tournament {
   private:
    std::vector<SmPlayerInTournament*> players;
    u8 amount_of_rounds;

   public:
    inline std::vector<SmPlayerInTournament*>* get_players() {
        return &this->players;
    }

    inline u8 get_amount_of_rounds() { return this->amount_of_rounds; }
    inline u8* get_amount_of_rounds_mut() { return &this->amount_of_rounds; }
    inline void set_amount_of_rounds(u8 amount_of_rounds) {
        this->amount_of_rounds = amount_of_rounds;
    }

    inline void add_player_to_tournament(SmPlayer* player) {
        assert(player != nullptr);

        // if (std::binary_search(this->players.begin(), this->players.end(), ))
    }
};