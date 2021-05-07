// tres_raya

#define MAX_X 3
#define MAX_Y 3
#define YO 'X'
#define TU '-'

char tablero[MAX_X][MAX_Y];

// PROTOTIPOS

/**
 * Imprime el imprimir_tablero
 * Jugador humano usa X
 */
void imprimir_tablero();

/**
 * Iniciar las variables y arreglos principales
 */
void iniciar();

/**
 * Piede un número de casilla y comprueba que esté libre
 * @return int num. casilla verificada.
 */
int pideNumero();

/**
 * Establece un caracter en la posicion int de la matriz
 * @param  int  Posición en la matriz (arreglo)
 * @param  char Caracter a posicionar.
 * @param  int  Mensaje: 0 = no muestra mensaje. 1 = muestra msg
 * @return int retorna 0 si la posición estaba libre. 1 = Posición ocupada
 */
int setN(int, char, int);

int aleatorio(); // busca número aleatorio
int libres(); // cuantas casillas quedan libres
int ganador();  // Establece un ganador
int estratega(char, char); // Estudia al oponente o así mismo.
