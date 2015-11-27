//============================================================================
// Name        : SFC.cpp
// Author      : FME
// Version     :
// Copyright   : 2do Cuatrimestre 2015
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "test/test.h"
#include "lectorCSV.h"

#define CANT_CENTROIDES 300

using namespace std;

int main() {
	testParser();
	/*
		//leemos el train
		lectorCSV CSVparser("train.csv");
		vector< vector<string> > train = CSVparser.devolverLineas();
		int cantidad_de_categorias = 32;

		GaussianNaiveBayes* clf = new GaussianNaiveBayes(cantidad_de_categorias);

		//creamos las feactures para entrenar

		//Entrenamos Kmeans
		Kmeans* kmeans = new Kmeans(CANT_CENTROIDES);

		//procesamos features

		features * ft = new features(kmeans);

		vector<vector<long double> > train_procesado = ft->transform_feacture(train);
		vector<int> categorias = ft->transform_categories(train);

		//entrenamos
		clf->fit(train_procesado,categorias);

		//cargamos test
		lectorCSV CSVparser("test.csv");


		//creamos las feactures para testear

		for (cada linea del test)
		 vector a guardar = clf->predict(linea_test);


		*/
}

