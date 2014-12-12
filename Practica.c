#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer;
int nnumeros;

bool esPrimo (int num) {
	int divs = 2;

	while (divs <= sqrt (num)) {
		if (num % divs == 0) { return false; }
		else { divs++; }
	}

	return true;
}

void *productor (void *arg) {
	int *args = (int *) arg, i;
	srand ((unsigned) time(NULL));

	for (i = 0; i < args[1]; i++) {
		buffer[i % args[2]] = rand() % 100000;
	}

	pthread_exit(NULL);
}

void *consumidor (void *arg) {
	int id = *((int *) arg);


}

int main (int argc, char *argv[]) {
	// Comprobamos si se pasan tres argumentos
	if (argc != 4) {
		fprintf (stderr, "ERROR: Numero de argumentos incorrecto\n");
		exit(1);
	}

	int i, args[3];
	/* Comprobamos que los argumentos son enteros y los almacenamos 
		args[0] = Nhilos
		args[1] = Nnumeros
		args[2] = TamBuffer */
	for (i = 1; i < argc; i++) {
		if (sscanf (argv[i], "%d", &args[i-1]) != 1) {
			fprintf (stderr, "ERROR: El argumento %dº no es un entero\n", i);
			exit(2);
		}
	}
	if (args[2] > args[1]/2) {
		fprintf (stderr, "ERROR: El argumento TamBuffer es demasiado grande");
		exit(3);
	}

	// Asignamos el tamaño al buffer reservando memoria dinamica
	buffer = (int *) malloc (sizeof (int) * args[2]);
	if (buffer == NULL) {
		fprintf (stderr, "ERROR: Fallo al reservar memoria\n");
		exit(4);
	}

	int num_hilo[args[0]];
	pthread_t productor, consumidor[args[0]];

	/* Creamos el hilo productor y los Nhilos consumidores 
		usando num_hilo para pasar argumentos de forma segura */
	pthread_create (&productor, NULL, productor, (void *) args);
	for (i = 0; i < args[0];i++) {
		num_hilo[i] = i+1;
	}
	for (i = 0; i < args[0]; i++) {
		pthread_create (&consumidor[i], NULL, consumidor, (void *) &num_hilo[i]);
	}

	return 0;
}