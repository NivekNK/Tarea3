#include "Vector2.h"
#include "list.h"
#include "direcciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Vector2 Vector2;

// Estructura que contiene dos valores de un punto, x, y
struct Vector2 
{
    int x;
    int y;
};

// Crea un nuevo vector con x e y indicados
Vector2* newVector2(int x, int y)
{
    Vector2* vec = (Vector2*)malloc(sizeof(Vector2));
    vec->x = x;
    vec->y = y;
    return vec;
}

Vector2* newVector2FromVector2(Vector2* aux)
{
    Vector2* vec = (Vector2*)malloc(sizeof(Vector2));
    vec->x = aux->x;
    vec->y = aux->y;
    return vec;
}

// Calcula la distancia desde un vector a otro
float vector2Distance(Vector2* vec1, Vector2* vec2)
{
    Vector2* newVec = newVector2((vec2->x - vec1->x), (vec2->y - vec1->y));
    return sqrt( ( pow(newVec->x, 2) + pow(newVec->y, 2) ) );
}

// Compara que dos vectores sean iguales o no, retorna 1 si son iguales y 0 si no
int compareVector2(Vector2* vec1, Vector2* vec2)
{
    if (vec1->x == vec2->x && vec1->y == vec2->y) return 1;
    else return 0;
}

void printVector2(Vector2* vec, char* mensaje)
{
    printf("%s (%i, %i)\n", mensaje, vec->x, vec->y);
}