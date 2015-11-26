/*
 * KMeans.cpp
 *
 *  Created on: 25 de nov. de 2015
 *      Author: tomi
 */

#include "KMeans.h"

KMeans::KMeans(int clusters ,int max_iter = 300, float tolerancia = 0.0001) {
	max_iterations = max_iter;
	max_tolerancia = tolerancia;
	nro_clusters = clusters;
}

float distance(Punto* p1,Punto* p2){
	float x = p1->x - p2->x;
	float y = p1->y - p2->y;
	return sqrt( pow(x,2) + pow(y,2) );
}



void KMeans::_initCentroides (vector<Punto*> puntos){
	//Elegir un punto cualquiera al azar como centroide
	vector<int> iCentroidesEnPuntos;
	iCentroidesEnPuntos.push_back( rand() % puntos.size() );

	for (int t = 0; t < nro_clusters; t++){

		//Calcular las distancias de cada Punto con los centroides y quedarnos con el minimo
		vector<float> dist;
		for (int i = 0; i < (int)puntos.size() ; i++){
			float dMin = distance(puntos[i],centroides[0]);
			for (int j = 1 ; j < (int)iCentroidesEnPuntos.size() ; j ++){
				if (iCentroidesEnPuntos[j] == i){
					//El centroide es el mismo que el punto (d va a ser 0)
					continue;
				}
				float d = distance(puntos[iCentroidesEnPuntos[j]],puntos[i]);
				if (d < dMin){
					dMin = d;
				}
			}
			dist.push_back(dMin);
		}
		//Calculo las P = dist/SUM(dists)para cada punto
		float sumTotal = 0;
		for (int k = 0; k < (int)dist.size(); k++ ){
			sumTotal += dist[k];
		}
		int posMax = 0;
		float probMax = dist[0]/sumTotal;
		for (int k = 1; k < (int)dist.size(); k++ ){
				float probK = dist[k]/sumTotal;
				if (probK > probMax){
					probMax = probK;
					posMax = k;
				}
		}
		iCentroidesEnPuntos.push_back( posMax );

	}

}

float _squared_norm(vector<Punto*> a, vector<Punto*> b){
	return 0.01;
}

void KMeans::fit(vector<Punto*> puntos){
	//Asignar a cada punto el centroide mas cercano
	//Recalcular centroides

	_initCentroides(puntos);

	for (int i = 0; i < max_iterations; i++){
		/*
		//Clono los centroides (hago Back UP)
		vector<Punto*> centroides_bak = new vector(centroides);
		labels, inertia = _labels_inertia(X, x_squared_norms, centers);

		centroides = _k_means._centers_dense(puntos, labels, n_clusters, distances)

		float shift = _squared_norm(centroides_bak,centroides)
		if (shift <= max_tolerancia)
			break;
		*/
	}
}

void KMeans::viewCentroides(){
	if (centroides.size() == 0){
		printf( "No hay centroides. Intenta con fit" );
		return;
	}
	for (int x = 0; x < (int)centroides.size(); x++){
		printf( "Centroide %i = (%Lf,%Lf) \n",x+1, centroides[x]->x, centroides[x]->y);
	}
}

KMeans::~KMeans() {
	// TODO Auto-generated destructor stub
}

