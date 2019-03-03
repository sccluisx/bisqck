/**
 * @file utils.h
 * @version 0.1
 * @date 20/11/2018
 * @author Luis Enrique Ramirez Chavez
 * @title Utility functions and structures
 */

#ifndef BISQCK_UTILS_H
#define BISQCK_UTILS_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <seqan/arg_parse.h>

#include <seqan/sequence.h>
#include <seqan/seq_io.h>

/**
 * @brief  Structure to contain the options from command line
 */
struct BisquickOptions
{
    unsigned kmersize;
    seqan::CharString genomePath;
    int currfilesize;
    inline BisquickOptions() :
            kmersize(7),
            genomePath("/home/lramirez/thesis/indata/toy")
    {}
} ;

extern int c_id_counter;



extern std::shared_ptr<BisquickOptions> bisquickOptions;


seqan::ArgumentParser::ParseResult
parseCommandLine(std::shared_ptr<BisquickOptions> options, int argc, char const ** argv);

/**
 * @brief The function hasEnding check if the string ends with a
 *          particular substring
 * @param fullString full string that we want check
 * @param ending the ending part
 * @return True if the string ends with the substring
 */

bool hasEnding (std::string const &fullString, std::string const &ending);


int createFaiFile(char const * fastafile);

int kmerRecover(char const * fastafile, seqan::CharString seqid, int ini, int fin);

std::vector<std::string> open_directory(char * curdir);

/**
 * @brief This functions help to convert all the kmers
 * @param kmer
 * @return The reduced kmer convertings all C's in T's
 */
seqan::CharString compressKmer(seqan::CharString kmer);
// --------------------------------------------------------------------------
// Function  print_mainstructs()
// --------------------------------------------------------------------------
// for debug
#define VAR_NAME(n) #n
template <class T>
void printvec(std::vector<T> const &myvec, const std::string &vecname ) {
    typename std::vector<T>::const_iterator it;
    std::cout <<vecname<< " vector contains:";
    if (typeid(unsigned char) == typeid(T))
        for( it = myvec.begin(); it < myvec.end(); it++) {
            std::cout << " " <<(seqan::CharString) *it;
        } else {
        for( it = myvec.begin(); it < myvec.end(); it++) {
            std::cout << " " << *it;
        }
    }
    std::cout << std::endl;
}



#endif //BISQCK_UTILS_H
