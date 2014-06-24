#ifndef __FILTER_CHAIN__
#define __FILTER_CHAIN__

#include "filter.hh"
#include <iostream>
#include <vector>

using namespace std;

class FilterChain {
private:
	istream &_input;
	ostream &_output;
	vector<Filter*> filters;
	vector<string> data;
    void process(ostream &output);
public:
	FilterChain(istream &input,ostream &output) : _input(input), _output(output) {
		string line;

		// cache input for future processing
		while(!input.eof()) {
			getline(input, line);
			data.push_back(line);
		}
	}
	
	~FilterChain();

    FilterChain(const FilterChain &other);

	void put_filter(Filter* filter);
	Filter* pop_filter();
	void filter();
	int serialize(ofstream &output);
	int deserialize(ifstream &input);

    bool operator==(const FilterChain &other) const;
    bool operator!=(const FilterChain &other) const;
    FilterChain& operator+=(Filter* other);
    FilterChain operator+(const FilterChain &second);
    FilterChain& operator|(Filter& filter);
    Filter* operator[](const int position) const;
    Filter* operator[](const char* filtering) const;
    FilterChain& operator-=(const char* filtering);
};

FilterChain operator|(Filter &first, Filter &second);

#endif
