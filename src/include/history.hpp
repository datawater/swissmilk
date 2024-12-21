#pragma once

#include <utility>
#include <unordered_map>

#include "player.hpp"
#include "utils.hpp"

class SmPlayerHistory {
   private:
    u8 amount_of_games_as_white;
    u8 amount_of_games_as_black;

    // NOTE: Consider switching this to a map
    /// Round, opponent, color
    std::unordered_map<int, SmPlayerInTournament*> rounds;

   public:
    SM_DEFINE_GETTER_SETTER(u8, amount_of_games_as_white)    
    inline u8* get_amount_of_games_as_white_mut() {
        return &this->amount_of_games_as_white;
    };

    SM_DEFINE_GETTER_SETTER(u8, amount_of_games_as_black)
    inline u8* get_amount_of_games_as_black_mut() {
        return &this->amount_of_games_as_black;
    };
    
    inline std::unordered_map<int, SmPlayerInTournament*>* get_rounds() {
        return &this->rounds;
    }
};