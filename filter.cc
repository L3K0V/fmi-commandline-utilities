#include "filter.hh"

Filter::Filter(const string &word) : word(word){}

// return empty string for filtered line
string Filter::apply(const string &line) {
	return line.find(word) == string::npos ? "" : line;
}

ostream& operator<<(ostream &os, const Filter &filter) {
    return os;
}

istream& operator>>(istream &is, Filter &filter) {
    return is;
}

Filter& Filter::operator+=(const char &c) {
    return *this;
}

Filter& Filter::operator+=(const char* std) {
    return *this;
}
