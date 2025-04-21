#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Dog.cpp"
#include "Cat.cpp"
#include "Arena.cpp"

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

// Get distance between cat and dog
double getDistance(Cat *cats[], Dog *dogs[], int catIndex, int dogIndex) {
    return dogs[dogIndex]->getCoordinate().distanceAway(cats[catIndex]->getCoordinate());
}

// Get distance between cat and mouse
double getDistance(Cat *cats[], Mouse *mice[], int catIndex, int mouseIndex) {
    return mice[mouseIndex]->getCoordinate().distanceAway(cats[catIndex]->getCoordinate());
}

// Display results
void displayResults(int numOfFights, double catVictory, int numberOfEscapes, int numberOfDogsTurned, int mousesLeft, int mousesStart, int dogsDiedDuringDay, int dogsDiedDuringNight) {
    cout << "Simulation ended [All dogs have become cats]" << endl;
    cout << "Simulation results: " << endl;
    cout << "\t⭐ Number of fights occurred: " << numOfFights << endl;
    cout << "\t⭐ Cats' overall successful turn rate: " << (int)((catVictory / numOfFights) * 100) << "%" << endl;
    cout << "\t⭐ Most dogs turned by a single cat: " << numberOfDogsTurned << endl;
    cout << "\t⭐ Dogs were able to outrun cats " << numberOfEscapes << " times" << endl;
    cout << "\t⭐ Number of mouses left after simulation: " << mousesLeft << "/" << mousesStart << endl;
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
    int numDogs = 47;
    int numCats = 3;

    int arena_x = 500;
    int arena_y = 500;

    Arena arena = Arena(arena_x, arena_y);

    for (int i = 0; i < numDogs; i++)
        dogArray[i] = new Dog(arena_x, arena_y);

    for (int i = 0; i < numCats; i++)
        catArray[i] = new Cat(arena_x, arena_y);
    

    Mouse** mouseArray = arena.getMouseArray();

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
                            if (catArray[j]->beatDog(dogArray[k], currentTime == NIGHT ? 1 : 0)) {
                            catArray[numCats] = new Cat(dogArray[k]->getCoordinate().getX(), dogArray[k]->getCoordinate().getY(), arena_x, arena_y);
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

            if (currentTime == NIGHT) {
                for (int m = 0; m < arena.getMiceRemaining(); m++) {
                    if (getDistance(catArray, mouseArray, j, m) < 1) {
                        if (getRandomNumber(1, 100) <= 10) {
                            int currentHealth = catArray[j]->getHealth();
                            int boost = currentHealth * 0.10;
                            catArray[j]->increaseCatHealth(boost);
                            arena.removeMouse(m);
                            break;
                        }
                    }
                }
            }
        }

        moveObjects(catArray, numCats);
        moveObjects(dogArray, numDogs);
        arena.moveMice();
    }

    displayResults(numOfFights, catVictory, numberOfEscapes, maxKillsBySingleCat, arena.getMiceRemaining(), arena.getMiceStart(), dogsDiedDuringDay, dogsDiedDuringNight);

    for (int i = 0; i < numDogs; i++) delete dogArray[i];
    for (int i = 0; i < numCats; i++) delete catArray[i];

    return 0;
}
