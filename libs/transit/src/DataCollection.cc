#include "DataCollection.h"
#include "SimulationModel.h"
#include <iostream>
#include <fstream>

DataCollection* DataCollection::instance = nullptr;

DataCollection* DataCollection::getInstance(){
    if(instance == nullptr){
        instance = new DataCollection();
    }
    return instance;
}

DataCollection::DataCollection(){

}

DataCollection::~DataCollection(){
    
}

void DataCollection::turnRight(){
    rightTurns += 1;
}

void DataCollection::turnLeft(){
    leftTurns += 1;
}

void DataCollection::resetTurns(){
    if(rightTurnsVec.size() == 0 && first == true){
        first = false;
        return;
    }
    rightTurnsVec.push_back(rightTurns);
    leftTurnsVec.push_back(leftTurns);
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

void DataCollection::writeStrategysToCSV(){

    std::printf("writestrat called");

    std::ofstream outputFile(csvFilename);

    if(!outputFile.is_open()){

        std::cerr << "Error Opening csv file" << std::endl;
    }
    static DataCollection instance;

    for (int i = 0; i < strategys.size(); i++) {
        outputFile << strategys[i] << ": " << rightTurnsVec[i] << ", " << leftTurnsVec[i] << "\n";
    }

    outputFile << strategys.size() << " vs " << rightTurnsVec.size() << "\n";

    outputFile.close();
}

void DataCollection::writeBatteryToCSV(){

    std::printf("writeBattery called");

    std::ofstream outputFile(csvFilename2);

    if(!outputFile.is_open()){
        std::cerr << "Error Opening csv file" << std::endl;
    }

    for (int i : batteryLevel) {
        outputFile << batteryLevel[i];
        if(i < batteryLevel.size() - 1) {
            outputFile << ", ";
        }
    }

    outputFile.close();
}