#include <iostream>
#include "filter.hh"
#include "filter_chain.hh"

using namespace std;

int main (int argc, char *argv[]) {
	Filter hello("hello");
	Filter f_chain("chain");
	Filter world("world");

	FilterChain chain(cin, cout);
	chain.put_filter(hello);
	chain.put_filter(f_chain);
	chain.put_filter(world);
    chain.filter();
    chain.serialize("homework.bad");
	// hello chained world
}
