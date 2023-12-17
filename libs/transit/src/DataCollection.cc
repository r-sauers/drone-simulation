#include "DataCollection.h"

#include <fstream>
#include <iostream>

#include "SimulationModel.h"

DataCollection* DataCollection::instance = nullptr;

DataCollection* DataCollection::getInstance() {
  if (instance == nullptr) {
    instance = new DataCollection();
  }
  return instance;
}

DataCollection::DataCollection() {}

DataCollection::~DataCollection() {}

void DataCollection::turnRight() { rightTurns += 1; }

void DataCollection::turnLeft() { leftTurns += 1; }

void DataCollection::resetTurns() {
  if (rightTurnsVec.size() == 0 && first == true) {
    first = false;
    leftTurns = 0;
    rightTurns = 0;
    return;
  }
  rightTurnsVec.push_back(rightTurns);
  leftTurnsVec.push_back(leftTurns);
  leftTurns = 0;
  rightTurns = 0;
}

std::string DataCollection::getLastStrategy() { return lastStrategy; }

void DataCollection::getBatteryLevel(double batteryL) {
  batteryLevel.push_back(batteryL);
  if (batteryLevel.size() == 10) {
    std::fstream outputFile;
    outputFile.open("batteryData.csv", std::ios_base::app);
    if (!outputFile.is_open()) {
      std::cerr << "Error Opening csv file" << std::endl;
    }
    for (int i = 0; i < 10; i++) {
      outputFile << batteryLevel.at(i);
      outputFile << ", ";
    }
    outputFile << "\n";
    outputFile.close();
    batteryLevel.clear();
  }
}

void DataCollection::getStrategy(std::string strategy) {
  lastStrategy = strategy;
  strategys.push_back(strategy);
}

void DataCollection::writeStrategysToCSV() {

  std::ofstream outputFile(csvFilename);

  if (!outputFile.is_open()) {
    std::cerr << "Error Opening csv file" << std::endl;
  }

    outputFile << "Strategy, right, left, time(dt)\n";

  static DataCollection instance;

  for (int i = 0; i < strategys.size(); i++) {
    outputFile << strategys[i] << ": " << rightTurnsVec[i] << ", "
               << leftTurnsVec[i] << ", " << timeTaken[i] << "\n";
  }

  outputFile.close();
}

void DataCollection::writeBatteryToCSV() {

  std::ofstream outputFile(csvFilename2);

  if (!outputFile.is_open()) {
    std::cerr << "Error Opening csv file" << std::endl;
  }

  for (int i : batteryLevel) {
    outputFile << batteryLevel[i];
    if (i < batteryLevel.size() - 1) {
      outputFile << ", ";
    }
  }

  outputFile.close();
}

void DataCollection::writeTimeToCSV() {
  std::ofstream outputFile("timeData.csv");
  if (!outputFile.is_open()) {
    std::cerr << "Error Opening csv file" << std::endl;
  }
  outputFile << totalTime;
  outputFile.close();
}

void DataCollection::addTotalTime(double dt) { 
    totalTime += dt;
    stratTime += dt;
}

void DataCollection::resetTime(){
  stratTime = 0.0;
}

void DataCollection::pushTimes(){
  timeTaken.push_back(stratTime);  
}
