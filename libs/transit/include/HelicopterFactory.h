#ifndef HELICOPTER_FACTORY_H_
#define HELICOPTER_FACTORY_H_

#include <vector>

#include "Helicopter.h"
#include "IEntityFactory.h"

/**
 *@brief Helicopter Factory to produce Helicopter class.
 **/
class HelicopterFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for HelicopterFactory class.
   **/
  virtual ~HelicopterFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif // HELICOPTER_FACTORY_H_
