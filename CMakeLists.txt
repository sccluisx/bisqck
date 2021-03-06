# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)
set(CMAKE_PREFIX_PATH "opt/seqan/util/cmake")
set (SEQAN_INCLUDE_PATH "/opt/seqan/include")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# Name of project and that it is C++ only.
project (bisqck CXX)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search for zlib as a dependency for SeqAn.
find_package (ZLIB)

# Load the SeqAn module and fail if not found.
find_package (SeqAn REQUIRED)
find_package (Threads)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

# Add include directories.
include_directories (${SEQAN_INCLUDE_DIRS})

# Add definitions set by find_package (SeqAn).
add_definitions (${SEQAN_DEFINITIONS})

# Add CXX flags found by find_package (SeqAn).
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# Add executable and link against SeqAn dependencies.
add_executable (bisquick main.cpp bisquick.h bisquick.cpp utils.h utils.cpp bisquick_index.cpp bisquick_index.h)
target_link_libraries (bisquick ${SEQAN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


add_executable (seqantst seqantst.cpp)
target_link_libraries (seqantst ${SEQAN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
