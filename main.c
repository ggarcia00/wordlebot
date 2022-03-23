#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define POPULACAO 10

typedef struct{
    int fitness;
    char genoma[5];
} Individuo;



void readfile(char **words){
    FILE *f = fopen("solutions.txt", "r");
    
    int c;
    int i = 0;
    int j = 0;

    while((c = fgetc(f)) != EOF){

        if( c == '\n'){
            i = 0;
            j++;
        }

        words[i][j] = c;
        i++;
    }
    printf("Fim do arquivo\n");
}



int evaluateFitness(Individuo ind, char target[5]){
    ind.fitness = 0;
    int i;
    int j;
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){

            if(ind.genoma[i] == ind.genoma[j]){
                if(i == j){
                    ind.fitness += 2;
                }else{
                    ind.fitness += 1;
                }
            }
        }
    }

}

void popula(Individuo *individuos, int len){
    srand(time(0));

    int i, j, letra;
    
    for(i =0; i < len; i++){
        for(j = 0; j < 5; j++){
            letra = (rand() % 25) + 'a';
            individuos[i].genoma[j] = letra;
        }
        individuos[i].genoma[j] = '\0';
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

    popula(individuos, POPULACAO);
    


    return 0;
}




