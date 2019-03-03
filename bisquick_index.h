/** @file bisquick_index.h
 *  @title Function definitions of the index
 *  @brief Declarations of functions for building the index
 *
 *  The functions here are intended to build the cg index and
 *  the hash map index
 *
 * @version 0.1
 * @date 20/11/2018
 * @author Luis Enrique Ramirez Chavez
 * @bug No known bugs.
 */

#ifndef BISQCK_BISQUICK_INDEX_H
#define BISQCK_BISQUICK_INDEX_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <seqan/seq_io.h>
#include <seqan/sequence.h>
#include <seqan/find.h>
#include <seqan/basic.h>
#include <seqan/modifier.h>


typedef struct {
    std::vector<seqan::CharString>seq_id;
    std::vector<int>position_seq;
    std::vector<int>c_id;
    std::vector<unsigned int>methylated;
    std::vector<unsigned int>unmethylated;
} CG_Index;


// intervals_index is the index to map all the intervals
typedef struct {
    std::vector<unsigned int>start_interval;
    std::vector<unsigned int>end_interval;
    std::vector<unsigned int>cg_start;
    std::vector<unsigned int>cg_offset;
} intervals_index;


typedef struct {
    std::vector<unsigned int>c_id;
    std::vector<unsigned int>offset;
} map_value;


int create_index(std::vector<std::string> fastafile);
int createIntervalIndex();

int test();





#endif //BISQCK_BISQUICK_INDEX_H


