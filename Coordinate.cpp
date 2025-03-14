#include <iostream>
#include "Random.cpp"
using namespace std;

class Coordinate{
    private:
        int x;
        int y;

    public: 

        Coordinate(){
            x = getRandomNumber(0,100);
            y = getRandomNumber(0,100);
        }

        void changeCoordinate(int newX, int newY){
            x = newX;
            y = newY;
            if(x < 0){
                x = 0;
            } else if (x > 100) {
                x = 100;
            } 
            if(y < 0){
                y = 0;
            } else if (y > 100) {
                y = 100;
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

