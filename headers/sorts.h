#ifndef SORTS_H
#define SORTS_H

extern int contador;

void bubbleSort(int arr[], int n);
void insertion(int arr[], int n);
void merge(int arr[], int temp[], int ini, int mid, int fin);
void mergeSort(int arr[], int temp[], int ini, int fin);
void blockSort(int arr[], int n);

#endif