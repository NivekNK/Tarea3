#include "list.h"

#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct Vector2 Vector2;

Vector2* newVector2(int x, int y);

float vector2Distance(Vector2* vec1, Vector2* vec2);

int compareVector2(Vector2* vec1, Vector2* vec2); // Retorna 1 si dos vectores son iguales

void printVector2(Vector2* vec, char* mensaje);

int listContainsVector2(List* list, Vector2* vec); // Retorna 1 si lista contiene al vector indicado

#endif /* VECTOR2_H */