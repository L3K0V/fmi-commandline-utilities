#include "filter.hh"

WordFilter::WordFilter(const string &word) : word(word){}

// return empty string for filtered line
string WordFilter::apply(const string &line) {
	return line.find(word) == string::npos ? "" : line;
}
