#include "filter_word.hh"

string WordFilter::apply(const string& line) {
    return line.find(word) == string::npos ? "" : line;
}

bool WordFilter::operator==(const WordFilter &other) const {
    return word.compare(other.word) == 0;
}

bool WordFilter::operator!=(const WordFilter &other) const {
    return word.compare(other.word) != 0;
}

WordFilter& WordFilter::operator+=(const char &c) {
    word += c;
    return *this;
}

WordFilter& WordFilter::operator+=(const char* str) {
    word += str;
    return *this;
}

ostream& operator<<(ostream &os, const WordFilter &filter) {
    os << filter.word;
    return os;
}

istream& operator>>(istream &is, WordFilter &filter) {
    is >> filter.word;
    return is;
}

void WordFilter::serialize(const string filename) {

}

Filter* WordFilter::deserialize(const string filename) {

}
