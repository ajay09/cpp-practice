//
//  main.cpp
//  string
//
//  Created by Ajay Singh on 13/09/20.
//  Copyright © 2020 Ajay Singh. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>  // quoted()

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using namespace std::string_literals; // for operator ""s
/*
 >>  c++ strings don't have a null terminator.
 >>  Though it is a sequence of characters.
*/
int main() {
    {
        string s = "Hello"; // lvalue of type 'const char [6]'  6 because it has a null character at the end
        // But the string object won't have the null character.
        
        //int i = "HELLO"; // Cannot initialize a variable of type 'int' with an lvalue of type 'const char [6]'
    }
    
    {
        // Using a character
        string s1{1, 'a'};
        string s2(4, '=');
        // string(std::initializer_list<charT> ilist)
        string s3({ 'C', '-', 's', 't', 'y', 'l', 'e' });
        cout << s1 << endl; // "a"
        cout << s2 << '\n'; // "===="
        cout << s3 << '\n'; // "C-style"
    }
    
    
    {
        // Multiple Lines
        string multipleLines = "Hey there. "
                               "Where have you been? "
                               "Haven't seen you for long time.";
        cout << multipleLines << endl;  // "Hey there. Where have you been? Haven't seen you for long time."
    
        
        // Copy constructor
        string hey(multipleLines);
        cout << hey << endl;            // "Hey there. Where have you been? Haven't seen you for long time."
    
        
        // Iterators
        string is1(hey.begin(), hey.begin() + 10);     // [being, end)
        string is2(hey.rbegin(), hey.rbegin() + 9);       // (rend, rbegin]
        cout << is1 << endl;    // "Hey there."
        cout << is2 << endl;    // "emit gnol"
    }
    
    
    {
       // Move Constructor
       // string::string(string&& str)
       std::string s(std::string("C++ by ") + std::string("example"));
       std::cout << s << '\n'; // "C++ by example"
    }
    
    
    {
        string s1("What is the sound of one clam napping?");    // constructor
        string s2{"Anything worth doing is worth overdoing."};  // constructor with initializer list.
        string s3("I saw Elvis in a UFO.");
        //  std::string(str, pos, count)
        string s4(s1, 0, 8);  // Copy the first 8 chars
        // Copy 6 chars after the 15th character
        string s5(s2, 15, 6);
        // Copy from 6 till end
        string s6(s3, 6);
        cout << s4 << endl;
        cout << s5 << endl;
        cout << s6 << endl;
        string quoteMe = s4 + "that" + s1.substr(20, 10) // substr copies 10 characters after the 20th
                          + "with" + s3.substr(5, 100)   // copies 100 character or till EOS starting from 5.
                          + s1.substr(37, 1);
        cout << quoteMe << endl;  // "What is that one clam with Elvis in a UFO.?"
    }
    
    
    {
        // Initialisation with string literal stops at the first occurance of NULL character.
        string s1 = "ab\0\0cd";   // s1 contains "ab"
        string s2{"ab\0\0cd", 6}; // s2 contains "ab\0\0cd"
        string s3 = "ab\0\0cd"s;  // s3 contains "ab\0\0cd"   // this can be avoided using ""s operator
        cout << s1 << endl;
        cout << s2 << endl;
        cout << s3 << endl;
    }
    
    
    {
        // operator=
        string s1;
        string s2 {"alpha"};
        
        // copy
        s1 = s2;
        cout << quoted(s1) << " == " << quoted(s2) << endl;   // "alpha == alpha"
        
        // move
        s1 = move(s2);
        cout << s1 << " == " << s2 << endl;  // "alpha == alpha" or "alpha == "  unspecified behavior
        
        // const
        string s3 = "beta";
        s3 = '!';
        string s4 = {'C','-','S','t','y','l','e'};
        cout << s3 << " " << s4 << endl;
    }
    
    
    
    {
        int a = 99999;
        string str = to_string(a);                                // to_string function is defined in the string class #include <string>
        cout << "Integer converted to string" << str << endl;
    }
    
    
    {
        // Input from user
        
        // getline
        
        // cin
        
        string s1, s2;
        
        cout << "Enter two names:\n";
        cin >> s1 >> s2;  // this reads whitespaces seperated strings to s1 and s2
        // Input =>  ajay singh then s1 will contain ajay and s2 will contain singh rather then the entire name in s1
        // Input =>  ajay  s1 will contain ajay and wait for you to enter one more string for s2
        cout << "You entered " << s1 << " and " << s2 << endl;
        
        cin.clear();
        fflush(stdin);
        
        // But sometimes you might want to read strings with spaces in them.  e.g. ajay singh as a name.
        // For that we have getline()
        cout << "Enter two names:\n";
        getline(cin, s1);
        getline(cin, s2);
        cout << " 1 > " << s1;
        cout << " 2 > " << s2;
        
    }
    return 0;
}
