//
//  capacity.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    {
        string s = "The setting sun!";
        if (!s.empty()) {  // Return a bool => True if string is empty.
            cout << s << endl;
        }
        
        string line;
        cout << "Enter an empty line to finish\n";
        do {
            getline(cin, line);
        } while (!line.empty());
    }
    
    {
        // Both string::size and string::length are synonyms and return the exact same value.
        string s{"The lost city of Aldorado."};
        cout << s.size() << "\t" << s.length() << "\t" << s.capacity() << endl;     // 26   26  31
        
        string s1{"The lost city of Aldorado." "12345"};
        cout << s1.size() << "\t" << s1.length() << "\t" << s1.capacity() << endl;  // 31   31  31
        
        string s2{"The lost city of Aldorado." "123456"};
        cout << s2.size() << "\t" << s2.length() << "\t" << s2.capacity() << endl;  // 32   32  47
        
        
        s = "Hello";
        cout << s.size() << "\t" << s.length() << "\t" << s.capacity() << endl;     // 5   5  31
        
        
        string s3;
        cout << s3.size() << "\t" << s3.length() << "\t" << s3.capacity() << endl;  // 0   0  22
        s3.reserve(100);
        cout << s3.size() << "\t" << s3.length() << "\t" << s3.capacity() << endl;  // 0   0  111
        
        
        s = "The lost city of Aldorado was found by the inquisitive explorers from Spain.";
        cout << "Capacity is " << s.capacity() << " and size is " << s.size() << '\n';
        s.clear();
        cout << "Capacity after clear() is " << s.capacity() << " and size is " << s.size() << '\n';
        s.shrink_to_fit();
        cout << "Capacity after shrink_to_fit() is " << s.capacity() << " and size is " << s.size() << '\n';
    }
    return 0;
}
