#ifndef __FILTER_S_H__
#define __FILTER_S_H__

#include "filter.hh"

class SortFilter: public Filter {
public:
    SortFilter():Filter('S'){};
    string apply(const string& input){return input;}
    void serialize(ofstream &output){
        output.write(reinterpret_cast<const char *>(&type_), sizeof(type_));
    }
};

#endif // __FILTER_S_H__
