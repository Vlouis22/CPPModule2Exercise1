#include <iostream>
#include <cstdlib>
#include <ctime>  
using namespace std;

int getRandomNumber (int minimum, int maximum);

int getRandomNumber(int minimum, int maximum){
    int difference = maximum - minimum + 1;
    int randomNum = rand() % difference; 
    randomNum += minimum;
    return randomNum;
}
