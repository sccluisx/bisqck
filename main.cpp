/** @file main.cpp
 *  @title Main bisquick file
 *  @brief Main code of bisquick
 *
 *  This function contains the main() function of bisquick
 *
 * @version 0.1
 * @date 20/11/2018
 * @author Luis Enrique Ramirez Chavez
 * @bug No known bugs.
 */


#include <iostream>
#include <iomanip>
#include <dirent.h>

#include "bisquick.h"
#include "bisquick_index.h"
#include "utils.h"

#include <seqan/seq_io.h>




extern std::shared_ptr<CG_Index> cg_index;
extern seqan::CharString current_file;
extern std::shared_ptr<BisquickOptions> bisquickOptions;
int c_id_counter;

int main(int argc, char const ** argv)
{
    c_id_counter=0;

    // Parse the command line.
    auto parsecmdln =  parseCommandLine(bisquickOptions, argc, argv);

    // If parsing was not successful then exit with code 1 if there were errors.
    // Otherwise, exit with code 0 (e.g. help was printed).
    if (parsecmdln != seqan::ArgumentParser::PARSE_OK)
        return parsecmdln == seqan::ArgumentParser::PARSE_ERROR;
    auto fastafile = open_directory(seqan::toCString(bisquickOptions->genomePath));
    auto i = create_index(fastafile);

    //auto i2 = createIntervalIndex();

    std::cout<< compressKmer("ACctt")<<std::endl;






//    for (auto i = fastafile.begin(); i != fastafile.end(); ++i)
//        std::cout << *i << ' '<< std::endl;


    std::cout<< bisquickOptions->kmersize << std::endl;
/*
    std::cout << "Path   \t" << bisquickOptions.genomePath << '\n'
              << "kmersize\t" << bisquickOptions.kmersize<< '\n';
*/

    kmerRecover(seqan::toCString(current_file),cg_index->seq_id[5], cg_index->position_seq[5], cg_index->position_seq[5]+7);


    return 0;
}