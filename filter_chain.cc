#include "filter_chain.hh"
#include <fstream>

FilterChain::FilterChain(const FilterChain &other)
: _input(other._input), _output(other._output), filters(other.filters), data(other.data) {}

void FilterChain::put_filter(const Filter &f) {
	return filters.push_back(f);
}

Filter FilterChain::pop_filter() {
	Filter f(filters.back());
	filters.pop_back();
	return f;
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
			line = filters[filter_num].apply(line);

			if(line.empty()) break;
		}

		if(!line.empty()) out << line << endl;
	}
}

int FilterChain::deserialize(const string &filename) {
	ifstream ifs(filename.c_str(), ios::binary);

	if(!ifs)
		return -1;

	data.clear();
	string line;

	while(!ifs.eof()) {
		getline(ifs, line);
		data.push_back(line);
	}
	return 1;
}

int FilterChain::serialize(const string &filename) {
	ofstream ofs(filename.c_str(), ios::binary);

	if(!ofs)
		return -1;

	process(ofs);
	return 0;
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

FilterChain& FilterChain::operator+=(const Filter &other) {
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

FilterChain& FilterChain::operator|(const Filter &filter) {
    this->operator+=(filter);
    return *this;
}

Filter& FilterChain::operator[](const int position) {
    return filters[position];
}

