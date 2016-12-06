#include "objread.h"

void desenhaArestas(SDL_Surface * screen, ARESTA * arestas, int qtdArestas) {
	for (int i = 0; i < qtdArestas; ++i) {
		lineRGBA(screen, vertices[(arestas[i].v1)-1].xd, vertices[(arestas[i].v1)-1].yd,
               vertices[(arestas[i].v2)-1].xd, vertices[(arestas[i].v2)-1].yd, 
               255, 255, 255, 100);
	}
}