#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer;
int n_numeros;

void *productor (void *arg) {
	int num_gen = rand() % 100000;
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

	// Asignamos el tamaño al buffer reservando memoria dinamica
	buffer = (int *) malloc (sizeof (int) * args[2]);
	if (buffer == NULL) {
		fprintf (stderr, "ERROR: Fallo al reservar memoria\n");
		exit(3);
	}

	n_numeros = args[1];

	int num_hilo[args[0]];
	pthread_t productor, consumidor[args[0]];

	/* Creamos el hilo productor y los Nhilos consumidores 
		usando num_hilo para pasar argumentos de forma segura */
	pthread_create (&productor, NULL, productor, (void *) NULL);
	for (i = 0; i < args[0];i++) {
		num_hilo[i] = i;
	}
	for (i = 0; i < args[0]; i++) {
		pthread_create (&consumidor[i], NULL, consumidor, (void *) &num_hilo[i]);
	}



	return 1;
}