#include "filter_word.hh"
#include "filter_capitalize.hh"
#include "filter_encode.hh"
#include "filter.hh"
#include "filter_chain.hh"

#include <iostream>

using namespace std;

int main() {

    WordFilter hobbit("hobbit");
    WordFilter world("world");

    EncodeDecodeFilter decode;
    CapitalizeFilter capitalize;

    FilterChain lotr = hobbit | world;
    lotr += &hobbit;
    lotr += &world;
    //lotr += &decode;
    lotr += &capitalize;
    
    lotr.filter();

    return 0;
}
