#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Human destructor
   */
  ~Human();

  /**
   * @brief Human move towards the destination, or select a new random
   * destination if the previous destination has been reached
   * @param dt Time change since the last update
   */
  void update(double dt);

 private:
  IStrategy* movement = nullptr;
};

#endif // HUMAN_H_
