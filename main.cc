#include <iostream>
#include "word_filter.hh"
#include "filter_chain.hh"

using namespace std;

int main (int argc, char *argv[]) {
	WordFilter hello("hello");
	WordFilter f_chain("chain");
	WordFilter world("world");

	FilterChain chain(cin, cout);
	chain.put_filter(hello);
	chain.put_filter(world);
	chain.put_filter(f_chain);
	chain.filter();
	chain.serialize("homework.bad");
	// hello chained world
}