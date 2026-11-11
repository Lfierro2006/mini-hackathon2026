#include "headers/sorts.h"
#include <stdio.h>
#include <string.h>

void merge(int arr[], int temp[], int ini, int mid, int fin ){
    int i = ini;
    int j = mid;
    int k = ini;
    
    while(i < mid && j < fin){
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

int main(int argc, char *argv[]){
    int arr[7]= {45,32,52,12,7,5,6};
    int n=7;
    int final[7];
    printf("45,32,52,12,7,5,6\n");
    mergeSort(arr, final, 0, n);
    printf("Post merge\n");
    for(int i=0; i<n; i++){
        printf("%d ", final[i]);
    }
    printf("\n");
    return 0;
}