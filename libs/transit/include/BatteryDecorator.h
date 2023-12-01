#ifndef BATTERYDECORATOR_H_
#define BATTERYDECORATOR_H_

#include "Drone.h"

/**
* @brief this class inherits from the Drone class and represents a Battery decorator
* that allows the Drone to move according to and maintain a batteryPower
* attribute
*/
class BatteryDecorator : public IEntity {
    public:
    /**
     * @brief Construct a Battery Decorator object
     * @param[in] drone the Drone to decorate onto
     * @param[in] batteryPower starting battery power
    */
        BatteryDecorator(Drone* drone, double batteryPower = 100);

    /**
     * @brief Placeholder constructor
    */
        ~BatteryDecorator() override;

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
     * @brief placeholder for custom update function
     * 
     * @param dt Delta Time
    */
        void update(double dt) override;
    private:
        Drone* drone = nullptr;
        double batteryPower = 100;
};

#endif