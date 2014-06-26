#include "filter_word.hh"
#include "filter_capitalize.hh"
#include "filter_encode.hh"
#include "filter.hh"
#include "filter_chain.hh"
#include "filter_sort.hh"

#include <iostream>

using namespace std;

int serialize_and_filter();
int deserialize_and_filter();

// Format: input-file.txt output-file.txt --sort --line-filter="The D programming language" --encode --zero-escape
int main(int argc, char *argv[]) {   
    vector<string> allArgs(argv, argv + argc);
    FilterChain* chain;
    
    if (argc > 3) {
        ifstream input(allArgs[1], ios::in);
        ofstream output(allArgs[2], ios::out);
        
        chain = new FilterChain(input, output);
        
        for (unsigned f = 3; f < allArgs.size(); f++) {
            if (allArgs[f] == "--encode") {
                *chain += new EncodeDecodeFilter();
            } else if (allArgs[f] == "--decode") {
                *chain += new EncodeDecodeFilter();
            } else if (allArgs[f] == "--sort") {
                // TODO:
            } else if (allArgs[f] == "--zero-escape") {
                // TODO:
            } else { // Word Filter
                *chain += new WordFilter(allArgs[f].substr(allArgs[f].find("=") + 1, allArgs[f].size()));
            }
        }
        
        chain->filter();
        
        input.close();
        output.close();
    } else if ( !deserialize_and_filter() ) {
            serialize_and_filter();
    }
    return 0;
}

int serialize_and_filter() {
   Filter* hobbit = new WordFilter("hobbit");
   Filter* world = new WordFilter("world");
   Filter* decode = new EncodeDecodeFilter();
   Filter* capitalize = new CapitalizeFilter();
   Filter* sort = new SortFilter();
   
   FilterChain lotr = *hobbit | *world | *capitalize | *decode | *sort;
   
   lotr.filter();
    
   ofstream ofs("ser.seri", ios::out | ios::binary);
    
   if(ofs.is_open()) {
        lotr.serialize(ofs);
   } else return 0;
   
   ofs.close();
   
   return 1;
}

int deserialize_and_filter() {
    ifstream ifs("ser.seri", ios::in | ios::binary);
    
    if(ifs.is_open()) {
        FilterChain lotr(cin, cout);
        lotr.deserialize(ifs);
    
        lotr.filter();
    } else return 0;
    
    ifs.close();
    return 1;   
}
