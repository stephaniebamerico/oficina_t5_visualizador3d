/*== Stephanie Briere Americo ==*/

#ifndef __DATA_TYPES__
#define __DATA_TYPES__

typedef struct VERTICE {
	double x, y, z;
	double xd, yd, zd;
} VERTICE;

typedef struct ARESTA {
	// id dos dois vertices que constituem a aresta
	unsigned int v1, v2;
} ARESTA;

#endif