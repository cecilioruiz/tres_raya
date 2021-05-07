#include <stdio.h>
#include <stdlib.h>
#include "tres_raya.h"

/**
* Inicializa variables y el arreglo del tablero
*/
void iniciar(){
	char c = '1';
	for(int i = 0; i<MAX_Y; i++){
		for(int j = 0; j<MAX_X; j++){
			tablero[i][j] = c++;
		}
	}
}

/**
 * Imprime el tablero en pantalla.
 * Muestra posiciones de los jugadores y
 * número de casilla libre.
 */
void imprimir_tablero(){
	for(int i = 0; i<MAX_Y; i++){
		for(int j = 0; j<MAX_X; j++){
			if(j < MAX_X -1){
				printf(" %c |", tablero[i][j]);
			}
			else{
				printf(" %c  ", tablero[i][j]);
			}
		}
		printf("\n%s\n", "----------");
	}
}

/**
 * Pide un número de casilla libre.
 * en bucle hasta introducir uno válido
 * @return int casilla introducida valida
 */
int pideNumero(){
	int n;
	do{
		printf("\n%s", "Número de casilla: ");
		fflush(stdin);
		scanf("%d", &n);
	}while (n < 1 || n > (MAX_X * MAX_Y));
	return n;
}

/**
 * Genera un número aleatorio válido
 * (mayor de cero y del tamaño del tablero)
 * @return int número generado
 */
int aleatorio(){
	int n;
	n = rand() % (MAX_X * MAX_Y) + 1;
	//printf("\n%d\n", n);
	return n;
}

/**
 * Fija uno de los dos caracteres en la posición n
 * @param  n   Posición a fijar
 * @param  c   Caracter a fijar (humano o máquina)
 * @param  msg si es 1, se enviará un mensaje a la consola (solo para humano)
 * @return     0 si todo fue bien. 1 si la casila estaba ocupada.
 */
int setN(int n, char c, int msg){
	int i, j;
	if(n<1 || n> (MAX_X * MAX_Y )+1) // error si está fuera de rango
	{
		return 1;
	}

	i = (n -1 ) / MAX_Y; // coordenada y
	j = (n -1 ) % MAX_X; // coordenada x

	if(tablero[i][j] != YO && tablero[i][j] != TU)
	{
		tablero[i][j] = c;
		return 0;
	}
	if(msg) printf("%s\n", "Busca casilla libre.");
	return 1;
}

/**
 * Busca las posiciones libres
 * @return num. de posiciones libres encontradas
 */
int libres(){
	int n = 0;
	for(int i = 0; i<MAX_Y; i++){
		for(int j = 0; j<MAX_X; j++){
			if(tablero[i][j] != YO && tablero[i][j] != TU){
				n++;
			}
		}
	}
	return n;
}

/**
 * Retorna el caracter que hay en la posición n
 * @param  n Posición a retornar
 * @return   caracter de la posicion n
 */
char getN(int n){
	int i, j;
	if(n<1 || n> (MAX_X * MAX_Y )+1) // error si está fuera de rango
	{
		return 1;
	}
	i = (n -1 ) / MAX_Y; // coordenada y
	j = (n -1 ) % MAX_X;

	return tablero[i][j];
}

/**
 * Retorna un ganador si lo hay
 * @return 0 = no hay aún ganador. 1 = gana humano. 2 = gana maquina
 */
int ganador(){
	int n = 0;
	char c;
	// VERTICALES, COLUMNAS
	for(int i=0; i<MAX_Y; i++){
		c = tablero[i][0];
		if(c == tablero[i][1] && c == tablero[i][2]){
			n = (c== YO) ? 1: 2;
			return n;
		}
	}
	// HORIZONTALES, FILAS
	for(int i=0; i<MAX_Y; i++){
		c = tablero[0][i];
		if(c == tablero[1][i] && c == tablero[2][i]){
			n = (c== YO) ? 1: 2;
			return n;
		}
	}
	// DIAGONALES
	c = tablero[0][0];
	if(c == tablero[1][1] && c == tablero[2][2]){
		n = (c== YO) ? 1: 2;
		return n;
	}
	// DIAGONAL INVERSA: [0,2],[1,1],[2,0]
	c = tablero[0][2];
	if(c == tablero[1][1] && c == tablero[2][0]){
		n = (c== YO) ? 1: 2;
		return n;
	}
	return 0;
}

/**
 * Convierte filas y columnas a su número correspondiente
 * comenzando por la 0,0 del imprimir_tablero
 * @param  y coordenada columnas
 * @param  x coordenada filas
 * @return   valor numerico de las coordenadas
 */
int conversor(int y, int x){
	return ((y * MAX_X) + x) + 1;
}

/**
 * Estrategia del jugador maquina para ganar si puedo o bloquear al humano
 * @param  c  Caracter con el que juega
 * @param  no Caracter a bloquear sino puede ganador
 * @return    Posición donde colocar su ficha si hay posibilidad o 0 sino.
 */
int estratega(char c, char no){
	int n = 0, x = 0;

	// HORIZONTALES
	for(int i=0; i<MAX_Y; i++){
		if(c == tablero[i][0]) x++;
		if(c == tablero[i][1]) x++;
		if(c == tablero[i][2]) x++;
		if(x==2){
			for(int j=0; j<3; j++){
				if((c != tablero[i][j]) && (no != tablero[i][j])){
					n = conversor(i, j);
				}else{
					x--;
				}
			}
			if( x == 2)  return n;
		}
		x = 0;
	}

	// VERTICALES
	x = 0;
	for(int i=0; i<MAX_X; i++){
		if(c == tablero[0][i]) x++;
		if(c == tablero[1][i]) x++;
		if(c == tablero[2][i]) x++;

		if(x==2){
			for(int j=0; j<3; j++){
				if((c != tablero[j][i]) && (no != tablero[j][i])){
					n = conversor(j, i);
				}else{
					x--;
				}
			}
			if( x == 2)  return n;
		}
		x = 0;
	}
	// DIAGONALES
	// D [0,0],[1,1],[2,2]

	x = 0;
	if((tablero[0][0] == c) && (tablero[0][0] != no)) x++;
	if((tablero[1][1] == c) && (tablero[1][1] != no)) x++;
	if((tablero[2][2] == c) && (tablero[2][2] != no)) x++;
	if(x == 2){
		if(tablero[0][0] != c) n = conversor(0, 0);
		if(tablero[1][1] != c) n = conversor(1, 1);
		if(tablero[2][2] != c) n = conversor(2, 2);
		return n;
	}

	// I [0,2],[1,1],[2,0]

	x = 0;
	if((tablero[0][2] == c) && (tablero[0][2] != no)) x++;
	if((tablero[1][1] == c) && (tablero[1][1] != no)) x++;
	if((tablero[2][0] == c) && (tablero[2][0] != no)) x++;
	if(x == 2){
		if(tablero[0][2] != c) n = conversor(0, 2);
		if(tablero[1][1] != c) n = conversor(1, 1);
		if(tablero[2][0] != c) n = conversor(2, 0);
		return n;
	}

	return n;
}
