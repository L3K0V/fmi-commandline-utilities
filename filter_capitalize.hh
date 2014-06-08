#ifndef __FILTER_C_H__
#define __FILTER_C_H__

#include "filter.hh"

class CapitalizeFilter: public Filter {
public:
    CapitalizeFilter(){};
    string apply(const string&);
    void serialize(const string filename);
    Filter* deserialize(const string filename);
};

#endif // __FILTER_C_H__
