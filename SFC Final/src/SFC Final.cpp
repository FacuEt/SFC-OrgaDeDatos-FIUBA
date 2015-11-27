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
	testGeneral();
	/*
	cout << "leemos el train..  " ;
	lectorCSV CSVparser("puntos.csv");
	vector< vector<string> > train = CSVparser.devolverLineas();
	cout << "OK.." << endl;

	int cantidad_de_categorias = 32;

	cout << "Creamos el clasificador... ";
	GaussianNaiveBayes* clf = new GaussianNaiveBayes(cantidad_de_categorias);
	cout << " OK.." << endl;

	cout << "Creamos Kmeans..";
	KMeans* kmeans = new KMeans(CANT_CENTROIDES);
	cout << "  OK.." << endl;

	cout << "Entrenamos Kmeans..";
	vector<Punto*> puntos;
	for (size_t i = 0; i < train.size(); i++ ){
		long double x = stold( train[i][POS_X] );
		long double y = stold( train[i][POS_Y] );
		puntos.push_back( new Punto{x,y} );
	}
	kmeans->fit(puntos);
	cout << "  OK.." << endl;

	cout << "Creamos el procesador de features..";
	features * ft = new features(kmeans);
	cout << "  OK.." << endl;

	cout << "procesando features..";
	vector<vector<long double> > train_procesado = ft->transform_feacture(train);
	vector<int> categorias = ft->transform_categories(train);
	cout << "  OK.." << endl;

	cout << "Entrenando clasificador..";
	clf->fit(train_procesado,categorias);
	cout << "  OK.." << endl;


	cout << "leemos el test..  " ;
	lectorCSV CSVparser2("test.csv");
	vector< vector<string> > test = CSVparser2.devolverLineas();
	cout << "OK.." << endl;

	cout << "procesando test..";
	vector<vector<long double> > test_procesado = ft->transform_feacture(test,true);
	cout << "OK.." << endl;

	cout << "Prediciendo los test..";
	vector<int> resultado;
	for (size_t i = 0; i < test_procesado.size();i++){
		resultado.push_back(clf->predict_category(test_procesado[i]));
	}
	cout << "  OK.." << endl;

	cout << "Generando submission.csv ...." << endl;

	cout << endl << "OK....!" << endl << " FinishHim ...." << endl;
	*/
}

