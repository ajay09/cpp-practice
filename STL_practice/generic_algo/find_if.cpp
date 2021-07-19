//
//  find_if.cpp
//  generic_algo
//
//  Created by Ajay Singh on 05/10/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class GreaterThan50{
public:
    bool operator() (int x) const { return x > 50; }
};

template <typename InputIterator, typename Predicate>
InputIterator my_find_if(InputIterator begin, InputIterator end, Predicate p) {
    while (begin != end) {
        if (p(*begin)) {
            return begin;
        }
        ++begin;
    }
    return begin;
}

int main() {
    cout << "generic find_if implementation using a class defined function object" << endl;
    
    vector<int> vec;
    for (int i = 0; i < 13; ++i)
        vec.push_back(i * i);
    
    vector<int>::iterator where1 = my_find_if(begin(vec), end(vec), GreaterThan50());
    /*
         GreaterThan50() calls the default constructor of the GreaterThan50 class and passes an object of the class to the function
         Since we have defined the () operator for this class hence
         object(integer)  =>   calls the operator() function of the class
         and thus the function will return the iterator to the value of the vector for which this function call returns true.
     */
    
    vector<int>::iterator where2 = find_if(vec.begin(), vec.end(), GreaterThan50());
    
    cout << *where1 << endl;
    cout << *where2 << endl;
    
    return 0;
}
