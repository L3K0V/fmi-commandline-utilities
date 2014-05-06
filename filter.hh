#ifndef __WORLD_FILTER__
#define __WORLD_FILTER__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Filter {
private:
	string word;
public:
	Filter(const string&);
	string apply(const string&);

    /* OPERATORS OVERLOADING  */
    bool operator==(const Filter &other) const;
    bool operator!=(const Filter &other) const;
    friend ostream& operator<<(ostream &os, const Filter &filter);
    friend istream& operator>>(istream &is, Filter &filter);
    Filter& operator+=(const char &c);
    Filter& operator+=(const char* std);
};

ostream& operator<<(ostream &os, const Filter &filter);
istream& operator>>(istream &is, Filter &filter);

#endif
