#ifndef __FILTER_CHAIN__
#define __FILTER_CHAIN__

#include "word_filter.hh"
#include <iostream>

using namespace std;

class FilterChain {
private:
	vector<WordFilter> filters;
	vector<string> data;
	ostream &_output;
	istream &_input;
	void process(ostream &output);
public:
	FilterChain(istream &input, ostream &output) : _input(input), _output(output) {
		string line;

		// cache input for future processing
		while(!input.eof()) {
			getline(input, line);
			data.push_back(line);
		}
	}

	int put_filter(WordFilter filter);
	WordFilter pop_filter();
	void filter();
	int serialize(string filename);
	int deserialize(string filename);
};

#endif