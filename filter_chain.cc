#include "filter_chain.hh"
#include <fstream>

int FilterChain::put_filter(WordFilter f) {
	filters.push_back(f);
}

WordFilter FilterChain::pop_filter() {
	WordFilter f(filters.back());
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

int FilterChain::deserialize(string filename) {
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

int FilterChain::serialize(string filename) {
	ofstream ofs(filename.c_str(), ios::binary);
	
	if(!ofs)
		return -1;
	
	process(ofs);
	return 0;
}