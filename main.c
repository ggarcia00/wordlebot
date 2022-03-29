#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define POPULACAO 200

typedef struct{
    int fitness;
    char genoma[5];
} Individuo;



void readfile(char **words){
    FILE *f = fopen("solutions.txt", "r");
    
    char c;
    int i = 0;
    int j = 0;

    while((c = fgetc(f)) != EOF){

        if( c == '\n'){
            j = 0;
            i++;
        } else {
            words[i][j] = c;
            j++;
        }

    }
    printf("Fim do arquivo\n");
    fclose(f);
}



void evaluateFitness(Individuo *ind, char target[5]){
    ind->fitness = 0;
    int i;
    int j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(ind->genoma[i] == target[j]){
                if(i == j){
                    ind->fitness += 2;
                }else{
                    ind->fitness += 1;
                }
            }
        }
    }
    // ind->fitness = ind->fitness/10;
}

void popula(Individuo *individuos, int len, char **words){
    srand(time(0));

    int i, j, letra, indice;
    
    for(i =0; i < len; i++){
        indice = (rand() % 2315);
        for(j = 0; j < 5; j++){
            letra = words[indice][j];
            // letra = (rand() % 25) + 'a';
            individuos[i].genoma[j] = letra;
        }
        // individuos[i].genoma[j] = '\0';
    }

}

void ordena(int array[POPULACAO]){
    int aux;

    for( int i = 0; i < POPULACAO; i++){
        for( int j = POPULACAO - 1; j > i; j--){
            if(array[j] < array[j-1]){
                aux = array[j];
                array[j] = array[j-1];
                array[j-1] = aux;
            }
        }
        // printf(" %d, ", array[i]);
    }
}


void roulette_wheel(Individuo *individuos){
    srand(time(0));

    int total_chance = 0, i, j;

    for (i = 0; i < POPULACAO; i++){
        total_chance += individuos[i].fitness;
    }
    int sorteio[POPULACAO];
    
    for(i = 0; i < POPULACAO; i++){
        sorteio[i] = rand() % total_chance;
    }

    ordena(sorteio);

    int atual_chance = 0;

    Individuo filhos[POPULACAO];
    
    for( i=0, j=0; j < POPULACAO; i++){
        atual_chance += individuos[i].fitness;
        if(atual_chance >= sorteio[j]){
            strcpy(filhos[j].genoma, individuos[i].genoma);
            atual_chance -= individuos[i].fitness;
            j++;
            i--;
        }
    }

    for(i=0; i < POPULACAO; i++){
        strcpy(individuos[i].genoma, filhos[i].genoma );
    }
}

// A D 
// C D 

// A B

void crossover(Individuo *individuos){
    Individuo troca;

    int i, j, k;

    for(i=0; i < POPULACAO; i+=2){
        strcpy(troca.genoma, individuos[i].genoma);

        // Crossover entre o começo do primeiro e final do segundo
        for(j=0; j<3; j++){
            individuos[i+1].genoma[j] = troca.genoma[j];
        }

        // Crossover entre o começo do segundo e final do primeiro
        for(j=4; j > 2; j--){
            individuos[i].genoma[j] = individuos[i+1].genoma[j];
        }
    
    }
}


void melhoresIndividuos(Individuo *individuos){
    int i = 0;

    printf("MELHORES INDIVIDUOS:\n");
    for(; i < POPULACAO; i++){
        printf("[%d] -> %s\n",  i+1, individuos[i].genoma);
    }
}


int main(){
    char *wordlist[2315];
    char target[5];
    Individuo individuos[POPULACAO];

    for( int i = 0; i < 2315; i++){
        wordlist[i] = malloc(sizeof(char) * 5 + 1);
    }

    readfile(wordlist);

    strcpy(target, wordlist[0]);

    popula(individuos, POPULACAO, wordlist);
    
    printf("\n");
    printf("\e[?25l");
    int geracao = 0;
    for(geracao = 1; geracao <= 1000; geracao++){
        printf("Geração: %d\r", geracao);

        for(int i = 0; i < POPULACAO; i++){
            evaluateFitness(&individuos[i], target);
        }

        // SELECIONA MELHORES INDIVIDUOS
        roulette_wheel(individuos);

        crossover(individuos);

        // scanf("a", NULL);
        // setbuf(stdin, NULL);
    }
    printf("\n");
    printf("\e[?25h");
    melhoresIndividuos(individuos);



    return 0;
}



