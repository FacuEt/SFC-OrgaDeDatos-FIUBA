/*
 * GaussianNaiveBayes.cpp
 *
 *  Created on: 25/11/2015
 *      Author: facu
 */

#include "GaussianNaiveBayes.h"
#include <iostream>

namespace std {

GaussianNaiveBayes::GaussianNaiveBayes(int cant_de_categorias) {
	cant_feactures = 0;
	cant_categories = cant_de_categorias;
	evidencia = 0;
}

bool GaussianNaiveBayes::fit(vector<vector<long double> > X,vector<int> Y){
	cant_feactures = X[0].size();

	for (int i = 0;i<cant_categories;i++){
		//media.push_back(new vector<long double)>);
		//varianza.push_back(new vector<long double)>);
		media[i].push_back(0);
		varianza[i].push_back(0);
		cant_por_categoria.push_back(0);
		prob_por_categoria.push_back(0);
	}
	cout << "DEBUG...." << endl;
	//categoria tiene que ser un numero entero
	int category;
	int cant_total = 0;


	//Calculo la media y la varianza de cada categoria
	for(size_t i = 0; i < X.size() ;i++) {
		//por cada fila
		category = Y[i];
		if (category > cant_categories) cant_categories = category + 1;

		for(size_t j = 0; j < X[i].size(); j++) {
			//por cada columna

			media[category][j] = media[category][j] + X[i][j];

			varianza[category][j] = varianza[category][j] + pow(varianza[category][j],2);

		}
		cant_por_categoria[category] = cant_por_categoria[category] + 1;
		cant_total += 1;
	}

	for (int k = 0;k<cant_categories;k++){
		for (int j = 0; j<cant_feactures; j++){
			media[k][j] = media[k][j]/cant_por_categoria[k];
			varianza[k][j] = varianza[k][j]/cant_por_categoria[k] - pow(media[k][j],2);
		}
		prob_por_categoria[k] = cant_por_categoria[k]/cant_total;
	}

	//calculo evidencia
	for (int cat = 0; cat < cant_categories; cat++){
		long double aux = prob_por_categoria[cat];
		for (int ft = 0;ft < cant_feactures;ft++){
			aux *= _calculoGaussiano(cat,ft);
		}
		evidencia += aux;
	}



	///TODO: sacar esto.. solo para testear
	cout << "Media.." << endl;
	for (size_t i=0;i< media.size();i++){
		cout << "Categoria.. " << i << endl;
		for (size_t j = 0; j< media[i].size();j++){
			cout << "FT " << j << "|" << media[i][j] << endl;
		}
	}
	cout << "Variaza.." << endl;
	for (size_t i=0;i< varianza.size();i++){
		cout << "Categoria.. " << i << endl;
		for (size_t j = 0; j< varianza[i].size();j++){
			cout << "FT " << j << "|" << varianza[i][j] << endl;
		}
	}


	return true;
}


long double GaussianNaiveBayes::_calculoGaussiano(int categoria, int feacture){
	long double res = 0;

	res = (1/sqrt(2*M_PI*varianza[categoria][feacture]))*exp( -pow((6 - media[categoria][feacture] ),2)/(2*varianza[categoria][feacture]));

	return res;
}

vector<long double> GaussianNaiveBayes::predict(vector<long double>  X){
	vector<long double> resultados (cant_categories) ;

	for (int i = 0;i<cant_categories;i++){
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
	delete(&cant_feactures);
	delete( &evidencia);
	delete(&cant_categories);

	for (size_t j = 0; j < media.size(); j++){
		media[j].clear();
	}
	delete(&media);

	for (size_t j = 0; j < varianza.size(); j++){
		varianza[j].clear();
	}
	delete(&varianza);
}

} /* namespace std */
