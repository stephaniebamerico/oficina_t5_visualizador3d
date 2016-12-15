/*== Stephanie Briere Americo ==*/

#ifndef __PERSPECT__
#define __PERSPECT__

// Dimensões da tela
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PI 3.14159265

void calculaMinMaxD(VERTICE * vertices, int qtdVertices, double * minX, double * maxX, double * minY, double * maxY);
void calculaMinMax(VERTICE * vertices, int qtdVertices, double * minX, double * maxX, double * minY, double * maxY);
void calculaEscala(double * escala, double minX, double maxX, double minY, double maxY);
void projetaVertices(VERTICE * vertices, int qtdVertices, double escala, double * minX, double * maxX, double * minY, double * maxY);
void perspectivaFracaVertices(VERTICE * vertices, int qtdVertices, double * ref);
void rotaciona(VERTICE * vertices, int qtdVertices, double * ref);
#endif