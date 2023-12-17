#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "SimulationModel.h"
#include "DataCollection.h"

BatteryDecorator::BatteryDecorator(Drone* drone, double batteryPower)
    : Drone(drone->getDetails()) {
  this->batteryPower = batteryPower;
  this->charging = 0;
  this->drone = drone;
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

  
  if (this->charging) {
    this->batteryPower += dt * 20;  // Charges over 5 seconds
    if (this->batteryPower >= 100) {
      this->charging = 0;
      this->batteryPower = 100;
      this->station->update(this->drone->getID());  // Undock
      this->drone->setSeekingCharge(false);
      this->drone->setAtStation(false);
    }
  } else {
    if (this->batteryPower > 0) {
      if (this->drone->getMoveStatus() == 2) {
        this->batteryPower -= dt; // Carrying Package, Drains over 100 seconds
      }
      else if (this->drone->getMoveStatus() == 1) {
        this->batteryPower -= dt / 1.5;  // Active, Drains over 150 seconds
      }
      else if (this->drone->getMoveStatus() == 0) {
        this->batteryPower -= dt / 2.0; // Idle, drains over 200 seconds
      }
    } else {
      if (this->drone->getSeekingCharge() == false &&
          this->drone->getAtStation() ==
              false) {  // Drone is not at station and not seeking charge
        this->drone->setSeekingCharge(true);
      }
    }

    if (this->drone->getAtStation()) {  // Drone is at station for charging
      if (this->station->dockDrone(this->drone->getID())) {  // Try to dock
        this->charging = true;
      }
    }

    drone->update(dt);

    counter += dt;
    if(counter >= 5) { // Write Battery level every one second
      counter = 0;
      DataCollection* instance = DataCollection::getInstance(); 
      instance->getBatteryLevel(this->batteryPower);
    }
    
    this->setPosition(this->drone->getPosition());
  }
}
