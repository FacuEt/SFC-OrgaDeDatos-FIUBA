#include "test.h"

void testParser(){


	lectorCSV CSVparser("pruebaparser.csv");
	vector<vector<string>> prueba;
	cout << CSVparser.devolverNombreArchivo() << endl;
	prueba = CSVparser.devolverLineas();
	cout << prueba.size() << endl;
}
