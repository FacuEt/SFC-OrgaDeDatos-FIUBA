#include "test.h"
#include "../lectorCSV.h"
void testParser(){

	vector<vector<string> > X;
	vector<string> linea {"2003-01-07 07:52:00","WARRANTS","WARRANTS ARREST","Tuesday","NORTHERN","ARREST, BOOKED", "AV CACHACAY 1942","-122.1241243534","37.1235671823"};
	X.push_back(linea);

	features* ft = new features(NULL);
	vector<vector<long double> > feat = ft->transformFeature(X);
	vector<int> cat = ft->transform_categories(X);

	for(size_t i = 0;i < feat[0].size();i++){
		cout << feat[0][i] << endl;
	}

	/*
	lectorCSV CSVparser("pruebaparser.csv");
	vector<vector<string>> prueba;
	cout << CSVparser.devolverNombreArchivo() << endl;
	prueba = CSVparser.devolverLineas();
	cout << prueba.size() << endl;
	*/
}
