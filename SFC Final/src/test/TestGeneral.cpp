#include "test.h"

void testGeneral(int cantidad_datos,int cantidad_test, int cant_centroides){
	//cantidad_datos = 0 (Todos)
	//cantidad_test = 20 (Extraidos del Train)
	//cant_centroides = 300

	cout << "\033[1;31mTest General\033[0m" << endl;

	printf("Cargando train (%s)...",TRAIN);

	lectorCSV* csvReader = new lectorCSV("datos/train_FIX.csv");
	vector< vector<string> > train = csvReader->devolverLineas();
	if (!train.size()){
		cout << "Error: No se pudieron cargar datos" << endl;
		return;
	}
	cout << OK << endl;



	//Pongo el 1 para sacar el header
	vector< vector<string> >::const_iterator first = train.begin() + 1;
	vector< vector<string> >::const_iterator last;
	if (cantidad_datos){
		cout << "[INFO] Reducimos el Train | tomaremos " << cantidad_datos << " datos (continuo) y " << cantidad_test << " test (random)" << endl;
		last = train.begin() + cantidad_datos;
	} else {
		cout << "[INFO] Se utilizaran todos los rows del train (menos los " << cantidad_test << " utilizados para test)" << endl;
		last = train.end();
	}
	vector< vector<string> > train_red(first, last);



	cout << "Generamos tests con rows del train (posiciones randoms)...";
	vector< vector<string> > test;
	for (int job = 0; job < cantidad_test; job++ ){
		int random = rand() % train.size();
		//printf("	test nro %d -> train[%d]\n",job,random);
		//Agrego el row random del train al test
		test.push_back( train[random] );
		//Extraigo la posicion random del train
		train.erase( train.begin() + random );

	}
	cout << OK << endl;

	int cantidad_de_categorias = 39;

	cout << "Creamos el clasificador....";
	GaussianNaiveBayes* clf = new GaussianNaiveBayes(cantidad_de_categorias);
	cout << OK << endl;

	cout << "Creamos Kmeans...";
	KMeans* kmeans = new KMeans(cant_centroides);//cant_centroides);
	cout << OK << endl;

	cout << "Entrenamos Kmeans...";
	/* Estaria bueno usar puntos.csv (ya estan filtrado los puntos que se repiten) */
	vector<Punto*> puntos;
	for (size_t i = 0; i < train_red.size(); i++ ){
		long double x = stold( train_red[i][POS_X] );
		long double y = stold( train_red[i][POS_Y] );
		puntos.push_back( new Punto{x,y} );
	}
	cout << endl ;kmeans->activarDebug();cout << endl ;
	kmeans->fit(puntos);
	for (size_t i = 0; i < puntos.size(); i++ ){
		delete puntos[i];
	}
	puntos.clear();
	cout << OK << endl;

	cout << "Creamos el procesador de features...";
	features* ft = new features(kmeans);
	cout << OK << endl;

	cout << "Procesando features [TRANSFORM]...";
	vector<vector<long double> > train_procesado = ft->transform_feacture(train_red);
	cout << OK << endl;

	cout << "Procesando features [CATEGORIAS]...";
	vector<int> categorias = ft->transform_categories(train_red);
	cout << OK << endl;

	cout << "Procesando features [TEST]...";
	vector<vector<long double> > test_procesado = ft->transform_feacture(test);
	cout << OK << endl;

	cout << "Entrenando clasificador...";
	clf->fit(train_procesado,categorias);
	cout << OK << endl;

	/*
	cout << "Prediciendo los test...";
	vector<int> resultado;
	for (size_t i = 0; i < test_procesado.size();i++){
		resultado.push_back(clf->predict_category(test_procesado[i]));
	}
	cout << OK << endl;

	vector<int> test_categorias = ft->transform_categories(test);
	int ok = 0;
	int error = 0;
	for (size_t i = 0; i < resultado.size();i++){
		if(test_categorias[i] == resultado[i])
			ok++;
		else {
			error++;


		}
	}
	*/

	cout << "Prediciendo los test...";
	vector<vector<long double> > resultado;
	for (size_t i = 0; i < test_procesado.size();i++){
		resultado.push_back(clf->predict(test_procesado[i]));
	}
	cout << OK << endl;

	vector<int> test_categorias = ft->transform_categories(test);
	int ok = 0;
	int error = 0;
	for (size_t i = 0; i < resultado.size();i++){
		int prediccion = - 1;
		long double max = 0;
		vector<long double> resultados_i = resultado[i];
		for (size_t j = 0;j < resultados_i.size();j++){
			if (resultados_i[j] > max){
				max = resultados_i[j];
				prediccion = (int)j;
			}
		}
		if(test_categorias[i] == prediccion)
			ok++;
		else {
			error++;
			cout << "Categoria correcta: " << test_categorias[i] << endl;
			cout << "Categoria predecida: " << prediccion << endl;
			for (size_t j = 0;j < resultado[i].size();j++){
				cout << " cat: " << j << " | pred: " << resultado[i][j] << " ";
			}
			cout << endl;
		}
	}

	cout << endl << "Efectividad: %" << ok*100.0/(int)test.size() << endl;

	/* Todavia no me importa la memoria
	for(size_t i = 0;i < puntos.size(); i++){
		delete puntos[i];
	}


	delete train_red;
	delete test;
	delete clf;
	delete puntos;
	delete kmeans;
	delete ft;
	delete test_procesado;
	delete categorias;
	delete train_procesado;
	delete resultado;
	delete test_categorias;
	delete CSVparser;
	*/
}
