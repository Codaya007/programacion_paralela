#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Inicializa el entorno MPI

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //  btiene el rango del proceso
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el número total de procesos

    if (size < 2) {
        printf("Este programa necesita al menos 2 procesos.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        // Proceso 0 envía un mensaje al proceso 1
        const char* message_to_send = "Hola desde el proceso 0";
        printf("Proceso %d enviando mensaje: %s\n", rank, message_to_send);
        MPI_Send(message_to_send, 30, MPI_CHAR, 1, 0, MPI_COMM_WORLD); // Enviar al proceso 1
    } else if (rank == 1) {
        // Proceso 1 recibe el mensaje del proceso 0
        char received_message[30];
        MPI_Recv(received_message, 30, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Recibir del proceso 0
        printf("Proceso %d recibió mensaje: %s\n", rank, received_message);
    }

    MPI_Finalize(); // Finaliza el entorno MPI
    return 0;
}
