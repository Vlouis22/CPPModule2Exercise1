#include <iostream>
#include "Coordinate.cpp"
using namespace std;

class Pet{
    private:
        Coordinate coordinate;
        int health;
    
    public:

        Pet(){
            coordinate = Coordinate();
            health = getRandomNumber(90, 100);
        }

        virtual ~Pet() {};

        int getHealth(){
            return health;
        }

        void decreaseHealth(){
            health -= 5;
            if (health < 20){
                health = 20;
            }
        }

        void changeHealth(int newHealth){
            health = newHealth;
        }

        void moveAround(){
            int newX = coordinate.getX() + getRandomNumber(-3, 3);
            int newY = coordinate.getY() + getRandomNumber(-3, 3);
            coordinate.changeCoordinate(newX, newY);
        }

        void moveAround(int newX, int newY){
            coordinate.changeCoordinate(newX, newY);
        }

        Coordinate getCoordinate(){
            return coordinate;
        }

};