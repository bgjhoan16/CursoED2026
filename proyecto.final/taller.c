jhoan  camilo bonilla 
wendy sarely caicedo 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EN_ESPERA 1
#define EMBARCADO 2
#define ROJO 1
#define NEGRO 0

// estructuras
typedef struct Pasajero {
    int documento;
    int tipoDocumento;
    int estado;
    struct Pasajero *sig;
} Pasajero;

typedef struct Viaje {
    int codigoViaje;
    int capacidad;
    int color;
    struct Viaje *izq;
    struct Viaje *der;
    struct Viaje *padre;
} Viaje;

typedef struct Destino {
    int codigo;
    char nombre[100];
    char empresa[100];
    Pasajero *listaPasajeros;
    Viaje *raizViajes;
    struct Destino *sig;
} Destino;

Destino *listaDestinos = NULL;
int totalEmbarcados = 0;

// ========== PASAJEROS ==========

Pasajero *crearPasajero(int doc, int tipo) {
    Pasajero *nuevo;
    nuevo = (Pasajero *)malloc(sizeof(Pasajero));
    nuevo->documento = doc;
    nuevo->tipoDocumento = tipo;
    nuevo->estado = EN_ESPERA;
    nuevo->sig = NULL;
    return nuevo;
}

// agregar al final
void agregarPasajero(Destino *d, Pasajero *p) {
    Pasajero *aux;
    
    if (d->listaPasajeros == NULL) {
        d->listaPasajeros = p;
    } else {
        aux = d->listaPasajeros;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = p;
    }
}

// sacar del inicio
Pasajero *sacarPasajero(Destino *d) {
    Pasajero *aux;
    
    if (d->listaPasajeros == NULL) {
        return NULL;
    }
    
    aux = d->listaPasajeros;
    d->listaPasajeros = aux->sig;
    aux->sig = NULL;
    return aux;
}

// contar recursivo
int contarPasajeros(Pasajero *p) {
    if (p == NULL) {
        return 0;
    }
    return 1 + contarPasajeros(p->sig);
}

// buscar recursivo
int buscarPasajero(Pasajero *p, int doc) {
    if (p == NULL) {
        return 0;
    }
    if (p->documento == doc) {
        return 1;
    }
    return buscarPasajero(p->sig, doc);
}

// ver si existe en todos los destinos
int pasajeroExiste(int doc) {
    Destino *d;
    d = listaDestinos;
    
    while (d != NULL) {
        if (buscarPasajero(d->listaPasajeros, doc) == 1) {
            return 1;
        }
        d = d->sig;
    }
    return 0;
}

void registrarPasajero() {
    int codDestino, doc, tipo;
    Destino *d;
    Pasajero *nuevo;

    printf("\nCodigo del destino: ");
    scanf("%d", &codDestino);

    d = listaDestinos;
    while (d != NULL && d->codigo != codDestino) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("Numero de documento: ");
    scanf("%d", &doc);

    if (pasajeroExiste(doc) == 1) {
        printf("El pasajero ya existe.\n");
        return;
    }

    printf("Tipo documento (1=CC 2=Pasaporte 3=TI): ");
    scanf("%d", &tipo);

    if (tipo < 1 || tipo > 3) {
        printf("Tipo invalido.\n");
        return;
    }

    nuevo = crearPasajero(doc, tipo);
    agregarPasajero(d, nuevo);
    printf("Pasajero registrado.\n");
}

// mostrar recursivo
void mostrarPasajeros(Pasajero *p) {
    if (p == NULL) {
        return;
    }
    printf("\nDoc: %d Tipo: %d Estado: En espera", p->documento, p->tipoDocumento);
    mostrarPasajeros(p->sig);
}

void verPasajerosDestino() {
    int cod;
    Destino *d;

    printf("\nCodigo del destino: ");
    scanf("%d", &cod);

    d = listaDestinos;
    while (d != NULL && d->codigo != cod) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    if (d->listaPasajeros == NULL) {
        printf("No hay pasajeros.\n");
        return;
    }

    printf("\n=== PASAJEROS ===");
    mostrarPasajeros(d->listaPasajeros);
    printf("\n");
}

void embarcarPasajero() {
    int cod;
    Destino *d;
    Pasajero *p;

    printf("\nCodigo del destino: ");
    scanf("%d", &cod);

    d = listaDestinos;
    while (d != NULL && d->codigo != cod) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    p = sacarPasajero(d);
    
    if (p == NULL) {
        printf("No hay pasajeros en espera.\n");
        return;
    }

    printf("Embarcando pasajero Documento: %d\n", p->documento);
    totalEmbarcados = totalEmbarcados + 1;
    free(p);
}

void buscarPasajeroPorDoc() {
    int doc;
    Destino *d;
    Pasajero *p;

    printf("\nDocumento a buscar: ");
    scanf("%d", &doc);

    d = listaDestinos;
    while (d != NULL) {
        p = d->listaPasajeros;
        while (p != NULL) {
            if (p->documento == doc) {
                printf("Encontrado en destino: %s\n", d->nombre);
                return;
            }
            p = p->sig;
        }
        d = d->sig;
    }
    printf("Pasajero no encontrado.\n");
}



