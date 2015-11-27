/*
 * KMeans.cpp
 *
 *  Created on: 25 de nov. de 2015
 *      Author: tomi
 */

#include "KMeans.h"

KMeans::KMeans(int clusters ,int max_iter, float tolerancia) {
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

	int random = rand() % puntos.size();
	iCentroidesEnPuntos.push_back( random );
	Punto* pRandom = new Punto{puntos[random]->x,puntos[random]->y};
	centroides.push_back( pRandom );

	for (int t = 0; t < nro_clusters - 1; t++){

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
					if ( find(iCentroidesEnPuntos.begin(),iCentroidesEnPuntos.end(),k) == iCentroidesEnPuntos.end() ){
						//Es max y ya no es centroide
						probMax = probK;
						posMax = k;
					}
				}
		}
		iCentroidesEnPuntos.push_back( posMax );

		//Aca puedo elegir el max prob el uno random
		Punto* pMaxProb = new Punto{puntos[posMax]->x,puntos[posMax]->y};
		centroides.push_back( pMaxProb );

	}

}

float _squared_norm(vector<Punto*> a, vector<Punto*> b){
	float maxD = distance(a[0],b[0]);
	for (size_t i = 0; i < a.size(); i++){
		float d = distance(a[i],b[i]);
		if (d > maxD)
			maxD = d;
	}
	return maxD;
}

int KMeans::_centroideMasCercano(Punto* punto){
	float minD = distance(centroides[0],punto);
	int cent =  0;
	for (size_t i = 0; i < centroides.size() ; i++){
		float d = distance(centroides[i],punto);
		if (d < minD){
			minD = d;
			cent = i;
		}
	}
	return (int)cent;
}

void KMeans::_recalcularCentroides(vector<Punto*> puntos){
	vector<int> centDePunto;
	for (int i = 0; i < (int)puntos.size(); i++){
		centDePunto.push_back( _centroideMasCercano(puntos[i]) );
	}

	for (int i = 0; i < (int)centroides.size(); i++){
		//Si se cuenta el centroide para el promedio  empieza en 1
		int cantidad = 1;
		float sumX = centroides[i]->x;
		float sumY = centroides[i]->y;

		for (int j = 0; j < (int)centDePunto.size(); j++){
			//Centroide i => el Punto j esta en el cluster i
			if (centDePunto[j] == i){
				sumX += puntos[j]->x;
				sumY += puntos[j]->y;
				cantidad++;
			}

		}

		//Nueva pos del centroide
		centroides[i]->x = sumX/cantidad;
		centroides[i]->y = sumY/cantidad;

	}

}

void KMeans::fit(vector<Punto*> puntos){

	_initCentroides(puntos);


	for (int i = 0; i < max_iterations; i++){
		//Clono los centroides (hago Back UP)

		vector<Punto*> centroides_bak;

		for (int x = 0; x < (int)centroides.size(); x++){
			Punto* p = new Punto{centroides[x]->x, centroides[x]->y};
			centroides_bak.push_back(p);
		}

		_recalcularCentroides(puntos);


		float shift = _squared_norm(centroides_bak,centroides);
		if (shift <= max_tolerancia){
			for (int i = 0; i < (int)centroides_bak.size(); i++){
				delete centroides_bak[i];
			}
			break;
		}

		for (int i = 0; i < (int)centroides_bak.size(); i++){
			delete centroides_bak[i];
		}
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

int KMeans::predict(Punto* punto){
	return _centroideMasCercano(punto);
}

KMeans::~KMeans() {
	for (int i = 0; i < (int)centroides.size(); i++){
		delete centroides[i];
	}
	centroides.clear();
}

