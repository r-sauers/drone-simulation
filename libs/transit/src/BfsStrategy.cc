#include "BfsStrategy.h"

#include "routing/breadth_first_search.h"

BfsStrategy::BfsStrategy(Vector3 pos, Vector3 des, const routing::IGraph* g) {
  std::vector<float> start = {static_cast<float>(pos[0]),
                              static_cast<float>(pos[1]),
                              static_cast<float>(pos[2])};
  std::vector<float> end = {static_cast<float>(des[0]),
                            static_cast<float>(des[1]),
                            static_cast<float>(des[2])};
  path = g->GetPath(start, end, routing::BreadthFirstSearch::Default());
}
