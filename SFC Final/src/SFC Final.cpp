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

using namespace std;

int main() {
	lectorCSV CSVparser("pruebaparser.csv");
	list<string> prueba;
	cout << CSVparser.devolverNombreArchivo() << endl;
	prueba = CSVparser.devolverLineas();
	for (list<string>::iterator it = prueba.begin(); it != prueba.end();++it)
	{
		cout << *it << endl;
	}
	return 0;
}

