#ifndef __FILTER_H__
#define __FILTER_H__

#include <string>

using namespace std;

class FilterException {};

class Filter {
public:    
    virtual ~Filter(){}
    virtual string apply(const string&) = 0;
    virtual void serialize(const string filename) = 0;
    virtual Filter* deserialize(const string filename) = 0;
    virtual const char* get_word() { return ""; }
};

ostream& operator<<(ostream &os, const Filter &filter);
istream& operator>>(istream &is, Filter &filter);

#endif //__FILTER_H__
