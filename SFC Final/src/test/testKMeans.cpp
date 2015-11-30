#include "test.h"

#define DEBUG true


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

void testConCSV(bool dePuntosProcesados){
	cout << "Prueba 2 | Prueba con datos reales" << endl;

	string FileToLoad = (dePuntosProcesados) ? PUNTOS_PROCESADOS : TRAIN;

	lectorCSV* CSVparser =  new lectorCSV(FileToLoad);
	cout << "Cargando lineas del CSV (" << FileToLoad << ")..." << endl;
	vector<vector<string> > lineas = CSVparser->devolverLineas();
	cout << "Lineas cargadas" << endl;

	vector<Punto*> puntos;

	printf("Fit de %d puntos...", (int)lineas.size());

	int columnX = (dePuntosProcesados) ? 0 : POS_X;
	int columnY = (dePuntosProcesados) ? 0 : POS_Y;

	for (int i = 1; i < (int)lineas.size(); i++ ){
		long double x = stold( lineas[i][columnX] );
		long double y = stold( lineas[i][columnY] );
		puntos.push_back( new Punto{x,y} );
	}

	KMeans* clf = new KMeans(50);

	time_t start,end;

	time (&start);

	cout << "Entrenando puntos" << endl;
	if (DEBUG)
		clf->activarDebug();

	clf->fit(puntos);

	time (&end);

	double dif = difftime (end,start);

	cout << "OK | time:" << dif << " segundos" << endl;

	cout << "Centroides Generados:" << endl;
	clf->viewCentroides();

	//delete []puntos;
	delete clf;
	delete CSVparser;

}

void testKMeans(){
	testBasicoCincoPuntos();
	cout << "Prueba KMeans guardando los puntos en map";
	testConCSV(true);


}
