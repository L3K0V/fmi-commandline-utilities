#ifndef __FILTER_C_H__
#define __FILTER_C_H__

#include "filter.hh"

class CapitalizeFilter: public Filter {
public:
    CapitalizeFilter():Filter('C'){};
    string apply(const string&);
    void serialize(ofstream &output);
    Filter* deserialize(ifstream &input);
};

#endif // __FILTER_C_H__
