#include <iostream>
#include <bits/stdc++.h>
#include "range_map.h"

using namespace std;

int main() {
    // initialize container
    range_map<int, char> mp{'1'};

    // insert elements in random order
    mp.assign(1,3, '1');
    mp.assign(3,5, '2');
    mp.assign(5,7, '1');

    mp.assign(4,5, '1');

    for(const auto& elem : mp.inner_map)
    {
        std::cout << elem.first << " " << elem.second<< "\n";
    }

    return 0;
}
