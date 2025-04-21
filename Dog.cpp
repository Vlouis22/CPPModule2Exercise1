#include "Pet.cpp"
#include <iostream>
#include <cmath>
using namespace std;

class Dog: public Pet{
    private:
        int size;
        bool isAlive;
    
        public:

            Dog(int x, int y, int maximum_x, int maximum_y): Pet(x, y, maximum_x, maximum_y){
                size = getRandomNumber(5,15);
                isAlive = true;
            }

            ~Dog(){};

            double runAway(){
                int prevX = getCoordinate().getX();
                int prevY = getCoordinate().getY();
                moveAround((getCoordinate().getX() + getRandomNumber(-size, size)), 
                            (getCoordinate().getY() +getRandomNumber(-size, size)));
                int newX = getCoordinate().getX();
                int newY = getCoordinate().getY();
                int distance = (newX - prevX)*(newX - prevX) + (newY - prevY)*(newY - prevY);
                return sqrt(distance);
            }

            int getSize(){
                return size;
            };

            bool gotAway(){
                double distanceRan = runAway();
                if (distanceRan >= 4.5){
                    return true;
                }
                return false;
            }

            void died(){
                isAlive = false;
            }

            bool dogisAlive(){
                return isAlive;
            }
};
