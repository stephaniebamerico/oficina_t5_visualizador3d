#include <SDL2/SDL.h>
#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"
#include "objread.h"

int main(int argc, char **argv) {

	double Cam[3];
	// double *projX, *projY, minX, maxX, minY, maxY;
	int qtdVertices;
	
	VERTICE * vertices;
	// o número de vertices É MAIS DE 8000
	vertices = (VERTICE *) malloc(sizeof(VERTICE)*70000);
	
	// tFace *F;
	// F = (tFace*) malloc(sizeof(tFace));

	//Leitura de dados
    lerComponentes(vertices, &qtdVertices, argc, argv);
	// projX = (double*) malloc((qtdVertices+1)*sizeof(double));
	// projY = (double*) malloc((qtdVertices+1)*sizeof(double));

    //Inicializa pos da camera
	Cam[0] = 5000.0;
	Cam[1] = 5000.0;
	Cam[2] = 5000.0;

	//Janela
	// SDL_Window* gWindow = NULL;

	//Superfície/tela
	// SDL_Surface* gScreen = NULL;

	//Renderizador
	// SDL_Renderer* gRenderer = NULL;

	//Inicializa SDL
	// SDL_Init( SDL_INIT_VIDEO );

	// gWindow = SDL_CreateWindow( "J&L Wireframe Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );
	// gScreen = SDL_GetWindowSurface( gWindow );
	// gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

	SDL_Event event;
	int exit = 0;
	while (!exit) {
		// Limpa tela
		// SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
		// SDL_RenderClear( gRenderer );

		// Projeção - encontra max e min
		// projetarVertices(V, projX, projY, Cam, quantV, &minX, &maxX, &minY, &maxY);

		// Transformação linear (?)
		// transformacaoLinear(V, projX, projY, quantV, minX, maxX, minY, maxY);

    	// Desenhar poliedro
		// desenharPoliedro(gRenderer, F, projX, projY, quantF);

        // Quando uma tecla é pressionada
        // SDL_RenderPresent( gRenderer );
        // if (SDL_PollEvent(&event)) {
        	// ESC ?
            if (event.type == SDL_QUIT) {
                exit = 1;
            } else if (event.type == SDL_KEYDOWN) {
            	if (event.key.keysym.sym == 'q')
					exit = 1;
				else if (event.key.keysym.sym == SDLK_LEFT)
					Cam[0]-=1000;
				else if (event.key.keysym.sym == SDLK_RIGHT)
					Cam[0]+=1000;
				else if (event.key.keysym.sym == SDLK_UP)
					Cam[1]-=1000;
				else if (event.key.keysym.sym == SDLK_DOWN)
					Cam[1]+=1000;
          	}
        // }
    }  

    // Destroi janela
    // SDL_DestroyRenderer( gRenderer );
    // gWindow = NULL;
    // gRenderer = NULL;

    // free(projX);
    // free(projY);
	// liberarVertices(V);
	// liberarFaces(F);
    
    return 0;
}
