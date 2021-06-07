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
    List* positions;
    float distance;
};

// Crea un camino vacio
Camino* crearCamino()
{
    Camino* cam = (Camino*)malloc(sizeof(Camino));
    cam->name = (char*)malloc(sizeof(char) * 20);
    cam->positions = createList();
    cam->distance = 0;

    return cam;
}

// Crea una posicion utilizando los valores indicados
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

char* getCaminoName(Camino* camino)
{
    return camino->name;
}

// Busca si una posicion ya se encuentra en el camino indicado
Position* searchPos(Camino* camino, int id)
{
    Position* pos = firstList(camino->positions);
    while (pos != NULL)
    {
        if (pos->id == id) return pos;
        pos = nextList(camino->positions);
    }

    return NULL;
}

void insertPosToMap(Map* map, Position* pos)
{
    insertMap(map, &pos->id, pos);
}

// retorna 1 si contiene a la posicion indicada
int listContainsPosition(List* list, Position* pos)
{
    Position* aux = firstList(list);
    while (aux != NULL)
    {
        if (compareVector2(pos->vec, aux->vec) == 1)
        {
            return 1;
        }
        aux = nextList(list);
    }

    return 0;
}

// Crea las posiciones adjuntas descartando las posiciones que ya estan en el camino
Map* crearMapConMenoresDistancias(Map* posibles, Camino* camino)
{
    Map* map = createMap(is_equal_float);
    setSortFunction(map, lower_than_float);
    Position* pos = firstMap(posibles);
    Position* lastPos = lastList(camino->positions);
    while (pos != NULL)
    {
        if (listContainsPosition(camino->positions, pos) != 1)
        {
            pos->distance = vector2Distance(lastPos->vec, pos->vec);
            insertMap(map, &pos->distance, pos);
        }
        pos = nextMap(posibles);
    }

    return map;
}

// Imprime todos los valores de un mapa de posiciones, principalmente usado para el de menores distancias
void printCurrentMenoresDist(Map* menoresDist, int check)
{
    int i = 0;
    Position* aux = firstMap(menoresDist);
    while (aux != NULL)
    {
        printf("ID: %i | Distancia: %f | ", returnIdFromPos(aux), returnDistFromPos(aux));
        printVector2(returnVecFromPos(aux), "Posicion:");
        aux = nextMap(menoresDist);
        i++;
        if (check != -1 && i >= check) break;
    }
}

// Retorna un random int, se puede indicar un int minus, que quiere decir que no retornara ese valor
int randomInt(int min, int max, int minus)
{
    int ret = -1;

    if (minus != -1)
    {
        ret = rand() % (max - min + 1) + min;
        while (ret == minus)
        {
            ret = rand() % (max - min + 1) + min;
        }
    }
    else
    {
        ret = rand() % (max - min + 1) + min;
    }

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
            id = randomInt(1, check, -1);
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
//obtener posicion aleatoria
Position* randomPos(Map* posibles, Map* menoresDist, int maxRandom)
{
    int id = randomInt(1, maxRandom, -1);
    Position* pos = positionFromId(posibles, menoresDist, id, maxRandom);
    return pos;
}

Position* searchByVector2(Map* map, Vector2* vec, int size)
{
    Position* pos = firstMap(map);
    for (int i = 0; i < size; i++)
    {
        if (compareVector2(pos->vec, vec) == 1)
        {
            return pos;
        }
        pos = nextMap(map);
    }

    return NULL;
}

// Genera una ruta random o no random, es random si int random = 1
Camino* crearRuta(Map* posibles, int random)
{
    int x, y;
    printf("Ingrese coordenada X: ");
    scanf("%i", &x);
    printf("Ingrese coordenada Y: ");
    scanf("%i", &y);

    int size = sizeMapa(posibles);
    Vector2* aux = newVector2(x, y);
    Position* current = searchByVector2(posibles, aux, size);
    if (current == NULL)
    {
        current = crearPos(aux, size + 1, 0);
    }
    else
    {
        size--;
    }
    Camino* camino = crearCamino();
    pushBack(camino->positions, current);
    for (int i = 0; i < size; i++)
    {
        // Empieza por crear el mapa de menores distancias desde la posicion actual
        Map* menoresDist = crearMapConMenoresDistancias(posibles, camino);
        Position* pos;
        if (random == 0) // Si no es random, pide al usuario el siguiente moviento
        {
            printCurrentMenoresDist(menoresDist, -1);
            pos = leerId(posibles, menoresDist);
        }
        else // Sino, busca una posicion random
        {
            if (current->id == size + 1)
            {
                pos = randomPos(posibles, menoresDist, size);
            }
            else
            {
                pos = randomPos(posibles, menoresDist, size + 1);
            }
        }
        // Finalmente se calcula la distancia actual y se inserta al camino actual
        camino->distance = camino->distance + pos->distance;
        if (random == 0) printf("Distancia Actual: %f\n", camino->distance);
        pushBack(camino->positions, pos);
    }

    char* name = (char*)malloc(sizeof(char) * 20);
    printf("Ingrese nombre de ruta: ");
    scanf("%s", name);
    strcpy(camino->name, name);

    return camino;
}

// Imprime las posiciones de un mapa cualquiera de posiciones
void printPositionsInMap(Map* posibles)
{
    Position* pos = firstMap(posibles);
    while (pos != NULL)
    {
        printf("ID: %i ", pos->id);
        printVector2(pos->vec, "Posicion:");
        pos = nextMap(posibles);
    }
}

// Imprime la distancia entre dos posiciones pidiendo el id de estas
void distanciaEntreDosPositions(Map* posibles)
{
    int id1, id2;

    printPositionsInMap(posibles);

    printf("Posicion 1: ");
    scanf("%i", &id1);
    printf("Posicion 2: ");
    scanf("%i", &id2);

    Position* pos1 = searchMap(posibles, &id1);
    Position* pos2 = searchMap(posibles, &id2);

    float result = vector2Distance(pos1->vec, pos2->vec);
    printf("Distancia: %f\n", result);
}

// Imprime un camino cualquiera indicado
void printCamino(Camino* camino)
{
    printf("Nombre: %s\n", camino->name);
    Position* pos = firstList(camino->positions);
    while (pos != NULL)
    {
        printf("ID: %i | ", pos->id);
        printVector2(pos->vec, "Posicion:");
        pos = nextList(camino->positions);
    }
    printf("Distancia total: %f\n", camino->distance);
}

// Pide unas coordenadas e imprime las primeras 3 menores distancias
void entregasMasCercanas(Map* posibles)
{
    int x, y;

    printf("Coordenada X: ");
    scanf("%i", &x);
    printf("Coordenada Y: ");
    scanf("%i", &y);

    Vector2* vec = newVector2(x, y);
    Camino* camino = crearCamino();
    pushBack(camino->positions, crearPos(vec, 0, 0));
    Map* distances = crearMapConMenoresDistancias(posibles, camino);
    printCurrentMenoresDist(distances, 3);
    free(vec);
    free(camino);
    free(distances);
}

// Intercambia dos posiciones en la lista de posiciones dentro del camino indicado
void changeListPositions(Camino* camino, Position* pos1, Position* pos2)
{
    Position* aux1 = crearPos(newVector2FromVector2(pos1->vec), pos1->id, pos1->distance);
    Position* aux2 = crearPos(newVector2FromVector2(pos2->vec), pos2->id, pos2->distance);

    List* list = createList();

    Position* data = firstList(camino->positions);
    while (data != NULL)
    {
        if (data->id == aux1->id)
        {
            pushBack(list, aux2);
        }
        else if (data->id == aux2->id)
        {
            pushBack(list, aux1);
        }
        else
        {
            pushBack(list, data);
        }
        data = nextList(camino->positions);
    }

    camino->positions = list;
}

// Recalcula la distancia total de un camino
void recalcularDistancias(Camino* camino)
{
    camino->distance = 0;
    List* list = createList();
    Position* aux = firstList(camino->positions);
    Position* pos;
    while (aux != NULL)
    {
        if (listSize(list) > 0)
        {
            if (listSize(list) == 1)
            {
                pos = firstList(list);
            }
            else
            {
                pos = nextList(list);
            }
            camino->distance = camino->distance + vector2Distance(pos->vec, aux->vec);
        }
        pushBack(list, aux);
        aux = nextList(camino->positions);
    }
    free(list);
}

// Intenta cambiar dos posiciones en un Camino o Ruta
void cambiarRuta(Map* rutas)
{
    char* aux = (char*)malloc(sizeof(char*) * 20);

    printf("Ruta a cambiar: ");
    scanf("%s", aux);
    
    Camino* camino = searchMap(rutas, aux);
    if (camino == NULL)
    {
        printf("Camino no encontrado!");
        return;
    }
    else
    {
        printCamino(camino);
    }

    int mode;
    printf("Indique 1 si manualmente o 0 si automatico: ");
    scanf("%i", &mode);

    int pos1, pos2;
    if (mode == 1)
    {
        printf("Posicion 1: ");
        scanf("%i", &pos1);
        printf("Posicion 2: ");
        scanf("%i", &pos2);
    }
    else if (mode == 0)
    {
        pos1 = randomInt(1, listSize(camino->positions), -1);
        pos2 = randomInt(1, listSize(camino->positions), pos1);
    }
    else
    {
        printf("Modo erroneo intente de nuevo!\n");
        return;
    }

    Position* aux1 = searchPos(camino, pos1);
    Position* aux2 = searchPos(camino, pos2);

    int message = 0;
    float oldDistance = camino->distance;
    changeListPositions(camino, aux1, aux2);
    recalcularDistancias(camino);

    // El cambio se revierte si la distancia actual es mayor a la distancia antigua
    if (camino->distance > oldDistance)
    {
        changeListPositions(camino, aux2, aux1);
        recalcularDistancias(camino);
        message = 1;
    }

    printCamino(camino);
    if (message == 1) printf("Cambio no realizado!\n");
}

// Muestra las rutas generando un mapa ordenado de floats con key distancia del Camino
// y valor lista de caminos con la misma distancia, luego lo imprime
void mostrarRutas(Map* rutas)
{
    Map* ordenado = createMap(is_equal_float);
    setSortFunction(ordenado, upper_than_float);

    Camino* aux = firstMap(rutas);
    while (aux != NULL)
    {
        List* auxCaminos = searchMap(ordenado, &aux->distance);
        if (auxCaminos != NULL)
        {
            pushBack(auxCaminos, aux);
        }
        else
        {
            auxCaminos = createList();
            pushBack(auxCaminos, aux);
            insertMap(ordenado, &aux->distance, auxCaminos);
        }
        aux = nextMap(rutas);
    }
    
    List* caminos = tailMap(ordenado);
    while (caminos != NULL)
    {
        printf("----------------------------\n");
        Camino* camino = firstList(caminos);
        while (camino != NULL)
        {
            printCamino(camino);
            camino = nextList(caminos);
        }
        
        caminos = prevMap(ordenado);
    }
    printf("----------------------------\n");

    free(ordenado);
}

// Obtiene los posibles caminos adjuntos desde un camino actual
List* getCaminosAdjuntos(Camino* current, Map* posibles)
{
    List* list = createList();

    Map* positions = crearMapConMenoresDistancias(posibles, current);
    Position* pos = firstMap(positions);
    while (pos != NULL)
    {
        Camino* camino = crearCamino();
        strcpy(camino->name, current->name);
        camino->positions = current->positions;
        pushBack(camino->positions, pos);
        recalcularDistancias(camino);

        pushBack(list, camino);

        pos = nextMap(positions);
    }

    return list;
}

// Realiza una busqueda en profundidad retornando el camino optimo desde un camino inicial
Camino* DFS(Camino* initial, Map* posibles, int size)
{
    Stack* stack = createStack();
    push(stack, initial);
    while (top(stack) != NULL)
    {
        Camino* current = top(stack);
        pop(stack);

        if (listSize(current->positions) >= size)
        {
            return current;
        }

        List* adj = getCaminosAdjuntos(current, posibles);
        Camino* aux = firstList(adj);
        while (aux != NULL)
        {
            push(stack, aux);
            aux = nextList(adj);
        }
        free(current);
    }

    return NULL;
}

// Retorna el camino optimo creado de el mapa de posibles posiciones
Camino* crearRutaOptima(Map* posibles, Map* rutas)
{
    int x, y;
    printf("Ingrese coordenada X: ");
    scanf("%i", &x);
    printf("Ingrese coordenada Y: ");
    scanf("%i", &y);

    int size = sizeMapa(posibles);
    Vector2* aux = newVector2(x, y);
    Position* current = searchByVector2(posibles, aux, size);
    if (current == NULL)
    {
        current = crearPos(aux, size + 1, 0);
    }
    else
    {
        size--;
    }
    
    Camino* init = crearCamino();
    strcpy(init->name, "RutaOptima");
    pushBack(init->positions, current);

    Camino* camino = DFS(init, posibles, size);

    char* name = "RutaOptima";
    for (int i = 2; searchMap(rutas, camino->name) != NULL; i++)
    {
        char* str = (char*)malloc(sizeof(char) * 10);
        strcpy(camino->name, name);
        sprintf(str, "%i", i);
        strcat(camino->name, str);
        free(str);
    }

    free(init);
    return camino;
}