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
    //lotr += &hobbit;
    //lotr += &world;
    //lotr += &decode;
    //lotr += &capitalize;
    
    //lotr.filter();
    
    //ofstream ofs("ser.seri", ios::out | ios::binary);
    
    //if(ofs.is_open()) {
        //lotr.serialize(ofs);
    //}
    
    ifstream ifs("ser.seri", ios::in | ios::binary);
    
    if(ifs.is_open()) {
        FilterChain lotr2(cin, cout);
        lotr2.deserialize(ifs);
    
        lotr2.filter();
    }
    
    

    return 0;
}
