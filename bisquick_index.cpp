//
// Created by lramirez on 18.11.18.
//

#include "bisquick_index.h"
#include "utils.h"

#include <seqan/seq_io.h>

using namespace seqan;

//CG_Index cg_index;
std::shared_ptr<CG_Index> cg_index = std::make_shared<CG_Index>();
extern int c_id_counter;
CharString current_file;
std::map<Dna5String, map_value> compresskmap;



int create_index(std::vector<std::string> fastafile){
    int ncpgs=0;
    int ksize = bisquickOptions->kmersize;
    current_file = fastafile[0];
    CharString id;
    Dna5String seq;
    createFaiFile(toCString(current_file));
    SeqFileIn seqFileIn(toCString(current_file));
    readRecord(id, seq, seqFileIn);


    CharString haystack = seq;
    CharString haystack_reversec = seq;
    reverseComplement(haystack_reversec);
    CharString needle = "CG";
    Finder<CharString> finder(haystack);
    Pattern<CharString, Horspool> pattern(needle);

    while (find(finder, pattern)) {
        uint cpos = beginPosition(finder);
        uint gpos = endPosition(finder);
        // save the position and the chromosome where "CG" is found
        cg_index->position_seq.emplace_back(cpos);
        cg_index->seq_id.emplace_back(id);
        cg_index->c_id.emplace_back(c_id_counter);



        ncpgs++;
        c_id_counter++;
    }
    cg_index->methylated.resize(cg_index->position_seq.size());
    cg_index->unmethylated.resize(cg_index->position_seq.size());
        //std::cout << '[' << beginPosition(finder) << ',' << endPosition(finder) << ")\t" << infix(finder) << std::endl;

    std::for_each(cg_index->position_seq.begin(), cg_index->position_seq.end(), [seq](int o) {

        //std::cout<<infixWithLength(seq,cg_index->position_seq[o]-bisquickOptions->kmersize+2,bisquickOptions->kmersize)<<std::endl;
        std::cout<<"("<<o<<")"<<std::endl;
        auto substr = infixWithLength(seq,o,bisquickOptions->kmersize);
//        for(int i = 0; i< bisquickOptions->kmersize; i++)
//            std::cout<<"#"<<substr[i]<<std::endl;
        //std::cout<<infixWithLength(seq,o,bisquickOptions->kmersize)<<std::endl;
        std::cout<<substr<<std::endl;
        auto lambda =  []() { std::cout << "Code within a lambda expression" << std::endl; };
        lambda();
        Dna5String t1= substr;
        std::cout << "substr is: " << typeid(t1).name() << '\n';

        std::unordered_map<Dna5String, int> umap;
        // umap[substr]=2;
        //std::unordered_map<Dna5String, int> umap;


//        for(int i=0;i<bisquickOptions->kmersize-1; i++){
//            for(int j = 0; j<i; j++)
//                std::cout<<" ";
//            std::cout<<infixWithLength(seq,o-bisquickOptions->kmersize+2+i,bisquickOptions->kmersize)<<std::endl;
//        }



    });



/*    for_each (myvector.begin(), myvector.end(), myfunction);

    std::cout<<"Testing: "<<cg_index->position_seq[3]<<std::endl;
    for(int i=0;i<ksize-1; i++){
        for(int j = 0; j<i; j++)
            std::cout<<" ";
        std::cout<<infixWithLength(seq,cg_index->position_seq[3]-ksize+2+i,ksize)<<std::endl;
    }*/
    //int ls;
    //std::cout<<cg_index->position_seq[3];
    //printvec(cg_index->c_id,VAR_NAME(c_id));
    //bisquickOptions->currfilesize = seqan::length(seq);

}

int createIntervalIndex(){

    for (int i =0; i<cg_index->position_seq.size();i++) {
        int ini = (int)cg_index->position_seq[i]-(bisquickOptions->kmersize-1);
        std::cout<<"<<"<<ini
        <<"--"<<cg_index->position_seq[i]<<"--"<<
        cg_index->position_seq[i]+(bisquickOptions->kmersize-1)<<std::endl;

    }


    return  0;
}

int test() {
     
}
