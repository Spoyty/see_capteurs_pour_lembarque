#include "dust_reading_lib.hpp"

namespace dust_reading {

// Constructeur
DustSensor::DustSensor(PinName tx, PinName rx) : sensor(tx, rx) {}

// Initialisation du capteur
bool DustSensor::initialize() {
    if (sensor.stop_measurement() != HPMA115::ErrorType::Ok) return false;
    if (sensor.stop_autosend() != HPMA115::ErrorType::Ok) return false;
    if (sensor.set_adjust_coef(200) != HPMA115::ErrorType::Ok) return false;

    uint8_t coef;
    if (sensor.read_adjust_coef(&coef) != HPMA115::ErrorType::Ok || coef != 200) {
        return false;
    }

    return sensor.start_measurement() == HPMA115::ErrorType::Ok;
}

// Lecture des données
bool DustSensor::read(uint16_t &pm1_0, uint16_t &pm2_5, uint16_t &pm4_0, uint16_t &pm10) {
    hpma115_data_t data;

    if (sensor.read_measurement(&data) != HPMA115::ErrorType::Ok) {
        return false;
    }

    // Transférer les données dans les variables de sortie
    pm1_0 = data.pm1_0;
    pm2_5 = data.pm2_5;
    pm4_0 = data.pm4_0;
    pm10 = data.pm10;

    return true;
}

} // namespace dust_reading
