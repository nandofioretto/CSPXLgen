//
// Created by Ferdinando Fioretto on 7/25/16.
//

#include <random>
#include "LargeInstance.hpp"
#include "LargeGraph.hpp"

LargeInstance::LargeInstance(size_t nVars, int domSize, double p1, double p2, Output::ptr out) {

    // Create a Large Graph, given the number of nodes (nVars) and p1
    LargeGraph::ptr graph = std::make_shared<LargeGraph>(nVars, p1);
    // The expected number of links for each node of the graph
    double expectedLinks = graph->getEoutEdges();
    std::vector<size_t> links;

    // Create the domains
    std::vector<int> domain(domSize);
    std::iota (std::begin(domain), std::end(domain), 0); // Fill with 0, 1, ..., domSize-1.


    double precUnits = 0.01;
    size_t perc = nVars * precUnits;
    int iPerc = 0;

    // Create the constraints
    Constraint::ptr con = std::make_shared<Constraint>(domSize, domSize, p2);
    std::default_random_engine pick;

    for (auto u = 0; u < graph->getNodes(); u++) {
        // Append domain of variableID=u on file
        out->appendDomains(u, domain);

        // Create constraint graph edges (u, v)  for some v > u
        links.clear();

        // Given a node u, every other node v can be selected for creating an edge (u, v)
        // with probability p = 1/expectedLinks
        double prob_v = expectedLinks > graph->getNodeEdge(u) ?
                        (1 / (expectedLinks - graph->getNodeEdge(u)))
                        : 0;
        std::bernoulli_distribution distribution(prob_v);

        for (auto v = u +1; v < graph->getNodes(); v++) {
            if (distribution(pick)) {
                graph->addEdge(u, v);
                links.push_back(v);
            }
        }

        // Output links
        out->appendTopology(u, links);


        // Output the constraints associated to the edges outgoing from u (i.e., (u,v) for all v in "links").
        for (auto v : links) {
            con->createRnd();
            out->appendConstraint(u, v, con);
        }

        if (u > 0 && perc > 0 && u % perc == 0) {
            std::cout << "\r" << 100 * (precUnits * iPerc++) << "% completed" << std::flush;
        }

    }
    std::cout << "\r100% completed" << std::endl;
    out->close();
}