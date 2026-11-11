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

## Cómo usar

1. Al ejecutar `./sorts`, la terminal pedirá el tamaño del arreglo (1-200). Escríbelo y presiona Enter.
2. Se abre una ventana con las barras del arreglo generado aleatoriamente.
3. Presiona una tecla para iniciar un sort:
   - `1` Bubble (animado)
   - `2` Insertion (animado)
   - `3` Merge (instantáneo)
   - `4` Block (animado)
4. Durante la animación:
   - **Amarillo** = elementos siendo comparados
   - **Rojo** = elementos siendo movidos
   - **Azul** = sin cambios
5. Arriba se muestra el nombre del sort y el número de operaciones.
6. `R` genera un nuevo arreglo con el mismo tamaño.
7. `N` pide un nuevo tamaño por terminal.
8. `ESC` cierra el programa.

**PD: Los archivos `bubble.c`, `insertion.c` y `block.c` no son necesarios para que funcione el programa, solo quedaron como evidencia de la referencia utilizada para hacer el `main.c`**
