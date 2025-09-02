#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "life.h"

void init_map(int n, int** map, int t) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            map[i][j] = 0;
        }
    }
    srand(time(NULL));
    i = 0;
    while (i < t) {
        int x = rand() % n;
        int y = rand() % n;
        if (map[x][y] == 0) {
            map[x][y] = 1;
            i++;
        }
    }
}

int count_neighbors(int n, int** map, int x, int y) {
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < n && j >= 0 && j < n && !(i == x && j == y)) {
                count += map[i][j];
            }
        }
    }
    return count;
}

void start_life(int n, int** map, int d) {
    int **new_map;
    FILE *output_file;
    char filename[20];

    new_map = (int**)malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++) {
        new_map[i] = (int*)malloc(sizeof(int)*n);
    }

    for (int a = 0; a < d; a++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int neighbors = count_neighbors(n, map, i, j);

                if (map[i][j] == 0 && neighbors == 3) {
                    new_map[i][j] = 1;
                } else if (map[i][j] == 1 && (neighbors < 2 || neighbors > 3)) {
                    new_map[i][j] = 0;
                } else {
                    new_map[i][j] = map[i][j];
                }
            }
        }

        snprintf(filename, sizeof(filename), "output_%d.txt", a + 1);
        output_file = fopen(filename, "w");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(output_file, "%d ", new_map[i][j]);
            }
            fprintf(output_file, "\n");
        }
        fclose(output_file);

        // переписывание старого поля в новое
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                map[i][j] = new_map[i][j];
            }
        }
    }

    
    for (int i = 0; i < n; i++) {							
        free(new_map[i]);								
    }											
    free(new_map);									
}
