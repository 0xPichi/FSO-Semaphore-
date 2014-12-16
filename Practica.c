#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

int *buffer, sig_leer, tam_buffer, nnumeros;
sem_t hay_dato, hay_espacio, mutex_leer;


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
	int i;
	srand ((unsigned) time(NULL));

	for (i = 0; i < nnumeros; i++) {
		sem_wait(&hay_espacio);
		buffer[i % tam_buffer] = rand() % 100000;
		sem_post(&hay_dato);
	}

	pthread_exit(NULL);
}

void *consumidor (void *arg) {
	int id = *((int *) arg);
	int i, dato, producido_numero;


	for(i = 0; i < nnumeros; i++) {
		sem_wait(&hay_dato);
		sem_wait($mutex_leer);
		dato = buffer[sig_leer];
		sig_leer = (sig_leer + 1) % tam_buffer;
		sem_post(&mutex_leer);
		sem_post(%hay_espacio);
		if (esPrimo(dato)) {
			printf("Hilo: %d , Valor producido numero: %d , Cantidad: %d , Es Primo.", id, producido_numero, dato);
		}
		else {
			printf("Hilo: %d , Valor producido numero: %d , Cantidad: %d , No es Primo.", id, producido_numero, dato);
		}

	}
	pthread_exit(NULL);

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

	
	pthread_t productor, consumidor[n_hilos];

	sem_init(&mutex_leer, 0, 1);
	sem_init(&hay_dato, 0, 0);
	sem_init(&hay_espacio, 0, tam_buffer);

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
	pthread_join(&productor);
	for(i = 0; i < n_hilos; i++){
		pthread_join(&consumidor[i]);
	}

	return 0;
}