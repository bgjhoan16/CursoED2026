 #include <stdio.h>
#include <stdlib.h>

#define MAX 100

int vector[MAX];
int n = 0;
int datosIngresados = 0;

// Mostrar arreglo
void mostrar() {
    printf("\nArreglo actual:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

// Burbuja
void burbuja() {
    int temp;
    printf("\n--- Metodo Burbuja ---\n");

    for (int i = 0; i < n - 1; i++) {
        printf("\nPasada %d:\n", i + 1);

        for (int j = 0; j < n - i - 1; j++) {
            if (vector[j] > vector[j + 1]) {
                printf("Intercambio: %d <-> %d\n", vector[j], vector[j+1]);
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
                mostrar();
            }
        }
    }
}

// Selección
void seleccion() {
    int min, temp;
    printf("\n--- Metodo Seleccion ---\n");

    for (int i = 0; i < n - 1; i++) {
        min = i;
        printf("\nPasada %d:\n", i + 1);

        for (int j = i + 1; j < n; j++) {
            if (vector[j] < vector[min]) {
                min = j;
            }
        }

        if (min != i) {
            printf("Intercambio: %d <-> %d\n", vector[i], vector[min]);
            temp = vector[i];
            vector[i] = vector[min];
            vector[min] = temp;
            mostrar();
        }
    }
}

// Inserción
void insercion() {
    int key, j;
    printf("\n--- Metodo Insercion ---\n");

    for (int i = 1; i < n; i++) {
        key = vector[i];
        j = i - 1;

        printf("\nPasada %d:\n", i);

        while (j >= 0 && vector[j] > key) {
            printf("Movimiento: %d -> posicion %d\n", vector[j], j + 1);
            vector[j + 1] = vector[j];
            j--;
            mostrar();
        }

        vector[j + 1] = key;
        mostrar();
    }
}

// MAIN CORRECTO
int main() {
    int opcion;

    do {
        printf("\n==== MENU ====\n");
        printf("1. Registrar datos\n");

        if (datosIngresados) {
            printf("2. Mostrar arreglo\n");
            printf("3. Ordenar Burbuja\n");
            printf("4. Ordenar Seleccion\n");
            printf("5. Ordenar Insercion\n");
        }

        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Cantidad de elementos: ");
                scanf("%d", &n);

                for (int i = 0; i < n; i++) {
                    printf("Elemento [%d]: ", i);
                    scanf("%d", &vector[i]);
                }
                datosIngresados = 1;
                break;

            case 2:
                if (datosIngresados)
                    mostrar();
                else
                    printf("Primero ingrese datos.\n");
                break;

            case 3:
                if (datosIngresados)
                    burbuja();
                else
                    printf("Primero ingrese datos.\n");
                break;

            case 4:
                if (datosIngresados)
                    seleccion();
                else
                    printf("Primero ingrese datos.\n");
                break;

            case 5:
                if (datosIngresados)
                    insercion();
                else
                    printf("Primero ingrese datos.\n");
                break;

            case 6:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 6);

    return 0; // IMPORTANTE
} 