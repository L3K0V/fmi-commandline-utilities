#include "filter_chain.hh"
#include <fstream>
#include <cstring>

#include "filter_word.hh"
#include "filter_capitalize.hh"
#include "filter_encode.hh"

FilterChain::FilterChain(const FilterChain &other)
: _input(other._input), _output(other._output), filters(other.filters), data(other.data) {}

FilterChain::~FilterChain() {
    //while(!filters.empty()) delete filters.back(), filters.pop_back();
}

void FilterChain::put_filter(Filter* f) {
	return filters.push_back(f);
}

Filter* FilterChain::pop_filter() {
    Filter* filter = filters.back();
	filters.pop_back();
	return filter;
}

void FilterChain::filter() {
	process(_output);
}

void FilterChain::process(ostream &out) {
	int size = data.size();
	int line_num;

	for(line_num = 0; line_num < size; line_num++) {
		string line = data[line_num];

		int filter_num;
		int filter_size = filters.size();

		/* 	apply filter on line,
			if line is empty == filtered from result,
			so break
		*/
		for(filter_num = 0; filter_num < filter_size; filter_num++) {
			line = filters[filter_num]->apply(line);

			if(line.empty()) break;
		}
		
		if(!line.empty()) out << line << endl;
	}
}

int FilterChain::deserialize(ifstream &input) {
    unsigned filter_size = 0, elem;
    input.read(reinterpret_cast<char *>(&filter_size), sizeof(filter_size));
    
    
    std::cerr << filter_size << std::endl;
    for (elem = 0; elem < filter_size; elem++) {
        char type = 0;
        input.read(&type, sizeof(type));
        
        Filter* filter;
        
        switch(type) {
            // Word filter
            case 'W': {
                unsigned size_to_read = 0;
    
                input.read(reinterpret_cast<char *>(&size_to_read), sizeof(size_to_read));
    
                char* buffer = new char[size_to_read+1];
    
                input.read(buffer, size_to_read);
                std::cerr << size_to_read << std::endl;
                buffer[size_to_read] = '\0';
    
                string word_to_read(buffer);
                
                delete [] buffer;
                filter = new WordFilter(word_to_read);
            }break;
            // Encode/Decode
            case 'E': {
                int key;
                input.read(reinterpret_cast<char *>(&key), sizeof(key));
                
                filter = new EncodeDecodeFilter(-key);
            }break;
            // Capitalize
            case 'C': {
                filter = new CapitalizeFilter();
            }break;
        }
        filters.push_back(filter);
    }
    
	return -1;
}

int FilterChain::serialize(ofstream &output) {
    unsigned size = filters.size();
    output.write(reinterpret_cast<const char *>(&size), sizeof(size));
    
    unsigned elem;
    for (elem = 0; elem < size; elem++) {
        filters[elem]->serialize(output);
    }
    
	return -1;
}

bool FilterChain::operator==(const FilterChain &other) const {
    unsigned elem, fil;

    /* Check if chains have different filter size.
     * If sizes are different, then filter chains cannot be equal. */
    if(other.filters.size() != filters.size()) {
        return false;
    }

    for (elem = 0; elem < filters.size(); elem++) {
        bool isThere = false;
        for (fil = 0; fil < other.filters.size(); fil++) {
            if (filters[elem] == other.filters[fil]) {
                isThere =  true;
                break;
            }
        }
        if (!isThere)
            return false;
    }

    for (fil = 0; fil < filters.size(); fil++) {
        bool isThere = false;
        for (elem = 0; elem < other.filters.size(); elem++) {
           if (filters[elem] == other.filters[fil]) {
               isThere = true;
               break;
           }
        }
        if (!isThere)
            return false;
    }

   return true;
}

bool FilterChain::operator!=(const FilterChain &other) const {
    return !this->operator==(other);
}

FilterChain& FilterChain::operator+=(Filter *other) {
    filters.push_back(other);
    return *this;
}

FilterChain FilterChain::operator+(const FilterChain &second) {
    FilterChain fresh(*this);

    // If are equals there no need to put additional filters.
    if(this->operator!=(second)) {
        unsigned fil, elem;
        for (fil = 0; fil < fresh.filters.size(); fil++) {
            for (elem = 0; elem < second.filters.size(); elem++) {
                if (fresh.filters[fil] != second.filters[elem]) {
                    fresh += second.filters[elem];
                    break;
                }
            }
        }
    }

    return fresh;
}

FilterChain& FilterChain::operator|(Filter& filter) {
    this->operator+=(&filter);
    return *this;
}

Filter* FilterChain::operator[](const int position) const {
    if(position > (int) filters.size()) throw FilterException();
    return filters[position];
}

Filter* FilterChain::operator[](const char* filtering) const {
    unsigned elem;
    for (elem = 0; elem < filters.size(); elem++) {
        if(strcmp(filters[elem]->get_word(), filtering)== 0) {
            return filters[elem];
        }
    }
    throw FilterException();
}

FilterChain& FilterChain::operator-=(const char* filtering) {
    unsigned elem;
    for (elem = 0; elem < filters.size(); elem++) {
        if(strcmp(filters[elem]->get_word(), filtering) == 0) {
            filters.erase(filters.begin()+elem);
        }
    }
    return *this;
}

FilterChain operator|(Filter &first, Filter &second) {
    FilterChain chained(cin, cout);
    chained+=(&first);
    chained+=(&second);
    
    return chained;
}

