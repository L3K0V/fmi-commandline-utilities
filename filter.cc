#include "filter.hh"

WordFilter::WordFilter(string word) : word(word){}

// return empty string for filtered line
string WordFilter::apply(string line) {
	return string(line.find(word) == string::npos ? "" : line);
}
