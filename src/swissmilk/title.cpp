#include "include/title.hpp"

#include <algorithm>
#include <map>
#include <string>

static const std::map<std::string, SmFideTitle> fide_title_to_string_table = {
    {std::string("NONE_TITLE"), SmFideTitle(SmFideTitlesEnum::NoTitle)},
    {std::string("WCM"), SmFideTitle(SmFideTitlesEnum::WCM)},
    {std::string("WFM"), SmFideTitle(SmFideTitlesEnum::WFM)},
    {std::string("CM"), SmFideTitle(SmFideTitlesEnum::CM)},
    {std::string("WIM"), SmFideTitle(SmFideTitlesEnum::WIM)},
    {std::string("FM"), SmFideTitle(SmFideTitlesEnum::FM)},
    {std::string("WGM"), SmFideTitle(SmFideTitlesEnum::WGM)},
    {std::string("IM"), SmFideTitle(SmFideTitlesEnum::IM)},
    {std::string("GM"), SmFideTitle(SmFideTitlesEnum::GM)},
};

static const std::map<SmFideTitle, u16> fide_title_to_rating_table = {
    {SmFideTitle(SmFideTitlesEnum::NoTitle), 0},
    {SmFideTitle(SmFideTitlesEnum::WCM), 1800},
    {SmFideTitle(SmFideTitlesEnum::WFM), 1900},
    {SmFideTitle(SmFideTitlesEnum::CM), 2000},
    {SmFideTitle(SmFideTitlesEnum::WIM), 2000},
    {SmFideTitle(SmFideTitlesEnum::FM), 2100},
    {SmFideTitle(SmFideTitlesEnum::WGM), 2100},
    {SmFideTitle(SmFideTitlesEnum::IM), 2200},
    {SmFideTitle(SmFideTitlesEnum::GM), 2300},
};

std::string& SmFideTitle::to_string() const {
    auto value = std::find_if(
        fide_title_to_string_table.begin(), fide_title_to_string_table.end(),
        [this](const auto& m) { return m.second == this->value; });

    return const_cast<std::string&>(value->first);
}

SmFideTitle SmFideTitle::from_string(const std::string& str) {
    return fide_title_to_string_table.at(str);
}

u16 SmFideTitle::to_rating() const {
    return fide_title_to_rating_table.at(this->get_value());
}