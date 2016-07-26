//
// Created by Ferdinando Fioretto on 7/26/16.
//

#ifndef CSPXLGEN_INPUT_HPP
#define CSPXLGEN_INPUT_HPP

#include <iostream>
#include <string>
#include <utils.hpp>

using namespace misc_utils;

namespace Input {


    int getNbinstances(char *argv[]) {
        return 1;//atoi(argv[1]);
    }

    int getMinNbArguments() {
        return 3;
    }

    std::string getFileOut(char *argv[]) {
        return argv[1];
    }

    std::string usage() {
        std::string ret = "CSPXLgen <outfile> --rand <nb-vars> <dom-size> <p1> <p2>\n";

//        std::string ret = "cspxlgen <nb_instances> <outfile> <instance>\n";
//        ret += "\twhere:\n";
//        ret += "\t  <nb_instances> = the number of instances to generate\n";
//        ret += "\t  <outfile>      = the output filename (will be numbered)\n";
//        ret += "\t  <instance>     = --random \n";
//        ret += "\n\t--random      nb-variables domain-size  p1 p2";

        return ret;
    }

    void checkParams(int argc, char *argv[]) {

        for (int i = 0; i < argc; ++i) {
            if (strcmp("--help", argv[i]) == 0) {
                std::cout << usage() << std::endl;
                exit(1);
            }
        }
        utils::massert(argc >= getMinNbArguments(),
                       "Wrong number of parameters received\n" + usage());

        for (int i = 0; i < argc; ++i) {
            if (strcmp("--rand", argv[i]) == 0 && (argc == getMinNbArguments() + 4))
            return;
        }

        std::cout << usage() << std::endl;
        exit(1);
    }

}
#endif //CSPXLGEN_INPUT_HPP
