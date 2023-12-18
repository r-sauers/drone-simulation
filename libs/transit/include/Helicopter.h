#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include "IEntity.h"
#include "IStrategy.h"

class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Helicopter destructor
   */
  ~Helicopter();

  /**
   * @brief Helicopters move towards the destination, or select a new random
   * destination if the previous destination has been reached
   * @param dt Time change since last update
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif // HELICOPTER_H_
