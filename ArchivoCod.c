#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESOS 5

int main() {
    int suma_total = 0;

    // Nombres de archivos de entrada
    char *archivos[NUM_PROCESOS] = {"archivo1.txt", "archivo2.txt", "archivo3.txt", "archivo4.txt", "archivo5.txt"};

    for (int i = 0; i < NUM_PROCESOS; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Proceso hijo
            FILE *archivo = fopen(archivos[i], "r");
            if (archivo == NULL) {
                perror("Error al abrir el archivo");
                exit(EXIT_FAILURE);
            }

            int digito;
            fscanf(archivo, "%d", &digito);

            printf("Proceso hijo %d: Leído %d del archivo %s\n", getpid(), digito, archivos[i]);

            fclose(archivo);
            exit(digito);
        }
    }

    // Proceso padre
    int status;
    for (int i = 0; i < NUM_PROCESOS; i++) {
        wait(&status);
        suma_total += WEXITSTATUS(status);
    }

    printf("Suma total: %d\n", suma_total);

    return 0;
}

