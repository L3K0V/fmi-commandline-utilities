#include "filter_encode.hh"

string EncodeDecodeFilter::apply(const string& line) {
    string out(line);
    
    for(unsigned i = 0; i < line.length(); ++i) {
        out[i] += key_;
    }
    return out;
}

void EncodeDecodeFilter::serialize(ofstream &output) {
    output.write(reinterpret_cast<const char *>(&type_), sizeof(type_));
    output.write(reinterpret_cast<const char *>(&key_), sizeof(key_));
}

Filter* EncodeDecodeFilter::deserialize(ifstream &input) {

}
