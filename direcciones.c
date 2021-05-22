#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "direcciones.h"
#include "Vector2.h"
#include "list.h"
#include "Map.h"

typedef struct Position Position;
typedef struct Camino Camino;

struct Position
{
    Vector2* vec;
    int id;
    float distance;
};

struct Camino
{
    char* name;
    List* vector2s;
    float distance;
};

Camino* crearCamino()
{
    Camino* cam = (Camino*)malloc(sizeof(Camino));
    cam->name = (char*)malloc(sizeof(char) * 20);
    cam->vector2s = createList();
    cam->distance = 0;

    return cam;
}

Position* crearPos(Vector2* vec, int id, float dist)
{
    Position* pos = (Position*)malloc(sizeof(Position));
    pos->vec = vec;
    pos->id = id;
    pos->distance = dist;

    return pos;
}

Vector2* returnVecFromPos(Position* pos)
{
    return pos->vec;
}

int returnIdFromPos(Position* pos)
{
    return pos->id;
}

float returnDistFromPos(Position* pos)
{
    return pos->distance;
}

void insertPosToMap(Map* map, Position* pos)
{
    insertMap(map, &pos->id, pos);
}

Map* crearMapConMenoresDistancias(Map* posibles, Camino* camino)
{
    Map* map = createMap(is_equal_float);
    setSortFunction(map, lower_than_float);
    Position* pos = firstMap(posibles);
    Vector2* vec = lastList(camino->vector2s);
    while (pos != NULL)
    {
        if (listContainsVector2(camino->vector2s, pos->vec) != 1)
        {
            pos->distance = vector2Distance(vec, pos->vec);
            insertMap(map, &pos->distance, pos);
        }
        pos = nextMap(posibles);
    }

    return map;
}

void printCurrentMenoresDist(Map* menoresDist)
{
    Position* aux = firstMap(menoresDist);
    while (aux != NULL)
    {
        printf("ID: %i Distance: %f ", returnIdFromPos(aux), returnDistFromPos(aux));
        printVector2(returnVecFromPos(aux), "Vector2:");
        aux = nextMap(menoresDist);
    }
}

int randomInt(int min, int max)
{
    int ret = rand() % (max - min + 1) + min;
    return ret;
}

// Si check es 1 no se hace scanf al id
Position* positionFromId(Map* posibles, Map* menoresDist, int id, int check)
{
    Position* pos = searchMap(posibles, &id);
    if (pos != NULL) pos = searchMap(menoresDist, &pos->distance);
    while (pos == NULL)
    {
        if (check == 0)
        {
            printf("Ingrese un ID Correcto: ");
            scanf("%i", &id);
        }
        else
        {
            id = randomInt(1, check);
        }
        pos = searchMap(posibles, &id);
        if (pos != NULL) pos = searchMap(menoresDist, &pos->distance);
    }

    return pos;
}

Position* leerId(Map* posibles, Map* menoresDist)
{
    int id;
    printf("Ingrese ID de siguiente entrega: ");
    scanf("%i", &id);
    Position* pos = positionFromId(posibles, menoresDist, id, 0);
    return pos;
}

Position* randomPos(Map* posibles, Map* menoresDist, int maxRandom)
{
    int id = randomInt(1, maxRandom);
    Position* pos = positionFromId(posibles, menoresDist, id, maxRandom);
    return pos;
}

Camino* crearRuta(Map* posibles, int random)
{
    int x, y;
    printf("Ingrese coordenada X: ");
    scanf("%i", &x);
    printf("Ingrese coordenada Y: ");
    scanf("%i", &y);

    Vector2* current = newVector2(x, y);
    Camino* camino = crearCamino();
    pushBack(camino->vector2s, current);
    int size = sizeMapa(posibles);
    for (int i = 0; i < size; i++)
    {
        Map* menoresDist = crearMapConMenoresDistancias(posibles, camino);
        Position* pos;
        if (random == 0)
        {
            printCurrentMenoresDist(menoresDist);
            pos = leerId(posibles, menoresDist);
        }
        else
        {
            pos = randomPos(posibles, menoresDist, size);
        }
        camino->distance = camino->distance + pos->distance;
        if (random == 0) printf("Distancia Actual: %f\n", camino->distance);
        pushBack(camino->vector2s, pos->vec);
    }

    char* name = (char*)malloc(sizeof(char) * 20);
    printf("Ingrese nombre de ruta: ");
    scanf("%s", name);
    strcpy(camino->name, name);

    return camino;
}

void printCamino(Camino* camino)
{
    printf("Camino creado: %s\n", camino->name);
    printf("Distancia abarcada: %f\n", camino->distance);
    Vector2* vec = firstList(camino->vector2s);
    while (vec != NULL)
    {
        printVector2(vec, "Vector2:");
        vec = nextList(camino->vector2s);
    }
}