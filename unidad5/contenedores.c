// jhoan camilo bonilla gamboa 
// wendy sarely calzada quintero
// Carolina angulo aramburo 
// Oscar elian Caicedo Taylor

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONTENEDORES 30

int pesos[MAX_CONTENEDORES];
int cantidad = 0;
int ordenado = 0;

/* PROTOTIPOS */
void registrarContenedores();
void generarAleatorios();
void mostrarContenedores();

void quickSort(int arreglo[], int inicio, int fin);
int particion(int arreglo[], int inicio, int fin);

void heapSort(int arreglo[], int n);
void heapify(int arreglo[], int n, int i);

void mergeSort(int arreglo[], int izquierda, int derecha);
void merge(int arreglo[], int izquierda, int medio, int derecha);

int busquedaBinaria(int arreglo[], int n, int valor);

/* FUNCION PRINCIPAL */
int main()
{
    int opcion;
    srand(time(NULL));

    do
    {
        printf("\n========================================\n");
        printf("SISTEMA DE ORGANIZACION DE CONTENEDORES\n");
        printf("MUELLE DE CARGA\n");
        printf("========================================\n");
        printf("1. Registrar peso de contenedores manualmente\n");
        printf("2. Generar pesos aleatorios de contenedores\n");
        printf("3. Mostrar contenedores registrados\n");
        printf("4. Ordenar contenedores Quick Sort\n");
        printf("5. Ordenar contenedores Heap Sort\n");
        printf("6. Ordenar contenedores Merge Sort\n");
        printf("7. Buscar contenedor\n");
        printf("8. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarContenedores();
                break;

            case 2:
                generarAleatorios();
                break;

            case 3:
                mostrarContenedores();
                break;

            case 4:
                if(cantidad > 0)
                {
                    quickSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("\nOrdenamiento Quick Sort realizado.\n");
                }
                else
                {
                    printf("\nNo hay datos registrados.\n");
                }
                break;

            case 5:
                if(cantidad > 0)
                {
                    heapSort(pesos, cantidad);
                    ordenado = 1;
                    printf("\nOrdenamiento Heap Sort realizado.\n");
                }
                else
                {
                    printf("\nNo hay datos registrados.\n");
                }
                break;

            case 6:
                if(cantidad > 0)
                {
                    mergeSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("\nOrdenamiento Merge Sort realizado.\n");
                }
                else
                {
                    printf("\nNo hay datos registrados.\n");
                }
                break;

            case 7:
            {
                int pesoBuscado;
                int posicion;

                if(cantidad == 0)
                {
                    printf("\nNo existen datos.\n");
                    break;
                }

                if(!ordenado)
                {
                    printf("\nDebe ordenar primero el arreglo.\n");
                    break;
                }

                printf("\nIngrese el peso a buscar: ");
                scanf("%d", &pesoBuscado);

                posicion = busquedaBinaria(pesos, cantidad, pesoBuscado);

                if(posicion != -1)
                {
                    printf("\nContenedor encontrado en la posicion %d\n", posicion);
                }
                else
                {
                    printf("\nContenedor no encontrado.\n");
                }

                break;
            }

            case 8:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    } while(opcion != 8);

    return 0;
}

/* REGISTRO MANUAL */
void registrarContenedores()
{
    int i;

    printf("\nCantidad de contenedores (Maximo 30): ");
    scanf("%d", &cantidad);

    if(cantidad < 1 || cantidad > MAX_CONTENEDORES)
    {
        printf("\nCantidad invalida.\n");
        cantidad = 0;
        return;
    }

    for(i = 0; i < cantidad; i++)
    {
        printf("Peso contenedor %d: ", i + 1);
        scanf("%d", &pesos[i]);
    }

    ordenado = 0;
}

/* ALEATORIOS */
void generarAleatorios()
{
    int i;

    printf("\nCantidad de contenedores (Maximo 30): ");
    scanf("%d", &cantidad);

    if(cantidad < 1 || cantidad > MAX_CONTENEDORES)
    {
        printf("\nCantidad invalida.\n");
        cantidad = 0;
        return;
    }

    for(i = 0; i < cantidad; i++)
    {
        pesos[i] = rand() % 30001 + 1000;
    }

    ordenado = 0;

    printf("\nPesos generados correctamente.\n");
}

/* MOSTRAR */
void mostrarContenedores()
{
    int i;

    if(cantidad == 0)
    {
        printf("\nNo existen contenedores registrados.\n");
        return;
    }

    printf("\nLISTA DE CONTENEDORES\n");

    for(i = 0; i < cantidad; i++)
    {
        printf("%d kg\n", pesos[i]);
    }
}

/* QUICK SORT */
int particion(int arreglo[], int inicio, int fin)
{
    int pivote = arreglo[inicio];
    int izquierda = inicio + 1;
    int derecha = fin;
    int temp;

    while(izquierda <= derecha)
    {
        while(izquierda <= fin && arreglo[izquierda] <= pivote)
            izquierda++;

        while(arreglo[derecha] > pivote)
            derecha--;

        if(izquierda < derecha)
        {
            temp = arreglo[izquierda];
            arreglo[izquierda] = arreglo[derecha];
            arreglo[derecha] = temp;
        }
    }

    temp = arreglo[inicio];
    arreglo[inicio] = arreglo[derecha];
    arreglo[derecha] = temp;

    return derecha;
}

void quickSort(int arreglo[], int inicio, int fin)
{
    int pivote;

    if(inicio < fin)
    {
        pivote = particion(arreglo, inicio, fin);

        quickSort(arreglo, inicio, pivote - 1);
        quickSort(arreglo, pivote + 1, fin);
    }
}

/* HEAP SORT */
void heapify(int arreglo[], int n, int i)
{
    int mayor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;
    int temp;

    if(izquierda < n && arreglo[izquierda] > arreglo[mayor])
        mayor = izquierda;

    if(derecha < n && arreglo[derecha] > arreglo[mayor])
        mayor = derecha;

    if(mayor != i)
    {
        temp = arreglo[i];
        arreglo[i] = arreglo[mayor];
        arreglo[mayor] = temp;

        heapify(arreglo, n, mayor);
    }
}

void heapSort(int arreglo[], int n)
{
    int i;
    int temp;

    for(i = n / 2 - 1; i >= 0; i--)
        heapify(arreglo, n, i);

    for(i = n - 1; i > 0; i--)
    {
        temp = arreglo[0];
        arreglo[0] = arreglo[i];
        arreglo[i] = temp;

        heapify(arreglo, i, 0);
    }
}

/* MERGE SORT */
void merge(int arreglo[], int izquierda, int medio, int derecha)
{
    int i, j, k;

    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int L[n1];
    int R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arreglo[izquierda + i];

    for(j = 0; j < n2; j++)
        R[j] = arreglo[medio + 1 + j];

    i = 0;
    j = 0;
    k = izquierda;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arreglo[k] = L[i];
            i++;
        }
        else
        {
            arreglo[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        arreglo[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arreglo[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arreglo[], int izquierda, int derecha)
{
    int medio;

    if(izquierda < derecha)
    {
        medio = (izquierda + derecha) / 2;

        mergeSort(arreglo, izquierda, medio);
        mergeSort(arreglo, medio + 1, derecha);

        merge(arreglo, izquierda, medio, derecha);
    }
}

/* BUSQUEDA BINARIA */
int busquedaBinaria(int arreglo[], int n, int valor)
{
    int inicio = 0;
    int fin = n - 1;
    int medio;

    while(inicio <= fin)
    {
        medio = (inicio + fin) / 2;

        if(arreglo[medio] == valor)
            return medio;

        if(arreglo[medio] < valor)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }

    return -1;
}


