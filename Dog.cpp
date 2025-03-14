#include "Pet.cpp"
#include <iostream>
#include <cmath>
using namespace std;

class Dog: public Pet{
    private:
        int size;
    
        public:

            Dog(){
                //size = getRandomNumber(5,15);
                size = 5;
            }

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
                if (distanceRan >= 10){
                    return true;
                }
                return false;
            }
};
