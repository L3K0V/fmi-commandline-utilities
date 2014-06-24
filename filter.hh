#ifndef __FILTER_H__
#define __FILTER_H__

#include <string>
#include <fstream>

using namespace std;

class FilterException {};

class Filter {
protected:
    char type_;
    Filter(char type):type_(type){}
public:    
    virtual ~Filter(){}
    virtual string apply(const string&) = 0;
    virtual void serialize(ofstream &output) = 0;
    virtual Filter* deserialize(ifstream &input) = 0;
    virtual const char* get_word() { return ""; }
    
    char get_type() { return type_; }
};

ostream& operator<<(ostream &os, const Filter &filter);
istream& operator>>(istream &is, Filter &filter);

#endif //__FILTER_H__
