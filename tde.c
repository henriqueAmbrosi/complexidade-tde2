#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Ponto;

double calcularDistancia(Ponto* p1, Ponto* p2){
    return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y);
}

double calcularDistanciaCompleta(Ponto* p1, Ponto* p2){
    return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}


int main() {
    int N, i;
    Ponto vetor[10001];
    double dist;

    // Remover para beecrowd
    FILE *arquivo = fopen("input.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo input.txt!\n");
        return 1;
    }
    // ---

    fscanf(arquivo, "%d", &N);
    //scanf("%d", &N);
    
    while (N != 0) {
        
        for (i = 0; i < N; i++) {
            //scanf("%lf %lf", &(vetor[i].x), &(vetor[i].y));
            fscanf(arquivo, "%lf %lf", &(vetor[i].x), &(vetor[i].y));
        }
        
        dist = calcularDistanciaCompleta(&vetor[0], &vetor[1]);

        if (dist >= 10000) {
            printf("INFINITY\n");
        } else {
            printf("%.4lf\n", dist);
        }

        fscanf(arquivo, "%d", &N);
        //scanf("%d", &N);
    }

    fclose(arquivo);
    return 0;
}