#include <iostream>
#include "filter.hh"
#include "filter_chain.hh"

using namespace std;

int main (int argc, char *argv[]) {
	Filter hello("hello");
	Filter f_chain("chain");
	Filter world("world");

    cout << "Filtering string: = [" << hello << ", " << f_chain << ", " << world << "]"<< endl;
    cout << "Filtering strings equals = " << (hello == f_chain) << endl;
    cout << "Filtering strings equals = " << (hello == hello) << endl;

    // Testing chaining filters add
    hello += 'o';
    cout << "New filtering string = " << hello << endl;

    hello += " woorld";
    cout << "New filtering string = " << hello << endl;

	FilterChain chain(cin, cout);
	chain.put_filter(hello);
	chain.put_filter(f_chain);
	chain.put_filter(world);
    chain.filter();
	// hello chained world
}
