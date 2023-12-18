#define _USE_MATH_DEFINES

#include "ChargeStation.h"

#include <cmath>
#include <cstdlib>
#include <limits>

#include "Package.h"
#include "SimulationModel.h"

ChargeStation::ChargeStation(JsonObject& obj) : IEntity(obj) {
  dockedDrone = -1;
}

void ChargeStation::update(double dt) {}

bool ChargeStation::dockDrone(int id) {
  if (dockedDrone == id) {  // Undocking case
    dockedDrone = -1;
    return true;
  } else if (dockedDrone == -1) {  // Docking case
    dockedDrone = id;
    return true;
  }
  return false;  // Failure case
}
