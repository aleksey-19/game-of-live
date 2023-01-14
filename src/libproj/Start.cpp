#include "Start.h"
#include <iostream>
#include <ctime>

// ширина игрового поля
#define world_height 10
// высота игрового поля
#define world_width 10

int x = 0;
int y = 0;

using namespace std;

//живое существо
class living_being
{
    int location[x][y];
}

public void spawn()
{

}

int start()
{
    srand(time(NULL));
    for (y = 0; x < world_height; y++)
    {
        cout << "\n";
        for (x = 0; x < world_height; x++)
        {
            int spawnOrNot rand() % 2
            if (spawnOrNot == 1)
                cout << "@";
            else
                cout << " ";
        }
    }
    getchar();
    return 0;
}