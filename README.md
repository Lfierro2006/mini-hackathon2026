# Sort Visualizer MICRO-HACKATHON 2026

Visualizador de algoritmos de ordenamiento con raylib.


**Miembros del equipo**: 

- Lucas Fierro
- Franco Paredes

## Requisitos

- GCC (MSYS2 UCRT64 en Windows)
- raylib instalado: **pacman -S mingw-w64-ucrt-x86_64-raylib**

## Para compilar

```
gcc main.c merge.c -o sorts -lraylib -lgdi32 -lwinmm
```

## Sorts Implementados

- Bubble Sort
- Insertion Sort
- Merge Sort
- Block Sort


**PD: Los archivos `bubble.c`, `insertion.c` y `block.c` no son necesarios para que funcione el programa, solo quedaron como evidencia de la referencia utilizada para hacer el `main.c`**
