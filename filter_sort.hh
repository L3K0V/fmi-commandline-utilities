#ifndef __FILTER_S_H__
#define __FILTER_S_H__

#include "filter.hh"

class SortFilter: public Filter {
public:
    SortFilter():Filter('S'){};
    string apply(const string&);
    void serialize(ofstream &output);
    Filter* deserialize(ifstream &input);
};

#endif // __FILTER_S_H__
