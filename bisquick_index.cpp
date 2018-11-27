//
// Created by lramirez on 18.11.18.
//

#include "bisquick_index.h"
#include "utils.h"

using namespace seqan;
struct cg_arrays {
    std::vector<CharString>seq_id;
    std::vector<unsigned int>position_seq;
    std::vector<unsigned int>methylated;
    std::vector<unsigned int>unmethylated;
} cg_index;

int createIndex(std::vector<std::string> fastafile){
    int ncpgs=0;
    CharString current_file = fastafile[0];
    CharString id;
    Dna5String seq;
    SeqFileIn seqFileIn(toCString(current_file));
    readRecord(id, seq, seqFileIn);
    std::cout<<seq<<std::endl;
    CharString haystack = seq;
    CharString haystack_reversec = seq;
    reverseComplement(haystack_reversec);
    CharString needle = "CG";
    Finder<CharString> finder(haystack);
    Pattern<CharString, Horspool> pattern(needle);
    while (find(finder, pattern)) {
        ncpgs++;
        uint cpos = beginPosition(finder);
        uint gpos = endPosition(finder);
        // save the position and the chromosome where "CG" is found
        cg_index.position_seq.emplace_back(cpos);
        cg_index.seq_id.emplace_back(id);
    }
    cg_index.methylated.resize(cg_index.position_seq.size());
    cg_index.unmethylated.resize(cg_index.position_seq.size());
        //std::cout << '[' << beginPosition(finder) << ',' << endPosition(finder) << ")\t" << infix(finder) << std::endl;

    printvec(cg_index.seq_id,VAR_NAME(cgindex));

    std::cout<< ncpgs <<std::endl;

}