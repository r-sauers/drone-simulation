#ifndef CHARGESTATION_H_
#define CHARGESTATION_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @class ChargeStation
 * @brief Represents a ChargeStation in a physical system. A ChargeStation is
 * spawned on the map at the beginning of each run of the simulation.
 */
class ChargeStation : public IEntity {
 public:
  /**
   * @brief ChargeStations are created with a JsonObject
   * @param obj JSON object containing the ChargeStation's information
   */
  ChargeStation(JsonObject& obj);

  /**
   * @brief Docks a drone to the station, if possible, or undocks the drone if
   * called by the drone that is currently docked, updates dockedDrone
   * accordingly
   * @param id Drone id of querying drone
   * @return If the update worked (true if the station was open and was filled
   * or if the station was filled but update was called by the drone currently
   * occupying the station, false otherwise, since no update is possible)
   */
  bool update(int id);

  /**
   * @brief Removing the copy constructor operator
   * so that ChargeStations cannot be copied.
   */
  ChargeStation(const ChargeStation& ChargeStation) = delete;

  /**
   * @brief Removing the assignment operator
   * so that ChargeStations cannot be copied.
   */
  ChargeStation& operator=(const ChargeStation& ChargeStation) = delete;

 private:
  int dockedDrone;  // The current drone that is at the chargestation, if any
};

#endif
