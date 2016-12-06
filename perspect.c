#include "datatypes.h"
#include "perspect.h"
#include <stdio.h>

void perspectivaFracaVertices(VERTICE * vertices, int qtdVertices, double * ref) {
	for (int i = 0; i < qtdVertices; ++i) {
		vertices[i].xd = ref[0] + ref[2]*((vertices[i].x - ref[0])/(vertices[i].z - ref[2]));
		vertices[i].yd = ref[1] + ref[2]*((vertices[i].y - ref[1])/(vertices[i].z - ref[2]));
	}
}

void calculaMinMax(VERTICE * vertices, int qtdVertices, double * minX, double * maxX, double * minY, double * maxY) {
	int i;
	if(vertices[0].xd < vertices[1].xd) {
		*minX = vertices[0].xd;
		*maxX = vertices[1].xd;	
	}
	else {
		*minX = vertices[1].xd;
		*maxX = vertices[0].xd;
	}
	if(vertices[0].yd < vertices[1].yd) {
		*minY = vertices[0].yd;
		*maxY = vertices[1].yd;	
	}
	else {
		*minY = vertices[1].yd;
		*maxY = vertices[0].yd;
	}

	for(i = 2; i < qtdVertices; i++) {
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

void calculaEscala(double * escala, double minX, double maxX, double minY, double maxY) {
	int escX, escY;
	escX = WINDOW_WIDTH/(maxX-minX);
	escY = WINDOW_HEIGHT/(maxY-minY);
	*escala = (escX < escY) ? escX : escY;
}

void projetaVertices(VERTICE * vertices, int qtdVertices, double escala, double * minX, double * maxX, double * minY, double * maxY) {
	int centroX, centroY;
	centroX = (*maxX + *minX)/2;
	centroY = (*maxY + *minY)/2;

	for(int i = 0; i < qtdVertices; i++) {
		vertices[i].xd = WINDOW_WIDTH/2 + (vertices[i].xd - centroX)*escala;
		vertices[i].yd = WINDOW_HEIGHT/2 + (vertices[i].yd - centroY)*escala;
	}
}