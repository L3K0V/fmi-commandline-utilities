#ifndef __WORLD_FILTER__
#define __WORLD_FILTER__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class WordFilter {
private:
	string word;
public:
	WordFilter(const string&);
	string apply(const string&);
};

#endif
