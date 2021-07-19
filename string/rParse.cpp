//
//  rParse.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>

using namespace std;

int main() {
    string s("now.;sense;make;to;going;is;This");  // ; is a delimiter
    string output;
    
    auto pos = s.rfind(';');
    auto prev = s.size();
    while (pos != string::npos) {
        output += s.substr(pos + 1, prev - pos) + " ";
        pos -= 1;
        prev = pos;
        pos = s.rfind(';', pos - 1);
    }
    
    output += s.substr(0, prev + 1);
    
    cout << output << endl;
    return 0;
}
