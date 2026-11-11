#include "headers/sorts.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_N 200

typedef enum { SORT_NONE, SORT_BUBBLE, SORT_INSERTION, SORT_MERGE, SORT_BLOCK } SortKind;

//para blocksort
static int bl_mid, bl_fin;

static SortKind current = SORT_NONE;
static int *arr, *base, *temp;
static int n;
static int ops;

static int cmpA = -1, cmpB = -1;
static int movA = -1, movB = -1;

static int b_i, b_pass; static bool b_sorted;
static int ins_i, ins_j, ins_val; static bool ins_active;
static int m_width, m_ini, m_i, m_j, m_k; static bool m_active;
static int bl_width, bl_ini, bl_i, bl_j; static bool bl_active;

static void nuevoArreglo(void){
    for(int i = 0; i < n; i++) base[i] = 1 + rand() % 9999;
    for(int i = 0; i < n; i++) arr[i] = base[i];
    ops = 0; current = SORT_NONE;
    cmpA = cmpB = movA = movB = -1;
}

static void iniciarSort(SortKind k){
    for(int i = 0; i < n; i++) arr[i] = base[i];
    ops = 0; current = k;
    cmpA = cmpB = movA = movB = -1;

    if(k == SORT_BUBBLE){ b_i = 0; b_pass = 0; b_sorted = false; }
    if(k == SORT_INSERTION){ ins_i = 1; ins_active = false; }
    if(k == SORT_MERGE){
        contador = 0;
        mergeSort(arr, temp, 0, n);
        ops = contador;
        current = SORT_MERGE;
    }
    if(k == SORT_BLOCK){ bl_width = 1; bl_ini = 0; bl_i = bl_j = 0; bl_active = false; }
}

static void stepBubble(void){
    if(b_sorted) return;
    if(b_pass >= n - 1){ b_sorted = true; cmpA = cmpB = movA = movB = -1; return; }

    cmpA = b_i; cmpB = b_i + 1; movA = movB = -1;
    ops++;
    if(arr[b_i] > arr[b_i + 1]){
        int t = arr[b_i]; arr[b_i] = arr[b_i+1]; arr[b_i+1] = t;
        movA = b_i; movB = b_i + 1;
    }
    b_i++;
    if(b_i >= n - 1 - b_pass){ b_i = 0; b_pass++; }
}

static void stepInsertion(void){
    if(ins_i >= n){ cmpA = cmpB = movA = movB = -1; return; }

    if(!ins_active){
        ins_val = arr[ins_i]; ins_j = ins_i - 1; ins_active = true;
        cmpA = cmpB = movA = movB = -1;
        return;
    }

    if(ins_j >= 0){
        cmpA = ins_j; cmpB = ins_i; movA = movB = -1;
        ops++;
        if(arr[ins_j] > ins_val){
            arr[ins_j + 1] = arr[ins_j];
            movA = ins_j; movB = ins_j + 1;
            ins_j--;
            return;
        }
    }
    arr[ins_j + 1] = ins_val;
    movA = ins_j + 1; movB = -1;
    ins_active = false;
    ins_i++;
}

static void stepBlock(void){
    if(bl_width >= n){ cmpA = cmpB = movA = movB = -1; return; }

    if(!bl_active){ bl_ini = 0; bl_active = true; }

    if(bl_ini >= n){ bl_width *= 2; bl_ini = 0; if(bl_width >= n) return; }

    if(bl_i == 0 && bl_j == 0){
        bl_mid = bl_ini + bl_width;
        bl_fin = bl_ini + 2 * bl_width;
        if(bl_mid > n) bl_mid = n;
        if(bl_fin > n) bl_fin = n;
        if(bl_mid >= bl_fin){ bl_ini += 2 * bl_width; return; }
        bl_i = bl_ini;
        bl_j = bl_mid;
    }

    if(bl_i < bl_mid && bl_j < bl_fin){
        cmpA = bl_i; cmpB = bl_j; movA = movB = -1;
        ops++;
        if(arr[bl_i] <= arr[bl_j]){
            bl_i++;
        } else {
            int val = arr[bl_j];
            for(int k = bl_j; k > bl_i; k--) arr[k] = arr[k-1];
            arr[bl_i] = val;
            movA = bl_i; movB = bl_j;
            bl_i++;
            bl_mid++;
            bl_j++;
        }
        return;
    }

    bl_i = bl_j = 0;
    bl_ini += 2 * bl_width;
}

static void step(void){
    switch(current){
        case SORT_BUBBLE: stepBubble(); break;
        case SORT_INSERTION: stepInsertion(); break;
        case SORT_BLOCK: stepBlock(); break;
        default: break;
    }
}

static int pasosPorFrame(void){
    int p;
    if(current == SORT_BUBBLE || current == SORT_INSERTION)
        p = (n * n) / 1600;
    else
        p = (n * 8) / 160;
    if(p < 1) p = 1;
    return p;
}

static void dibujar(void){
    int w = GetScreenWidth(), h = GetScreenHeight();
    float barW = (float)w / n;
    for(int i = 0; i < n; i++){
        Color c = BLUE;
        if(i == movA || i == movB)      c = RED;
        else if(i == cmpA || i == cmpB) c = YELLOW;
        float barH = (float)arr[i] / 10000.0f * (h - 100);
        DrawRectangle((int)(i * barW), h - (int)barH, (int)barW - 1, (int)barH, c);
    }
    DrawText("1:Bubble 2:Insertion 3:Merge 4:Block  R:Nuevo  N:Cantidad  ESC:Salir", 10, 10, 18, DARKGRAY);
    DrawText(TextFormat("%s - %d ops",
        current==SORT_BUBBLE?"Bubble":current==SORT_INSERTION?"Insertion":
        current==SORT_MERGE?"Merge":current==SORT_BLOCK?"Block":"-", ops), 10, 40, 20, BLACK);
}

int main(void){
    printf("Ingrese tamaño del arreglo (1-%d): ", MAX_N);
    if(scanf("%d", &n) != 1 || n < 1 || n > MAX_N) return 1;

    base = malloc(n * sizeof(int));
    arr  = malloc(n * sizeof(int));
    temp = malloc(n * sizeof(int));
    if(!base || !arr || !temp) return 1;

    srand((unsigned)time(NULL));
    nuevoArreglo();

    InitWindow(1200, 700, "Sort Visualizer");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_ONE))   iniciarSort(SORT_BUBBLE);
        if(IsKeyPressed(KEY_TWO))   iniciarSort(SORT_INSERTION);
        if(IsKeyPressed(KEY_THREE)) iniciarSort(SORT_MERGE);
        if(IsKeyPressed(KEY_FOUR))  iniciarSort(SORT_BLOCK);
        if(IsKeyPressed(KEY_R))     nuevoArreglo();

        if(IsKeyPressed(KEY_N)){
            printf("Nuevo tamaño (1-%d): ", MAX_N);
            int nn;
            if(scanf("%d", &nn) == 1 && nn >= 1 && nn <= MAX_N){
                free(base); free(arr); free(temp);
                n = nn;
                base = malloc(n * sizeof(int));
                arr  = malloc(n * sizeof(int));
                temp = malloc(n * sizeof(int));
                nuevoArreglo();
            }
        }

        if(current != SORT_NONE){
            int pasos = pasosPorFrame();
            for(int s = 0; s < pasos; s++) step();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        dibujar();
        EndDrawing();
    }

    CloseWindow();
    free(base); free(arr); free(temp);
    return 0;
}