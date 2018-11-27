//
// Created by lramirez on 20.11.18.
//

#include <iostream>
#include <seqan/find.h>
#include <seqan/modifier.h>
using namespace seqan;

int main()
{
    CharString needle = "GGGGaaaaaaaatttatataNt";
    reverseComplement(needle);
    reverseComplement(needle);

    std::cout<< needle <<std::endl;

    return 0;
}