/*
 * GaussianNaiveBayes.cpp
 *
 *  Created on: 25/11/2015
 *      Author: facu
 */

#include "GaussianNaiveBayes.h"

namespace std {

GaussianNaiveBayes::GaussianNaiveBayes(int cant_de_categorias) {
	cant_feactures = 0;
	cant_categories = cant_de_categorias;
	evidencia = 0;
}

bool GaussianNaiveBayes::fit(vector<vector*> X,vector<int>Y){
	cant_feactures = X[0]->size();

	for (int i = 0;i<=cant_categories;i++){
		media[i].push_back(0);
		varianza[i].push_back(0);
		cant_por_categoria.push_back(0);
		prob_por_categoria.push_back(0);
	}

	//categoria tiene que ser un numero entero
	int category;
	int cant_total = 0;


	//Calculo la media y la varianza de cada categoria
	for(size_t i = 0; i != (sizeof X / sizeof *X); i++) {
		//por cada fila
		category = Y[i];
		if (category > cant_categories) cant_categories = category;

		for(size_t j = 0; j != (sizeof X[i] / sizeof *X[i]); j++) {
			//por cada columna

			media[category][j] = media[category][j] + X[i][j];

			varianza[category][j] = varianza[category][j] + pow(varianza[category][j],2);

		}
		cant_por_categoria[category] = cant_por_categoria[category] + 1;
		cant_total += 1;
	}

	for (int k = 0;k<=cant_categories;k++){
		for (int j = 0; j<cant_feactures; j++){
			media[k][j] = media[k][j]/cant_por_categoria[k];
			varianza[k][j] = varianza[k][j]/cant_por_categoria[k] - pow(media[k][j],2);
		}
		prob_por_categoria[k] = cant_por_categoria[k]/cant_total;
	}

	//calculo evidencia
	for (int cat = 0; cat <= cant_categories; cat++){
		long double aux = prob_por_categoria[cat];
		for (int ft = 0;ft < cant_feactures;ft++){
			aux *= _calculoGaussiano(cat,ft);
		}
		evidencia += aux;
	}

	return true;
}


long double GaussianNaiveBayes::_calculoGaussiano(int categoria, int feacture){
	long double res = 0;

	res = (1/sqrt(2*M_PI*varianza[categoria][feacture]))*exp( -pow((6 - media[categoria][feacture] ),2)/(2*varianza[categoria][feacture]));

	return res;
}

vector<long double> GaussianNaiveBayes::predict(vector<vector*> X){
	vector<long double> resultados;

	for (int i = 0;i<=cant_categories;i++){
		long double prob = prob_por_categoria[i];

		for (int ft = 0; ft < cant_feactures;ft++){
			prob*=_calculoGaussiano(i,ft);
		}

		prob = prob/evidencia;

		resultados.push_back(prob);
	}

	return resultados;
}

GaussianNaiveBayes::~GaussianNaiveBayes() {
	delete(cant_feactures);
	delete( evidencia);
	delete(cant_categories);
	vector<vector<long double>> media;
	vector<vector<long double>> varianza;
	vector<long double> prob_por_categoria;
	vector<int> cant_por_categoria;
}

} /* namespace std */
