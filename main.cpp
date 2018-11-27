//
// Created by lramirez on 19.08.18.
//

#include <iostream>

#include <dirent.h>

#include "bisquick.h"
#include "bisquick_index.h"
#include "utils.h"

#include <seqan/seq_io.h>

int main(int argc, char const ** argv)
{
    // Parse the command line.
    auto parsecmdln =  parseCommandLine(bisquickOptions, argc, argv);

    // If parsing was not successful then exit with code 1 if there were errors.
    // Otherwise, exit with code 0 (e.g. help was printed).
    if (parsecmdln != seqan::ArgumentParser::PARSE_OK)
        return parsecmdln == seqan::ArgumentParser::PARSE_ERROR;
    auto fastafile = open_directory(toCString(bisquickOptions.genomePath));
    auto i = createIndex(fastafile);





    for (auto i = fastafile.begin(); i != fastafile.end(); ++i)
        std::cout << *i << ' '<< std::endl;

/*
    std::cout << "Path   \t" << bisquickOptions.genomePath << '\n'
              << "kmersize\t" << bisquickOptions.kmersize<< '\n';
*/

    return 0;
}