#include <iostream>
#include "Random.cpp"
using namespace std;

class Coordinate
{
private:
    int x;
    int y;
    // static const int MAXIMUM_SIZE = 250;
    int maximum_x;
    int maximum_y;

    public :

    Coordinate(int new_x, int new_y, int new_maximum_x, int new_maximum_y)
    {
        maximum_x = new_maximum_x;
        maximum_y = new_maximum_y;
        if(!(new_x && new_y)){
            x = getRandomNumber(0, maximum_x);
            y = getRandomNumber(0, maximum_y);
        } else {
            x = new_x;
            y = new_y;
        }
    }

    ~Coordinate() {};

    void changeCoordinate(int newX, int newY)
    {
        x = newX;
        y = newY;
        if (x < 0)
        {
            x = 0;
        }
        else if (x > maximum_x)
        {
            x = maximum_x;
        }
        if (y < 0)
        {
            y = 0;
        }
        else if (y > maximum_y)
        {
            y = maximum_y;
        }
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    double distanceAway(Coordinate c1)
    {
        int x1 = c1.getX();
        int y1 = c1.getY();
        double distance = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
        return distance;
    }
};
