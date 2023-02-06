#include "../../inc/map.hpp"
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include "map_prelude.hpp"

#define _map ft::map

#define _ratio 1

#define _make_pair ft::make_pair
#include "map_prelude.hpp"

void map_test_erase_range()
{
    SETUP_ARRAYS();

    {
        strmap m;

        m.erase(m.begin(), m.end());

        PRINT_ALL(m);

        m.insert(strstr_arr, strstr_arr + strstr_size);

        m.erase(m.begin(), m.end());

        PRINT_ALL(m);
    }

    {
        intmap m(intstr_arr, intstr_arr + intstr_size);

        intmap::iterator it(m.begin());
        intmap::iterator end(it);

        std::advance(end, 1);

        m.erase(it, end);

        PRINT_ALL(m);

        it = m.begin();
        end = it;
        std::advance(it, 24);
        std::advance(end, 30);

        m.erase(it, end);

        PRINT_ALL(m);

        it = m.begin();
        end = it;
        std::advance(it, 34);
        std::advance(end, 55);

        m.erase(it, end);

        PRINT_ALL(m);

        it = m.begin();
        end = it;
        std::advance(end, 1);

        m.erase(it, end);

        PRINT_ALL(m);

        m.erase(m.begin(), m.end());

        PRINT_ALL(m);
    }
}

int main(void)
{
    map_test_erase_range();
    return 0;
}
