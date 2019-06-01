//
// Created by lramirez on 14.11.18.
//

#include "utils.h"

//BisquickOptions * bisquickOptions;
std::shared_ptr<BisquickOptions> bisquickOptions = std::make_shared<BisquickOptions>();

seqan::ArgumentParser::ParseResult
parseCommandLine(std::shared_ptr<BisquickOptions> bisquickOptions, int argc, char const ** argv)
{
    // Setup ArgumentParser.
    seqan::ArgumentParser parser("bisquick");


    // Set short description, version, and date.
    setShortDescription(parser, "Bisquick");
    setVersion(parser, "0.1");
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




    setDefaultValue(parser, "kmersize", "7");

    // Parse command line.
    seqan::ArgumentParser::ParseResult res = seqan::parse(parser, argc, argv);

    // Only extract  options if the program will continue after parseCommandLine()
    if (res != seqan::ArgumentParser::PARSE_OK)
        return res;

    // Extract option values.
    getOptionValue(bisquickOptions->kmersize, parser, "kmersize");
    getOptionValue(bisquickOptions->genomePath, parser, "genomePath");
    getOptionValue(bisquickOptions->readsdir, parser, "readsdir");
    getOptionValue(bisquickOptions->output, parser, "output");
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
                    if(!(hasEnding(dir->d_name,".fasta") || hasEnding(dir->d_name,".fa"))){
                        continue;
                    }

                    int totsize = strlen(curdir)+strlen(dir->d_name);
                    char * fastafile=NULL;
                    fastafile = (char *)malloc(sizeof(char) * totsize);
                    strcpy (fastafile,curdir);
                    strcat (fastafile,"/");

                    strcat (fastafile,dir->d_name);
                    std::cout << "fasta file: "<<fastafile<<"\n";
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



seqan::CharString compressKmer(seqan::CharString kmer){
    seqan::CharString compressedKmer = kmer;
    std::replace(compressedKmer.data_begin, compressedKmer.data_end, 'C', 'T');
    return compressedKmer;
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int createFaiFile(char const * fastafile)
{

    seqan::FaiIndex faiIndex;
    if (!seqan::build(faiIndex, fastafile))
    {
        std::cerr << "ERROR: Could not build FAI index for file " << fastafile << ".\n";
        return 0;
    }

    seqan::CharString faiFilename = fastafile;
    append(faiFilename, ".fai");

    if (!seqan::save(faiIndex, toCString(faiFilename)))
    {
        std::cerr << "ERROR: Could not write the index to file!\n";
        return 0;
    }

    std::cout << "Index file " << faiFilename << " was successfully created.\n";
    return 0;
}



int kmerRecover(char const * fastafile, seqan::CharString seqid, int ini, int fin){
    // Try to load index and create on the fly if necessary.
    seqan::FaiIndex faiIndex;
    if (!seqan::open(faiIndex, fastafile))
    {
        if (!seqan::build(faiIndex, fastafile))
        {
            std::cerr << "ERROR: Index could not be loaded or built.\n";
            return 0;
        }
        if (!seqan::save(faiIndex))    // Name is stored from when reading.
        {
            std::cerr << "ERROR: Index could not be written do disk.\n";
            return 0;
        }
    }

    // Translate sequence name to index.
    unsigned idx = 0;
    if (!seqan::getIdByName(idx, faiIndex, seqid))
    {
        std::cerr << "ERROR: Index does not know about sequence " << seqid << "\n";
        return 0;
    }


    unsigned beginPos = ini, endPos = fin;


    // Make sure begin and end pos are on the sequence and begin <= end.
    if (beginPos > seqan::sequenceLength(faiIndex, idx))
        beginPos = seqan::sequenceLength(faiIndex, idx);
    if (endPos > seqan::sequenceLength(faiIndex, idx))
        endPos = seqan::sequenceLength(faiIndex, idx);
    if (beginPos > endPos)
        endPos = beginPos;

    // Finally, get infix of sequence.
    seqan::Dna5String sequenceInfix;
    seqan::readRegion(sequenceInfix, faiIndex, idx, beginPos, endPos);
    std::cout << sequenceInfix << "\n";

    return 0;
}