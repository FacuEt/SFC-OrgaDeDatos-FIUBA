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


	lectorCSV* CSVparser =  new lectorCSV(PUNTOS_PROCESADOS);
	cout << "Cargando puntos del CSV (" << PUNTOS_PROCESADOS << "...";
	vector<vector<string> > lineas = CSVparser->devolverLineas();
	cout<< OK << endl << "[INFO] Entrenamos Kmeans con " << lineas.size() << " puntos...";
	vector<Punto*> puntos;
	for (int i = 1; i < (int)lineas.size(); i++ ){
		long double x = stold( lineas[i][0] );
		long double y = stold( lineas[i][1] );
		puntos.push_back( new Punto{x,y} );
	}
	//Muestre el proceso de KMeans
	cout << endl ;kmeans->activarDebug();cout << endl ;
	kmeans->fit(puntos);
	cout << OK << endl;

	cout << "Creamos el procesador de features...";
	features* ft = new features(kmeans);
	cout << OK << endl;

	cout << "Procesando features [TRANSFORM]...";
	vector<vector<long double> > train_procesado = ft->transformFeature(train);
	cout << OK << endl;

	cout << "Procesando features [CATEGORIAS]...";
	vector<int> categorias = ft->transform_categories(train);
	cout << OK << endl;

	cout << "Procesando features [TEST]...";
	vector<vector<long double> > test_procesado = ft->transformFeature(test,true);
	cout << OK << endl;

	cout << "[INFO] Tests procesados (a predecir):" << test_procesado.size() << endl;

	cout << "Entrenando clasificador...";
	clf->fit(train_procesado,categorias);
	cout << OK << endl;

	cout << "Prediciendo los test...";
	vector< vector<long double> > predicciones;
	for (size_t i = 0; i < test_procesado.size();i++){
		predicciones.push_back( clf->predict(test_procesado[i]) );
	}
	cout << OK << endl;

	cout << "Generando CSV con " << predicciones.size() + 1  <<" rows" << "...";
	lectorCSV* submission = new lectorCSV("datos/submission" + getTimeNow() + ".csv");
	submission->generarArchivoCSV(predicciones);
	cout << OK << endl;

	/* Memoria chicas, memoria */
}

void help(){
	printf("SAN FRANCISCO CRIME CLASSIFICATION\n\n");
	printf(" -general [n_cluster] [n_train] [n_test]:\n");
	printf("	Correr test de integracion y calcula efectividad\n");
	printf("		default n_cluster: 	20\n");
	printf("		default n_datos: 	0 	(Todos)\n");
	printf("		default n_test: 	20 (test extraidos del train)\n");
	printf(" -kmean: 	Correr pruebas de KMeans\n");
	printf(" -sub: 		Generar submission para Kaggle\n");
	printf(" -bayes: 	Correr pruebas de Naive Bayes\n");
	printf(" -help: 	Mostrar ayudas\n");
	printf(" -parser: 	Correr pruebas de Parser CSV\n");
	printf("\nDEFAULT (Sin parametros) -> Correr test de integracion (configuracion default) y calcular efectividad \n");
}

int main(int argc, char** argv) {
	//Si no hay comandos se corre la prueba general
	if (argc == 1){
		testGeneral(0,20,20,true);
		return 0;
	}


	string parametro = string(argv[1]);
	if (parametro == "-sub"){
		generarSubmission();
	} else if (parametro == "-kmean"){
		testKMeans();
	} else if (parametro == "-bayes"){
		testNaiveBayes();
	} else if (parametro == "-parser"){
		testParser();
	} else if (parametro == "-percep"){
		testPerceptron();
	} else if (parametro == "-help"){
		help();
	} else if (parametro == "-general"){
		int cantidadDeCluster = (argc > 1) ? stoi( string(argv[2]) ) : 20;
		int cantidadDeDatos = (argc > 2) ? stoi( string(argv[3]) ) : 0;
		int cantidadDeTest = (argc > 3) ? stoi( string(argv[4]) ) : 20;
		bool conPuntos = (argc > 4) ? (string(argv[5]) == "true") ? true : false : true;
		testGeneral(cantidadDeDatos,cantidadDeTest,cantidadDeCluster,conPuntos);
	} else {
		printf("****Error en parametro*** [AYUDA]:\n");
		help();
	}


	return 0;
}

