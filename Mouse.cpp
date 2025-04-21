#include <iostream>
#include <cmath>
using namespace std;

class Mouse: public Pet{
    private:
        int power;
        static int count;

    
        public:

            Mouse(int x, int y, int maximum_x, int maximum_y): Pet(x,y, maximum_x, maximum_y){
                power = getRandomNumber(1,10);
                count++;
            }

            Mouse(int maximum_x, int maximum_y): Pet(maximum_x, maximum_y){
                power = getRandomNumber(1,10);
                count++;
            }

            ~Mouse() {};

            void move(){
                int prevX = getCoordinate().getX();
                int prevY = getCoordinate().getY();
                moveAround((getCoordinate().getX() + getRandomNumber(-2, 2)), 
                            (getCoordinate().getY() +getRandomNumber(-2, 2)));
            };

            int getPower(){
                return power;
            };

            int getCount(){
                return count;
            };

            Mouse& operator++() {
                count++;
                return *this;
            };
    
            Mouse operator++(int) {
                Mouse temp = *this;
                count++;
                return temp;
            };
};

int Mouse::count = 0; 