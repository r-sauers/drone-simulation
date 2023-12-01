#include "BatteryDecorator.h"
#include "Drone.h"

BatteryDecorator::BatteryDecorator(Drone* drone, double batteryPower) {
    this->batteryPower = batteryPower;
    this->drone = drone;
}

double BatteryDecorator::getBatteryPower() {
    return batteryPower;
}

void BatteryDecorator::setBatteryPower(double batteryPower) {
    this->batteryPower = batteryPower;
}

void BatteryDecorator::update(double dt) {
    drone->update(dt);
}