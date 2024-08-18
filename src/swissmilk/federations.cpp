#include "federations.hpp"
#include <algorithm>
#include <string>
#include <map>

static const std::map<std::string, SmFederationsEnum> federation_to_long_name_table = {
    {"Afghanistan", SmFederationsEnum::AFG},
    {"Albania", SmFederationsEnum::ALB},
    {"Algeria", SmFederationsEnum::ALG},
    {"Andorra", SmFederationsEnum::AND},
    {"Angola", SmFederationsEnum::ANG},
    {"Antigua & Barbuda", SmFederationsEnum::ANT},
    {"Argentina", SmFederationsEnum::ARG},
    {"Armenia", SmFederationsEnum::ARM},
    {"Aruba", SmFederationsEnum::ARU},
    {"ASEAN", SmFederationsEnum::ASE},
    {"Australia", SmFederationsEnum::AUS},
    {"Austria", SmFederationsEnum::AUT},
    {"Azerbaijan", SmFederationsEnum::AZE},
    {"The Bahamas", SmFederationsEnum::BAH},
    {"Bahrain", SmFederationsEnum::BRN},
    {"Bangladesh", SmFederationsEnum::BAN},
    {"Barbados", SmFederationsEnum::BAR},
    {"Belarus", SmFederationsEnum::BLR},
    {"Belgium", SmFederationsEnum::BEL},
    {"Belize", SmFederationsEnum::BLZ},
    {"Bermuda", SmFederationsEnum::BER},
    {"Bolivia", SmFederationsEnum::BOL},
    {"Bosnia & Herzegovina", SmFederationsEnum::BIH},
    {"Botswana", SmFederationsEnum::BOT},
    {"Brazil", SmFederationsEnum::BRA},
    {"British Virgin Islands", SmFederationsEnum::IVB},
    {"Brunei", SmFederationsEnum::BRU},
    {"Bulgaria", SmFederationsEnum::BUL},
    {"Canada", SmFederationsEnum::CAN},
    {"Chile", SmFederationsEnum::CHI},
    {"China", SmFederationsEnum::CHN},
    {"Columbia", SmFederationsEnum::COL},
    {"Costa Rica", SmFederationsEnum::CRC},
    {"Croatia", SmFederationsEnum::CRO},
    {"Cuba", SmFederationsEnum::CUB},
    {"Cyprus", SmFederationsEnum::CYP},
    {"Czech Republic", SmFederationsEnum::CZE},
    {"Czechoslovakia", SmFederationsEnum::CSR},
    {"Denmark", SmFederationsEnum::DEN},
    {"Dominican Republic", SmFederationsEnum::DOM},
    {"East Germany", SmFederationsEnum::GDR},
    {"Ecuador", SmFederationsEnum::ECU},
    {"Egypt", SmFederationsEnum::EGY},
    {"El Salvador", SmFederationsEnum::ESA},
    {"England", SmFederationsEnum::ENG},
    {"Estonia", SmFederationsEnum::EST},
    {"Ethiopia", SmFederationsEnum::ETH},
    {"Faroe Islands", SmFederationsEnum::FAI},
    {"Fiji", SmFederationsEnum::FIJ},
    {"Finland", SmFederationsEnum::FIN},
    {"France", SmFederationsEnum::FRA},
    {"The Gambia", SmFederationsEnum::GAM},
    {"Georgia", SmFederationsEnum::GEO},
    {"Germany", SmFederationsEnum::GER},
    {"Ghana", SmFederationsEnum::GHA},
    {"Great Britain", SmFederationsEnum::GBR},
    {"Greece", SmFederationsEnum::GRE},
    {"Guatemala", SmFederationsEnum::GUA},
    {"Guernsey", SmFederationsEnum::GCI},
    {"Guernsey-Jersey", SmFederationsEnum::GBG},
    {"Guyana", SmFederationsEnum::GUY},
    {"Haiti", SmFederationsEnum::HAI},
    {"Honduras", SmFederationsEnum::HON},
    {"Hong Kong", SmFederationsEnum::HKG},
    {"Hungary", SmFederationsEnum::HUN},
    {"Iceland", SmFederationsEnum::ISL},
    {"India", SmFederationsEnum::IND},
    {"Indonesia", SmFederationsEnum::INA},
    {"Iran", SmFederationsEnum::IRI},
    {"Iraq", SmFederationsEnum::IRQ},
    {"Ireland", SmFederationsEnum::IRL},
    {"Israel", SmFederationsEnum::ISR},
    {"Italy", SmFederationsEnum::ITA},
    {"Jamaica", SmFederationsEnum::JAM},
    {"Japan", SmFederationsEnum::JPN},
    {"Jersey", SmFederationsEnum::JCI},
    {"Jordan", SmFederationsEnum::JOR},
    {"Kazakhstan", SmFederationsEnum::KAZ},
    {"Kenya", SmFederationsEnum::KEN},
    {"Kuwait", SmFederationsEnum::KUW},
    {"Kyrgyzstan", SmFederationsEnum::KGZ},
    {"Latvia", SmFederationsEnum::LAT},
    {"Lebanon", SmFederationsEnum::LIB},
    {"Libya", SmFederationsEnum::LBA},
    {"Liechtenstein", SmFederationsEnum::LIE},
    {"Lithuania", SmFederationsEnum::LTU},
    {"Luxembourg", SmFederationsEnum::LUX},
    {"Macau", SmFederationsEnum::MAC},
    {"FYR Macedonia", SmFederationsEnum::MKD},
    {"Madagascar", SmFederationsEnum::MAD},
    {"Malaysia", SmFederationsEnum::MAS},
    {"Malawi", SmFederationsEnum::MAW},
    {"Mali", SmFederationsEnum::MLI},
    {"Malta", SmFederationsEnum::MLT},
    {"Mauritania", SmFederationsEnum::MAU},
    {"Mauritius", SmFederationsEnum::MRI},
    {"Mexico", SmFederationsEnum::MEX},
    {"Moldova", SmFederationsEnum::MDA},
    {"Montenegro", SmFederationsEnum::MNE},
    {"Monaco", SmFederationsEnum::MNC},
    {"Mongolia", SmFederationsEnum::MGL},
    {"Morocco", SmFederationsEnum::MAR},
    {"Mozambique", SmFederationsEnum::MOZ},
    {"Myanmar", SmFederationsEnum::MYA},
    {"Namibia", SmFederationsEnum::NAM},
    {"Nepal", SmFederationsEnum::NEP},
    {"Netherlands", SmFederationsEnum::NED},
    {"Netherlands Antilles", SmFederationsEnum::AHO},
    {"New Zealand", SmFederationsEnum::NZL},
    {"Nicaragua", SmFederationsEnum::NCA},
    {"Nigeria", SmFederationsEnum::NGR},
    {"Nordic Team", SmFederationsEnum::NRD},
    {"Norway", SmFederationsEnum::NOR},
    {"Pakistan", SmFederationsEnum::PAK},
    {"Palestine", SmFederationsEnum::PLE},
    {"Panama", SmFederationsEnum::PAN},
    {"Papua New Guinea", SmFederationsEnum::PNG},
    {"Paraguay", SmFederationsEnum::PAR},
    {"Peru", SmFederationsEnum::PER},
    {"Philippines", SmFederationsEnum::PHI},
    {"Poland", SmFederationsEnum::POL},
    {"Portugal", SmFederationsEnum::POR},
    {"Puerto Rico", SmFederationsEnum::PUR},
    {"Qatar", SmFederationsEnum::QAT},
    {"Romania", SmFederationsEnum::ROM},
    {"Rwanda", SmFederationsEnum::RWA},
    {"Russia", SmFederationsEnum::RUS},
    {"Saarland", SmFederationsEnum::SAA},
    {"San Marino", SmFederationsEnum::SMR},
    {"Scotland", SmFederationsEnum::SCO},
    {"Senegal", SmFederationsEnum::SEN},
    {"Serbia", SmFederationsEnum::SRB},
    {"Seychelles", SmFederationsEnum::SEY},
    {"Singapore", SmFederationsEnum::SIN},
    {"Slovakia", SmFederationsEnum::SVK},
    {"Slovenia", SmFederationsEnum::SLO},
    {"Somalia", SmFederationsEnum::SOM},
    {"South Africa", SmFederationsEnum::RSA},
    {"Soviet Union", SmFederationsEnum::URS},
    {"Spain", SmFederationsEnum::ESP},
    {"Sri Lanka", SmFederationsEnum::SRI},
    {"Sudan", SmFederationsEnum::SUD},
    {"Surinam", SmFederationsEnum::SUR},
    {"Sweden", SmFederationsEnum::SWE},
    {"Switzerland", SmFederationsEnum::SUI},
    {"Syria", SmFederationsEnum::SYR},
    {"Tajikistan", SmFederationsEnum::TJK},
    {"Tanzania", SmFederationsEnum::TAN},
    {"Thailand", SmFederationsEnum::THA},
    {"Togo", SmFederationsEnum::TOG},
    {"Trinidad & Tobago", SmFederationsEnum::TRI},
    {"Tunisia", SmFederationsEnum::TUN},
    {"Turkey", SmFederationsEnum::TUR},
    {"Turkmenistan", SmFederationsEnum::TKM},
    {"U.S. Virgin Islands", SmFederationsEnum::ISV},
    {"Uganda", SmFederationsEnum::UGA},
    {"Ukraine", SmFederationsEnum::UKR},
    {"United Arab Emirates", SmFederationsEnum::UAE},
    {"United States of America", SmFederationsEnum::USA},
    {"Uruguay", SmFederationsEnum::URU},
    {"Uzbekistan", SmFederationsEnum::UZB},
    {"Venezuela", SmFederationsEnum::VEN},
    {"Vietnam", SmFederationsEnum::VIE},
    {"Virgin Islands", SmFederationsEnum::VIR},
    {"Wales", SmFederationsEnum::WLS},
    {"Yemen", SmFederationsEnum::YEM},
    {"Yugoslavia", SmFederationsEnum::YUG},
    {"Zair", SmFederationsEnum::ZAI},
    {"Zambia", SmFederationsEnum::ZAM},
    {"Zimbabwe", SmFederationsEnum::ZIM},
    {"International BrailleChess Association", SmFederationsEnum::IBC},
    {"International Committeeof Silent Chess", SmFederationsEnum::ICS},
    {"International PhysicallyDisabled Chess Association ", SmFederationsEnum::IPC},
    {"None", SmFederationsEnum::NON},
};

static const std::map<std::string, SmFederationsEnum> federation_to_code_table = {
    {"AFG", SmFederationsEnum::AFG},
    {"ALB", SmFederationsEnum::ALB},
    {"ALG", SmFederationsEnum::ALG},
    {"AND", SmFederationsEnum::AND},
    {"ANG", SmFederationsEnum::ANG},
    {"ANT", SmFederationsEnum::ANT},
    {"ARG", SmFederationsEnum::ARG},
    {"ARM", SmFederationsEnum::ARM},
    {"ARU", SmFederationsEnum::ARU},
    {"ASE", SmFederationsEnum::ASE},
    {"AUS", SmFederationsEnum::AUS},
    {"AUT", SmFederationsEnum::AUT},
    {"AZE", SmFederationsEnum::AZE},
    {"BAH", SmFederationsEnum::BAH},
    {"BRN", SmFederationsEnum::BRN},
    {"BAN", SmFederationsEnum::BAN},
    {"BAR", SmFederationsEnum::BAR},
    {"BLR", SmFederationsEnum::BLR},
    {"BEL", SmFederationsEnum::BEL},
    {"BLZ", SmFederationsEnum::BLZ},
    {"BER", SmFederationsEnum::BER},
    {"BOL", SmFederationsEnum::BOL},
    {"BIH", SmFederationsEnum::BIH},
    {"BOT", SmFederationsEnum::BOT},
    {"BRA", SmFederationsEnum::BRA},
    {"IVB", SmFederationsEnum::IVB},
    {"BRU", SmFederationsEnum::BRU},
    {"BUL", SmFederationsEnum::BUL},
    {"CAN", SmFederationsEnum::CAN},
    {"CHI", SmFederationsEnum::CHI},
    {"CHN", SmFederationsEnum::CHN},
    {"COL", SmFederationsEnum::COL},
    {"CRC", SmFederationsEnum::CRC},
    {"CRO", SmFederationsEnum::CRO},
    {"CUB", SmFederationsEnum::CUB},
    {"CYP", SmFederationsEnum::CYP},
    {"CZE", SmFederationsEnum::CZE},
    {"CSR", SmFederationsEnum::CSR},
    {"DEN", SmFederationsEnum::DEN},
    {"DOM", SmFederationsEnum::DOM},
    {"GDR", SmFederationsEnum::GDR},
    {"ECU", SmFederationsEnum::ECU},
    {"EGY", SmFederationsEnum::EGY},
    {"ESA", SmFederationsEnum::ESA},
    {"ENG", SmFederationsEnum::ENG},
    {"EST", SmFederationsEnum::EST},
    {"ETH", SmFederationsEnum::ETH},
    {"FAI", SmFederationsEnum::FAI},
    {"FIJ", SmFederationsEnum::FIJ},
    {"FIN", SmFederationsEnum::FIN},
    {"FRA", SmFederationsEnum::FRA},
    {"GAM", SmFederationsEnum::GAM},
    {"GEO", SmFederationsEnum::GEO},
    {"GER", SmFederationsEnum::GER},
    {"GHA", SmFederationsEnum::GHA},
    {"GBR", SmFederationsEnum::GBR},
    {"GRE", SmFederationsEnum::GRE},
    {"GUA", SmFederationsEnum::GUA},
    {"GCI", SmFederationsEnum::GCI},
    {"GBG", SmFederationsEnum::GBG},
    {"GUY", SmFederationsEnum::GUY},
    {"HAI", SmFederationsEnum::HAI},
    {"HON", SmFederationsEnum::HON},
    {"HKG", SmFederationsEnum::HKG},
    {"HUN", SmFederationsEnum::HUN},
    {"ISL", SmFederationsEnum::ISL},
    {"IND", SmFederationsEnum::IND},
    {"INA", SmFederationsEnum::INA},
    {"IRI", SmFederationsEnum::IRI},
    {"IRQ", SmFederationsEnum::IRQ},
    {"IRL", SmFederationsEnum::IRL},
    {"ISR", SmFederationsEnum::ISR},
    {"ITA", SmFederationsEnum::ITA},
    {"JAM", SmFederationsEnum::JAM},
    {"JPN", SmFederationsEnum::JPN},
    {"JCI", SmFederationsEnum::JCI},
    {"JOR", SmFederationsEnum::JOR},
    {"KAZ", SmFederationsEnum::KAZ},
    {"KEN", SmFederationsEnum::KEN},
    {"KUW", SmFederationsEnum::KUW},
    {"KGZ", SmFederationsEnum::KGZ},
    {"LAT", SmFederationsEnum::LAT},
    {"LIB", SmFederationsEnum::LIB},
    {"LBA", SmFederationsEnum::LBA},
    {"LIE", SmFederationsEnum::LIE},
    {"LTU", SmFederationsEnum::LTU},
    {"LUX", SmFederationsEnum::LUX},
    {"MAC", SmFederationsEnum::MAC},
    {"MKD", SmFederationsEnum::MKD},
    {"MAD", SmFederationsEnum::MAD},
    {"MAS", SmFederationsEnum::MAS},
    {"MAW", SmFederationsEnum::MAW},
    {"MLI", SmFederationsEnum::MLI},
    {"MLT", SmFederationsEnum::MLT},
    {"MAU", SmFederationsEnum::MAU},
    {"MRI", SmFederationsEnum::MRI},
    {"MEX", SmFederationsEnum::MEX},
    {"MDA", SmFederationsEnum::MDA},
    {"MNE", SmFederationsEnum::MNE},
    {"MNC", SmFederationsEnum::MNC},
    {"MGL", SmFederationsEnum::MGL},
    {"MAR", SmFederationsEnum::MAR},
    {"MOZ", SmFederationsEnum::MOZ},
    {"MYA", SmFederationsEnum::MYA},
    {"NAM", SmFederationsEnum::NAM},
    {"NEP", SmFederationsEnum::NEP},
    {"NED", SmFederationsEnum::NED},
    {"AHO", SmFederationsEnum::AHO},
    {"NZL", SmFederationsEnum::NZL},
    {"NCA", SmFederationsEnum::NCA},
    {"NGR", SmFederationsEnum::NGR},
    {"NRD", SmFederationsEnum::NRD},
    {"NOR", SmFederationsEnum::NOR},
    {"PAK", SmFederationsEnum::PAK},
    {"PLE", SmFederationsEnum::PLE},
    {"PAN", SmFederationsEnum::PAN},
    {"PNG", SmFederationsEnum::PNG},
    {"PAR", SmFederationsEnum::PAR},
    {"PER", SmFederationsEnum::PER},
    {"PHI", SmFederationsEnum::PHI},
    {"POL", SmFederationsEnum::POL},
    {"POR", SmFederationsEnum::POR},
    {"PUR", SmFederationsEnum::PUR},
    {"QAT", SmFederationsEnum::QAT},
    {"ROM", SmFederationsEnum::ROM},
    {"RWA", SmFederationsEnum::RWA},
    {"RUS", SmFederationsEnum::RUS},
    {"SAA", SmFederationsEnum::SAA},
    {"SMR", SmFederationsEnum::SMR},
    {"SCO", SmFederationsEnum::SCO},
    {"SEN", SmFederationsEnum::SEN},
    {"SRB", SmFederationsEnum::SRB},
    {"SEY", SmFederationsEnum::SEY},
    {"SIN", SmFederationsEnum::SIN},
    {"SVK", SmFederationsEnum::SVK},
    {"SLO", SmFederationsEnum::SLO},
    {"SOM", SmFederationsEnum::SOM},
    {"RSA", SmFederationsEnum::RSA},
    {"URS", SmFederationsEnum::URS},
    {"ESP", SmFederationsEnum::ESP},
    {"SRI", SmFederationsEnum::SRI},
    {"SUD", SmFederationsEnum::SUD},
    {"SUR", SmFederationsEnum::SUR},
    {"SWE", SmFederationsEnum::SWE},
    {"SUI", SmFederationsEnum::SUI},
    {"SYR", SmFederationsEnum::SYR},
    {"TJK", SmFederationsEnum::TJK},
    {"TAN", SmFederationsEnum::TAN},
    {"THA", SmFederationsEnum::THA},
    {"TOG", SmFederationsEnum::TOG},
    {"TRI", SmFederationsEnum::TRI},
    {"TUN", SmFederationsEnum::TUN},
    {"TUR", SmFederationsEnum::TUR},
    {"TKM", SmFederationsEnum::TKM},
    {"ISV", SmFederationsEnum::ISV},
    {"UGA", SmFederationsEnum::UGA},
    {"UKR", SmFederationsEnum::UKR},
    {"UAE", SmFederationsEnum::UAE},
    {"USA", SmFederationsEnum::USA},
    {"URU", SmFederationsEnum::URU},
    {"UZB", SmFederationsEnum::UZB},
    {"VEN", SmFederationsEnum::VEN},
    {"VIE", SmFederationsEnum::VIE},
    {"VIR", SmFederationsEnum::VIR},
    {"WLS", SmFederationsEnum::WLS},
    {"YEM", SmFederationsEnum::YEM},
    {"YUG", SmFederationsEnum::YUG},
    {"ZAI", SmFederationsEnum::ZAI},
    {"ZAM", SmFederationsEnum::ZAM},
    {"ZIM", SmFederationsEnum::ZIM},
    {"IBC", SmFederationsEnum::IBC},
    {"ICS", SmFederationsEnum::ICS},
    {"IPC", SmFederationsEnum::IPC},
    {"NON", SmFederationsEnum::NON},
};

std::string SmFederation::to_string() const {
    auto value = std::find_if(
                    federation_to_code_table.begin(), 
                    federation_to_code_table.end(),
                    [this](const auto& m) {return m.second == this->get_value();});
    
    return value->first;
}

SmFederation SmFederation::from_string(std::string str) {
    return federation_to_code_table.at(str);
}

std::string SmFederation::to_long_name() const {
    auto value = std::find_if(
                    federation_to_long_name_table.begin(), 
                    federation_to_long_name_table.end(),
                    [this](const auto& m) {return m.second == this->get_value();});
    
    return value->first;
}

SmFederation SmFederation::from_long_name(std::string str) {
    return federation_to_long_name_table.at(str);
}