#include "filter.hh"

Filter::Filter(const string &word) : word(word){}

string Filter::apply(const string &line) {
	return line.find(word) == string::npos ? "" : line;
}

bool Filter::operator==(const Filter &other) const {
    return word.compare(other.word) == 0;
}

bool Filter::operator!=(const Filter &other) const {
    return word.compare(other.word) != 0;
}

Filter& Filter::operator+=(const char &c) {
    word += c;
    return *this;
}

Filter& Filter::operator+=(const char* str) {
    word += str;
    return *this;
}

ostream& operator<<(ostream &os, const Filter &filter) {
    os << filter.word;
    return os;
}

istream& operator>>(istream &is, Filter &filter) {
    is >> filter.word;
    return is;
}
