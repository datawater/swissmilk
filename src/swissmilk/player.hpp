#pragma once

#include <string>

#include "federations.hpp"
#include "rating.hpp"
#include "title.hpp"
#include "utils.hpp"

class SmPlayer {
   private:
    std::string name;
    SmFederation federation;

    f32 rating;
    SmFideTitle title;

    // NOTE: Becuse of only using u8, this will have an y2155 bug, but I doubt
    // that this will be used in 2155.
    u8 birth_year;

    u32 fide_id;
    DevelopmentCoefficientK k;

   public:
    inline std::string get_name() const { return this->name; };
    inline std::string* get_name_mut() { return &this->name; };
    inline void set_name(std::string name) { this->name = name; };

    inline SmFederation get_federation() const { return this->federation; }
    inline SmFederation* get_federation_mut() { return &this->federation; }
    inline void set_federation(SmFederation federation) {
        this->federation = federation;
    }

    inline f32 get_rating() const { return this->rating; };
    inline f32* get_rating_mut() { return &this->rating; };
    inline void set_rating(f32 rating) { this->rating = rating; };

    inline u16 get_birth_year() const { return 1900 + (u16)this->birth_year; };
    [[deprecated]] inline u8* get_birth_year_mut() {
        return &this->birth_year;
    };

    inline void set_birth_year(u16 birth_year) {
        this->birth_year = birth_year - 1900;
    };

    inline u32 get_fide_id() const { return this->fide_id; };
    inline u32* get_fide_id_mut() { return &this->fide_id; };
    inline void set_fide_id(u32 fide_id) { this->fide_id = fide_id; };

    inline DevelopmentCoefficientK get_k() const { return this->k; }
    inline DevelopmentCoefficientK* get_k_mut() { return &this->k; }
    inline void set_k(DevelopmentCoefficientK k) { this->k = k; }

    inline SmFideTitle get_fide_title() const { return this->title; };
    inline SmFideTitle* get_fide_title_mut() { return &this->title; };
    inline void set_fide_title(SmFideTitle title) { this->title = title; };

    DevelopmentCoefficientK try_guess_k(RatingType type);

    f32 expected_score_against_player(SmPlayer* other);
    f32 rating_change_after_game(SmPlayer* other, GameResult result);

    inline SmPlayer() {
        this->name = std::string();
        this->federation = SmFederation(SmFederationsEnum::NON);
        this->rating = 0;
        this->title = SmFideTitle(SmFideTitlesEnum::NoTitle);
    }

    friend std::ostream& operator<<(std::ostream& out, SmPlayer& player) {
        out << std::string("SmPlayer {\n\tname: '") << player.name
            << std::string("'\n\trating: ") << std::to_string(player.rating)
            << std::string("\n\ttitle: ") << player.get_fide_title().to_string()
            << std::string("\n\tfederation: ")
            << player.get_federation().to_string() << std::string("\n};");

        return out;
    }

    inline SmPlayer(std::string name, SmFederation federation, u16 rating,
                    SmFideTitle title)
        : name(std::move(name)),
          federation(std::move(federation)),
          rating(rating),
          title(std::move(title)) {}
};