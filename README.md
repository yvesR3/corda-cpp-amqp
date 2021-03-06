# Corda Blob Inspection

This is a best effort attempt at a C++ implemention of the CORDA serialization framework in a non JVM language. The initial target is a working "blob inspector", that is an exe that can take a serialised blob from a vault (or other) and decode it using C++.

This project exists in parallel with the code checked into the experimental part of the Corda repository.

## Currently Working

An implementation of a "blob inspector" that can take a serialised blob and decode it into a printable JSON format where that blob contains a constrained set of types.

Containers and enumerations are now supported

## Fututre Work

 * Encode and decode of local C++ types
 * Decpdable encode of native types
 * Some schema generation from the JVM canonical source

## Dependencies

 * qpid-proton
 * C++17
 * gtest
 * cmake

## Setup

### MacOS

 * brew install cmake
 * brew install qpid-proton

Google Test

 * git clone https://github.com/google/googletest
 * cd googletest
 * mkdir build
 * cd build
 * cmake ..
 * make
 * make install

### Linux (Ubuntu)

 * sudo apt-get install cmake
 * sudo apt-get install libqpid-proton8-dev
 * sudo apt-get install libgtest-dev

 And now because that installer only pulls down the sources
 * cd /usr/src/googletest
 * sudo cmake .
 * sudo cmake --build . --target install
 
 ### Windows
 
 You're on your own. I have no idea how Windows works or how one builds code for it.
