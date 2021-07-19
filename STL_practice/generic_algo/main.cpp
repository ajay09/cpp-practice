//
//  main.cpp
//  generic_algo
//
//  Created by Ajay Singh on 02/10/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a[10];

    for (int i = 0; i < 10; ++i)
        a[i] = i;

    random_shuffle(&a[0], &a[10]);

    random_shuffle(a, a + 10);
//    int *b = a + 10;
    random_shuffle(begin(a), end(a));
    random_shuffle(begin(a), end(a));

    for (int i = 0; i < 10; ++i)
        cout << a[i] << " ";
    cout << endl;

    random_shuffle(a, a + 10);
    
    for (int i = 0; i < 10; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
