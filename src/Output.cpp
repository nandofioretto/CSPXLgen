//
// Created by Ferdinando Fioretto on 7/26/16.
//

#include "Output.hpp"



Output::Output(std::string file, int instanceNo, size_t buffSize)
        : bufferLimit(buffSize)
{
    std::string fileTopology;
    std::string fileDomains;
    std::string fileConstraints;

    size_t found = file.find_last_of(".");
    std::string extension = file.substr(found+1);
    if (found == std::string::npos) {
        fileTopology = file + "_" + std::to_string(instanceNo) + ".cgxl";
        fileDomains = file + "_" + std::to_string(instanceNo) + ".dmxl";
        fileConstraints = file + "_" + std::to_string(instanceNo) + ".cnxl";
    }
    else if ( extension.compare("topo") != 0 ){
        file = file.substr(0, found);
        fileTopology = file + "_" + std::to_string(instanceNo) + ".cgxl";
        fileDomains = file + "_" + std::to_string(instanceNo) + ".dmxl";
        fileConstraints = file + "_" + std::to_string(instanceNo) + ".cnxl";
    }
    else std::cout << "Cannot open file: " << file << std::endl;

    osTopology.open(fileTopology.c_str(), std::ofstream::out);
    osDomains.open(fileDomains.c_str(), std::ofstream::out);
    osConstraints.open(fileConstraints.c_str(), std::ofstream::out);
}



Output::~Output() {
    close();
}

void Output::close() {
    osTopology << bufferTopology;
    bufferTopology.clear();
    osTopology.close();

    osDomains << bufferDomains;
    bufferDomains.clear();
    osDomains.close();

    osConstraints << bufferConstraints;
    bufferConstraints.clear();
    osConstraints.close();
}

void Output::appendTopology(size_t varID, std::vector<size_t> links) {
    if (links.empty()) return;

    bufferTopology += std::to_string(varID) + outSep;
    for (auto u : links) {
        bufferTopology += std::to_string(u) + outSep;
    }
    bufferTopology += "\n";

    dump(osTopology, bufferTopology);
}

void Output::appendDomains(size_t varID, std::vector<int> domain) {
    bufferDomains += std::to_string(varID) + outSep;
    for (auto d : domain) {
        bufferDomains += std::to_string(d) + outSep;
    }
    bufferDomains += "\n";

    dump(osDomains, bufferDomains);
}

void Output::appendConstraint(size_t u, size_t v, Constraint::ptr con) {
    bufferConstraints += std::to_string(u) + outSep + std::to_string(v) + outSep;

    for (auto val : con->getValues()) {
        bufferConstraints += std::to_string(val) + outSep;
    }
    bufferConstraints += "\n";

    dump(osConstraints, bufferConstraints);
}


void Output::dump(std::ofstream& os, std::string& buffer) {
    if( os.is_open()) {
        if (buffer.size() >= bufferLimit) {
            os << buffer;
            buffer.clear();
        }
    }
    else std::cout << "Cannot open buffer: ";
}