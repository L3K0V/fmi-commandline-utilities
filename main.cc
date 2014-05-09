#include <iostream>
#include "filter.hh"
#include "filter_chain.hh"
using namespace std;

int main (int argc, char *argv[]) {
    Filter hobbit("hobbit");
    Filter world("world");

    FilterChain lotr(cin, cout);
    lotr += hobbit;
    lotr += world;

    //lotr.filter();

    FilterChain lotrCopy(cin, cout);
    lotrCopy += world;

    FilterChain lotrNew(lotr+lotrCopy);
    lotrNew.filter();

    Filter f = lotr["world"];
    cout << f << endl;
}
