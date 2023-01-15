#include "Start.h"
#include <iostream>
#include <ctime>

// высота мира
#define world_height 20
// ширина мира
#define world_width 20

using namespace std;

//живой объект
class living_being
{
public:
    int x;
    int y;
};

class plant : public living_being
{
private:
    char p = 'Р';
};

class herbivore : public living_being
{
private:
    char h = 'Т';
};

class predator : public living_being
{
private:
    char p = 'Х';
};

struct point {
    unsigned is_live:1;
};

// Игровое поле размером 10x10 клеток
point world[world_width][world_height];

void init_world (point world[][world_height]){
    srand(time(NULL));
    for (int i = 0; i < world_width; i++){
        for (int j = 0; j < world_height; j++){
            int spawnOrNot = rand() % 2;
            if (spawnOrNot == 1)
                world[i][j].is_live = 1;
            else
                world[i][j].is_live = 0;
        }
    }
}

unsigned int get_live_count(point world[][world_height]){
    unsigned int count = 0;
    unsigned i, j;
    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            if (world[i][j].is_live == 1)
                count++;
        }
    }
    return count;
}

void read_point_neighbors(signed int nb[][2], unsigned int x, unsigned int y)
{
    unsigned int i, j;
    unsigned int k = 0;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y)
                continue;
            nb[k][0] = i;
            nb[k][1] = j;
            k++;
        }
    }
}

unsigned int count_live_neighbors(point world[][world_height], unsigned int x, unsigned int y)
{
    unsigned int count = 0;
    unsigned int i;
    signed int nb[8][2];
    signed int _x, _y;

    read_point_neighbors(nb, x, y);

    for (i = 0; i < 8; i++) {
        _x = nb[i][0];
        _y = nb[i][1];

        if (_x < 0 || _y < 0)
            continue;
        if (_x >= world_width || _y >= world_height)
            continue;

        if (world[_x][_y].is_live == 1)
            count++;
    }
    return count;
}

void next_generation(point world[][world_height], point prev_world[][world_height])
{
    unsigned int i, j;
    unsigned int live_nb;
    point p;

    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            p = prev_world[i][j];
            live_nb = count_live_neighbors(prev_world, i, j);

            if (p.is_live == 0) {
                if (live_nb == 3)
                    world[i][j].is_live = 1;
            } else {
                if (live_nb < 2 || live_nb > 3)
                    world[i][j].is_live = 0;
            }
        }
    }
}

/*
 * Копирование игрового мира. Используется для сохранения предыдущего поколения
*/
void copy_world(point src[][world_height], point dest[][world_height]){
    unsigned int i, j;
    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            dest[i][j] = src[i][j];
        }
    }
}


/*
 * Сравнение игровых миров текущего и предыдущего поколения
 */
int cmp_world(point w1[][world_height], point w2[][world_height]){
    unsigned int i, j;
    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            if (w1[i][j].is_live != w2[i][j].is_live) {
                return -1;
            }
        }
    }
    return 0;
}

void print_world(point world[][world_width]){
    unsigned int i, j;
    for (i = 0; i < world_width; i++) {
        for (j = 0; j < world_height; j++) {
            if (world[i][j].is_live == 1) {
                cout << '@';
            } else {
                cout << ' ';
            }
            cout << ' ';
        }
        cout << endl;
    }
}

int start(){
    point world[world_width][world_height];
    point prev_world[world_width][world_height];
    char key = '0';
    
    init_world(world);
    unsigned int live_points = -1;
    bool is_optimal = false;
    while (key != '1')
    {
        system("cls");
        print_world(world);
        copy_world(world, prev_world);
        next_generation(world, prev_world);

        is_optimal = cmp_world(world, prev_world) == 0;
        live_points = get_live_count(world);  

        if (is_optimal) {
            cout << "Optimal configuration detected" << endl;
        }

        if (live_points == 0) {
            cout << "All points died" << endl;
        }     
        key = getchar();
        cout<<endl<<endl;
    }
    return 0;
}