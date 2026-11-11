#include "headers/sorts.h"

void insertion(int arr[], int n){ 
    for(int i=1; i<n; i++){ 
        int ins= arr[i];
        int j = i-1;
    
        while(j>=0 && arr[j]>ins){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = ins;
    }
}