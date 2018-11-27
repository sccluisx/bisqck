//
// Created by lramirez on 14.11.18.
//

#include "utils.h"

BisquickOptions bisquickOptions;


seqan::ArgumentParser::ParseResult
parseCommandLine(BisquickOptions & bisquickOptions, int argc, char const ** argv)
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
                   "Bisulfite analysis as fast as baking a pie! ");


    // We require one argument.
    //addArgument(parser, seqan::ArgParseArgument(
    //        seqan::ArgParseArgument::STRING, "PATH"));

    // Define Options
    addOption(parser, seqan::ArgParseOption(
            "k", "kmersize", "Indicate the length of the kmer.",
            seqan::ArgParseArgument::INTEGER, "INT"));
    addOption(parser, seqan::ArgParseOption(
            "gp", "genomePath", "Directory path of the genome.",
            seqan::ArgParseArgument::STRING, "STRING"));
    addOption(parser, seqan::ArgParseOption(
            "r", "readsdir", "Directory of the reads.",
            seqan::ArgParseArgument::STRING, "STRING"));
    addOption(parser, seqan::ArgParseOption(
            "o", "output", "Output file.",
            seqan::ArgParseArgument::STRING, "STRING"));




    setDefaultValue(parser, "kmersize", "30");

    // Parse command line.
    seqan::ArgumentParser::ParseResult res = seqan::parse(parser, argc, argv);

    // Only extract  options if the program will continue after parseCommandLine()
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res;

    // Extract option values.
    getOptionValue(bisquickOptions.kmersize, parser, "kmersize");
    getOptionValue(bisquickOptions.genomePath, parser, "genomePath");
    //getOptionValue(options.readsdir, parser, "readsdir");
    //getOptionValue(options.output, parser, "output");
    //getArgumentValue(options.genomePath, parser, 0);
    return seqan::ArgumentParser::PARSE_OK;

}





// --------------------------------------------------------------------------
// Function open_directory(char * curdir);
// --------------------------------------------------------------------------

// receives a  directory curdir to open all files in it */
std::vector<std::string> open_directory(char * curdir)
{
    std::vector<std::string> fastafiles;
    DIR           *d;
    struct dirent *dir;
    d = opendir(curdir);
    int file_counter=0;			 // file counter
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(dir->d_name)
                if((std::strcmp(dir->d_name,".")) && (std::strcmp(dir->d_name,"..")) ) {
                    int totsize = strlen(curdir)+strlen(dir->d_name);
                    char * fastafile=NULL;
                    fastafile = (char *)malloc(sizeof(char) * totsize);
                    strcpy (fastafile,curdir);
                    strcat (fastafile,"/");
                    strcat (fastafile,dir->d_name);
                    //std::cout << "___________________"<<fastafile<<"\n";
                    fastafiles.emplace(fastafiles.begin(),fastafile);
                    //if(filetype == 1)
                    //openreads();
                    //readfasta(fastafile,file_counter);
                    free(fastafile);
                    file_counter++;
                }
        }
        closedir(d);
    }
    else{
        std::cerr<<"Invalid directory"<<std::endl;
    }
    return fastafiles;
}

