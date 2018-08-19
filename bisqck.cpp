//
// Created by lramirez on 19.08.18.
//

#include <seqan/seq_io.h>
#include <seqan/modifier.h>

using namespace seqan;

int main()
{
    CharString seqFileName = getAbsolutePath("../../home/lramirez/Downloads/humangenome/chr22.fa");
    CharString id;
    Dna5String seq;

    SeqFileIn seqFileIn(toCString(seqFileName));
    readRecord(id, seq, seqFileIn);
    std::cout << id << '\t' << seq << '\n';

    reverseComplement(seq);

    std::cout << id << '\t' << seq << '\n';

    return 0;
}