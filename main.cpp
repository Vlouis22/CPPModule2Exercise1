#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Dog.cpp"
#include "Cat.cpp"
#include "Mouse.cpp"

// Enum to represent time of day
enum TimeOfDay { DAY, NIGHT };

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
void displayResults(int numOfFights, double catVictory, int numberOfEscapes, int numberOfDogsTurned, int mousesLeft, int totalMice, int dogsDiedDuringDay, int dogsDiedDuringNight) {
    cout << "Simulation ended [All dogs have become cats]" << endl;
    cout << "Simulation results: " << endl;
    cout << "\t⭐ Number of fights occurred: " << numOfFights << endl;
    cout << "\t⭐ Cats' overall successful turn rate: " << (int)((catVictory / numOfFights) * 100) << "%" << endl;
    cout << "\t⭐ Most dogs turned by a single cat: " << numberOfDogsTurned << endl;
    cout << "\t⭐ Dogs were able to outrun cats " << numberOfEscapes << " times" << endl;
    cout << "\t⭐ Number of mice left: " << mousesLeft  << "/" << totalMice << endl;
    cout << "\t🌞 Dogs turned during the day: " << dogsDiedDuringDay << endl;
    cout << "\t🌙 Dogs turned during the night: " << dogsDiedDuringNight << endl;
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
    int dogsDiedDuringDay = 0;
    int dogsDiedDuringNight = 0;
    int maxKillsBySingleCat = 0;
    srand(time(0));

    Dog *dogArray[100];
    Cat *catArray[100];
    Mouse *mouseArray[100];

    int numDogs = 47;
    int numCats = 3;
    int numMice = getRandomNumber(20, 50);
    int totalMice = numMice;

    for (int i = 0; i < numDogs; i++)
        dogArray[i] = new Dog();

    for (int i = 0; i < numCats; i++)
        catArray[i] = new Cat();

    for (int i = 0; i < numMice; i++)
        mouseArray[i] = new Mouse();

    TimeOfDay currentTime = DAY;
    int turnCounter = 0;
    const int DAY_LENGTH = 10;
    const int NIGHT_LENGTH = 10;

    while (numCats < 100 && numDogs > 0) {
        turnCounter++;
        if ((currentTime == DAY && turnCounter >= DAY_LENGTH) ||
            (currentTime == NIGHT && turnCounter >= NIGHT_LENGTH)) {
            currentTime = (currentTime == DAY ? NIGHT : DAY);
            turnCounter = 0;
        }

        for (int j = 0; j < numCats; j++) {
            for (int k = 0; k < numDogs; k++) {
                if (getDistance(catArray, dogArray, j, k) < 2 && dogArray[k]->dogisAlive()) {
                    if (dogArray[k]->gotAway()) {
                        numberOfEscapes++;
                    } else {
                        numOfFights++;
                        double baseChance = 0.3;
                        double effectiveChance = (currentTime == NIGHT) ? min(baseChance * 2, 1.0) : baseChance;
                        if ((rand() / (double)RAND_MAX) < effectiveChance) {
                            catArray[numCats] = new Cat();
                            numCats++;
                            catVictory++;
                            catArray[j]->turnDog(dogArray[k]);
                            int currentKills = catArray[j]->getNumberOfKills();
                            if (currentKills > maxKillsBySingleCat) {
                                maxKillsBySingleCat = currentKills;
                            }
                            if (currentTime == NIGHT)
                                dogsDiedDuringNight++;
                            else
                                dogsDiedDuringDay++;
                            removeDog(dogArray, numDogs, k);
                            k--;
                        }
                    }
                }
            }

            for (int m = 0; m < numMice; m++) {
                if (getDistance(catArray, mouseArray, j, m) < 1) {
                    if (getRandomNumber(1, 100) <= 10) {
                        int currentHealth = catArray[j]->getHealth();
                        int boost = currentHealth * 0.10;
                        catArray[j]->increaseCatHealth(boost);
                        removeMouse(mouseArray, numMice, m);
                        break;
                    }
                }
            }
        }

        moveObjects(catArray, numCats);
        moveObjects(dogArray, numDogs);
        moveObjects(mouseArray, numMice);
    }

    displayResults(numOfFights, catVictory, numberOfEscapes, maxKillsBySingleCat, numMice, totalMice, dogsDiedDuringDay, dogsDiedDuringNight);

    for (int i = 0; i < numDogs; i++) delete dogArray[i];
    for (int i = 0; i < numCats; i++) delete catArray[i];
    for (int i = 0; i < numMice; i++) delete mouseArray[i];

    return 0;
}
