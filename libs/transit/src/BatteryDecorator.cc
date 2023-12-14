#include "BatteryDecorator.h"
#include "SimulationModel.h"
#include "BeelineStrategy.h"

BatteryDecorator::BatteryDecorator(Drone* drone, double batteryPower)
    : Drone(drone->getDetails()) {
  this->batteryPower = batteryPower;
  this->charging = 0;
  this->drone = drone;
  // this->station = this->model->chargeStations.back();
}

double BatteryDecorator::getBatteryPower() { return batteryPower; }

void BatteryDecorator::setBatteryPower(double batteryPower) {
  this->batteryPower = batteryPower;
}

void BatteryDecorator::update(double dt) {
  if (!this->linked) {
    this->drone->linkModel(model);
    this->linked = 1;
  }

  if (!this->station) {
    this->station = this->model->chargeStations.back();
  }

  std::cout << "Battery Power: " << this->batteryPower << std::endl;
  if (this->charging) {
    this->batteryPower += dt * 20;  // Charges over 5 seconds
    if (this->batteryPower >= 100) {
      this->charging = 0;
      this->batteryPower = 100;
      this->station->update(this->drone->getID());  // Undock
    }
  } else {
    if (this->batteryPower > 0) {
      this->batteryPower -= dt * 2;  // Drains over 50 seconds
      if ((this->drone->getPosition() == this->station->getPosition()) &&
          (this->drone->getSeekingCharge() == 1)) {
        if (this->station->dockDrone(this->drone->getID())) {  // Try to dock
          this->charging = 1;
          this->drone->setSeekingCharge(0);
        } else {
          this->drone->update(dt);
          this->setPosition(this->drone->getPosition());
        }
      }
    }
  }
}

