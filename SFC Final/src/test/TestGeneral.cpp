#include "test.h"

void testGeneral(int cantidad_datos,int cantidad_test, int cant_centroides, bool kmeanConPuntosProcesados){
	//cantidad_datos = 0 (Todos)
	//cantidad_test = 20 (Extraidos del Train)
	//cant_centroides = 300

	cout << "\033[1;31mTest General\033[0m" << endl;
	string msg = (cantidad_datos == 0) ? "todos" : to_string(cantidad_datos);
	cout << "[INFO] Se utilizaran " << msg << " los datos del TRAIN." << endl;
	cout << "[INFO] Se testeara con " << cantidad_test << " rows del TRAIN (No seran utilizadas para entrenar)" << endl;
	cout << "[INFO] Se entrenara KMEANS con " << cant_centroides << " centroides" << endl;
	string msh_km = (kmeanConPuntosProcesados) ? "archivo que tiene los puntos procesados (elimina repetidos)" : "train";
	cout << "[INFO] Kmeans usara los puntos del " << msh_km << endl;

	printf("Cargando train (%s)...",TRAIN);

	lectorCSV* csvReader = new lectorCSV(TRAIN);
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
	KMeans* kmeans = new KMeans(cant_centroides);
	cout << OK << endl;

	cout << "Entrenamos Kmeans...";

	vector<Punto*> puntos;
	if (kmeanConPuntosProcesados){
		lectorCSV* CSVparser =  new lectorCSV(PUNTOS_PROCESADOS);
		cout << "Cargando puntos del CSV ("<< PUNTOS_PROCESADOS << ")..";
		vector<vector<string> > lineas = CSVparser->devolverLineas();
		cout<< OK << endl << "Entrenamos Kmeans (" << lineas.size() << " puntos)...";

		for (int i = 1; i < (int)lineas.size(); i++ ){
			long double x = stold( lineas[i][0] );
			long double y = stold( lineas[i][1] );
			puntos.push_back( new Punto{x,y} );
		}
	} else {
		for (int i = 1; i < (int)train.size(); i++ ){
			long double x = stold( train[i][POS_X] );
			long double y = stold( train[i][POS_Y] );
			puntos.push_back( new Punto{x,y} );
		}
	}
	cout << endl ;kmeans->activarDebug();cout << endl ;
	kmeans->fit(puntos);
	cout << OK << endl;

	cout << "Creamos el procesador de features...";
	features* ft = new features(kmeans);
	cout << OK << endl;

	cout << "Procesando features [TRANSFORM]...";
	vector<vector<long double> > train_procesado = ft->transformFeature(train_red);
	cout << OK << endl;

	cout << "Procesando features [CATEGORIAS]...";
	vector<int> categorias = ft->transform_categories(train_red);
	cout << OK << endl;

	cout << "Procesando features [TEST]...";
	vector<vector<long double> > test_procesado = ft->transformFeature(test,false);
	cout << OK << endl;

	cout << "Entrenando clasificador...";
	clf->fit(train_procesado,categorias);
	cout << OK << endl;

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
			//Estaria para poner aca las probabilidaes
			error++;
		}
	}
	cout << endl << "Efectividad: %" << ok*100.0/(int)test.size() << endl;


	/* Todavia no me importa la memoria
	delete[] train_red;
	delete[] test;
	delete clf;
	delete[] puntos;
	delete kmeans;
	delete ft;
	delete[] test_procesado;
	delete[] categorias;
	delete[] train_procesado;
	delete[] resultado;
	delete[] test_categorias;
	delete CSVparser;
	delete csvReader;
	*/
}
