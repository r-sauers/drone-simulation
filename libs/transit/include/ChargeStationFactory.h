#ifndef CHARGE_STATION_FACTORY_H_
#define CHARGE_STATION_FACTORY_H_

#include <vector>

#include "ChargeStation.h"
#include "IEntityFactory.h"

/**
 *@brief ChargeStation Factory to produce ChargeStation class.
 **/
class ChargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for ChargeStationFactory class.
   **/
  virtual ~ChargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
