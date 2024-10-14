#pragma once

#include <string>

#include "utils.hpp"

// Sourced from
// https://www.fide.com/docs/regulations/FIDE%20Title%20Regulations%202022.pdf

enum class SMATTR_PACKED SmFideTitlesEnum {
    GM = 6,
    WGM = 4,
    IM = 5,
    WIM = 3,
    FM = 4,
    WFM = 2,
    CM = 3,
    WCM = 1,

    NoTitle = 0
};

/**
 * @brief A Class representing a FIDE given title.
 *
 */
class SmFideTitle {
   private:
    SmFideTitlesEnum value;

   public:
    std::string& to_string() const;
    static SmFideTitle from_string(const std::string& str);

    u16 to_rating() const;

    inline SmFideTitlesEnum get_value() const { return this->value; }

    inline void set_value(SmFideTitlesEnum value) { this->value = value; }

    inline bool operator==(SmFideTitle rhs) const {
        return this->get_value() == rhs.get_value();
    }

    inline bool operator<(const SmFideTitle& rhs) const {
        return this->value < rhs.value;
    }
    inline bool operator>(const SmFideTitle& rhs) const {
        return this->value > rhs.value;
    }

    friend std::ostream& operator<<(std::ostream& out, SmFideTitle& title) {
        out << std::string("SmFideTitle { value: '") << title.to_string()
            << std::string("' }");
        return out;
    }

    inline SmFideTitle() { this->value = SmFideTitlesEnum::NoTitle; }

    inline SmFideTitle(SmFideTitlesEnum value) { this->value = value; }
};