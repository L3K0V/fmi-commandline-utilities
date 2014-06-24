#ifndef __FILTER_W_H__
#define __FILTER_W_H__

#include "filter.hh"

class WordFilter : public Filter {
public:
    WordFilter(const string& word):Filter('W'), word(word){};
    string apply(const string&);
    void serialize(ofstream &output);
    Filter* deserialize(ifstream &input);
    const char* get_word() { return word.c_str();}
    
     /* OPERATORS OVERLOADING  */
    bool operator==(const WordFilter &other) const;
    bool operator!=(const WordFilter &other) const;
    friend ostream& operator<<(ostream &os, const WordFilter &filter);
    friend istream& operator>>(istream &is, WordFilter &filter);
    WordFilter& operator+=(const char &c);
    WordFilter& operator+=(const char* std);
private:
    string word;
};

#endif // __FILTER_W_H__
