#ifndef BATTERYDECORATOR_H_
#define BATTERYDECORATOR_H_

#include "ChargeStation.h"
#include "Drone.h"

/**
 * @brief this class inherits from the IEntity class and represents a Battery
 * decorator that allows the Drone to move according to and maintain a
 * batteryPower attribute
 */
class BatteryDecorator : public Drone {
 public:
  /**
   * @brief Construct a Battery Decorator object
   * @param[in] drone the Drone to decorate onto
   * @param[in] batteryPower starting battery power
   */
  BatteryDecorator(Drone* drone, double batteryPower = 100);

  /**
   * @brief Gets the current battery power
   *
   * @return double current batteryPower
   */
  double getBatteryPower();

  /**
   * @brief set the battery power of the drone
   *
   * @param double batteryPower
   */
  void setBatteryPower(double batteryPower);

  /**
   * @brief updates the battery charge, and calls drone update function if
   * not charging
   *
   * @param dt Delta Time
   */
  void update(double dt) override;

 private:
  Drone* drone = nullptr;
  double batteryPower = 100;
  ChargeStation* station = nullptr;
  int charging = 0;
  int linked = 0;
  IStrategy* movement = nullptr;
  double counter = 0;
};

#endif // BATTERY_DECORATOR_H_
