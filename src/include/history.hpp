#pragma once

#include <utility>
#include <vector>

#include "player.hpp"
#include "utils.hpp"

class SmPlayerHistory {
   private:
    u8 amount_of_games_as_white;
    u8 amount_of_games_as_black;

    // NOTE: Consider switching this to a map
    /// Round, opponent, color
    std::vector<std::pair<SmPlayerInTournament*, bool>> rounds;

   public:
    inline u8 get_amount_of_games_as_white() const {
        return this->amount_of_games_as_white;
    };
    
    inline u8* get_amount_of_games_as_white_mut() {
        return &this->amount_of_games_as_white;
    };
    
    inline void set_amount_of_games_as_white(
        const u8& amount_of_games_as_white) {
        this->amount_of_games_as_white = amount_of_games_as_white;
    };

    inline u8 get_amount_of_games_as_black() const {
        return this->amount_of_games_as_black;
    };
    
    inline u8* get_amount_of_games_as_black_mut() {
        return &this->amount_of_games_as_black;
    };

    inline void set_amount_of_games_as_black(
        const u8& amount_of_games_as_black) {
        this->amount_of_games_as_black = amount_of_games_as_black;
    };

    inline std::vector<std::pair<SmPlayerInTournament*, bool>>* get_rounds() {
        return &this->rounds;
    }
};