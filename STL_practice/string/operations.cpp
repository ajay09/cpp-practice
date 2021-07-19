//
//  operations.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

/*
String Operators
 +, <, >, +=, ==, !=, <<, >>
*/


#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    {
        // string::clear()
        // Removes all characters from the string as if by executing erase(begin(), end()).
        // The string becomes an empty string.
        string s = "String will become empty with size == 0 but capacity will remain same.";
        cout << s.size() << "\t" << s.length() << "\t" << s.capacity() << endl;     // 70  70  79
        s.clear();
        cout << s.size() << "\t" << s.length() << "\t" << s.capacity() << endl;     // 0    0   79
        cout << s.empty() << endl;  // 1
    }
    
    
    {
        // string::insert()
        string str = "to be question";
        string str2 = "the ";
        string str3 = "or not to be";
        string str4 = "Before him someone said, he would";
        
        // [1]          pos, count, character   => position can be iterator or index
        str.insert(str.begin() + str.size() - 1, 3, '-');           // to be questio---n
        str.insert(16, 1, 'A');                                     // to be questio---An
        
        // [2]          insert_pos, string, from_pos, count_of_char
        str.insert(13, "n");                                                 // to be questio---An
        str.insert(14, ".    ");                                             // to be question.  ---An
        str.insert(6, str2);                                                 // to be the question.  ---An
        str.insert(str.size(), "anachronistic fool"s, 2, 9);                 // to be the question.    ---Anachronist
        str.insert(6, "that is cool", 8);                                    // to be that is the question.    ---Anachronist
        str.insert(str.begin() + str.find_first_of('n') + 1, 2, '.');        // to be that is the question...    ---Anachronist
        str.insert(str.begin() + str.find_first_of('.'), 3, '!');            // to be that is the question!!!...    ---Anachronist
        str.insert(str.begin() + str.find_last_of('-') + 1, 3, ' ');         // to be that is the question!!!...    ---   Anachronist
        
        // [3]      itr_insert_pos,  itr_insert_start,     itr_insert_end
        str.insert(str.begin() + 6, str3.begin(), str3.begin() + 7);         // to be or not that is the question!!!...    ---   Anachronist
        str.insert(str.begin(), str4.begin() + 11, str4.begin() + 25);       // someone said, to be or not that is the question!!!...    ---   Anachronist
        str.insert(0, "As ");                                                // As someone said, to be or not that is the question!!!...    ---   Anachronist
        str.insert(str.begin(), 3, '"');
        str.insert(str.end(), 3, '"');                                      // """As someone said, to be or not that is the question!!!...    ---   Anachronist"""
        
        cout << str << endl;
    }
    
    
    {
        // string::erase()
        string str = "This is an example sentence of c++.";
        string str2 = "Hello, world!";
        
        // [1] Sequence    start_pos, count(number of characters)
        str.erase(9, 9);                                // This is a sentence of c++.
        str2.erase(1);                                  // H
        str2 = "Hello, world!";
        str2.erase(str2.find(','));                     // Hello
        
        // [2] Character
        str.erase(5,1);                                 // This s a sentence of c++.
        str.erase(str.begin());                         // his s a sentence of c++.
        str.erase(str.begin() + 4);                     // his  a sentence of c++.
        
        // [3] Range    [itr_begin, itr_end)               0   4  7
        str.erase(str.begin() + 3, str.begin() + 6);    // his sentence of c++.
                                                        //            9    4  1
        str.erase(str.begin() + 7, str.end() - 10);     // his sence of c++.
        
        cout << str << endl;
    }
    
    
    {
        // push_back   pop_back
        string str = "Hello, world";
        str.push_back('!');                             // Hello, world!
        str.insert(str.end(), '!');                     // equivalent to push_back
        
        str.pop_back();                                 // Hello, world!
        str.erase(str.end() - 1);                       // Hello, world   equivalent to pop_back
        
        cout << str << endl;
    }
    
    
    {
        // string::append()
        
        string str = "writ";
        //                    7
        string str2 = "a sport is not";
        //                       9
        string str3 =  "I went for playing football";
        //                                    5   1
        string output;
        
        // [1] character
        output.append(3, '*');                          // ***
        
        // [2] string
        output.append(1, ' ').append(str);              // *** writ             Append a string
        output.append(str3, 15, 3);                     // *** writing          Append a substring of a string
        output.append(str2, 7);                         // *** writing is not
        
        // [3] Range    [begin_itr, end_itr)
        output.append(str3.begin() + 10, str3.end() - 5);       // *** writing is not playing foo
        
        // [4] list
        output.append({'b','a','r','.'});                       // *** writing is not playing foobar.
        
        
        // operator +=
        output += " Coding is ";                                // *** writing is not playing foobar. Coding is
        output += str2.substr(0, 7);                            // *** writing is not playing foobar. Coding is a sport
        output += '!';                                          // *** writing is not playing foobar. Coding is a sport!
        
        output += {' ', '*', '*', '*'};                         // *** writing is not playing foobar. Coding is a sport! ***
        output += 97;                                           // *** writing is not playing foobar. Coding is a sport! ***a
        // equivalent to static_cast<char>(97)
        
        cout << output << endl;
    }
    
    
    {
        // string::compare()
        //  0   =>  if the strings are equal
        //  <0  =>  if the first character that doesn't match is smaller in the first string
        //  >0  =>  if the first character that doesn't match is larger in the second string
        string a{"green apple"};
        string b{"red apple"};
        
        // [1] compare strings
        if (a.compare(b) < 0)   //  i.e. a < b   as g < r
            cout << a << " is not " << b << endl;
        
        // [2] compare substrings
        if (a.compare(0, 5, b, 0, 3))
            cout << "Because " << a.substr(0, 5) << " is not " << b.substr(0, 3) << endl;
        
        // [3] compare with string constants
        if (a.compare(6, 5, "apple") == 0)
            cout << "But an " << a.substr(6) << " is an " << "apple" << endl;
    }


    {
        // string::replace()
        //          0   4    9
        string str("The quick brown fox jumps over the lazy dog.");
        string str2("tiger is not lion");
        
        str.replace(10, 5, "red");                                          // The quick red fox jumps over the lazy dog.
        // Range [begin, end)
        str.replace(str.begin(), str.begin() + 3, "A");                     // A quick red fox jumps over the lazy dog.
        str.replace(str.end() - 1, str.end(), 3, '!');                      // A quick red fox jumps over the lazy dog!!!
        
        str.replace(12, 3, str2, 13, 4);                                                // A quick red lion jumps over the lazy dog!!!
        str.replace(str.end() - 6, str.end() - 3, str2.begin(), str2.begin() + 5);      // A quick red lion jumps over the lazy tiger!!!
        
        cout << str << endl;
        
        
        
        // replace form STL
        string s{"XXxxxxZZZxxxxXX"};
        replace(s.begin(), end(s), 'X', 'Y');                               // YYxxxxZZZxxxxYY
        cout << s << endl;                                                  // replaces all occurance of the character  -> only for characters.
    }
    
    
    {
        // string::substr (size_t pos = 0, size_t len = npos)
        string str{"We think in generalities, but we live in details."};
        string output;
        
        output = str.substr();                                              // We think in generalities, but we live in details.
        output = output.substr(0, 24);                                      // We think in generalities
        output = str.substr(30);                                            // we live in details.
        
        cout << output << endl;
    }
    
    
    {
        // string::copy(char* s, len, pos = 0)
        // Copies a substring of the string object into the array pointed by s
        char buffer[20];
        string str{"If you could see your whole life from start to finish, would you change things?"};
        str.copy(buffer, sizeof(buffer), 7);                                                                         // could see your whol
        
        buffer[19] = '\0';
        cout << buffer << endl;
    }
    
    
    {
        // string::resize()
        string str("I like to code in C");
        str.resize(str.size() + 2, '+');                        // I like to code in C++
        str.resize(14);                                         // I like to code
        
        cout << str << endl;
    }
    
    
    {
        // string::swap()
        string a{"Hello"};
        string b{"Fellow"};
        a.swap(b);
        
        swap(a, b);
        
        cout << a << " " << b << endl;                          // Fellow Hello
    }
    
    
    {
        // string::find(<sequence/character>, pos = 0)
        // Searches the string for the first occurrence of the sequence specified by its arguments.
        
        string str = "There are two needles in this haystack with needles.";
        string str2{"needle"};
        
        u_int64_t pos = str.find(str2);
        if (pos != string::npos) {
            cout << "Found first the needle at " << pos << endl;                      // Found the needle at 14
        }
        
        pos = str.find(str2, 20);
        if (pos != string::npos) {
            cout << "Found the second needle at " << pos << endl;                      // Found the needle at 44
        }
        
        pos = str.find("th");
        if (pos != string::npos) {
            cout << "Found th at " << pos << endl;                                      // Found th at 25
        }
        
        pos = str.find(".");
        if (pos != string::npos) {
            cout << "Found . at " << pos << endl;                                       // Found . at 51
        }
        
        str.replace(str.find(str2),str2.length(),"preposition");                        // There are two prepositions in this haystack with needles.
        cout << str << endl;
    }
    
    
    {
        // string::rfind()
        // Finds the last substring equal to the given character sequence. Position of the first character of this sequence.
        string str{"Pain is certain, suffering is optional."};
        u_int64_t pos = str.rfind("is");
        if (pos != string::npos) {
            cout << "Found is at " << pos << " => " << str.substr(pos) << endl;                      // Found the needle at 27
        }
        
        pos = str.rfind("is", 26);
        if (pos != string::npos) {
            cout << "Found is at " << pos << " => " << str.substr(pos) << endl;                      // Found the needle at 27
        }
    }
    
    
    {
        // string::find_first_of()
        // Searches the string for the first character that >>> matches any of <<< the characters specified in its arguments.
        string str ("Please, replace the vowels in this sentence by asterisks.");
        
        size_t found = str.find_first_of("aeiou");
        while (found != string::npos) {
          str[found] = '*';
          found = str.find_first_of("aeiou", found + 1);
        }

        std::cout << str << '\n';                                                                   //  Pl**s*, r*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks.
    }
    
    
    {
        // string::find_first_not_of()
        // Searches a target string and returns the position of the first element that doesn’t match any character in a specified group.
        // If no such element is found, it returns npos.
        string str = "Some data with %MACROS to substitute %MACRO";
        auto pos = string::npos;
        while ((pos = str.find('%')) != string::npos) {
            auto till = str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz"
                                              "0123456789", pos + 1);
            str.replace(pos, till - pos, "some nice macro");
        }
        cout << str << endl;
    }
    
    
    {
        // string::find_last_of()
        // Finds the last character equal to one of characters in the given character sequence.
        // Searches the string for the last character that matches any of the characters specified in its arguments.
        string str1 ("/usr/bin/man");
        string str2 ("c:\\windows\\winhelp.exe");
        
        auto pos = str1.find_last_of('/');
        if (pos != string::npos) {
            cout << "File : " << str1.substr(pos + 1) << endl;
            cout << "Path : " << str1.substr(0, pos + 1) << endl;
        }
    }
    
    
    {
        // string::find_last_not_of()
        string str = "Remove trailing white spaces.          ";
        string spaces{" \t\f\v\r\n"};
        
        size_t pos = str.find_last_not_of(spaces); // that is find the first character that is not a space
        if (pos != string::npos) {
            str.erase(pos + 1);
        }
        cout << quoted(str) << endl;
    }
    
    return 0;
}
