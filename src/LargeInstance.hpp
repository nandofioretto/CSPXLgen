//
// Created by Ferdinando Fioretto on 7/25/16.
//

#ifndef CSPXLGEN_LARGEINSTANCE_H
#define CSPXLGEN_LARGEINSTANCE_H


#include <iostream>
#include <memory>
#include "Output.hpp"

class LargeInstance {
public:
    typedef std::shared_ptr<LargeInstance> ptr;
    LargeInstance(size_t nvars, int dom, double p1, double p2, Output::ptr out);
};


#endif //CSPXLGEN_LARGEINSTANCE_H
