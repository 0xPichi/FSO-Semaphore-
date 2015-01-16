#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

int string_to_int (char **argv, int i);
int esPrimo (int num);
void *produce (void *arg);
void *consume (void *arg);

int *buffer, sig_leer, tam_buffer, nnumeros;
sem_t hay_dato, hay_espacio, mutex_leer;

int main (int argc, char *argv[]) {
	// Comprobamos si se pasan tres argumentos
	if (argc != 4) {
		fprintf (stderr, "ERROR: Numero de argumentos incorrecto\n");
		exit(1);
	}

	int n_hilos = string_to_int (argv, 1);				// Convertimos los parametros recibidos a valores enteros que almacenamos
	nnumeros = string_to_int (argv, 2);					// en variables diferenciadas para facilitar su uso.
	tam_buffer = string_to_int (argv, 3);

	if (tam_buffer > nnumeros/2) {
		fprintf (stderr, "ERROR: El argumento TamBuffer es demasiado grande\n");
		exit(3);
	}

	// Asignamos el tamaño al buffer reservando memoria dinamica
	buffer = (int *) malloc (tam_buffer * sizeof (int));
	if (buffer == NULL) {
		fprintf (stderr, "ERROR: Fallo al reservar memoria\n");
		exit(4);
	}
	
	pthread_t productor, consumidor[n_hilos];

	sem_init (&mutex_leer, 0, 1);			//Semaforo inicializado a valor 1 encargado de la exclusion mutua.
	sem_init (&hay_dato, 0, 0);				//Semaforo inicializado a 0 que permite el paso en caso de que halla datos en el buffer.
	sem_init (&hay_espacio, 0, tam_buffer);	//Semaforo incializado al tamaño del buffer que permite el paso en caso de que halla datos en el buffer.

	/* Creamos el hilo productor y los Nhilos consumidores 
	   usando num_hilo para pasar argumentos de forma segura */
	pthread_create (&productor, NULL, produce, (void *) NULL);
	int i, id_hilo[n_hilos];

	for (i = 0; i < n_hilos; i++) {			// Llenamos id_hilo[] para el paso de argumentos seguro a los hilos	
		id_hilo[i] = i+1; 
	}
	for (i = 0; i < n_hilos; i++) {												// Creamos nhilos consumidores almacenando sus referencias en un array
		pthread_create (&consumidor[i], NULL, consume, (void *) &id_hilo[i]);	// para poder referirnos a ellos a traves del indice del array y crearlos 
	}																			// de forma iterativa.

	pthread_join(productor, NULL);
	for (i = 0; i < n_hilos; i++){												//Cada hilo consumidor espera a que el hilo anterior halla terminado o se
		pthread_join (consumidor[i], NULL);										// halla quedado bloqueado en algun semaforo.
	}

	return 0;
}

/* Metodo que convierte los argumentos recibidos por el main
   en enteros, en caso de no poderse realizar, lanza un mensaje
   de error y termina */

int string_to_int (char **argv, int i) {
	int arg;

	if (sscanf (argv[i], "%d", &arg) != 1) {
		fprintf (stderr, "ERROR: El argumento %dº no es un entero\n", i);
		exit(2);
	}

	return arg;
}

/* Calcula si un numero es primo */

int esPrimo (int num) {
	int divs = 2;

	while (divs <= sqrt (num)) {
		if (num % divs == 0) { return 0; }
		else { divs++; }
	}

	return 1;
}

/* Metodo con el cual los hilos productores
  producen los numeros aleatorios y los 
  almacenan en el buffer circular. */

void *produce (void *arg) {
	int i;
	srand ((unsigned) time(NULL));

	for (i = 0; i < nnumeros; i++) {
		sem_wait(&hay_espacio);							
		buffer[i % tam_buffer] = rand() % 100000;
		sem_post(&hay_dato);
	}

	pthread_exit(NULL);
}

/* Metodo con el cual los hilos consumidores
   leen los datos del buffer circular e imprimen 
   por pantalla su numero de hilo, el numero del
   valor producido, el numero leido y si es primo o no.*/

void *consume (void *arg) {
	int id = *((int *) arg);
	int i, dato;

	while (1) {
		sem_wait(&mutex_leer);		// Asignamos a cada hilo en local el indice del dato
		i = sig_leer;				// que le tocará leer en exclusion mutua
		sig_leer++;
		sem_post(&mutex_leer);
										
		if (!(i < nnumeros)) {			
			pthread_exit(NULL);
		}
		
		sem_wait(&hay_dato);			// Copiamos el dato que le toca leer al hilo
		dato = buffer[i % tam_buffer];
		sem_post(&hay_espacio);

		if (esPrimo(dato)) {
			printf("Hilo: %d, Valor producido numero: %d, Cantidad: %d, Es primo.\n", id, i+1, dato);
		}
		else {
			printf("Hilo: %d, Valor producido numero: %d, Cantidad: %d, No es primo.\n", id, i+1, dato);
		}
	}
}