#include "Vector2.h"
#include "Map.h"

#ifndef DIRECCIONES_H
#define DIRECCIONES_H

typedef struct Position Position;

typedef struct Camino Camino;

Position* crearPos(Vector2* vec, int id, float dist);

Vector2* returnVecFromPos(Position* pos);

int returnIdFromPos(Position* pos);

float returnDistFromPos(Position* pos);

void insertPosToMap(Map* map, Position* pos);

Map* crearMapConMenoresDistancias(Map* posibles, Camino* camino);

Camino* crearRuta(Map* posibles, int random); // es random si int random = 1

void printCamino(Camino* camino);

#endif /* DIRECCIONES_H */