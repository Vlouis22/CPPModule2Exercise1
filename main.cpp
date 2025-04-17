#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Dog.cpp"
#include "Cat.cpp"
#include "Mouse.cpp"

// Move all dogs
void moveObjects(Dog *dogs[], int size) {
    for (int i = 0; i < size; i++)
        dogs[i]->moveAround();
}

// Move all cats
void moveObjects(Cat *cats[], int size) {
    for (int i = 0; i < size; i++)
        cats[i]->moveAround();
}

// Move all mice
void moveObjects(Mouse *mice[], int size) {
    for (int i = 0; i < size; i++)
        mice[i]->move();
}

// Get distance between cat and dog
double getDistance(Cat *cats[], Dog *dogs[], int catIndex, int dogIndex) {
    return dogs[dogIndex]->getCoordinate().distanceAway(cats[catIndex]->getCoordinate());
}

// Get distance between cat and mouse
double getDistance(Cat *cats[], Mouse *mice[], int catIndex, int mouseIndex) {
    return mice[mouseIndex]->getCoordinate().distanceAway(cats[catIndex]->getCoordinate());
}

// Display results
void displayResults(int numOfFights, double catVictory, int numberOfEscapes, int numberOfDogsTurned, int mousesLeft) {
    cout << "Simulation ended [All dogs have become cats]" << endl;
    cout << "Simulation results: " << endl;
    cout << "\t⭐ Number of fights occurred: " << numOfFights << endl;
    cout << "\t⭐ Cats' overall successful turn rate: " << (int)((catVictory / numOfFights) * 100) << "%" << endl;
    cout << "\t⭐ Most dogs turned by a single cat: " << numberOfDogsTurned << endl;
    cout << "\t⭐ Dogs were able to outrun cats " << numberOfEscapes << " times" << endl;
    cout << "\t⭐ Number of mouses left after simulation: " << mousesLeft << endl;

}

// Remove a dog from array
void removeDog(Dog* dogArray[], int& numDogs, int indexToRemove) {
    delete dogArray[indexToRemove];
    for (int i = indexToRemove; i < numDogs - 1; ++i) {
        dogArray[i] = dogArray[i + 1];
    }
    numDogs--;
}

// Remove a mouse from array
void removeMouse(Mouse* mouseArray[], int& numMice, int indexToRemove) {
    delete mouseArray[indexToRemove];
    for (int i = indexToRemove; i < numMice - 1; ++i) {
        mouseArray[i] = mouseArray[i + 1];
    }
    numMice--;
}

int main() {
    int numOfFights = 0;
    double catVictory = 0;
    int numberOfEscapes = 0;
    srand(time(0));

    Dog *dogArray[47];
    Cat *catArray[50];
    Mouse *mouseArray[50];

    int numDogs = 47;
    int numCats = 3;
    int numMice = getRandomNumber(20,50);
    cout << "Mice count for this simulation: " << numMice << endl;

    for (int i = 0; i < numDogs; i++)
        dogArray[i] = new Dog();

    for (int i = 0; i < numCats; i++)
        catArray[i] = new Cat();

    for (int i = 0; i < numMice; i++)
        mouseArray[i] = new Mouse();

    while (numCats < 50) {
        for (int j = 0; j < numCats; j++) {
            // Check for nearby dogs
            for (int k = 0; k < numDogs; k++) {
                if (getDistance(catArray, dogArray, j, k) < 2 && dogArray[k]->dogisAlive()) {
                    if (dogArray[k]->gotAway()) {
                        numberOfEscapes++;
                    } else {
                        numOfFights++;
                        if (catArray[j]->turnDog(dogArray[k])) {
                            catArray[numCats] = new Cat();
                            numCats++;
                            catVictory++;
                            removeDog(dogArray, numDogs, k);
                            k--;
                        }
                    }
                }
            }

            // Check for nearby mice
            for (int m = 0; m < numMice; m++) {
                if (getDistance(catArray, mouseArray, j, m) < 1) {
                    if (getRandomNumber(1, 100) <= 5) {
                        int currentHealth = catArray[j]->getHealth();
                        int boost = currentHealth * 0.10;
                        catArray[j]->increaseCatHealth(boost);
                        removeMouse(mouseArray, numMice, m);
                        break; // only one mouse per round
                    }
                }
            }
        }

        moveObjects(catArray, numCats);
        moveObjects(dogArray, numDogs);
        moveObjects(mouseArray, numMice);
    }

    int catWithMostKills = catArray[0]->getMostKills();
    displayResults(numOfFights, catVictory, numberOfEscapes, catWithMostKills, numMice);

    for (int i = 0; i < numDogs; i++)
        delete dogArray[i];
    for (int i = 0; i < numCats; i++)
        delete catArray[i];
    for (int i = 0; i < numMice; i++)
        delete mouseArray[i];

    return 0;
}