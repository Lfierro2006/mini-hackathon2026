#include "headers/sorts.h"

void merge(int arr[], int temp[], int ini, int mid, int fin ){
    int i = ini;
    int j = mid;
    int k = fin;
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
    memcpy(&a[ini], &temp[ini], (fin-ini)*sizeof(int));
}