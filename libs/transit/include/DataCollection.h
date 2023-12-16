#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include <vector>
#include "graph.h"
#include "routing_strategy.h"

/**
 * @brief
 */

class DataCollection {
 public:

   static DataCollection& getInstance();
   
   void turnRight();
   void turnLeft();
   void resetTurns();
   std::string getLastStrategy();
   void getBatteryLevel(double batteryLevel);
   void getStrategy(std::string strategy);
   void getDronePath(std::vector<float> start, std::vector<float> end, const routing::RoutingStrategy& pathing, const routing::IGraph* g);
   void writeStrategysToCSV();
   void writeBatteryToCSV();
  // some functions that track nodes
 private:

   DataCollection();
   ~DataCollection();
   DataCollection(const DataCollection&) = delete;
   DataCollection& operator=(const DataCollection&) = delete;
   
    static DataCollection* instance = nullptr;
    int rightTurns = 0;
    int leftTurns = 0;
    std::string lastStrategy;
    std::vector<routing::IGraphNode*> nodePath;
    std::vector< std::vector<float> > posPath;
    std::vector<double> batteryLevel;
    std::vector<std::string> strategys;
    std::vector<int> rightTurnsVec;
    std::vector<int> leftTurnsVec;
    std::string csvFilename = "strategyData.csv";
    std::string csvFilename2 = "batteryData.csv";
};

#endif
