#include <iostream>
#include <cmath>
using namespace std;

class Cat: public Pet{
    private:
        int numberOfKills;
    
        public:

            Cat(){
                numberOfKills = 0;
            }

            int getNumberOfKills(){
                return numberOfKills;
            };
            
            double calculateChanceOfWinning(Dog dog){
                double catPower = getHealth() * (100 + (numberOfKills * 10))/90;
                double dogPower = dog.getHealth() + dog.getSize() * 2;

                int diff = catPower - dogPower;
                if(diff > 25){
                    diff = 25;
                } else if (diff < -25){
                    diff = -25;
                }
                double changeOfWinning = diff + 50;
                return changeOfWinning;
            }

            bool turnDog(Dog dog){
                double getChanceOfWinning = calculateChanceOfWinning(dog);
                double randomNum = getRandomNumber(1,100);
                if (randomNum <= getChanceOfWinning){
                    numberOfKills++;
                    return true;
                }
                return false;
            }
};
