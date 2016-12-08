#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"

void leVertice(VERTICE * v, char* dados);
void leFace(ARESTA ** arestas, int * qtdArestas, int * limArestas, char* dados);
FILE * retornaEntrada(int argc, char **argv);
int achaAresta(ARESTA * l, int tam, int e1, int e2);

void lerComponentes(VERTICE ** vertices, int * qtdVertices, int * limVertices, ARESTA ** arestas, int * qtdArestas, int * limArestas, int argc, char **argv) {
    FILE * entr = retornaEntrada(argc, argv);

    char dados[255];

    while(fgets(dados, 255, entr)>0){
    	// vertice
        if(dados[0] == 'v' && dados[1] == ' '){
        	if(*qtdVertices+10 >= *limVertices) {
        		*vertices = (VERTICE *) realloc(*vertices, sizeof(VERTICE)*(*limVertices+1000));
        		*limVertices += 1000;
        		if(*vertices == NULL) {
        			perror("Erro ao realocar vertices");
					exit(1);
        		}
        	}

            leVertice(&((*vertices)[*qtdVertices]), dados);
            ++(*qtdVertices);
        }
        // face
        else if (dados[0] == 'f' && dados[1] == ' '){
            leFace(arestas, qtdArestas, limArestas, dados);
        }
    }
    fclose(entr);
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

void leFace(ARESTA ** arestas, int * qtdArestas, int * limArestas, char* dados) {
	char *tmp;
	// ignora o 'f'
	tmp = strtok(dados, " ");
	tmp = strtok(NULL, " ");
	
	// le o id dos vertices em um vetor temporario
	int ti[255];
	int cont = 0;
	while(cont+2 < 100 && (tmp!=NULL) && (tmp[0] >= '0' && tmp[0] <= '9')) {
		ti[cont] = atoi(tmp);
		++cont;
		tmp = strtok(NULL, " ");
	}

	// liga o primeiro e o ultimo vertice da face
	ti[cont++] = ti[0];
	int j, a, b;
	for (int i = 0; i < cont-1; i++) {
		// "ordena" a aresta
		if(ti[i] < ti[i+1]) {
			a = ti[i];
			b = ti[i+1];
		} else {
			a = ti[i+1];
			b = ti[i];
		}

		if(!achaAresta(*arestas, *qtdArestas, a, b)){
			// **conferir se ainda cabe na lista de arestas**
			if(*qtdArestas+10 >= *limArestas) {
        		*arestas = (ARESTA *) realloc(*arestas, sizeof(ARESTA)*(*limArestas+1000));
       			*limArestas += 1000;

        		if(*arestas == NULL) {
        			perror("Erro ao realocar vertices");
					exit(1);
        		}
        	}

			// move as arestas ate achar o local correto da nova
			for (j = *qtdArestas-1; j >= 0 && (a < (*arestas)[j].v1 
				|| (a == (*arestas)[j].v1 && b < (*arestas)[j].v2)); --j) {
				(*arestas)[j+1].v1 = (*arestas)[j].v1;
				(*arestas)[j+1].v2 = (*arestas)[j].v2;
			}
			++j;
		
			// coloca os ids na lista de arestas
			(*arestas)[j].v1 = a;
			(*arestas)[j].v2 = b;
			++(*qtdArestas);
		}
	}
}

int achaAresta(ARESTA * l, int tam, int e1, int e2) {
	int inf = 0;
    int sup = tam-1;
    int meio;
    while (inf <= sup) {
		meio = (inf + sup)/2;
        if (l[meio].v1 == e1 && l[meio].v2 == e2)
        	return 1;
		if ((l[meio].v1 < e1) || (l[meio].v1 == e1 && l[meio].v2 <= e2))
        	sup = meio-1;
        else
        	inf = meio+1;
    }
    return 0; // não encontrado
}