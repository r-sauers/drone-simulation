#include "BatteryDecorator.h"
#include "SimulationModel.h"

BatteryDecorator::BatteryDecorator(Drone* drone, double batteryPower)
    : Drone(drone->getDetails()) {
  this->batteryPower = batteryPower;
  this->charging = 0;
  //this->station = chargeStations.back();
}

double BatteryDecorator::getBatteryPower() { return batteryPower; }

void BatteryDecorator::setBatteryPower(double batteryPower) {
  this->batteryPower = batteryPower;
}

void BatteryDecorator::update(double dt) {
  if (charging) {
    this->batteryPower += dt * 20;  // Charges over 5 seconds
    if (this->batteryPower >= 100) {
      this->charging = 0;
      this->batteryPower = 100;
      this->station->update(this->drone->getID());  // Undock
    }
  } else {
    this->batteryPower -= dt * 2;  // Drains over 50 seconds
    if (this->batteryPower > 0) {
      if ((this->drone->getPosition() == this->station->getPosition()) &&
          (this->drone->getSeekingCharge() == 1)) {
        if (this->station->update(this->drone->getID())) {  // Try to dock
          this->charging = 1;
          this->drone->setSeekingCharge(0);
        } else {
          drone->update(dt);
        }
      }
    }
  }
}