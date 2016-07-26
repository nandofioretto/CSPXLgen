//
// Created by Ferdinando Fioretto on 7/25/16.
//

#ifndef CSPXLGEN_LARGEGRAPH_H
#define CSPXLGEN_LARGEGRAPH_H


#include <vector>
#include <utils.hpp>

using namespace misc_utils;

class LargeGraph {
public:
    typedef std::shared_ptr<LargeGraph> ptr;

    LargeGraph(size_t nodes, double p1)
            : nodes(nodes), p1(p1) {

        nodeEdges.resize(nodes, 0);
        size_t max_nb_edges = (nodes * (nodes - 1)) / 2;
        edges = std::ceil(p1 * max_nb_edges);
        utils::massert(LargeGraph::edges >= nodes - 1,
                       "The graph connectivity " + std::to_string(p1) +
                       "cannot ensure a connected graph.");

        EoutEdges = (LargeGraph::edges / (double)nodes);

        std::cout << "GRAPH - nodes: " << nodes << " Total Possible Edges: " << edges
           << " Expected outgpoing edges per node: " << EoutEdges << "\n";
    }

    void addEdge(size_t u, size_t v) {
        nodeEdges[u]++;
        nodeEdges[v]++;
    }

    size_t getNodes() const {
        return nodes;
    }

    const std::vector<size_t> &getNodeEdges() const {
        return nodeEdges;
    }

    size_t getEdges() const {
        return edges;
    }

    double getEoutEdges() const {
        return EoutEdges;
    }

    size_t getNodeEdge(size_t i) const {
        return nodeEdges[i];
    }

private:
    size_t nodes;
    // nodeEdges[i] contains the number of outgoing edges ofo node i
    std::vector<size_t> nodeEdges;
    // number of edges in the graph
    size_t edges;
    // Expected outgoing edges for each node
    double EoutEdges;
    // constraint connectivity
    double p1;

};


#endif //CSPXLGEN_LARGEGRAPH_H
