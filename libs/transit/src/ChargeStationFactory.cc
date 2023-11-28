#include "ChargeStationFactory.h"

IEntity* ChargeStationFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("charge_station") == 0) {
    std::cout << "ChargeStation Created" << std::endl;
    return new ChargeStation(entity);
  }
  return nullptr;
}
