#include "filter_capitalize.hh"

string CapitalizeFilter::apply(const string& line) {
    string formated(line);
    
    if(formated.length() > 0)
    formated[0] = toupper(formated[0]);

    for(std::string::iterator it = formated.begin() + 1; it != formated.end(); ++it) {
        if(!isalpha(*(it - 1)) && islower(*it)) {
            *it = toupper(*it);
        }
    }
    return formated;
}

void CapitalizeFilter::serialize(ofstream &output) {
    output.write(reinterpret_cast<const char *>(&type_), sizeof(type_));
}

Filter* CapitalizeFilter::deserialize(ifstream &input) {
    return new CapitalizeFilter();
}
