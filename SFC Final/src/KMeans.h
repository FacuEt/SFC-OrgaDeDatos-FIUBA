/*
 * KMeans.h
 *
 *  Created on: 25 de nov. de 2015
 *      Author: tomi
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>



using namespace std;

struct Punto {
	long double x;
	long double y;
};


class KMeans {
private:
	int max_iterations;
	int	nro_clusters;
	float max_tolerancia;
	vector<Punto*> centroides;

	void _initCentroides (vector<Punto*> puntos);

public:
	KMeans( int clusters ,int max_iter, float tolerancia );
	void fit( vector<Punto*> puntos);
	int predict( Punto* punto );

	void viewCentroides();
	virtual ~KMeans();
};

#endif /* KMEANS_H_ */