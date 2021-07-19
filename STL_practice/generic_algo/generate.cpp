//
//  generate.cpp
//  generic_algo
//
//  Created by Ajay Singh on 06/10/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>

using namespace std;

template <typename T>
class cal_square{
private:
    T i;
public:
    cal_square() : i(0) {};
    T operator () () { ++i; return i * i;}
};

int main() {
    cal_square<int> gen = cal_square<int>();
    
    cout << gen() << endl;
    cout << gen() << endl;
    cout << gen() << endl;
    cout << gen() << endl;
    cout << gen() << endl;
    
    cout << cal_square<int>()() << endl;
    cout << cal_square<int>()() << endl;
    
    return 0;
}
