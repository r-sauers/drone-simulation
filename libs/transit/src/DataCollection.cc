#include "DataCollection.h"
#include "SimulationModel.h"

void DataCollection::turnRight(){
    rightTurns += 1;
}

void DataCollection::turnLeft(){
    leftTurns += 1;
}

void DataCollection::resetTurns(){
    leftTurns = 0;
    rightTurns = 0;
}

void DataCollection::getBatteryLevel(double batteryLevel){
    //battery Level, pathStrategy, delivered, picked up
    //record these somehow, depends on # of drones
    batteryLevel.push_back(batteryLevel);


}

void DataCollection::getDronePath(std::vector<float> start, std::vector<float> end, const routing::RoutingStrategy& pathing, const routing::IGraph* g){
    std::vector< std::vector<float> > positionPath = g->GetPath(start, end, pathing);
    posPath = positionPath; 
}
