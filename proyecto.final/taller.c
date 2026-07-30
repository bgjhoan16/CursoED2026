//jhoan  camilo bonilla 
//wendy sarely caicedo 
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

// ========== ARBOL ROJO-NEGRO ==========

Viaje *crearViaje(int cod, int cap) {
    Viaje *nuevo;
    nuevo = (Viaje *)malloc(sizeof(Viaje));
    nuevo->codigoViaje = cod;
    nuevo->capacidad = cap;
    nuevo->color = ROJO;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->padre = NULL;
    return nuevo;
}

// buscar recursivo en arbol
Viaje *buscarViaje(Viaje *raiz, int cod) {
    if (raiz == NULL) {
        return NULL;
    }
    if (cod == raiz->codigoViaje) {
        return raiz;
    }
    if (cod < raiz->codigoViaje) {
        return buscarViaje(raiz->izq, cod);
    }
    return buscarViaje(raiz->der, cod);
}

// rotaciones
void rotarIzq(Destino *d, Viaje *x) {
    Viaje *y;
    y = x->der;
    x->der = y->izq;
    
    if (y->izq != NULL) {
        y->izq->padre = x;
    }
    
    y->padre = x->padre;
    
    if (x->padre == NULL) {
        d->raizViajes = y;
    } else if (x == x->padre->izq) {
        x->padre->izq = y;
    } else {
        x->padre->der = y;
    }
    
    y->izq = x;
    x->padre = y;
}

void rotarDer(Destino *d, Viaje *y) {
    Viaje *x;
    x = y->izq;
    y->izq = x->der;
    
    if (x->der != NULL) {
        x->der->padre = y;
    }
    
    x->padre = y->padre;
    
    if (y->padre == NULL) {
        d->raizViajes = x;
    } else if (y == y->padre->der) {
        y->padre->der = x;
    } else {
        y->padre->izq = x;
    }
    
    x->der = y;
    y->padre = x;
}

// balancear
void balancear(Destino *d, Viaje *z) {
    Viaje *tio;
    
    while (z->padre != NULL && z->padre->color == ROJO) {
        if (z->padre == z->padre->padre->izq) {
            tio = z->padre->padre->der;
            
            if (tio != NULL && tio->color == ROJO) {
                z->padre->color = NEGRO;
                tio->color = NEGRO;
                z->padre->padre->color = ROJO;
                z = z->padre->padre;
            } else {
                if (z == z->padre->der) {
                    z = z->padre;
                    rotarIzq(d, z);
                }
                z->padre->color = NEGRO;
                z->padre->padre->color = ROJO;
                rotarDer(d, z->padre->padre);
            }
        } else {
            tio = z->padre->padre->izq;
            
            if (tio != NULL && tio->color == ROJO) {
                z->padre->color = NEGRO;
                tio->color = NEGRO;
                z->padre->padre->color = ROJO;
                z = z->padre->padre;
            } else {
                if (z == z->padre->izq) {
                    z = z->padre;
                    rotarDer(d, z);
                }
                z->padre->color = NEGRO;
                z->padre->padre->color = ROJO;
                rotarIzq(d, z->padre->padre);
            }
        }
    }
    d->raizViajes->color = NEGRO;
}

// insertar en arbol
void insertarViaje(Destino *d, int cod, int cap) {
    Viaje *nuevo, *y, *x;
    
    nuevo = crearViaje(cod, cap);
    y = NULL;
    x = d->raizViajes;

    while (x != NULL) {
        y = x;
        if (cod < x->codigoViaje) {
            x = x->izq;
        } else if (cod > x->codigoViaje) {
            x = x->der;
        } else {
            printf("Viaje ya existe.\n");
            free(nuevo);
            return;
        }
    }

    nuevo->padre = y;
    
    if (y == NULL) {
        d->raizViajes = nuevo;
    } else if (cod < y->codigoViaje) {
        y->izq = nuevo;
    } else {
        y->der = nuevo;
    }

    balancear(d, nuevo);
    printf("Viaje registrado.\n");
}

void registrarViaje() {
    int codDest, codViaje, cap;
    Destino *d;

    printf("\nCodigo destino: ");
    scanf("%d", &codDest);

    d = listaDestinos;
    while (d != NULL && d->codigo != codDest) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("Codigo viaje: ");
    scanf("%d", &codViaje);
    printf("Capacidad: ");
    scanf("%d", &cap);

    insertarViaje(d, codViaje, cap);
}

// inorden recursivo
void inorden(Viaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    inorden(raiz->izq);
    printf("\nViaje: %d Cap: %d Color: ", raiz->codigoViaje, raiz->capacidad);
    if (raiz->color == ROJO) {
        printf("ROJO");
    } else {
        printf("NEGRO");
    }
    inorden(raiz->der);
}

void verArbolViajes() {
    int cod;
    Destino *d;

    printf("\nCodigo destino: ");
    scanf("%d", &cod);

    d = listaDestinos;
    while (d != NULL && d->codigo != cod) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    if (d->raizViajes == NULL) {
        printf("No hay viajes.\n");
        return;
    }

    printf("\n=== VIAJES (INORDEN) ===");
    inorden(d->raizViajes);
    printf("\n");
}

void buscarViajeDestino() {
    int codDest, codViaje;
    Destino *d;
    Viaje *v;

    printf("\nCodigo destino: ");
    scanf("%d", &codDest);

    d = listaDestinos;
    while (d != NULL && d->codigo != codDest) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }

    printf("Codigo viaje: ");
    scanf("%d", &codViaje);

    v = buscarViaje(d->raizViajes, codViaje);
    
    if (v == NULL) {
        printf("Viaje no encontrado.\n");
        return;
    }

    printf("Viaje: %d Capacidad: %d Color: ", v->codigoViaje, v->capacidad);
    if (v->color == ROJO) {
        printf("ROJO\n");
    } else {
        printf("NEGRO\n");
    }
}

// contar viajes recursivo
int contarViajes(Viaje *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarViajes(raiz->izq) + contarViajes(raiz->der);
}

 // ========== DESTINOS ==========

Destino *crearDestino(int cod, char nom[], char emp[]) {
    Destino *nuevo;
    nuevo = (Destino *)malloc(sizeof(Destino));
    nuevo->codigo = cod;
    strcpy(nuevo->nombre, nom);
    strcpy(nuevo->empresa, emp);
    nuevo->listaPasajeros = NULL;
    nuevo->raizViajes = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

void registrarDestino() {
    int cod;
    char nom[100], emp[100];
    Destino *aux, *nuevo;

    printf("\nCodigo: ");
    scanf("%d", &cod);

    aux = listaDestinos;
    while (aux != NULL) {
        if (aux->codigo == cod) {
            printf("Destino ya existe.\n");
            return;
        }
        aux = aux->sig;
    }

    printf("Nombre: ");
    scanf(" %[^\n]", nom);
    printf("Empresa: ");
    scanf(" %[^\n]", emp);

    nuevo = crearDestino(cod, nom, emp);

    if (listaDestinos == NULL) {
        listaDestinos = nuevo;
    } else {
        aux = listaDestinos;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    printf("Destino registrado.\n");
}

// mostrar destinos recursivo
void mostrarDestinos(Destino *d) {
    if (d == NULL) {
        return;
    }
    printf("\nCodigo: %d Nombre: %s Empresa: %s", d->codigo, d->nombre, d->empresa);
    mostrarDestinos(d->sig);
}

void modificarDestino() {
    int cod;
    Destino *d;

    printf("\nCodigo destino: ");
    scanf("%d", &cod);

    d = listaDestinos;
    while (d != NULL && d->codigo != cod) {
        d = d->sig;
    }

    if (d == NULL) {
        printf("No encontrado.\n");
        return;
    }

    printf("Nuevo nombre: ");
    scanf(" %[^\n]", d->nombre);
    printf("Nueva empresa: ");
    scanf(" %[^\n]", d->empresa);
    printf("Modificado.\n");
    }
    // ========== ESTADISTICAS ==========

void estadisticas() {
    Destino *d;
    int totalPas, totalDes, totalVia, pas;
    Destino *mayor, *menor;
    float prom1, prom2;

    totalPas = 0;
    totalDes = 0;
    totalVia = 0;
    mayor = NULL;
    menor = NULL;
    d = listaDestinos;

    while (d != NULL) {
        pas = contarPasajeros(d->listaPasajeros);
        totalPas = totalPas + pas;
        totalDes = totalDes + 1;
        totalVia = totalVia + contarViajes(d->raizViajes);

        if (mayor == NULL || pas > contarPasajeros(mayor->listaPasajeros)) {
            mayor = d;
        }
        if (menor == NULL || pas < contarPasajeros(menor->listaPasajeros)) {
            menor = d;
        }

        d = d->sig;
    }

    printf("\n=== ESTADISTICAS ===");
    printf("\nTotal pasajeros: %d", totalPas);
    printf("\nTotal embarcados: %d", totalEmbarcados);

    if (totalDes > 0) {
        prom1 = (float)totalPas / totalDes;
        printf("\nPromedio pas/destino: %.2f", prom1);
    }
    
    if (totalVia > 0) {
        prom2 = (float)totalEmbarcados / totalVia;
        printf("\nPromedio emb/viaje: %.2f", prom2);
    }

    if (mayor != NULL) {
        printf("\nMayor espera: %s (%d pas)", mayor->nombre, 
               contarPasajeros(mayor->listaPasajeros));
    }
    
    if (menor != NULL) {
        printf("\nMenor espera: %s (%d pas)", menor->nombre,
               contarPasajeros(menor->listaPasajeros));
    }
    printf("\n");
}

// ========== LIBERAR MEMORIA ==========

void liberarPasajeros(Pasajero *p) {
    if (p == NULL) {
        return;
    }
    liberarPasajeros(p->sig);
    free(p);
}

void liberarViajes(Viaje *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarViajes(raiz->izq);
    liberarViajes(raiz->der);
    free(raiz);
}

void liberarTodo() {
    Destino *aux;
    
    while (listaDestinos != NULL) {
        aux = listaDestinos;
        liberarPasajeros(aux->listaPasajeros);
        liberarViajes(aux->raizViajes);
        listaDestinos = aux->sig;
        free(aux);
    }
}
// ========== MENU ==========

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


