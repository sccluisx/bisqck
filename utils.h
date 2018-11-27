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
            kmersize(30),
            genomePath("/home/lramirez/thesis/indata/toy")
    {}
};

extern BisquickOptions bisquickOptions;

seqan::ArgumentParser::ParseResult
parseCommandLine(BisquickOptions & options, int argc, char const ** argv);



std::vector<std::string> open_directory(char * curdir);


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
