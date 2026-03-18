#include <stdio.h>
#include "areas.h"
#include "volumenes.h" 



int main() {
    double radio, lado;

    radio = 5.0;
    printf("Área del círculo (r=%.2f): %.2f\n", radio, areaCirculo(radio));

    lado = 4.0;
    printf("Área del cuadrado (l=%.2f): %.2f\n", lado, areaCuadrado(lado));

    radio = 3.0;
    printf("Volumen de la esfera (r=%.2f): %.2f\n", radio, volumenEsfera(radio));

    lado = 2.0;
    printf("Volumen del cubo (l=%.2f): %.2f\n", lado, volumenCubo(lado));

    return 0;
}

