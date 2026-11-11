#include "headers/sorts.h"
#include <stdbool.h>
#include <stdio.h>

int contador=0;

void bubbleSort(int arr[], int n){
    contador=0;
    int temp;
    bool issorted= false;
    while(!issorted){
        issorted=true;
        for(int i=0 ; i<n-1; i++){
            if(arr[i]>arr[i+1]){
                temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
                issorted=false;
            }
            contador++;
        }
    }
}