#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// jhoan camilo bonilla 
//wendy sarely calzada 
// carolina aramburo
// oscar elian caicedo

struct Cliente {
    char nombre[50];
    char cedula[20];
    struct Cliente *sig;
};

struct Devolucion {
    char producto[50];
    struct Devolucion *sig;
};

struct Cliente *frente = NULL;
struct Cliente *fin = NULL;

struct Devolucion *tope = NULL;

void registrarCliente() {
    struct Cliente *nuevo;

    nuevo = (struct Cliente *)malloc(sizeof(struct Cliente));

    printf("Nombre: ");
    scanf(" %[^\n]", nuevo->nombre);

    printf("Cedula: ");
    scanf(" %[^\n]", nuevo->cedula);

    nuevo->sig = NULL;

    if (frente == NULL) {
        frente = nuevo;
        fin = nuevo;
    } else {
        fin->sig = nuevo;
        fin = nuevo;
    }

    printf("Cliente registrado en la cola.\n");
}

void mostrarCola() {
    struct Cliente *aux = frente;

    if (frente == NULL) {
        printf("No hay clientes en la cola.\n");
        return;
    }

    printf("\n--- FILA DE CLIENTES ---\n");

    while (aux != NULL) {
        printf("Nombre: %s\n", aux->nombre);
        printf("Cedula: %s\n\n", aux->cedula);
        aux = aux->sig;
    }
}

void atenderCliente() {
    struct Cliente *aux;

    if (frente == NULL) {
        printf("No hay clientes para atender.\n");
        return;
    }

    aux = frente;

    printf("\nCliente atendido:\n");
    printf("Nombre: %s\n", aux->nombre);
    printf("Cedula: %s\n", aux->cedula);

    frente = frente->sig;

    if (frente == NULL) {
        fin = NULL;
    }

    free(aux);
}

void registrarDevolucion() {
    struct Devolucion *nueva;

    nueva = (struct Devolucion *)malloc(sizeof(struct Devolucion));

    printf("Producto a devolver: ");
    scanf(" %[^\n]", nueva->producto);

    nueva->sig = tope;
    tope = nueva;

    printf("Devolucion registrada.\n");
}

void mostrarDevoluciones() {
    struct Devolucion *aux = tope;

    if (tope == NULL) {
        printf("No hay devoluciones pendientes.\n");
        return;
    }

    printf("\n--- DEVOLUCIONES PENDIENTES ---\n");

    while (aux != NULL) {
        printf("Producto: %s\n", aux->producto);
        aux = aux->sig;
    }
}

void procesarDevolucion() {
    struct Devolucion *aux;

    if (frente != NULL) {
        printf("Aun hay clientes en la cola.\n");
        printf("Primero deben atenderse todos los clientes.\n");
        return;
    }

    if (tope == NULL) {
        printf("No hay devoluciones pendientes.\n");
        return;
    }

    aux = tope;

    printf("Procesando devolucion del producto: %s\n", aux->producto);

    tope = tope->sig;

    free(aux);
}

void liberarMemoria() {
    struct Cliente *auxCliente;
    struct Devolucion *auxDevolucion;

    while (frente != NULL) {
        auxCliente = frente;
        frente = frente->sig;
        free(auxCliente);
    }

    while (tope != NULL) {
        auxDevolucion = tope;
        tope = tope->sig;
        free(auxDevolucion);
    }
}

int main() {
    int opcion;

    do {
        printf("\n===== SUPERMERCADO =====\n");
        printf("1. Registrar cliente\n");
        printf("2. Mostrar fila de clientes\n");
        printf("3. Atender cliente\n");
        printf("4. Registrar devolucion\n");
        printf("5. Mostrar devoluciones pendientes\n");
        printf("6. Procesar devolucion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarCliente();
                break;

            case 2:
                mostrarCola();
                break;

            case 3:
                atenderCliente();
                break;

            case 4:
                registrarDevolucion();
                break;

            case 5:
                mostrarDevoluciones();
                break;

            case 6:
                procesarDevolucion();
                break;

            case 7:
                liberarMemoria();
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 7);

    return 0;
}