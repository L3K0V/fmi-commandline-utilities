#include "filter_encode.hh"

string EncodeDecodeFilter::apply(const string& line) {
    string out(line);
    
    for(unsigned i = 0; i < line.length(); ++i) {
        out[i] += key_;
    }
    return out;
}

void EncodeDecodeFilter::serialize(const string filename) {

}

Filter* EncodeDecodeFilter::deserialize(const string filename) {

}
