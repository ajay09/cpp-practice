/*
   problem statement : 
Write a program that implements a guessing game. 
Our program generates a random number between 0 and 100. 
The player must guess the secret number. 
The program provides hints like "that's too high" or "that's too low" 
until the player finally guesses the secret number.
*/


#include <iostream>
#include <time.h>

using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;

int getRandomNumber() {
    srand (time(NULL));
    return rand() % 100 + 1;
}

// https://isocpp.org/wiki/faq/input-output#istream-and-ignore
int getUserInput() {
    int number;

    while (cout << "\tPlease enter your guess : " && !(cin >> number)) {
        cin.clear(); // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "\n\tIncorrect input, it is not a number. Try again!\n\n";
    }

    return number;
}

int main () {
    cout << "\n\t Let's play the Random Number Game\n";
    cout << "\t Guess a number between 1 and 100\n\n";

    int random_number = getRandomNumber();
    int guessed_num;
  
    do {
        // cin >> guessed_num;
        guessed_num = getUserInput();
        if (guessed_num < random_number) {
            cout << "\t Sorry your number is less than the random number\n";
        } else if (guessed_num > random_number) {
            cout << "\t Sorry your number is greater than the random number\n";
        }
        cout << "\n";
    } while (guessed_num != random_number);

    
    cout << "\n\t***Congrats!!! you have won.\n\n";
 
    return 0;
}

/*
// guess.cpp.  Maggie Johnson
// Description: A guessing game where the player guesses
// the secret number.

#include <iostream>
#include <time.h>
using namespace std;

int main () {
  int random_number, guess;

  // Initialize random seed.
  srand (time(NULL));

  // Generate random number between 1 and 100
  random_number = rand() % 100 + 1;

  cout << "Guess our number (1 to 100) ";
  do {
    if (!(cin >> guess)) {
      cout << "Please enter only numbers" << endl;
      cin.clear();
      cin.ignore(10000,'\n');
    } else {
      if (random_number < guess) {
        cout << "The secret number is lower than " << guess << endl;
      } else if (random_number > guess) {
        cout << "The secret number is higher than " << guess << endl;
      }
    }
  } while (random_number != guess);
  cout << "Congratulations!" <<  endl;
  return 0;
}
 */
