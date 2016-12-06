#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"
#include "objread.h"
#include "perspect.h"

int main(int argc, char **argv) {
	VERTICE * vertices;
	// O número de vertices É MAIS DE 8000 - **realocar**
	vertices = (VERTICE *) malloc(sizeof(VERTICE)*70000);

	ARESTA * arestas;
	// O número de arestas É MAIS DE 8000 - **realocar**
	arestas = (ARESTA *) malloc(sizeof(ARESTA)*70000);	
	
	int qtdVertices, qtdArestas;
	qtdVertices = qtdArestas = 0;

	// De onde voce observa o objeto
	double pontoDeReferencia[3];
	pontoDeReferencia[0] = 100.0;
	pontoDeReferencia[1] = 1000.0;
	pontoDeReferencia[2] = -5000.0;

	double minX, maxX, minY, maxY;
	double escala;

	// Leitura de dados
    lerComponentes(vertices, &qtdVertices, arestas, &qtdArestas, argc, argv);

	SDL_Init( SDL_INIT_VIDEO );
	SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Visualizador 3D", 0 );

	SDL_Event event;

	int exit = 0;
	while (!exit) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		perspectivaFracaVertices(vertices, qtdVertices, pontoDeReferencia);
		calculaMinMax(vertices, qtdVertices, &minX, &maxX, &minY, &maxY);
		calculaEscala(&escala, minX, maxX, minY, maxY);
		projetaVertices(vertices, qtdVertices, escala, &minX, &maxX, &minY, &maxY);

		//desenhaArestas(gRender, arestas, &qtdArestas);
		for (int i = 0; i < qtdArestas; ++i) {
			lineRGBA(screen, vertices[(arestas[i].v1)-1].xd, vertices[(arestas[i].v1)-1].yd,
            	vertices[(arestas[i].v2)-1].xd, vertices[(arestas[i].v2)-1].yd, 
            	255, 255, 255, 100);
		}

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit = 1;
            } else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == 'q' || event.key.keysym.sym == SDLK_ESCAPE)
					exit = 1;
				else if (event.key.keysym.sym == SDLK_LEFT)
					pontoDeReferencia[0]-=200;
				else if (event.key.keysym.sym == SDLK_RIGHT)
					pontoDeReferencia[0]+=200;
				else if (event.key.keysym.sym == SDLK_UP)
					pontoDeReferencia[1]-=200;
				else if (event.key.keysym.sym == SDLK_DOWN)
					pontoDeReferencia[1]+=200;
          	}
        }

    	SDL_Flip(screen);
    }  

    // Destroi janela
    SDL_Quit();
    
    return 0;
}
