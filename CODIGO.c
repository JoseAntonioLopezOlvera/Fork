#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Proceso hijo
        if (execvp(argv[1], &argv[1]) < 0) {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    } else { // Proceso padre
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("El proceso hijo terminó con estado de salida: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}

