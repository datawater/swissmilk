#pragma once

#include <iostream>
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

    u32 fide_id;

    // NOTE: Becuse of only using u8, this will have an y2155 bug, 
    //       but I doubt that this will be used in 2155.
    u8 birth_year;

    SmDevelopmentCoefficientK k;

   public:
    SM_DEFINE_GETTER_SETTER(std::string, name)

    SM_DEFINE_GETTER_SETTER(SmFederation, federation)
    SM_DEFINE_GETTER_SETTER(f32, rating)

    inline u16 get_birth_year() const { return 1900 + (u16)this->birth_year; };
    [[deprecated]] inline u8* get_birth_year_mut() {
        return &this->birth_year;
    };

    inline void set_birth_year(u16 birth_year) {
        this->birth_year = birth_year - 1900;
    };

    SM_DEFINE_GETTER_SETTER(u32, fide_id)
    SM_DEFINE_GETTER_SETTER(SmDevelopmentCoefficientK, k)
    SM_DEFINE_GETTER_SETTER(SmFideTitle, title)

    SmDevelopmentCoefficientK try_guess_k(SmRatingType type);

    f32 expected_score_against_player(SmPlayer* other);
    f32 rating_change_after_game(SmPlayer* other, SmGameResult result);

    friend std::ostream& operator<<(std::ostream& out, SmPlayer& player) {
        out << std::string("SmPlayer {\n\tname: '") << player.name
            << std::string("'\n\trating: ") << std::to_string(player.rating)
            << std::string("\n\ttitle: ") << player.get_title().to_string()
            << std::string("\n\tfederation: ")
            << player.get_federation().to_string()
            << std::string("\n\tk_value: ")
            << std::to_string(static_cast<int>(player.get_k()))
            << std::string("\n\tfide_id: ")
            << std::to_string(player.get_fide_id()) << std::string("\n};");

        return out;
    }

    bool operator<(SmPlayer& rhs) {
        return (this->rating < rhs.rating && this->title < rhs.title &&
                this->name < rhs.name);
    }

    bool operator>(SmPlayer& rhs) {
        return (this->rating > rhs.rating && this->title > rhs.title &&
                this->name > rhs.name);
    }

    bool operator==(SmPlayer& rhs) {
        return (this->rating == rhs.rating && this->title == rhs.title &&
                this->name == rhs.name);
    }

    bool operator<=(SmPlayer& rhs) { return (*this < rhs && *this == rhs); }

    bool operator>=(SmPlayer& rhs) { return (*this > rhs && *this == rhs); }

    bool operator!=(SmPlayer& rhs) { return !(*this == rhs); }

    inline SmPlayer() {
        this->name = std::string();
        this->federation = SmFederation(SmFederationsEnum::NON);
        this->rating = 0;
        this->title = SmFideTitle(SmFideTitlesEnum::NoTitle);
        this->k = SmDevelopmentCoefficientK::K40;
        this->fide_id = 0;
    }

    inline SmPlayer(std::string name, SmFederation federation, u16 rating,
                    SmFideTitle title, u32 fide_id, u16 birth_year,
                    SmRatingType type)
        : name(std::move(name)),
          federation(std::move(federation)),
          rating(rating),
          title(std::move(title)),
          fide_id(fide_id),
          birth_year(static_cast<u8>(birth_year - 1900)) {
        this->k = SmDevelopmentCoefficientK::K40;
        this->k = this->try_guess_k(type);
    }

    inline SmPlayer(std::string name, SmFederation federation, u16 rating,
                    SmFideTitle title, u32 fide_id, u16 birth_year,
                    SmDevelopmentCoefficientK k)
        : name(std::move(name)),
          federation(std::move(federation)),
          rating(rating),
          title(std::move(title)),
          fide_id(fide_id),
          birth_year(static_cast<u8>(birth_year - 1900)),
          k(k) {}
};

class SmPlayerHistory;

class SmPlayerInTournament : public SmPlayer {
   private:
    u8 score;
    f32 performance_rating;
    SmPlayerHistory* history;

   public:
    inline f32 get_score() { return static_cast<f32>(this->score) / 2; }
    [[deprecated]] inline u8* get_score_mut() { return &this->score; }
    inline void set_score(f32 score) {
        this->score = static_cast<u8>(score * 2);
    }

    SM_DEFINE_GETTER_SETTER(f32, performance_rating)
    
    f32 calculate_performance_rating_binary_search(f32 epsilon = 0.0001);
    f32 calculate_performance_rating_fide();

    inline SmPlayerInTournament(const SmPlayer& player)
        : score(0), performance_rating(0.0) {
        this->set_name(player.get_name());
        this->set_birth_year(player.get_birth_year());
        this->set_federation(player.get_federation());
        this->set_fide_id(player.get_fide_id());
        this->set_title(player.get_title());
        this->set_k(player.get_k());
        this->set_rating(player.get_rating());

        this->history = nullptr;
    }

    inline SmPlayerInTournament(const SmPlayer& player, u8 score,
                                SmPlayerHistory* history)
        : score(score), performance_rating(0.0), history(history) {
        this->set_name(player.get_name());
        this->set_birth_year(player.get_birth_year());
        this->set_federation(player.get_federation());
        this->set_fide_id(player.get_fide_id());
        this->set_title(player.get_title());
        this->set_k(player.get_k());
        this->set_rating(player.get_rating());

        this->performance_rating =
            this->calculate_performance_rating_binary_search();
    }

    inline SmPlayerInTournament() {
        this->set_name(std::string());
        this->set_federation(SmFederation(SmFederationsEnum::NON));
        this->set_rating(0);
        this->set_title(SmFideTitle(SmFideTitlesEnum::NoTitle));
        this->set_k(SmDevelopmentCoefficientK::K40);
        this->set_fide_id(0);
        this->score = 0;
        this->performance_rating = 0;
    }
};

#include "history.hpp"