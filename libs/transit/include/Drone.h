#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  Drone(const JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  void setDirection(Vector3 dir_) override;

  void rotate(double angle);

  /**
   * @brief Gets the ID of the drone
   * @return The ID of the drone
   */
  int getID();

  /**
   * @brief Gets the charge seeking status of the drone
   * @return The charge seeking status of the drone
   */
  bool getSeekingCharge();

  /**
   * @brief Sets the charge seeking status of the drone
   * @param seek the new charge seeking status of the drone
   */
  void setSeekingCharge(bool seek);

  /**
   * @brief Gets the status of the drone that states whether its at a station or
   * not
   * @return The status of the drone that states whether its at a station or not
   */
  bool getAtStation();

  /**
   * @brief Gets the status of the drone that states whether its moving, carrying or charging
   * not
   * @return The status of the drone that states whether its moving, carrying or charging
   */
  int getMoveStatus();

  /**
   * @brief Sets the status of the drone that states whether its at a station or
   * not
   * @param atStation the new status of the drone that states whether its at a
   * station or not
   */
  void setAtStation(bool atStation);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  //  private
  int moveStatus = 0;
  bool available = false;
  bool pickedUp = false;
  bool seekingCharge = false;
  bool atStation = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  IStrategy* toCharge = nullptr;
  std::string currentStrategy;
  std::string futureStrategy;
};

#endif
