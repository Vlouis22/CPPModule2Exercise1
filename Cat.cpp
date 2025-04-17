#include <iostream>
#include <cmath>
using namespace std;

class Cat: public Pet{
    private:
        int numberOfKills;
        static int count;
        static int mostKills;

        public:

            Cat(){
                numberOfKills = 0;
                count++;
            }

            ~Cat(){};

            int getNumberOfKills(){
                return numberOfKills;
            };

            int getCount(){
                return count;
            }

            int getMostKills(){
                return mostKills;
            }
            
            double calculateChanceOfWinning(Dog* dog){
                double catPower = getHealth() * (100 + (numberOfKills * 10))/100;
                double dogPower = dog->getHealth() + dog->getSize() * 4;

                int diff = catPower - dogPower;
                if(diff > 25){
                    diff = 25;
                } else if (diff < -25){
                    diff = -25;
                }
                double changeOfWinning = diff + 50;
                return changeOfWinning;
            }

            bool turnDog(Dog* dog){
                double getChanceOfWinning = calculateChanceOfWinning(dog);
                double randomNum = getRandomNumber(1,100);
                if (randomNum <= getChanceOfWinning){
                    dog->died();
                    numberOfKills++;
                    if(numberOfKills > mostKills){
                        mostKills = numberOfKills;
                    }
                    return true;
                }
                decreaseHealth();
                dog->decreaseHealth();
                return false;
            }

            void increaseCatHealth(int amount) {
                changeHealth(min(getHealth() + amount, 100));
            }
};

int Cat::count = 0; 
int Cat::mostKills = 0;