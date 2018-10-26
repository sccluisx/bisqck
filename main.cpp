//
// Created by lramirez on 19.08.18.
//

#include <iostream>
#include "bisquick.h"
#include "utils.h"



int main(int argc, char const ** argv)
{
    // Parse the command line.
    auto res =  parseCommandLine(bisquickOptions, argc, argv);

    // If parsing was not successful then exit with code 1 if there were errors.
    // Otherwise, exit with code 0 (e.g. help was printed).
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res == seqan::ArgumentParser::PARSE_ERROR;

    std::cout << "Path   \t" << bisquickOptions.genomePath << '\n'
              << "kmersize\t" << bisquickOptions.kmersize<< '\n';

    return 0;
}