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

 std::string DataCollection::getLastStrategy(){
    return lastStrategy;
}

void DataCollection::getBatteryLevel(double batteryL){
    batteryLevel.push_back(batteryL);
}

void DataCollection::getStrategy(std::string strategy){
    lastStrategy = strategy; 
    strategys.push_back(strategy);
}

void DataCollection::getDronePath(std::vector<float> start, std::vector<float> end, const routing::RoutingStrategy& pathing, const routing::IGraph* g){
    std::vector< std::vector<float> > positionPath = g->GetPath(start, end, pathing);

    //write/save old path maybe somehow

    posPath = positionPath; 
}
