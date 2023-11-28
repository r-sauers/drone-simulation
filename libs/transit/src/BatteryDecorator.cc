#include "BatteryDecorator.h"
#include "Drone.h"

BatteryDecorator::BatteryDecorator(Drone* drone, double batteryPower) : Drone(const_cast<JsonObject&>(drone->getDetails())){
    this->batteryPower = batteryPower;
}

double BatteryDecorator::getBatteryPower() const {
    return batteryPower;
}

void BatteryDecorator::setBatteryPower(double batteryPower) {
    this->batteryPower = batteryPower;
}

void BatteryDecorator::update(double dt) {
    return;
}