#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define EN_ESPERA 1
#define EMBARCADO 2
#define ROJO 1
#define NEGRO 0

// Estructuras
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

// Variables globales (extern para evitar duplicaciones al compilar)
extern Destino *listaDestinos;
extern int totalEmbarcados;

// Prototipos de Funciones - Pasajeros
Pasajero *crearPasajero(int doc, int tipo);
void agregarPasajero(Destino *d, Pasajero *p);
Pasajero *sacarPasajero(Destino *d);
int contarPasajeros(Pasajero *p);
int buscarPasajero(Pasajero *p, int doc);
int pasajeroExiste(int doc);
void registrarPasajero(void);
void mostrarPasajeros(Pasajero *p);
void verPasajerosDestino(void);
void embarcarPasajero(void);
void buscarPasajeroPorDoc(void);

// Prototipos de Funciones - Árbol Rojo-Negro / Viajes
Viaje *crearViaje(int cod, int cap);
Viaje *buscarViaje(Viaje *raiz, int cod);
void rotarIzq(Destino *d, Viaje *x);
void rotarDer(Destino *d, Viaje *y);
void balancear(Destino *d, Viaje *z);
void insertarViaje(Destino *d, int cod, int cap);
void registrarViaje(void);
void inorden(Viaje *raiz);
void verArbolViajes(void);
void buscarViajeDestino(void);
int contarViajes(Viaje *raiz);

// Prototipos de Funciones - Destinos
Destino *crearDestino(int cod, char nom[], char emp[]);
void registrarDestino(void);
void mostrarDestinos(Destino *d);
void modificarDestino(void);

// Prototipos de Funciones - Estadísticas y Memoria
void estadisticas(void);
void liberarPasajeros(Pasajero *p);
void liberarViajes(Viaje *raiz);
void liberarTodo(void);

#endif