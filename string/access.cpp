//
//  access.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>  // quoted

using namespace std;

int main() {
    {
        // string::at(pos)  =>  returns the char at pos   or  raise our of bound exception.
        string s("message");
        cout << s.size() << "\t" << s.capacity() << endl; // 7   22
        
        s = "abc";
        cout << s.at(2) << endl;    // c
        s.at(2) = 'x';
        cout << s << endl;          // abx
        cout << s.size() << "\t" << s.capacity() << endl; // 3   22
        
        try {
            s.at(3) = 'y';  // This will fail as it tries to modify string out of its bounds.
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
    
    
    {
        // operator[]
        string s{"examplar!"};
        const char* c = &s[0];
        cout << c << endl;
        s[s.size() - 1] = 'y';
        cout << s << endl;
    }
    
    
    {
        // References
        // front and back provide constant time access.
        string s{"INDIA"};
        char& f = s.front();  // Returns a reference to the first character.
        f = 'i';
        cout << s << endl;
        cout << &f << endl;
        
        char& b = s.back();  //  Returns a reference to the last character.
        b = 'a';
        cout << b << endl;
    }
    
    
    {
        // Iterators
        
        //  [begin  ->  end)
        string s("Exemplar!");
        *s.begin() = 'e';
        cout << s << '\n';
        auto i = s.begin();
        std::cout << *i << '\n';
        
        //  (rend  <-  rbegin]
        *s.rbegin() = 'y';
        cout << s << '\n';
        
        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            cout << *it << " ";
        } cout << endl;
        
        
        cout << "String size = " << s.end() - s.begin() << endl;
        
        // 3rd character from the end
        cout << quoted(s) << "  3rd from end : "<< *(s.rbegin() + 2) << endl; //
    }
    return 0;
}
