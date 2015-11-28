//============================================================================
// Name        : SFC.cpp
// Author      : FME
// Version     :
// Copyright   : 2do Cuatrimestre 2015
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <ctime>
#include "test/test.h"

#define CANT_CENTROIDES 20

using namespace std;

string getTimeNow(){
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"[%d-%m-%Y %I:%M:%S]",timeinfo);
	string str(buffer);
	return str;
}

void generarSubmission(){
	cout << "\033[1;31mGenerando submission para KAGGLE\033[0m" << endl;

	printf("Cargando train (%s)...",TRAIN);

	lectorCSV* csvTrainReader = new lectorCSV(TRAIN);
	vector< vector<string> > train = csvTrainReader->devolverLineas();
	if (!train.size()){
		cout << "Error: No se pudieron cargar train" << endl;
		return;
	}
	cout << OK << endl;
	//Recordae que train[0] es el HEADER
	train.erase(train.begin());


	printf("Cargando test (%s)...",TEST);
	lectorCSV* csvTestReader = new lectorCSV(TEST);
	vector< vector<string> > test = csvTestReader->devolverLineas();
	if (!test.size()){
		cout << "Error: No se pudieron cargar test. Esta dentro de la carpeta datos?" << endl;
		return;
	}
	cout << OK << endl;
	test.erase(test.begin());
	//Recordae que test[0] es el HEADER

	int cantidad_de_categorias = 39;

	cout << "Creamos el clasificador....";
	GaussianNaiveBayes* clf = new GaussianNaiveBayes(cantidad_de_categorias);
	cout << OK << endl;

	cout << "Creamos Kmeans...";
	KMeans* kmeans = new KMeans(CANT_CENTROIDES);
	cout << OK << endl;

	cout << "Entrenamos Kmeans...";
	/* Estaria bueno usar puntos.csv (ya estan filtrado los puntos que se repiten) */
	vector<Punto*> puntos;
	for (size_t i = 0; i < train.size(); i++ ){
		long double x = stold( train[i][POS_X] );
		long double y = stold( train[i][POS_Y] );
		puntos.push_back( new Punto{x,y} );
	}
	//Muestre el proceso de KMeans
	//cout << endl ;kmeans->activarDebug();cout << endl ;
	kmeans->fit(puntos);
	cout << OK << endl;

	cout << "Creamos el procesador de features...";
	features* ft = new features(kmeans);
	cout << OK << endl;

	cout << "Procesando features [TRANSFORM]...";
	vector<vector<long double> > train_procesado = ft->transform_feacture(train);
	cout << OK << endl;

	cout << "Procesando features [CATEGORIAS]...";
	vector<int> categorias = ft->transform_categories(train);
	cout << OK << endl;

	cout << "Procesando features [TEST]...";
	vector<vector<long double> > test_procesado = ft->transform_feacture(test,true);
	cout << OK << endl;

	cout << "Entrenando clasificador...";
	clf->fit(train_procesado,categorias);
	cout << OK << endl;

	cout << "Prediciendo los test...";
	vector< vector<long double> > predicciones;
	for (size_t i = 1; i < test_procesado.size();i++){
		predicciones.push_back( clf->predict(test_procesado[i]) );
	}
	cout << OK << endl;

	cout << "Generando CSV...";
	lectorCSV* submission = new lectorCSV("datos/sumbission" + getTimeNow() + ".csv");
	submission->generarArchivoCSV(predicciones);

	/* Memoria chicas, memoria */
}

int main() {
	generarSubmission();
}

