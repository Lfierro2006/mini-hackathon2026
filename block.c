#include "headers/sorts.h"
#include <stdio.h>

/*
 * Tiempo:  O(n log n)   (igual que merge sort)
 * Memoria: O(1)
 * no es una implementación perfecta pero funciona, 
 * aunque el peor caso (arreglo invertido) no cumple con la complejidad O(n log n)
 * teniendo (n^2 log n)
*/

static void revertir(int arr[], int ini, int fin){
    for(int i=ini, j=fin-1; i<j; i++,j--){
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

//este merge es distinto al de merge.c porque este usa O(1) en
//memoria a diferencia de merge.c que tiene O(n) debido al temp
static void mergeDeBlock(int arr[], int ini, int mid, int fin){
    int i = ini;
    int j = mid;

    while(i < mid && j < fin){
        if(arr[i] <= arr[j]){
            i++;
        } else {
            int val = arr[j];
            for(int k = j; k > i; k--){
                arr[k] = arr[k-1];
            }
            arr[i] = val;
            i++;
            mid++;
            j++;
        }
        contador++;
    }
}

void blockSort(int arr[], int n){
    contador=0;
    if(n < 2) return;
    for(int width = 1; width < n; width *= 2){
        for(int ini = 0; ini < n; ini += 2 * width){
            int mid = ini + width;
            int fin = ini + 2 * width;
            if(mid > n) mid = n;
            if(fin > n) fin = n;
            if(mid < fin){
                mergeDeBlock(arr, ini, mid, fin);
            }
        }
    }
}