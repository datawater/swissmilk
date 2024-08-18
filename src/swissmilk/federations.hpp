#pragma once

#include <string>

#include "utils.hpp"

enum class SMATTR_PACKED SmFederationsEnum {
    AFG,
    ALB,
    ALG,
    AND,
    ANG,
    ANT,
    ARG,
    ARM,
    ARU,
    ASE,
    AUS,
    AUT,
    AZE,
    BAH,
    BRN,
    BAN,
    BAR,
    BLR,
    BEL,
    BLZ,
    BER,
    BOL,
    BIH,
    BOT,
    BRA,
    IVB,
    BRU,
    BUL,
    CAN,
    CHI,
    CHN,
    COL,
    CRC,
    CRO,
    CUB,
    CYP,
    CZE,
    CSR,
    DEN,
    DOM,
    GDR,
    ECU,
    EGY,
    ESA,
    ENG,
    EST,
    ETH,
    FAI,
    FIJ,
    FIN,
    FRA,
    GAM,
    GEO,
    GER,
    GHA,
    GBR,
    GRE,
    GUA,
    GCI,
    GBG,
    GUY,
    HAI,
    HON,
    HKG,
    HUN,
    ISL,
    IND,
    INA,
    IRI,
    IRQ,
    IRL,
    ISR,
    ITA,
    JAM,
    JPN,
    JCI,
    JOR,
    KAZ,
    KEN,
    KUW,
    KGZ,
    LAT,
    LIB,
    LBA,
    LIE,
    LTU,
    LUX,
    MAC,
    MKD,
    MAD,
    MAS,
    MAW,
    MLI,
    MLT,
    MAU,
    MRI,
    MEX,
    MDA,
    MNE,
    MNC,
    MGL,
    MAR,
    MOZ,
    MYA,
    NAM,
    NEP,
    NED,
    AHO,
    NZL,
    NCA,
    NGR,
    NRD,
    NOR,
    PAK,
    PLE,
    PAN,
    PNG,
    PAR,
    PER,
    PHI,
    POL,
    POR,
    PUR,
    QAT,
    ROM,
    RWA,
    RUS,
    SAA,
    SMR,
    SCO,
    SEN,
    SRB,
    SEY,
    SIN,
    SVK,
    SLO,
    SOM,
    RSA,
    URS,
    ESP,
    SRI,
    SUD,
    SUR,
    SWE,
    SUI,
    SYR,
    TJK,
    TAN,
    THA,
    TOG,
    TRI,
    TUN,
    TUR,
    TKM,
    ISV,
    UGA,
    UKR,
    UAE,
    USA,
    URU,
    UZB,
    VEN,
    VIE,
    VIR,
    WLS,
    YEM,
    YUG,
    ZAI,
    ZAM,
    ZIM,
    IBC,
    ICS,
    IPC,
    NON
};

/**
 * @brief An enum-like class that represents a FIDE recognized federation
 *
 */
class SmFederation {
   private:
    SmFederationsEnum value;

   public:
    std::string to_string() const;
    static SmFederation from_string(std::string str);

    std::string to_long_name() const;
    static SmFederation from_long_name(std::string str);

    inline SmFederationsEnum get_value() const { return this->value; }

    inline void set_value(SmFederationsEnum value) { this->value = value; }

    inline bool operator==(SmFederation rhs) {
        return this->get_value() == rhs.get_value();
    }

    inline SmFederation& operator=(SmFederation& rhs) = default;
    inline SmFederation& operator=(const SmFederation& rhs) = default;

    friend std::ostream& operator<<(std::ostream& out, SmFederation& fed) {
        out << std::string("SmFederation { value: '") << fed.to_string()
            << std::string("' }");
        return out;
    }

    inline SmFederation() { this->value = SmFederationsEnum::NON; }

    inline SmFederation(SmFederationsEnum value) { this->value = value; }
};