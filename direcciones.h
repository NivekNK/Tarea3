#include "Vector2.h"
#include "Map.h"

#ifndef DIRECCIONES_H
#define DIRECCIONES_H

typedef struct Position Position;

typedef struct Camino Camino;

// Crea una posicion utilizando los valores indicados
Position* crearPos(Vector2* vec, int id, float dist);

// Retorna el nombre del camino indicado
char* getCaminoName(Camino* camino);

// Inserta posicion indicada al mapa de posiciones
void insertPosToMap(Map* map, Position* pos);

// Funcion 3 y 4 de la tarea, es random si int random = 1
Camino* crearRuta(Map* posibles, int random);

// Funcion 2 de la tarea, pide int ids y entrega la distancia entre las posiciones que corresponden a estas
void distanciaEntreDosPositions(Map* posibles);

// Funcion 3 de la tarea, pide unas coordenadas e imprime las primeras 3 menores distancias
void entregasMasCercanas(Map* posibles);

// Funcion 6 de la tarea
void cambiarRuta(Map* rutas);

// Funcion 7 de la tarea, muestra la rutas generando un mapa ordenado 
// de floats con valor distancia del Camino y luego lo imprime
void mostrarRutas(Map* rutas);

// Funcion 8 de la tarea, retorna el Camino optimo
Camino* crearRutaOptima(Map* posibles);

// Imprime un camino cualquiera indicado
void printCamino(Camino* camino);

#endif /* DIRECCIONES_H */