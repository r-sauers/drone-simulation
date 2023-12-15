#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  seekingCharge = false;
}

Drone::Drone(const JsonObject& obj) : IEntity(obj) {
  available = true;
  seekingCharge = false;
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
  if (toCharge) delete toCharge;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {
  if (seekingCharge && !toCharge && !atStation) {
    available = false;

    Vector3 chargeDestination = model->chargeStations.back()->getPosition();

    toCharge = new BeelineStrategy(position, chargeDestination);
  }

  if (toCharge) {
    toCharge->move(this, dt);
    std::cout << "Moving to Charge" << std::endl;

    if (toCharge->isCompleted()) {
      delete toCharge;
      toCharge = nullptr;
      available = true;
      atStation = true;
    }
  }

  if (available)
    getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}

int Drone::getID() {
  return id;
}

bool Drone::getSeekingCharge() {
  return seekingCharge;
}

void Drone::setSeekingCharge(bool seek) {
  seekingCharge = seek;
}

bool Drone::getAtStation() {
  return atStation;
}

void Drone::setAtStation(bool atStation) {
  this->atStation = atStation;
}
