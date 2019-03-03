#include <iostream>
#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include <seqan/stream.h>
#include <unordered_map>
#include <functional>
#include <map>


using namespace seqan;

struct Dna5StringHasher {
    size_t operator()(const seqan::Dna5String  & obj) const
    {
        std::string Dna5StdString(obj.data_begin,obj.data_end);
        std::hash<std::string> hash_fn;
        size_t hash = hash_fn(Dna5StdString);
        return hash;
    }
};


int main(int argc, char const ** argv){
    Dna5String seq= "acgtt";
    Dna5String seq2= "acgtta";

    std::unordered_map<Dna5String,int, Dna5StringHasher > u1;
    u1.insert({\
                {seq,2},
                {seq,3},
            {seq2,4}
            });
    Dna5String seq3= "acgttaaa";

    std::cout<<u1[seq];
    return 0;
}

int main2(int argc, char const ** argv)
{
    if (argc != 5)
    {
        std::cerr << "USAGE: query_fai FILE.fa SEQ BEGIN END\n";
        return 0;
    }

    // Try to load index and create on the fly if necessary.
    FaiIndex faiIndex;
    if (!open(faiIndex, argv[1]))
    {
        if (!build(faiIndex, argv[1]))
        {
            std::cerr << "ERROR: Index could not be loaded or built.\n";
            return 0;
        }
        if (!save(faiIndex))    // Name is stored from when reading.
        {
            std::cerr << "ERROR: Index could not be written do disk.\n";
            return 0;
        }
    }

    // Translate sequence name to index.
    unsigned idx = 0;
    if (!getIdByName(idx, faiIndex, argv[2]))
    {
        std::cerr << "ERROR: Index does not know about sequence " << argv[2] << "\n";
        return 0;
    }

    // Convert positions into integers.
    unsigned beginPos = 0, endPos = 0;
    if (!lexicalCast(beginPos, argv[3]))
    {
        std::cerr << "ERROR: Cannot cast " << argv[3] << " into an unsigned.\n";
        return 0;
    }
    if (!lexicalCast(endPos, argv[4]))
    {
        std::cerr << "ERROR: Cannot cast " << argv[4] << " into an unsigned.\n";
        return 0;
    }

    // Make sure begin and end pos are on the sequence and begin <= end.
    if (beginPos > sequenceLength(faiIndex, idx))
        beginPos = sequenceLength(faiIndex, idx);
    if (endPos > sequenceLength(faiIndex, idx))
        endPos = sequenceLength(faiIndex, idx);
    if (beginPos > endPos)
        endPos = beginPos;

    // Finally, get infix of sequence.
    Dna5String sequenceInfix;
    readRegion(sequenceInfix, faiIndex, idx, beginPos, endPos);
    std::cout << sequenceInfix << "\n";


    return 0;
}

/*
//
// Created by lramirez on 20.11.18.
//

#include <iostream>
#include <algorithm>
#include <string>

#include <seqan/find.h>
#include <seqan/modifier.h>
using namespace seqan;

int main()
{
    CharString needle2 = "GGGGaaaaaaaatttatataNt";
    CharString needle = needle2;

    reverseComplement(needle);
    reverseComplement(needle);

    for(auto it = needle.data_begin;  it!= needle.data_end; it++){
        std::cout << ' ' << *it;
    }
    std::cout<<std::endl;
    std::replace(needle.data_begin, needle.data_end, 'G', 'U');

    for(auto it = needle.data_begin;  it!= needle.data_end; it++){
        std::cout << ' ' << *it;
    }


    std::cout<<std::endl;
    std::cout<<needle;
    std::cout<<std::endl;
    std::cout<<needle2;
    return 0;
}*/
