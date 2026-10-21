#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Ponto;

// Ordenação

void troca(Ponto vet[], int i, int j) {
    Ponto aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particiona(Ponto vet[], int inicio, int fim) {
    double pivo = vet[fim].x;
    int pivo_indice = inicio;
    
    for (int i = inicio; i < fim; i++) {
        if (vet[i].x <= pivo) {
            troca(vet, i, pivo_indice);
            pivo_indice++;
        }
    }
    troca(vet, pivo_indice, fim);
    return pivo_indice;
}

void quickSort(Ponto vet[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo_indice = particiona(vet, inicio, fim);
        quickSort(vet, inicio, pivo_indice - 1);
        quickSort(vet, pivo_indice + 1, fim);
    }
}

// Cálculos de distância

double calcularDistanciaQuadrada(Ponto* p1, Ponto* p2){
    return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y);
}

// Obter menor distância

double menorDistanciaBacktracking(Ponto vet[], int size){
    double dist, temp;
    int i, j;
    dist = 10000 * 10000;
    for(i = 0; i < size - 1; i++){
        for(j = i + 1; j < size; j++){
            temp = calcularDistanciaQuadrada(&vet[i], &vet[j]);
            dist = fmin(dist, temp);
        }
    }

    return dist;

}

double menorDistanciaQuadrada(Ponto vet[], int size){
    double dist1, dist2, dist3, dist_real, mediana, limiteEsquerda, limiteDireita;
    int i, j;

    if(size < 5) return menorDistanciaBacktracking(vet, size);

    int half = size / 2;
    dist1 = menorDistanciaQuadrada(vet, half);
    dist2 = menorDistanciaQuadrada(&(vet[half]), size - half);

    dist3 = fmin(dist1, dist2);

    // calculando distancias em pontos de metade diferente
    mediana = vet[half].x;
    printf("mediana %lf\n", mediana);
    dist_real = sqrt(dist3);
    printf("Maior distancia até aqui %lf\n", dist_real);
    limiteEsquerda = mediana - dist_real;
    printf("Limite esquerdo %lf\n", limiteEsquerda);
    limiteDireita = mediana + dist_real;
    printf("Limite direito %lf\n", limiteDireita);
    for(i = half; vet[i].x > limiteEsquerda && i >= 0; i--);
    for(j = half; vet[j].x < limiteDireita && j < size; j++);
    printf("Primeiro numero %d %lf\n", i, vet[i].x);
    printf("Último numero %d %lf\n", j -1, vet[j-1].x);

    dist1 = menorDistanciaBacktracking(&(vet[i]), j - i);
    return fmin(dist1, dist3);
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
        
        quickSort(vetor, 0, N - 1);
        dist = sqrt(menorDistanciaQuadrada(vetor, N));

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