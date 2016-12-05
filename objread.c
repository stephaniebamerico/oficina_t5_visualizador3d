#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"

void leVertice(VERTICE * v, char* dados);
FILE * retornaEntrada(int argc, char **argv);

void lerComponentes(VERTICE * vertices, int * qtdVertices, int argc, char **argv) {
    FILE * entr = retornaEntrada(argc, argv);

    char dados[200];
    *qtdVertices = 0;

    while(fgets(dados, 200, entr)>0){
    	// vertice
        if(dados[0] == 'v' && dados[1] == ' '){
            leVertice(&(vertices[*qtdVertices]), dados);
            ++(*qtdVertices);
        }
        // face
        /*else if (dados[0] == 'f' && dados[1] == ' '){
            lerFace(F->prox, dados);
            (*qtF)++;
        }*/
    }
}

FILE * retornaEntrada(int argc, char **argv) {
	if(argc > 1) {
		FILE * entr = fopen(argv[1], "r");

		if (!entr){
			perror("Erro ao abrir arquivo");
			exit(1);
		}

		return entr;
	}
	else
		return stdin;
}

void leVertice(VERTICE * v, char* dados) {
	char *tmp;
	// ignora o 'v'
	tmp = strtok(dados, " ");
	// le as coordenadas
	tmp = strtok(NULL, " ");
	v->x = atof(tmp);
	tmp = strtok(NULL, " ");
	v->y = atof(tmp);
	tmp = strtok(NULL, " ");
	v->z = atof(tmp);
}