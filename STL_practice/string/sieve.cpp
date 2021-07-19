//
//  sieve.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    string sieveChars(50, 'P');
    sieveChars.replace(0, 2, "NN"); // Since 0 and 1 are not primes.
    
    for (auto i = 2; i < sieveChars.size(); ++i) {
        if (sieveChars[i] == 'P') {
            for (auto factor = 2; (i * factor) < sieveChars.size(); ++factor) {
                sieveChars[factor * i] = 'N';
            }
        }
    }
    
    cout << sieveChars << endl;
    
    cout << "  All Primes : " << endl;
    auto pos = sieveChars.find('P');
    while (pos != string::npos) {
        cout << " " << pos;
        pos = sieveChars.find('P', pos + 1);
    } cout << endl;
    
    cout << "  Not Primes : " << endl;
    pos = sieveChars.find_first_not_of('P');
    while (pos != string::npos) {
        cout << " " << pos;
        pos = sieveChars.find_first_not_of('P', pos + 1);
    } cout << endl;
    
    return 0;
}
