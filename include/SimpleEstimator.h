#ifndef QS_SIMPLEESTIMATOR_H
#define QS_SIMPLEESTIMATOR_H

#include "Estimator.h"
#include "SimpleGraph.h"
#include <vector>
#include <memory>

class SimpleEstimator : public Estimator {
private:
    std::shared_ptr<SimpleGraph> graph; // Pointer to the graph

    // Graph statistics and auxiliary data structures
    uint32_t totalVertices;              // Total number of vertices in the graph
    uint32_t totalEdges;                 // Total number of edges in the graph
    uint32_t totalDistinctEdges;         // Total number of distinct edges in the graph
    uint32_t totalLabels;                // Total number of edge labels in the graph

    std::vector<uint32_t> outDegrees;    // Out-degrees of each vertex
    std::vector<uint32_t> inDegrees;  
    
    std::vector<uint32_t> inDegreeHistogram;   // Histogram for in-degrees
    std::vector<uint32_t> outDegreeHistogram;  // Histogram for out-degrees
    std::vector<uint32_t> labelHistogram;  
    std::vector<uint32_t> outDegrees; // Out-degree of each vertex
    std::vector<uint32_t> inDegrees;    // Histogram for label frequencies
   // In-degrees of each vertex

public:
    explicit SimpleEstimator(std::shared_ptr<SimpleGraph> &g); // Constructor
    ~SimpleEstimator(); // Destructor

    void prepare() override; // Prepares auxiliary structures for estimation
    cardStat estimate(Triple &q) override; // Estimates cardinality for a given query
};

#endif // QS_SIMPLEESTIMATOR_H
