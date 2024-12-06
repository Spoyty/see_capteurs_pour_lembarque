#include "mbed.h"
#include "./mbed_zest-core-fmlr-72/TARGET_ZEST_CORE_FMLR-72/PinNames.h"
#include "hpma115.h"
using namespace std::chrono;
using namespace sixtron;

#ifndef DUST_READING_LIB_HPP
#define DUST_READING_LIB_HPP

namespace dust_reading {

class DustSensor {
public:
    // Constructeur
    DustSensor(PinName tx, PinName rx);

    // Initialisation et configuration
    bool initialize();

    // Lecture des mesures
    bool read(uint16_t &pm1_0, uint16_t &pm2_5, uint16_t &pm4_0, uint16_t &pm10);

private:
    HPMA115 sensor; // Instance du driver HPMA115
};

} // namespace dust_reading

#endif // DUST_READING_LIB_HPP
