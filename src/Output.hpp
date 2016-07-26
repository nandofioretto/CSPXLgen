//
// Created by Ferdinando Fioretto on 7/26/16.
//

#ifndef CSPXLGEN_OUTPUT_HPP
#define CSPXLGEN_OUTPUT_HPP


#include <memory>
#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "Constraint.hpp"

#define KBytes 1000

class Output {

public:
    typedef std::shared_ptr<Output> ptr;

    Output(std::string file, int instanceNo=0, size_t buffSize=500*KBytes);

    virtual ~Output();

    void close();

    void appendDomains (size_t nVars, std::vector<int> domain);

    void appendTopology(size_t varID, std::vector<size_t> links);

    void appendConstraint(size_t u, size_t v, Constraint::ptr con);

    void dump(std::ofstream& os, std::string& buffer);

private:
    std::string bufferTopology;
    std::string bufferDomains;
    std::string bufferConstraints;
    const std::string outSep = " ";

    std::ofstream osTopology;
    std::ofstream osDomains;
    std::ofstream osConstraints;

    size_t bufferLimit;

};


#endif //CSPXLGEN_OUTPUT_HPP
