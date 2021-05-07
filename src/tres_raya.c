#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tres_raya.h"

struct tres_raya *tres_raya;

int main()
{
  srand (time(NULL));
  iniciar();
  int libre, gana, faltan, err;

  do {
    system("clear");
    printf("%s %c\n", "Fichas del humano:", YO );
    printf("%s %c\n", "Fichas del ordenador:", TU );
    libre = libres();

    printf("Libres: %d\n\n", libre-1);

    if(libre>1){ // Primero la maquina
      err = 1;
      faltan = estratega(TU, YO); // TENGO OPORTUNIDAD ?
      if(faltan >0){ // si hay un hueco poner
        err = setN(faltan, TU, 0); // devuelve 0 o 1
      }
      else // buscar ahora en humano.
      {
        faltan = estratega(YO, TU); // buscar hueco en humano
        if(faltan >0){
         err = setN(faltan, TU, 0);
        }
      }
      if(err == 1)
      {
          do{
          }while(setN(aleatorio(), TU, 0));
        }
      }

    imprimir_tablero();

    gana = ganador();
    if(gana !=0 ) break;

    do {} // Le toca al humano.
    while (setN(pideNumero(), YO, 1));

    gana = ganador();
    if(gana !=0 ) break;

  }while (libre>2 && gana == 0);

  if(gana !=0 ) printf("\n%s %s\n","¡¡ Gana el ", (gana==1)?"Humano !!":"Ordenador !!" );
    return 0;
}
