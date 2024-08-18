#pragma once

#include "federations.hpp"
#include "title.hpp"
#include "utils.hpp"
#include <string>

class SmPlayer {
    private:
        std::string name;
        SmFederation federation;

        u16 rating;
        SmFideTitle title;
  
    public:
        inline std::string get_name() const { return this->name; };
        inline std::string* get_name_mut() { return &this->name; };
        inline void set_name(std::string name) { this->name = name; };

        inline SmFederation get_federation() const { return this->federation; }
        inline SmFederation* get_federation_mut() { return &this->federation; }
        inline void set_federation(SmFederation federation) { this->federation = federation; }

        inline u16 get_rating() const { return this->rating; };
        inline u16* get_rating_mut() { return &this->rating; };
        inline void set_rating(u16 rating) { this->rating = rating; };

        inline SmFideTitle get_fide_title() const { return this->title; };
        inline SmFideTitle* get_fide_title_mut() { return &this->title; };
        inline void set_fide_title(SmFideTitle title) { this->title = title; };

        inline SmPlayer() { 
            this->name = std::string();
            this->federation = SmFederation(SmFederationsEnum::NON);
            this->rating = 0;
            this->title = SmFideTitle(SmFideTitlesEnum::NoTitle);
        }

        friend std::ostream& operator<<(std::ostream &out, SmPlayer& player) {
            out << 
                std::string("SmPlayer {\n\tname: '") <<
                player.name <<
                std::string("'\n\trating: ") <<
                std::to_string(player.rating) <<
                std::string("\n\ttitle: ") <<
                player.get_fide_title().to_string() <<
                std::string("\n\tfederation: ") <<
                player.get_federation().to_string() <<
                std::string("\n};")
            ;

            return out;
        }

        inline SmPlayer(std::string name, SmFederation federation, u16 rating, SmFideTitle title)
          : name(std::move(name)), federation(std::move(federation)), rating(rating), title(std::move(title)) {}
};