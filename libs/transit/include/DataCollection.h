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
    void turnRight();
    void turnLeft();
    void resetTurns();
    std::string getLastStrategy();
    void getBatteryLevel(double batteryLevel);
    void getStrategy(std::string strategy);
    void getDronePath(std::vector<float> start, std::vector<float> end, const routing::RoutingStrategy& pathing, const routing::IGraph* g);
  // some functions that track nodes
 private:
    int rightTurns = 0;
    int leftTurns = 0;
    std::string lastStrategy;
    std::vector<routing::IGraphNode*> nodePath;
    std::vector< std::vector<float> > posPath;
    std::vector<double> batteryLevel;
    std::vector<std::string> strategys;
};

#endif
