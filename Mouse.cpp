#include <iostream>
#include <cmath>
using namespace std;

class Mouse: public Pet{
    private:
        int power;
        static int count;

    
        public:

            Mouse(){
                power = getRandomNumber(1,10);
                count++;
            }

            ~Mouse() {};

            void move(){
                int prevX = getCoordinate().getX();
                int prevY = getCoordinate().getY();
                moveAround((getCoordinate().getX() + getRandomNumber(-2, 2)), 
                            (getCoordinate().getY() +getRandomNumber(-2, 2)));
                int newX = getCoordinate().getX();
                int newY = getCoordinate().getY();
            }

            int getPower(){
                return power;
            };

            int getCount(){
                return count;
            }

};

int Mouse::count = 0; 