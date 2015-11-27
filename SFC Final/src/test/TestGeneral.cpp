#include "test.h"

void testGeneral(int cantidad_datos,int cantidad_test, int cant_centroides){

	//leemos el train
	cout << "leemos el train..  " ;
	lectorCSV CSVparser("puntos.csv");
	vector< vector<string> > train = CSVparser.devolverLineas();
	cout << "OK.." << endl;

	cout << "reducimos el train.. tomaremos " << cantidad_datos << " datos y " << cantidad_test << " test..  ";
	vector< vector<string> >::const_iterator first = train.begin();
	vector< vector<string> >::const_iterator last = train.begin() + cantidad_datos;
	vector< vector<string> > train_red(first, last);
	cout << " OK.." << endl;

	cout << " Generamos los test del train...";
	int random = rand() % train.size();
	vector< vector<string> >::const_iterator first_t = train.begin() + random;
	vector< vector<string> >::const_iterator last_t = train.begin() + random + cantidad_test;
	vector< vector<string> > test(first_t, last_t);
	cout << " OK.." << endl;

	int cantidad_de_categorias = 32;

	cout << "Creamos el clasificador... ";
	GaussianNaiveBayes* clf = new GaussianNaiveBayes(cantidad_de_categorias);
	cout << " OK.." << endl;

	cout << "Creamos Kmeans..";
	KMeans* kmeans = new KMeans(cant_centroides);
	cout << "  OK.." << endl;

	cout << "Entrenamos Kmeans..";
	vector<Punto*> puntos;
	for (size_t i = 0; i < train_red.size(); i++ ){
		long double x = stold( train_red[i][POS_X] );
		long double y = stold( train_red[i][POS_Y] );
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
	vector<vector<long double> > test_procesado = ft->transform_feacture(test,false);
	cout << "  OK.." << endl;

	cout << "Entrenando clasificador..";
	clf->fit(train_procesado,categorias);
	cout << "  OK.." << endl;

	cout << "Prediciendo los test..";
	vector<int> resultado;
	for (size_t i = 0; i < test_procesado.size();i++){
		resultado.push_back(clf->predict_category(test_procesado[i]));
	}
	cout << "  OK.." << endl;

	cout << "Calculando efectividad...." << endl;
	vector<int> test_categorias = ft->transform_categories(test);
	int ok,error = 0;
	for (size_t i = 0; i < resultado.size();i++){
		if(test_categorias[i] == resultado[i])
			ok++;
		else error++;
	}

	cout << endl << "Efectividad: %" << ok*100.0/cantidad_test << " ...." << endl;
}
