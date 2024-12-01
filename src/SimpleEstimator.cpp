#include "SimpleGraph.h"
#include "SimpleEstimator.h"

// Constructor
SimpleEstimator::SimpleEstimator(std::shared_ptr<SimpleGraph> &g) : graph(g) {}

// Destructor
SimpleEstimator::~SimpleEstimator() {
    // Clean up any dynamically allocated memory or resources (if needed)
}

// Prepare auxiliary structures for estimation
void SimpleEstimator::prepare() {
    // Initialize histograms with appropriate sizes
    inDegreeHistogram.resize(totalVertices, 0);
    outDegreeHistogram.resize(totalVertices, 0);
    labelHistogram.resize(totalLabels, 0);

    // Populate histograms
    for (uint32_t i = 0; i < totalVertices; ++i) {
        outDegreeHistogram[outDegrees[i]]++;
        for (const auto &edge : graph->adj[i]) {
            uint32_t label = edge.first;
            uint32_t target = edge.second;
            labelHistogram[label]++;
            inDegreeHistogram[target]++;
        }
    }
}

// Estimate cardinalities
cardStat SimpleEstimator::estimate(Triple &q) {
    uint32_t estimatedCardinality = graph->getNoEdges(); // Start with total edges
    uint32_t srcOutDegree = 0;
    uint32_t trgInDegree = 0;

    // Estimate based on `src` (source vertex)
    if (q.src != NO_IDENTIFIER) {
        uint32_t srcOutDegree = outDegrees[q.src];
        estimatedCardinality = std::min(estimatedCardinality, srcOutDegree);
    }

    // Estimate based on `trg` (target vertex)
    if (q.trg != NO_IDENTIFIER) {
        uint32_t trgInDegree = inDegrees[q.trg];
        estimatedCardinality = std::min(estimatedCardinality, trgInDegree);
    }

    // Estimate based on `path` (edge labels)
    if (!q.path.empty()) {
        uint32_t pathLabelCount = 0;
        for (const auto &pathEntry : q.path) {
            for (const auto &labelDir : pathEntry.labels) {
                uint32_t label = labelDir.label; // Assume LabelDir contains `label`
                pathLabelCount += labelHistogram[label];
            }
        }
        estimatedCardinality = std::min(estimatedCardinality, pathLabelCount);
    }

    return cardStat{srcOutDegree, trgInDegree, estimatedCardinality};
}

