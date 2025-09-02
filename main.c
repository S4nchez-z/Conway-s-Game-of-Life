#include <stdio.h>
#include <stdlib.h>
#include "life.c"

int main(void) {
    int n;
    int t;
    int d;
    int **map;
    printf("Введите размер поля: ");
    scanf("%d", &n);
    printf("Введите колличество живых клеток: ");
    scanf("%d", &t);
    printf("Введите колличество ходов: ");
    scanf("%d", &d);

    FILE *input_file;

    map = (int**)malloc(sizeof(int*)*n);		
    for (int i = 0; i < n; i++) {			
        map[i] = (int*)malloc(sizeof(int)*n);		
    }							
    init_map(n, map, t);				

    input_file = fopen("input.txt", "w");
    
    for (int i = 0; i < n; i++) {					
        for (int j = 0; j < n; j++) {			
            fprintf(input_file, "%d ", map[i][j]);	
        }						
        fprintf(input_file, "\n");			
    }							
    fclose(input_file);					

    start_life(n, map, d);				 

    
    for (int i = 0; i < n; i++) {			
        free(map[i]);					
    }							
    free(map);						

    return 0;
}
