#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "Dog.cpp"
#include "Cat.cpp"

void moveObjects(Dog *dogs[], int size)
{
    for (int i = 0; i < size; i++)
        dogs[i]->moveAround();
}

void moveObjects(Cat *cats[], int size)
{
    for (int i = 0; i < size; i++)
        cats[i]->moveAround();
}

double getDistance(Cat *cats[], Dog *dogs[], int catIndex, int dogIndex)
{
    double distance = dogs[dogIndex]->getCoordinate().distanceAway(cats[catIndex]->getCoordinate());
    return distance;
}

void displayResults(int numOfFights, double catVictory, int numberOfEscapes, int numberOfDogsTurned){
    cout << "Simulation ended [All dogs have become cats]" << endl;
    cout << "Simulation results: " << endl;
    cout << "\t⭐ Number of fights occured: " << numOfFights << endl;
    cout << "\t⭐ Cats' overall successful turn rate: : " << (int) ((catVictory/numOfFights)*100) << "%" << endl;
    cout << "\t⭐ Most dogs turned by a single cat: " << numberOfDogsTurned << endl;
    cout << "\t⭐ Dogs were able to outrun cats " << numberOfEscapes << " times" << endl;
}

int main()
{

    int numOfFights = 0;
    double catVictory = 0;
    int numberOfEscapes = 0;
    srand(time(0));
    Dog *dogArray[47];
    Cat *catArray[50];

    for (int i = 0; i < 47; i++)
        dogArray[i] = new Dog();

    for (int i = 0; i < 3; i++)
        catArray[i] = new Cat();
    
    // Beginning of simulation: 
    while ((catArray[0]->getCount()) < 50)
    {
        for (int j = 0; j < catArray[0]->getCount(); j++)
        {
            for (int k = 0; k < 47; k++)
            {
                if (getDistance(catArray, dogArray, j, k) < 2 && dogArray[k]->dogisAlive())
                {
                    if(dogArray[k]->gotAway()){
                        numberOfEscapes++;
                    } else {
                        numOfFights++;
                        if (catArray[j]->turnDog(dogArray[k]))
                        {
                            int index = catArray[0]->getCount();
                            catArray[index] = new Cat();
                            catVictory++;
                        }
                    }
                }
            }
        }
        moveObjects(catArray, (catArray[0]->getCount()));
        moveObjects(dogArray, 50 - (catArray[0]->getCount()));
    }
    // End of simulation
    int catWithMostKills = catArray[0]->getMostKills();
    displayResults(numOfFights, catVictory, numberOfEscapes, catWithMostKills);

    return 0;
}
