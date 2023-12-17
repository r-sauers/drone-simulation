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
#include "DataCollection.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
  seekingCharge = false;
  moveStatus = 0;
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
      if(currentStrategy == strat){
        std::string temp = strat;
        temp[0] = toupper(temp[0]);
        currentStrategy = temp;
      }else{
        currentStrategy = strat;
      }
      
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
    

    Vector3 chargeDestination = model->chargeStations.back()->getPosition();

    toCharge = new AstarStrategy(position, chargeDestination, model->getGraph());
    moveStatus = 1;
  }

  if (toCharge) {
    toCharge->move(this, dt);
    moveStatus = 1;

    if (toCharge->isCompleted()) {
      delete toCharge;
      toCharge = nullptr;
      pickedUp = false;
      atStation = true;
      moveStatus = 0;
    }
  }
  else {
    if (available)
      getNextDelivery();

    if (toPackage) {
      toPackage->move(this, dt);
      moveStatus = 1;

      if (toPackage->isCompleted()) {
        delete toPackage;
        toPackage = nullptr;
        pickedUp = true;
        moveStatus = 2;
      }
    } else if (toFinalDestination) {
      toFinalDestination->move(this, dt);
      moveStatus = 2;
      if (!pickedUp && (abs(position.x - package->getPosition().x) < 50) && (abs(position.z - package->getPosition().z) < 50)) {
        pickedUp = true;
      }

      if (package && pickedUp) {
        package->setPosition(position);
        package->setDirection(direction);
        moveStatus = 2;
      }

      if (toFinalDestination->isCompleted()) {
        delete toFinalDestination;
        toFinalDestination = nullptr;
        package->handOff();
        package = nullptr;
        available = true;
        pickedUp = false;
        moveStatus = 0;
        DataCollection* instance = DataCollection::getInstance();
        instance->pushTimes();
      }
    }
    else {
      moveStatus = 0;
    }
  }
  DataCollection* instance = DataCollection::getInstance(); 
  if(currentStrategy != instance->getLastStrategy()){
    instance->getStrategy(currentStrategy);
    instance->resetTime();
    instance->resetTurns();
 }
}

void Drone::setDirection(Vector3 dir_){

  double dot = direction * dir_;
  double angle = std::acos(dot);  

  direction = dir_;


  DataCollection* instance = DataCollection::getInstance(); 

  if(angle <= 3.1415926535){
    instance->turnRight();
  }else{
    instance->turnLeft();
  }
}

void Drone::rotate(double angle){
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
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

int Drone::getMoveStatus() {
  return this->moveStatus;
}
