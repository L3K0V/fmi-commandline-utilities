#ifndef __FILTER_CHAIN__
#define __FILTER_CHAIN__

#include "filter.hh"
#include <iostream>

using namespace std;

class FilterChain {
private:
	istream &_input;
	ostream &_output;
	vector<Filter> filters;
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

    FilterChain(const FilterChain &other);

	void put_filter(const Filter &filter);
	Filter pop_filter();
	void filter();
	int serialize(const string &filename);
	int deserialize(const string &filename);

    bool operator==(const FilterChain &other) const;
    bool operator!=(const FilterChain &other) const;
    FilterChain& operator+=(const Filter &other);
    FilterChain operator+(const FilterChain &second);
    FilterChain& operator|(const Filter &filter);
    Filter& operator[](const int position);
    Filter& operator[](const char* filtering);
    FilterChain& operator-=(const char* filtering);
};

FilterChain operator|(const Filter &first, const Filter &second);

#endif
