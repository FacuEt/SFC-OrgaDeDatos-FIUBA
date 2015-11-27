#include "test.h"

void testBasicoCincoPuntos(){
	cout << "Prueba 1 | Simple con 5 puntos" << endl;
	Punto* p1 = new Punto{1,5};
	Punto* p2 = new Punto{3,2};
	Punto* p3 = new Punto{4,6};
	Punto* p4 = new Punto{10,5};
	Punto* p5 = new Punto{7,3};

	vector<Punto*> puntos {p1,p2,p3,p4,p5};

	KMeans* clf = new KMeans(2);

	clf->fit(puntos);

	clf->viewCentroides();

	for (size_t i = 0; i < puntos.size(); i++){
		cout << "P: (" << puntos[i]->x << "," << puntos[i]->y << ") \t ->";
		cout << clf->predict(puntos[i]) << endl;

		delete puntos[i];
	}
	puntos.clear();
	delete clf;
}

void testConCSV(){
	cout << "Prueba 2 | Prueba con datos reales" << endl;

	lectorCSV* CSVparser =  new lectorCSV("datos/puntos.csv");
	cout << "Cargando lineas del CSV" << endl;
	vector<vector<string> > lineas = CSVparser->devolverLineas();
	cout << "Lineas cargadas" << endl;

	vector<Punto*> puntos;

	printf("fit de %d puntos (puntos.csv)\n", (int)lineas.size());
	printf("Ejemplo lineaCargadas ");
	cout << lineas[0][0] << ", " << lineas[0][1] << endl;
	for (int i = 0; i < (int)lineas.size(); i++ ){
		long double x = stold( lineas[i][0] );
		long double y = stold( lineas[i][1] );
		puntos.push_back( new Punto{x,y} );
	}

	KMeans* clf = new KMeans(100);

	cout << "Entrenando puntos" << endl;
	clf->fit(puntos);
	cout << "Entrenado..." << endl;


	clf->viewCentroides();

	for (size_t i = 0; i < puntos.size(); i++){
		delete puntos[i];
	}
	puntos.clear();
	delete clf;
	delete CSVparser;

}

void testKMeans(){
	testBasicoCincoPuntos();
	testConCSV();


}
