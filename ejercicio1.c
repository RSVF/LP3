#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodo {
    char * dato;
    struct nodo * izquierda;
    struct nodo * derecha;
};


void imprimir_vector(int arr[],int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r , int nivel);
int contar_comas(char* numeros_string);
void imprimir_vector_limites(int arr[], int izq , int der , int nivel);
struct nodo * crearNodo(char * dato);
void insertar(struct nodo ** arbol, char * dato);

struct nodo * crearNodo(char * dato) {
    struct nodo * nuevo = (struct nodo *) malloc(sizeof(struct nodo));
    nuevo->dato = dato;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

void insertar(struct nodo ** arbol, char * dato) {
    if (*arbol == NULL) {
        *arbol = crearNodo(dato);
        return;
    }
    if (strcmp(dato, (*arbol)->dato) < 0) {
        insertar(&((*arbol)->izquierda), dato);
        return;
    }
    if (strcmp(dato, (*arbol)->dato) > 0) {
        insertar(&((*arbol)->derecha), dato);
        return;
    }
}

// Merge sort 
// Función para fusionar dos subarreglos ordenados
void merge(int arr[], int l, int m, int r)
{
    int i, j, k; // índices para recorrer los subarreglos
    int n1 = m - l + 1; // tamaño del subarreglo izquierdo
    int n2 = r - m; // tamaño del subarreglo derecho

    // Crear arreglos temporales
    int L[n1], R[n2];

    // Copiar los datos a los arreglos temporales
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionar los arreglos temporales de vuelta al arreglo original
    i = 0; // índice inicial del primer subarreglo
    j = 0; // índice inicial del segundo subarreglo
    k = l; // índice inicial del subarreglo fusionado
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes del subarreglo izquierdo, si hay alguno
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del subarreglo derecho, si hay alguno
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función para ordenar un arreglo usando merge sort
void mergeSort(int arr[], int l, int r , int nivel)
{
    if (l < r) {

        // Encontrar el punto medio del arreglo
        
        int m = l + (r - l) / 2;

        // Ordenar las dos mitades recursivamente

        mergeSort(arr, l, m , nivel+1);
        mergeSort(arr, m + 1, r , nivel+1);

        // Fusionar las dos mitades ordenadas
        merge(arr, l, m, r);

        // simular el arbol en el printf

        //imprimir_vector_limites(arr,l,r+1,nivel);

    }

}

void recorrerMerge(int arr[], int l, int r , int nivel)
{
    if (l < r) {

        // Encontrar el punto medio del arreglo
        
        int m = l + (r - l) / 2;

        // Ordenar las dos mitades recursivamente

        recorrerMerge(arr, l, m , nivel+1);
        imprimir_vector_limites(arr,l,r+1,nivel);
        recorrerMerge(arr, m + 1, r , nivel+1);

        // Fusionar las dos mitades ordenadas
        // merge(arr, l, m, r);

        // simular el arbol en el printf

    printf("\n");

    }

}

int contar_comas(char* numeros_string) {
    int count = 0;
    char* ptr = numeros_string;

    while (*ptr) {
        if (*ptr == ',') {
            count++;
        }
        ptr++;
    }

    return count;
}

void imprimir_vector(int arr[],int n){

    printf("\n");

    for(int i = 0 ; i < n ; i++){

        printf("%d ",arr[i]);

    }

}

void imprimir_vector_limites(int arr[], int izq , int der , int nivel){

    printf("\n");

    for(int i=0; i < nivel; i++ ){

        printf("\t");

    }

    for(int i = izq ; i < der ; i++){

        printf("%d ",arr[i]);

    }

}



int main(int argc , char *argv[]){

    int i,n;

    // contar las comas equivale a contar cuantos numeros hay

    n =  contar_comas(argv[2])+1;

    // Para pasar los numeros del string al vector

    char * numeros_string = argv[2];

    // Creamos el vector

    int numeros[n];

    i = 0;

    char* token = strtok(numeros_string, ",");

    while (token != NULL && i < n) {

        numeros[i++] = atoi(token);

        token = strtok(NULL, ",");
    }

    printf("Vector antes de ordenar:");

    imprimir_vector(numeros,n);

    printf("\nTamaño del vector = %d\n", n);

    // Probamos el recorrido sin ordenar

    recorrerMerge(numeros,0,n-1,0);

    // Ordenanamos por MergeSort

    mergeSort(numeros,0,n-1,0);

    // Imprimir el vector ordenado

    printf("Luego de la ordenacion , el vector queda asi = ");

    imprimir_vector(numeros,n);

    printf("\n");

    return 0;
}