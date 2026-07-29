#include <stdio.h>
#include "terminal.h"

int main() {
    int op;

    do {
        printf("\n========== TERMINAL ==========");
        printf("\n1. Registrar destino");
        printf("\n2. Ver destinos");
        printf("\n3. Modificar destino");
        printf("\n4. Registrar pasajero");
        printf("\n5. Ver pasajeros destino");
        printf("\n6. Buscar pasajero");
        printf("\n7. Embarque (FIFO)");
        printf("\n8. Registrar viaje");
        printf("\n9. Ver arbol viajes");
        printf("\n10. Buscar viaje");
        printf("\n11. Estadisticas");
        printf("\n0. Salir");
        printf("\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) {
            registrarDestino();
        } else if (op == 2) {
            if (listaDestinos == NULL) {
                printf("No hay destinos.\n");
            } else {
                mostrarDestinos(listaDestinos);
            }
        } else if (op == 3) {
            modificarDestino();
        } else if (op == 4) {
            registrarPasajero();
        } else if (op == 5) {
            verPasajerosDestino();
        } else if (op == 6) {
            buscarPasajeroPorDoc();
        } else if (op == 7) {
            embarcarPasajero();
        } else if (op == 8) {
            registrarViaje();
        } else if (op == 9) {
            verArbolViajes();
        } else if (op == 10) {
            buscarViajeDestino();
        } else if (op == 11) {
            estadisticas();
        } else if (op == 0) {
            liberarTodo();
            printf("Fin del programa.\n");
        } else {
            printf("Opcion invalida.\n");
        }
    } while (op != 0);

    return 0;
}