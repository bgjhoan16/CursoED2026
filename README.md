# Sistema de Gestión de Terminal de Transportes

*Integrantes:*
* Jhoan Camilo Bonilla
* Wendy Sarely Calzada

---

## Descripción del Proyecto
Este proyecto es una aplicación de consola escrita en C que gestiona los destinos, pasajeros en lista de espera (mediante colas FIFO) y viajes programados (organizados en un Árbol Rojo-Negro balanceado) de un terminal de transportes.

---

## Estructura de Archivos
* terminal.h: Contiene las definiciones de estructuras, constantes y prototipos de funciones.
* terminal.c: Contiene la lógica de negocio y manipulación de las estructuras de datos.
* main.c: Contiene el menú interactivo para el usuario.
* Makefile: Script para automatizar la compilación con GCC.

---

## Instrucciones de Compilación y Ejecución

### Opción 1: Compilación con GCC (Windows / CMD)
```cmd
gcc main.c terminal.c -o programa
programa.exe 

*
informe 
El sistema está diseñado en lenguaje C bajo una arquitectura modular compuesta por un archivo de cabecera (terminal.h) y dos archivos de implementación (terminal.c y main.c). La solución permite administrar destinos, pasajeros en espera y viajes mediante estructuras de datos dinámicas avanzadas.2. ARQUITECTURA DEL SISTEMAEl software utiliza un enfoque de programación modular que divide la interfaz de declaración, la lógica interna y el menú de navegación para optimizar el mantenimiento y facilitar la compilación.                                                                                    +-------------------------------------------------+
|                    main.c                       |
|           (Interfaz y Menú Principal)            |
+-------------------------------------------------+
                        |
                        v
+-------------------------------------------------+
|                   terminal.h                    |
|      (Estructuras, Constantes y Prototipos)     |
+-------------------------------------------------+
                        |
                        v
+-------------------------------------------------+
|                   terminal.c                    |
|  (Lógica de Negocio y Estructuras de Datos)     |
+-------------------------------------------------+
3. ESTRUCTURAS DE DATOS UTILIZADASPara manejar los datos con eficiencia operacional y memoria dinámica, el programa combina tres tipos de estructuras:3.1. Lista Simplemente Enlazada (Destinos)Función: Representa el catálogo global de destinos (Destino).Propósito: Permite almacenar de forma dinámica los nodos correspondientes a cada destino (código, nombre, empresa) conectándolos a sus respectivas subsistemas de pasajeros y viajes.3.2. Cola FIFO / Lista Enlazada (Pasajeros)Función: Gestiona la lista de espera de pasajeros (Pasajero).Propósito: Garantiza que el embarque se realice bajo la lógica First-In, First-Out (El primero en llegar es el primero en embarcar). Cada pasajero registra su documento, tipo de documento y estado actual.3.3. Árbol Rojo-Negro (Viajes)Función: Representa el árbol binario de búsqueda balanceado de viajes (Viaje).Propósito: Indexa los viajes asociados a cada destino ordenados por su código de viaje. La propiedad de autorebalanceo del árbol rojo-negro asegura operaciones de búsqueda, inserción y rotación eficientes con una complejidad temporal de $O(\log n)$.4. FUNCIONALIDADES DEL SISTEMAEl programa incluye las siguientes operaciones divididas en módulos clave:Gestión de Destinos: Registro de destinos únicos, modificación de nombres/empresas asociadas y despliegue recursivo de información.Control de Pasajeros: Registro con validación previa para evitar duplicados en distintos destinos, consulta recursiva por documento y proceso de embarque dinámico mediante liberación de memoria.Manejo de Árbol de Viajes: Inserción con balanceo automático (rotaciones a la izquierda/derecha y reasignación de colores rojo/negro) y recorrido inorden para visualización ordenada de viajes.Módulo de Estadísticas: Cálculo de totales de pasajeros, embarcados, métricas promedio y búsqueda de destinos con mayor/menor tiempo o cantidad de espera.Gestión de Memoria: Liberación recursiva de memoria dinámica (free) al finalizar la ejecución para prevenir fugas de memoria (memory leaks).5. CONCLUSIÓNEl sistema desarrollado por Jhoan Camilo Bonilla y Wendy Sarely Calzada representa una solución completa y eficiente para el control de terminales de transporte. La integración de listas dinámicas junto con un árbol autorebalanceado demuestra un dominio sólido de estructuras de datos avanzadas, modularización en C y manejo responsable de la memoria dinámica.
*




*
explicación del Funcionamiento de las Colas FIFO
FIFO son las siglas de First-In, First-Out (Primero en Entrar, Primero en Salir). En este sistema representa la fila de espera de los pasajeros para abordar.

Mecanismo en el Código:
Inserción (Encolar / agregarPasajero): Los nuevos pasajeros se añaden al final de la lista enlazada recorriendo el puntero sig hasta llegar al último nodo (NULL).

Atención (Desencolar / sacarPasajero / embarcarPasajero): Al realizar el embarque, siempre se extrae el nodo que está al inicio de la lista (listaPasajeros). Luego, la cabeza de la lista avanza al siguiente pasajero (d->listaPasajeros = aux->sig).

Liberación: El nodo procesado se elimina de la memoria con free(p), garantizando que el orden de llegada sea estrictamente respetado.*




*Explicación del ABB Histórico (Árbol Binario de Búsqueda)El Árbol Binario de Búsqueda (ABB) 
es la estructura base previa a aplicar algoritmos de balanceo.Propiedades Clave:Organización: Cada nodo tiene como máximo dos hijos (izq y der).Regla de Orden: Para cualquier nodo con un valor $K$:Todos los nodos en su subárbol izquierdo tienen claves menores que $K$.Todos los nodos en su subárbol derecho tienen claves mayores que $K$.Utilidad: Permite realizar búsquedas rápidas con una complejidad promedio de $O(\log n)$.Limitación Histórica: Si los elementos se insertan en orden secuencial o casi ordenado (por ejemplo: 1, 2, 3, 4), el ABB se desbalancea y se degrada hasta convertirse en una lista enlazada, perdiendo su eficiencia y pasando a una complejidad de $O(n)$.*


*Explicación del Árbol Balanceado Asignado (Árbol Rojo-Negro)
Para solucionar el problema de degeneración del ABB tradicional, en este proyecto se implementó un Árbol Rojo-Negro, que es un Árbol Binario de Búsqueda Auto-Balanceado.Propiedades y Funcionamiento:Atributo Color: Cada nodo Viaje almacena un color (ROJO o NEGRO).Reglas de Balanceo:La raíz siempre debe ser de color NEGRO.Un nodo ROJO no puede tener hijos rojos (no existen dos nodos rojos consecutivos).Todos los caminos desde la raíz hasta las hojas nulas contienen la misma cantidad de nodos negros.Operaciones de Reajuste (balancear):Al insertar un nuevo viaje (que entra siempre como ROJO), se comprueba si se viola alguna regla. Si hay conflicto, el algoritmo realiza dos tipos de ajustes:Recoloreado: Cambia el color de los nodos (padre, tío y abuelo) para redistribuir el peso.Rotaciones (rotarIzq y rotarDer): Reorganiza los punteros del árbol para reducir la altura de la rama más larga.Gracias a este balanceo continuo, la altura del árbol nunca excede $2\log(n + 1)$, garantizando que las búsquedas e inserciones de viajes siempre sean óptimas con complejidad $O(\log n)$*





*casos de usos

### Caso de Uso 1: Registrar Nuevo Destino

* Actores: Administrador / Usuario del sistema.
* Descripción: Permite agregar una nueva ciudad de destino a la lista principal del terminal.
* Flujo Principal:
1. El usuario selecciona la opción 1 en el menú.
2. El sistema solicita el código del destino, el nombre de la ciudad y la empresa de transporte.
3. El sistema verifica si el código ya está registrado.
4. Si no existe, crea el nodo Destino y lo agrega al final de la lista enlazada.
5. El sistema muestra el mensaje "Destino registrado".


* Flujo Alternativo: Si el código ya existe, el sistema muestra el mensaje "Destino ya existe" y cancela la operación.

---

### Caso de Uso 2: Registrar Pasajero en Lista de Espera

* Actores: Pasajero / Operador de taquilla.
* Descripción: Registra un nuevo pasajero en la cola de espera de un destino específico.
* Flujo Principal:
1. El usuario selecciona la opción 4 en el menú.
2. El sistema solicita el código del destino.
3. El sistema valida que el destino exista en la lista principal.
4. El sistema pide el número de documento y el tipo de documento (CC, Pasaporte, TI).
5. El sistema verifica que el pasajero no esté registrado previamente en ningún destino.
6. Se crea el nodo Pasajero con estado EN_ESPERA y se encola al final de la lista del destino.
7. El sistema confirma "Pasajero registrado".


* Flujo Alternativo: * Si el destino no existe, muestra "Destino no encontrado".
* Si el documento ya está en el sistema, muestra "El pasajero ya existe".



---

### Caso de Uso 3: Embarcar Pasajero (Atención FIFO)

* Actores: Operador de abordaje.
* Descripción: Desencola y atiende al primer pasajero que llegó a la fila de espera de un destino.
* Flujo Principal:
1. El usuario selecciona la opción 7 en el menú.
2. El sistema solicita el código del destino.
3. El sistema ubica la cola de pasajeros del destino.
4. Se extrae el primer nodo de la lista (listaPasajeros), se actualiza la cabeza de la cola al siguiente nodo y se incrementa el contador de totalEmbarcados.
5. El sistema muestra el mensaje de confirmación con el documento embarcado y libera la memoria del nodo.


* Flujo Alternativo: Si no hay pasajeros en la fila, muestra "No hay pasajeros en espera".

---

### Caso de Uso 4: Registrar Viaje en Árbol Balanceado

* Actores: Administrador de rutas.
* Descripción: Inserta un nuevo viaje asociado a un destino manteniendo la estructura del Árbol Rojo-Negro balanceada.
* Flujo Principal:
1. El usuario selecciona la opción 8 en el menú.
2. El sistema solicita el código del destino, el código del viaje y su capacidad.
3. El sistema ubica el destino y busca la posición correcta en el árbol binario raizViajes según el código del viaje.
4. Se inserta el nuevo nodo Viaje con color inicial ROJO.
5. Se ejecuta la función balancear para verificar violaciones de color y realizar las rotaciones necesarias (izquierda o derecha) y recoloraciones.
6. El sistema confirma "Viaje registrado".


* Flujo Alternativo: Si el código del viaje ya existe en el árbol de ese destino, el sistema muestra "Viaje ya existe" y libera el nodo creado.

---

### Caso de Uso 5: Generar Estadísticas de la Terminal

* Actores: Gerencia / Administrador.
* Descripción: Calcula y muestra métricas generales sobre la operación de la terminal.
* Flujo Principal:
1. El usuario selecciona la opción 11 en el menú.
2. El sistema recorre la lista de destinos acumulando la cantidad total de pasajeros en espera, cantidad de destinos, total de viajes en los árboles y total de embarcados.
3. El sistema calcula los promedios de pasajeros por destino y embarcados por viaje.
4. El sistema determina cuál destino tiene la mayor y menor cantidad de pasajeros en espera.
5. Se despliegan todas las métricas procesadas en pantalla.*
