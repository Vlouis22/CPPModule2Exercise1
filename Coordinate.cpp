#include <iostream>
#include "Random.cpp"
using namespace std;

class Coordinate{
    private:
        int x;
        int y;
        static const int MAXIMUM_SIZE = 250;

    public: 

        Coordinate(){
            x = getRandomNumber(0,MAXIMUM_SIZE);
            y = getRandomNumber(0,MAXIMUM_SIZE);
        }

        ~Coordinate(){};

        void changeCoordinate(int newX, int newY){
            x = newX;
            y = newY;
            if(x < 0){
                x = 0;
            } else if (x > MAXIMUM_SIZE) {
                x = MAXIMUM_SIZE;
            } 
            if(y < 0){
                y = 0;
            } else if (y > MAXIMUM_SIZE) {
                y = MAXIMUM_SIZE;
            } 
        }

        int getX(){
            return x;
        }

        int getY(){
            return y;
        }

        double distanceAway(Coordinate c1){
            int x1 = c1.getX();
            int y1 = c1.getY();
            double distance = sqrt((x1-x) * (x1-x) + (y1-y) * (y1-y));
            return distance;
        }
};

