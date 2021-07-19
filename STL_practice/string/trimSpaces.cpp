//
//  trimSpaces.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void trimSpaces(string& str) {
    string spaces(" \t\n\v\f\r");

    auto start = str.find_first_not_of(spaces);
    auto end = str.find_last_not_of(spaces);
    str = str.substr(start, end - start + 1);
}

int main() {
    string str{"  \t\n This line needs some trimming.    \t\n"};
    
    trimSpaces(str);
    
    cout << quoted(str) << endl;
    return 0;
}
