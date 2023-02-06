#include "../../inc/map.hpp"
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include "map_prelude_bench.hpp"

#define _map ft::map

#define _ratio 1

#define _make_pair ft::make_pair


#define NAMESPACE ft
int main(void)
{

    NAMESPACE::map<int, int> data;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(NAMESPACE::make_pair(rand(), rand()));
    }

    NAMESPACE::map<int, int> m(data);

    for (int i = 0; i < 3000; ++i) {
        m.erase(m.begin());
    }

    for (int i = 0; i < 10000; ++i) {
        NAMESPACE::map<int, int>::iterator it = m.begin();
        std::advance(it, i % 2 == 0 ? 2400 : 3064);
        m.erase(it);
    }

    for (int i = 0; i < 100000; ++i) {
        NAMESPACE::map<int, int>::iterator it = m.end();
        std::advance(it, i % 2 == 0 ? -1 : -364);
        m.erase(it);
    }

}