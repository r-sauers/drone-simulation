#define _USE_MATH_DEFINES
#include "ChargeStation.h"

#include <cmath>
#include <cstdlib>
#include <limits>

#include "Package.h"
#include "SimulationModel.h"

ChargeStation::ChargeStation(JsonObject& obj) : IEntity(obj) {
  dockedDrone = -1;
  Vector3 spawnPt = {static_cast<double>((std::rand() % (1500 + 1400)) - 1400),
                     static_cast<double>((std::rand() % (600 - 240)) + 240),
                     static_cast<double>((std::rand() % (800 + 800)) - 800)};
  position = spawnPt;
}

bool ChargeStation::update(int id) {
  if (dockedDrone == id) {  // Undocking case
    dockedDrone = -1;
    return true;
  } else if (dockedDrone == -1) {  // Docking case
    dockedDrone = id;
    return true;
  }
  return false;  // Failure case
}
