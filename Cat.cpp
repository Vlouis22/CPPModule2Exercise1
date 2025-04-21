#include <iostream>
#include <cmath>
using namespace std;

class Cat: public Pet{
    private:
        int numberOfKills;
        static int count;
        static int mostKills;

        public:

            Cat(int x, int y, int maximum_x, int maximum_y): Pet(x, y, maximum_x, maximum_y){
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
            
            double calculateChanceOfWinning(Dog* dog, int time){
                double catPower = getHealth() * (100 + (numberOfKills * 10))/100;
                if(time == 1){
                    catPower *= 2;
                }
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

            void turnDog(Dog* dog){
                dog->died();
                numberOfKills++;
                if(numberOfKills > mostKills){
                    mostKills = numberOfKills;
                }
            }

            bool beatDog(Dog* dog, int time = 0){
                decreaseHealth();
                dog->decreaseHealth();
                double getChanceOfWinning = calculateChanceOfWinning(dog, time);

                double randomNum = getRandomNumber(1,100);
                if (randomNum <= getChanceOfWinning){
                    return true;
                }
                return false;
            }

            void increaseCatHealth(int amount) {
                changeHealth(min(getHealth() + amount, 100));
            }
};

int Cat::count = 0; 
int Cat::mostKills = 0;