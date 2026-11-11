#include "headers/sorts.h"
#include <stdio.h>

void insertion(int arr[], int n){ 
    contador=0;
    for(int i=1; i<n; i++){ 
        int ins= arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>ins){
            contador++;
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = ins;
        if(j >= 0) contador++;
    }
}