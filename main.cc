#include "filter_word.hh"
#include "filter_capitalize.hh"
#include "filter_encode.hh"
#include "filter.hh"
#include "filter_chain.hh"

#include <iostream>

using namespace std;

void serialize_and_filter();
void deserialize_and_filter();

int main(int argc, char *argv[]) {   
    vector<string> allArgs(argv, argv + argc);
    
    //serialize_and_filter();
    deserialize_and_filter();
    
    return 0;
}

void serialize_and_filter() {
   WordFilter hobbit("hobbit");
   WordFilter world("world");
   EncodeDecodeFilter decode;
   CapitalizeFilter capitalize;
   
   FilterChain lotr = hobbit | world | capitalize | decode;
   
   lotr.filter();
    
   ofstream ofs("ser.seri", ios::out | ios::binary);
    
   if(ofs.is_open()) {
        lotr.serialize(ofs);
   }
   
   ofs.close();
}

void deserialize_and_filter() {
    ifstream ifs("ser.seri", ios::in | ios::binary);
    
    if(ifs.is_open()) {
        FilterChain lotr(cin, cout);
        lotr.deserialize(ifs);
    
        lotr.filter();
    }
    
    ifs.close();   
}
