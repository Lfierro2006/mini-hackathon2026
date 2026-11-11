#include "headers/sorts.h"
#include <stdio.h>
#include <string.h>

void merge(int arr[], int temp[], int ini, int mid, int fin ){
    int i = ini;
    int j = mid;
    int k = ini;
    
    while(i < mid && j < fin){
        contador++;
        if(arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }
    while(i<mid) temp[k++] = arr[i++];
    while(j<fin) temp [k++] = arr[j++];
    memcpy(&arr[ini], &temp[ini], (fin-ini)*sizeof(int));
}

void mergeSort(int arr[], int temp[], int ini, int fin){
    if(fin-ini < 2) return;
    int mid = (ini + fin)/2;
    mergeSort(arr, temp, ini, mid);
    mergeSort(arr, temp, mid, fin);
    merge(arr, temp, ini, mid, fin);
}