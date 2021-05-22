#include "manageFiles.h"
#include "Map.h"
#include "Vector2.h"
#include "direcciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printOpciones()
{
  printf("1. Importar archivo\n");
  printf("2. Distancia entre entregas\n");
  printf("3. Mostrar 3 entregas mas cercanas\n");
  printf("4. Crear Ruta\n");
  printf("5. Generar ruta aleatoria\n");
  printf("6. Mejorar ruta\n");
  printf("7. Mostrar rutas\n");
  printf("8. Mejor ruta\n");
}

void operaciones(int solicitud, Map* posiblesVec2, FILE* file)
{
  Camino* camino;
  switch (solicitud)
  {
        case 1:
          file = importarArchivo();
          int lineas = 0;
          while (lineas < 1)
          {
            printf("escriba el numero de lineas que quiere leer\n");
            scanf("%i", &lineas);
          }
          insertarAMapa(file, posiblesVec2, lineas);
          break;
        case 2:
          break;
        case 4:
          camino = crearRuta(posiblesVec2, 0);
          printCamino(camino);
          break;
        case 5:
          camino = crearRuta(posiblesVec2, 1);
          printCamino(camino);
          break;
        
        default:
        break;
  }
}

int main()
{
    srand(time(NULL)); //reinicio del random
    FILE* file;

    Map* posiblesVec2 = createMap(is_equal_int);
    setSortFunction(posiblesVec2, lower_than_int);

    int solicitud = 100;
    while( solicitud != 0 )
    {
      printf("Selecione una opcion\n");
      printOpciones();
      scanf("%d", &solicitud);
      while(solicitud < 0 || solicitud > 8 ) 
      {
          printf("Selecione una opcion correcta\n");
          printOpciones();
          scanf("%d", &solicitud);
      }
      operaciones(solicitud, posiblesVec2, file);
    }
    return 0;
}