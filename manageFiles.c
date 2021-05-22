#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Map.h"
#include "Vector2.h"
#include "direcciones.h"

FILE* leerArchivo()
{
    char* filename = (char*)malloc(sizeof(char) * 30);

    printf("Ingrese nombre de archivo a importar: ");
    scanf("%s", filename);
    filename[strcspn(filename, "\n")] = 0;
    strcat(filename, ".txt");

    FILE* file = fopen(filename, "r");

    return file;
}

FILE* importarArchivo()
{
  FILE* newFile = NULL;
  while (newFile == NULL)
  {
    newFile = leerArchivo();
  }
    
  if (newFile != NULL) printf("Archivo importado!\n");

  return newFile;
}

int* separarPorEspacio(char* linea)
{
    int* returnValue = (int*)malloc(sizeof(int) * 2);

    char delimitador[] = " ";
    returnValue[0] = atoi(strtok(linea, delimitador));
    returnValue[1] = atoi(strtok(NULL, delimitador));

    return returnValue;
}

void insertarAMapa(FILE* file, Map* map, int max)
{
    char linea[1024];
    for (int i = 1; fgets(linea, 100, file) != NULL && i < max + 1; i++)
    {
        linea[strcspn(linea, "\n")] = 0;
        int* values = separarPorEspacio(linea);
        Position* pos = crearPos(newVector2(values[0], values[1]), i, 0);
        insertPosToMap(map, pos);
    }
}