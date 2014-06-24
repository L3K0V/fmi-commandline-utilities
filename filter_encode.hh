#ifndef __FILTER_E_H__
#define __FILTER_E_H__

#include "filter.hh"

class EncodeDecodeFilter: public Filter {
public:
    EncodeDecodeFilter(int key):Filter('E'), key_(key){};
    
    // Random generated key for Caesar cipher
    EncodeDecodeFilter():Filter('E'), key_(7) {};    
    
    // Encode and decode input string using Caesar cipher
    string apply(const string&);
    void serialize(ofstream &output);
private:
    int key_;
};

#endif //__FILTER_E_H__
