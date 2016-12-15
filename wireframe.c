#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"
#include "objread.h"
#include "perspect.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

int main(int argc, char **argv) {

/* =================================================== */
/* 			 Alocação de vertices e arestas 		   */
/* =================================================== */
	VERTICE * vertices;
	vertices = (VERTICE *) malloc(sizeof(VERTICE)*1000);
	int limiteVertices = 1000;

	if(vertices == NULL) {
    	perror("Erro ao alocar vertices");
		exit(1);
	}

	ARESTA * arestas;
	arestas = (ARESTA *) malloc(sizeof(ARESTA)*1000);	
	int limiteArestas = 1000;

	if(arestas == NULL) {
		perror("Erro ao alocar vertices");
		exit(1);
	}

	int qtdVertices, qtdArestas;
	qtdVertices = qtdArestas = 0;

/* =================================================== */
/* 		   Variaveis de controle de perspectiva		   */
/* =================================================== */
	double pontoDeReferencia[3];
	double minX, maxX, minY, maxY;
	double escala;

/* =================================================== */
/* 			 Leitura dos vertices e arestas 		   */
/* 			 Calculo dos vertices min e max 		   */
/*    Calibra posição da câmera e rotação do objeto    */
/* =================================================== */
    lerComponentes(&vertices, &qtdVertices, &limiteVertices, &arestas, &qtdArestas, &limiteArestas, argc, argv);
    calculaMinMax(vertices, qtdVertices, &minX, &maxX, &minY, &maxY);
	
	pontoDeReferencia[0] = 0;
	pontoDeReferencia[1] = 0;
	pontoDeReferencia[2] = 180;

	double rotacao = 1;
/* =================================================== */
/* 	 	Inicia janela, cria tela e controles da SDL	   */
/* =================================================== */
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Visualizador 3D", 0 );

	SDL_Event event;
	int buttonDown = 0;
	int exit = 0;

	rotaciona(vertices, qtdVertices, pontoDeReferencia);
	while (!exit) {
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		calculaMinMaxD(vertices, qtdVertices, &minX, &maxX, &minY, &maxY);
		calculaEscala(&escala, minX, maxX, minY, maxY);
		projetaVertices(vertices, qtdVertices, escala, &minX, &maxX, &minY, &maxY);

		//desenhaArestas(gRender, arestas, &qtdArestas);
		for (int i = 0; i < qtdArestas; ++i) {
			lineRGBA(screen, vertices[(arestas[i].v1)-1].xd, vertices[(arestas[i].v1)-1].yd,
            	vertices[(arestas[i].v2)-1].xd, vertices[(arestas[i].v2)-1].yd, 
            	255, 255, 255, 100);
		}

		SDL_PollEvent(&event);
        switch(event.type){
        	case SDL_QUIT: // fechar janela
				exit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
            	buttonDown = 1;   
            	break;
             case SDL_MOUSEBUTTONUP:
             	buttonDown = 0;   
            	break;
			case SDL_MOUSEMOTION:
				if(buttonDown) {
					if (event.motion.xrel < 0) {
              			pontoDeReferencia[0]+=rotacao;
              			rotaciona(vertices, qtdVertices, pontoDeReferencia);
					}
            		else if (event.motion.xrel > 0) {
	            		pontoDeReferencia[0]-=rotacao;
	            		rotaciona(vertices, qtdVertices, pontoDeReferencia);
            		}
           			
           			if (event.motion.yrel < 0) {
            			pontoDeReferencia[1]-=rotacao;
            			rotaciona(vertices, qtdVertices, pontoDeReferencia);
           			}
            		else if (event.motion.yrel > 0) {
            			pontoDeReferencia[1]+=rotacao;
            			rotaciona(vertices, qtdVertices, pontoDeReferencia);
            		}
            	}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case 'q':
					case SDLK_ESCAPE:
						exit = 1;
						break;
					case SDLK_UP:
						pontoDeReferencia[0]-=rotacao;
						rotaciona(vertices, qtdVertices, pontoDeReferencia);
						break;
					case SDLK_DOWN:
						pontoDeReferencia[0]+=rotacao;
						rotaciona(vertices, qtdVertices, pontoDeReferencia);
						break;
					case SDLK_LEFT:
						pontoDeReferencia[1]+=rotacao;
						rotaciona(vertices, qtdVertices, pontoDeReferencia);
						break;
					case SDLK_RIGHT:
						pontoDeReferencia[1]-=rotacao;
						rotaciona(vertices, qtdVertices, pontoDeReferencia);
						break;
					default:
						break;
           		}
				break;
        }
        SDL_Flip(screen);
    }  

    // Destroi janela
    SDL_Quit();
    
    return 0;
}
