#include "datatypes.h"
#include "perspect.h"
#include <stdio.h>
#include <math.h>

void rotacionarX(VERTICE * vertices, int qtdVertices, double * ref);
void rotacionarY(VERTICE * vertices, int qtdVertices, double * ref);
void rotacionarZ(VERTICE * vertices, int qtdVertices, double * ref);

void perspectivaFracaVertices(VERTICE * vertices, int qtdVertices, double * ref) {
	for (int i = 0; i < qtdVertices; ++i) {
		// (vertices[i] - ref[2]) para inverter a posicao da camera
		vertices[i].xd = ref[0] + ref[2]*((vertices[i].x - ref[0])/(vertices[i].z - ref[2]));
		vertices[i].yd = ref[1] + ref[2]*((vertices[i].y - ref[1])/(vertices[i].z - ref[2]));
	}
}

void rotaciona(VERTICE * vertices, int qtdVertices, double * ref) {
	rotacionarX(vertices, qtdVertices, ref);
	rotacionarY(vertices, qtdVertices, ref);
	rotacionarZ(vertices, qtdVertices, ref);
}

void rotacionarX(VERTICE * vertices, int qtdVertices, double * ref) {
	double val = PI / 180.0;
	double u = ref[0]*val;
	
	for (int i = 0; i < qtdVertices; ++i) {
		vertices[i].xd = vertices[i].x;
		vertices[i].yd = vertices[i].y*cos(u) - vertices[i].z*sin(u);
		vertices[i].zd = vertices[i].y*sin(u) + vertices[i].z*cos(u);	
	}
}

void rotacionarY(VERTICE * vertices, int qtdVertices, double * ref) {
	double val = PI / 180.0;
	double v = ref[1]*val;
	
	for (int i = 0; i < qtdVertices; ++i) {
		vertices[i].xd = vertices[i].xd*cos(v) + vertices[i].zd*sin(v);
		vertices[i].yd = vertices[i].yd;
		vertices[i].zd = vertices[i].yd*cos(v) - vertices[i].xd*sin(v);		
	}
}

void rotacionarZ(VERTICE * vertices, int qtdVertices, double * ref) {
	double val = PI / 180.0;
	double w = ref[2]*val;
	
	for (int i = 0; i < qtdVertices; ++i) {
		vertices[i].xd = vertices[i].xd*cos(w) - vertices[i].yd*sin(w);
		vertices[i].yd = vertices[i].xd*sin(w) + vertices[i].yd*cos(w);
		vertices[i].zd = vertices[i].zd;		
	}
}

void calculaMinMaxD(VERTICE * vertices, int qtdVertices, double * minX, double * maxX, double * minY, double * maxY) {
	int i;
	*minX = *maxX = vertices[0].xd;
	*minY = *maxY = vertices[0].yd;	

	for(i = 1; i < qtdVertices; i++) {
		if(vertices[i].xd > *maxX)
			*maxX = vertices[i].xd;
		else if(vertices[i].xd < *minX)
			*minX = vertices[i].xd;

		if(vertices[i].yd > *maxY)
			*maxY = vertices[i].yd;
		else if(vertices[i].yd < *minY)
			*minY = vertices[i].yd;
	}
}

void calculaMinMax(VERTICE * vertices, int qtdVertices, double * minX, double * maxX, double * minY, double * maxY) {
	int i;
	*minX = *maxX = vertices[0].x;
	*minY = *maxY = vertices[0].y;	

	for(i = 1; i < qtdVertices; i++) {
		if(vertices[i].x > *maxX)
			*maxX = vertices[i].x;
		else if(vertices[i].x < *minX)
			*minX = vertices[i].x;

		if(vertices[i].y > *maxY)
			*maxY = vertices[i].y;
		else if(vertices[i].y < *minY)
			*minY = vertices[i].y;
	}
}

void calculaEscala(double * escala, double minX, double maxX, double minY, double maxY) {
	double escX, escY;
	// -20 porque não queria os vertices de limite colados nos limites da tela 
	escX = ((WINDOW_WIDTH-20)/(maxX-minX));
	escY = ((WINDOW_HEIGHT-20)/(maxY-minY));
	*escala = (escX < escY) ? escX : escY;
}

void projetaVertices(VERTICE * vertices, int qtdVertices, double escala, double * minX, double * maxX, double * minY, double * maxY) {
	double centroX, centroY;
	centroX = (*maxX + *minX)/2.0;
	centroY = (*maxY + *minY)/2.0;

	for(int i = 0; i < qtdVertices; i++) {
		vertices[i].xd = WINDOW_WIDTH/2 + ((vertices[i].xd - centroX)*escala);
		vertices[i].yd = WINDOW_HEIGHT/2 + ((vertices[i].yd - centroY)*escala);
	}
}