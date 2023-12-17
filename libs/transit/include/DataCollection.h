#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

#include <vector>

#include "graph.h"
#include "routing_strategy.h"

/**
 * @class DataCollection
 * @brief Gathers data about the number and type of turns, total time, time in
 * each strategy, and battery level for analysis
 */
class DataCollection {
 public:
  /**
   * @brief Gets the one instance of the DataCollection singleton, or creates it
   * if it has not been created yet
   * @return The DataCollection object instance
   */
  static DataCollection* getInstance();

  /**
   * @brief Adds a right turn to rightTurns total
   */
  void turnRight();

  /**
   * @brief Adds a left turn to leftTurns total
   */
  void turnLeft();

  /**
   * @brief Resets turn counters
   */
  void resetTurns();

  /**
   * @brief Gets the last used strategy for use in strategy data collection
   * @return The name of the type of prior strategy
   */
  std::string getLastStrategy();

  /**
   * @brief Adds the current drone battery level to the batteryLevels vector
   * for eventual writing to the batteryData CSV file
   * @param batteryLevel The drone battery level at time of function call
   */
  void getBatteryLevel(double batteryLevel);

  /**
   * @brief Adds the current strategy to the strategies vector and makes
   * lastStretegy equal the current strategy
   * @param strategy The current strategy to be used
   */
  void getStrategy(std::string strategy);

  /**
   * @brief Sets posPath to the current path the drone is taking
   * @param start The location of the start of the current path
   * @param end The location of the end of the current path
   * @param pathing The strategy used for the current path
   * @param g The graph of nodes that the path uses
   */
  void getDronePath(std::vector<float> start, std::vector<float> end,
                    const routing::RoutingStrategy& pathing,
                    const routing::IGraph* g);

  /**
   * @brief Writes the strategy and turn data to the strategyData CSV file
   */
  void writeStrategysToCSV();

  /**
   * @brief Writes the battery data to the batteryData CSV file
   */
  void writeBatteryToCSV();

  /**
   * @brief Writes the time data to the timeData CSV file
   */
  void writeTimeToCSV();

  /**
   * @brief Adds most recent time delta to the total time
   * @param dt The time delta to add to the total time
   */
  void addTotalTime(double dt);

 private:
  /**
   * @brief DataCollection constructor, only used in getInstance
   * @return The DataCollection object instance
   */
  DataCollection();

  /**
   * @brief DataCollection destructor
   */
  ~DataCollection();

  /**
   * @brief Remove DataCollection assignment constructor
   */
  DataCollection(const DataCollection&) = delete;

  /**
   * @brief Remove DataCollection copy constructor
   */
  DataCollection& operator=(const DataCollection&) = delete;

  static DataCollection* instance;

  bool first = true;
  int rightTurns = 0;
  int leftTurns = 0;
  double totalTime;
  std::string lastStrategy;
  std::vector<routing::IGraphNode*> nodePath;
  std::vector<std::vector<float> > posPath;
  std::vector<double> batteryLevel;
  std::vector<std::string> strategys;
  std::vector<int> rightTurnsVec;
  std::vector<int> leftTurnsVec;
  std::string csvFilename = "strategyData.csv";
  std::string csvFilename2 = "batteryData.csv";
};

#endif
