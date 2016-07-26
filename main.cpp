#include <iostream>
#include <InstanceFactory.hpp>
#include "string_utils.hpp"
#include "LargeInstance.hpp"
#include "Input.hpp"

using namespace std;
using namespace misc_utils;

int main(int argc, char* argv[]) {

    Input::checkParams(argc, argv);

    std::string filePath = Input::getFileOut(argv);
    std::string pathout = string_utils::split_path_file(filePath)[0];
    std::string fileout = string_utils::split_path_file(filePath)[1];
    int nbInstances = Input::getNbinstances(argv);

    LargeInstance::ptr instance = InstanceFactory::create(argc, argv);

    return 0;
}