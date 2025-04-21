#include <iostream>
#include <cmath>
using namespace std;

class Arena {
    private:
        Mouse* mouseArray[100];
        int numMice;
        int startingMice;
        int gridWidth;
        int gridHeight;
    
    public:
        Arena(int width = 250, int height = 250) {
            gridHeight = height;
            gridWidth = width;
            numMice = getRandomNumber((width + height)/20, (width+height)/10);
            startingMice = numMice;
            for (int i = 0; i < numMice; i++) {
                mouseArray[i] = new Mouse();
            }
            cout << "Mice count for this simulation: " << numMice << endl;
            cout << "Arena size: " << gridWidth << "x" << gridHeight << endl;
        }
    
        int getWidth() const {
            return gridWidth;
        }
    
        int getHeight() const {
            return gridHeight;
        }
    
        int getMiceRemaining() const {
            return numMice;
        }
    
        int getMiceStart() const {
            return startingMice;
        }
    
        Mouse** getMouseArray() {
            return mouseArray;
        }
    
        void removeMouse(int indexToRemove) {
            delete mouseArray[indexToRemove];
            for (int i = indexToRemove; i < numMice - 1; ++i) {
                mouseArray[i] = mouseArray[i + 1];
            }
            numMice--;
        }
    
        void moveMice() {
            for (int i = 0; i < numMice; i++) {
                mouseArray[i]->move();
            }
        }
    
        ~Arena() {
            for (int i = 0; i < numMice; i++) {
                delete mouseArray[i];
            }
        }
    };