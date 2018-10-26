//
// Created by lramirez on 14.11.18.
//

#ifndef BISQCK_UTILS_H
#define BISQCK_UTILS_H

#include <seqan/arg_parse.h>

struct BisquickOptions
{
    unsigned kmersize;
    seqan::CharString genomePath;
    inline BisquickOptions() :
            kmersize(30),genomePath("")
    {}
};

extern BisquickOptions bisquickOptions;

seqan::ArgumentParser::ParseResult
parseCommandLine(BisquickOptions & options, int argc, char const ** argv);

#endif //BISQCK_UTILS_H
