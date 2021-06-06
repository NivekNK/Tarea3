#include "list.h"

#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct Vector2 Vector2; // Estructura que contiene valores x e y de un punto

Vector2* newVector2(int x, int y); // Se crea un vector

Vector2* newVector2FromVector2(Vector2* aux); // Copia un vector existente en uno nuevo

float vector2Distance(Vector2* vec1, Vector2* vec2); // Retorna la distancia entre 2 vectores

int compareVector2(Vector2* vec1, Vector2* vec2); // Retorna 1 si dos vectores son iguales

void printVector2(Vector2* vec, char* mensaje); // Imprime un vector con el mensaje indicado

#endif /* VECTOR2_H */