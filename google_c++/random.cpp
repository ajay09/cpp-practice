#include <iostream>
#include <time.h>

using std::cout;
using std::endl;

int main () {
  srand (time(NULL));

  int random_number = rand() % 100 + 1;

  cout << "Your random number : " << random_number << endl;

  return 0;
}
