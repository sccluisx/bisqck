//
// Created by lramirez on 14.11.18.
//

#include "utils.h"

BisquickOptions bisquickOptions;


seqan::ArgumentParser::ParseResult
parseCommandLine(BisquickOptions & options, int argc, char const ** argv)
{
    // Setup ArgumentParser.
    seqan::ArgumentParser parser("bisquick");


    // Set short description, version, and date.
    setShortDescription(parser, "Bisquick");
    setVersion(parser, "0.5");
    setDate(parser, "October 2018");

    // Define usage line and long description.
    addUsageLine(parser,
                 "[\\fIOPTIONS\\fP] \"\\fITEXT\\fP\"");
    addDescription(parser,
                   "This program allows simple character modifications to "
                   "each i-th character.");


    // We require one argument.
    addArgument(parser, seqan::ArgParseArgument(
            seqan::ArgParseArgument::STRING, "PATH"));

    // Define Options
    addOption(parser, seqan::ArgParseOption(
            "k", "kmersize", "Indicate the length of the kmer.",
            seqan::ArgParseArgument::INTEGER, "INT"));
    setDefaultValue(parser, "kmersize", "30");

    // Parse command line.
    seqan::ArgumentParser::ParseResult res = seqan::parse(parser, argc, argv);

    // Only extract  options if the program will continue after parseCommandLine()
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res;

    // Extract option values.
    getOptionValue(options.kmersize, parser, "kmersize");
    getArgumentValue(options.genomePath, parser, 0);
    return seqan::ArgumentParser::PARSE_OK;

}
