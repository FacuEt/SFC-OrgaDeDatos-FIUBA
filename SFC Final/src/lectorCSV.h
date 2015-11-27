/*
 * lectorCSV.h
 *
 *  Created on: Nov 25, 2015
 *      Author: xx
 */

#ifndef LECTORCSV_H_
#define LECTORCSV_H_
#include <iostream> //cout, endl
#include <fstream> //manejo de archivo
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>

#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;

using namespace std;
class lectorCSV {
public:
	lectorCSV(string nombrearchivo);
	virtual ~lectorCSV();

	string devolverNombreArchivo();
	vector<vector<string>> devolverLineas();
	void levantarArchivo();
	vector<string> devolverHeader();
	void separarHeader();
private:
	string nombrearch;
	ifstream archivocsv;
	vector<string> headerCSV;
	vector<vector<string>> listaADevolver;
};

#endif /* LECTORCSV_H_ */
