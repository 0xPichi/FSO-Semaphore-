#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer, sig_leer;

typedef struct {
	int id;
	int n_hilos;
	int n_numeros;
	int tam_buffer;
} argumentos;

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

	argumentos args_programa;
	args_programa.n_hilos = string_to_int (argv, 1);
	args_programa.n_numeros = string_to_int (argv, 2);
	args_programa.tam_buffer = string_to_int (argv, 3);

	if (args_programa.tam_buffer > args_programa.nnumeros/2) {
		fprintf (stderr, "ERROR: El argumento TamBuffer es demasiado grande");
		exit(3);
	}

	// Asignamos el tamaño al buffer reservando memoria dinamica
	buffer = (int *) malloc (sizeof (int) * args_programa.tam_buffer);
	if (buffer == NULL) {
		fprintf (stderr, "ERROR: Fallo al reservar memoria\n");
		exit(4);
	}

	argumentos args_productor = args_programa, args_consumidor[args_programa.n_hilos];
	pthread_t productor, consumidor[args_programa.n_hilos];

	/* Creamos el hilo productor y los Nhilos consumidores 
		usando num_hilo para pasar argumentos de forma segura */
	pthread_create (&productor, NULL, productor, (void *) &args_productor);
	parametro 
	for (i = 0; i < args_programa.n_hilos;i++) {
		args_consumidor[i] = args_programa;
		args_consumidor[i].id = i + 1;
	}
	for (i = 0; i < args_programa.n_hilos; i++) {
		pthread_create (&consumidor[i], NULL, consumidor, (void *) &args_consumidor[i]);
	}

	return 0;
}