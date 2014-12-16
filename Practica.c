#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer, sig_leer, tam_buffer, nnumeros ;


int string_to_int (char **argv, int i) {
	int arg;

	if (sscanf (argv[i], "%d", &arg) != 1) {
		fprintf (stderr, "ERROR: El argumento %dº no es un entero\n", i);
		exit(2);
	}

	return arg;
}

bool esPrimo (int num) {
	int divs = 2;

	while (divs <= sqrt (num)) {
		if (num % divs == 0) { return false; }
		else { divs++; }
	}

	return true;
}

void *productor (void *arg) {
	argumentos *args_consumidor = (argumentos *) arg, i;
	srand ((unsigned) time(NULL));

	for (i = 0; i < args_consumidor->n_numeros; i++) {
		buffer[i % args_consumidor->tam_buffer] = rand() % 100000;
	}

	pthread_exit(NULL);
}

void *consumidor (void *arg) {
	int id = *((int *) arg);
	int dato;

	while (true) {
		dato = buffer[sig_leer];
		sig_leer = (sig_leer + 1) % TamBuffer;

		if (esPrimo(dato)) {
			// Mensaje
		}
		else {
			// Mensaje
		}


		if (sig_leer >= nnumeros) {
			pthread_exit (NULL);
		}
	}

}

int main (int argc, char *argv[]) {
	// Comprobamos si se pasan tres argumentos
	if (argc != 4) {
		fprintf (stderr, "ERROR: Numero de argumentos incorrecto\n");
		exit(1);
	}

	
	tam_buffer = string_to_int (argv, 3);
	nnumeros = string_to_int (argv, 2);

	if (tam_buffer > nnumeros/2) {
		fprintf (stderr, "ERROR: El argumento TamBuffer es demasiado grande");
		exit(3);
	}

	// Asignamos el tamaño al buffer reservando memoria dinamica
	buffer = (int *) malloc (sizeof (int) * tam_buffer);
	if (buffer == NULL) {
		fprintf (stderr, "ERROR: Fallo al reservar memoria\n");
		exit(4);
	}

	
	pthread_t productor, consumidor[args_programa.n_hilos];

	/* Creamos el hilo productor y los Nhilos consumidores 
		usando num_hilo para pasar argumentos de forma segura */
	pthread_create (&productor, NULL, productor, (void *) NULL);
	int id_hilo[n_hilos];

	for (i = 0; i < n_hilos ;i++) {
		id_hilo[i] = i+1; 
	}
	for (i = 0; i < n_hilos; i++) {
		pthread_create (&consumidor[i], NULL, consumidor, (void *) &id_hilo[i]);
	}

	return 0;
}