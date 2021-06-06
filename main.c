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
  printf("0. Salir\n");
}

void operaciones(int solicitud, Map* posiblesVec2, Map* rutas, FILE* file, int* imported)
{
  Camino* camino;
 
  switch (solicitud)
  {
    //el switch se encarga de que el archivo sea leido correctamente 
        case 1:
          file = importarArchivo();
          int lineas = 0;
          *imported = 1;
          while (lineas < 1)
          {
            printf("escriba el numero de lineas que quiere leer\n");
            scanf("%i", &lineas);
          }
          insertarAMapa(file, posiblesVec2, lineas);
          break;
        case 2:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          distanciaEntreDosPositions(posiblesVec2);
          break;
        case 3:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          entregasMasCercanas(posiblesVec2);
          break;
        case 4:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          camino = crearRuta(posiblesVec2, 0);
          insertMap(rutas, getCaminoName(camino), camino);
          printCamino(camino);
          break;
        case 5:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          camino = crearRuta(posiblesVec2, 1);
          insertMap(rutas, getCaminoName(camino), camino);
          printCamino(camino);
          break;
        case 6:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          cambiarRuta(rutas);
          break;
        case 7:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          mostrarRutas(rutas);
          break;
        case 8:
          if (*imported == 0)
          {
            printf("Archivo no importado aun!\n");
            return;
          }
          else if (searchMap(rutas, "RutaOptima") != NULL)
          {
            printf("Ruta optima ya creada!");
            return;
          }
          camino = crearRutaOptima(posiblesVec2);
          insertMap(rutas, getCaminoName(camino), camino);
          printCamino(camino);
          break;
  }
}

int main()
{
    srand(time(NULL)); //reinicio del random
    FILE* file;
    int imported = 0;
//mapas que guardan rutas y vectores
    Map* posiblesVec2 = createMap(is_equal_int);
    setSortFunction(posiblesVec2, lower_than_int);

    Map* rutas = createMap(is_equal_string);

    int solicitud = 100;
    //se impromen las opciones y reimprimen de acuerdo a lo deseado
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
      operaciones(solicitud, posiblesVec2, rutas, file, &imported);
    }
    return 0;
}