//
// Created by Ferdinando Fioretto on 7/26/16.
//

#ifndef CSPXLGEN_INSTANCEFACTORY_HPP
#define CSPXLGEN_INSTANCEFACTORY_HPP

#include <string>
#include <vector>
#include "LargeInstance.hpp"
#include "Input.hpp"

class InstanceFactory {
    public:
        static LargeInstance::ptr create(int argc, char *argv[]) {

            Input::checkParams(argc, argv);
            std::string file = Input::getFileOut(argv);

            Output::ptr out = std::make_shared<Output>(file);
            for (int i = 0; i < argc; ++i) {
                if (!strcmp("--rand", argv[i])) {
                    int vars = std::stoi(argv[++i]);
                    int doms = std::stoi(argv[++i]);
                    double p1 = std::stof(argv[++i]);
                    double p2 = std::stof(argv[++i]);
                    return std::make_shared<LargeInstance>(vars, doms, p1, p2, out);
                }
            }
            return nullptr;
        }

};

#endif //CSPXLGEN_INSTANCEFACTORY_HPP
