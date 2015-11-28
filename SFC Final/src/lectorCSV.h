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
typedef tokenizer<escaped_list_separator<char> > Tokenizador;
typedef tokenizer<char_separator<char> > Tokenizadorfecha;

class lectorCSV {
public:
	lectorCSV(string nombrearchivo);
	virtual ~lectorCSV();

	string devolverNombreArchivo();
	vector<vector<string>> devolverLineas();
	void levantarArchivo();
	void generarArchivoCSV(vector<vector<long double>> vector_probas);
	vector<string> devolverHeader();
	vector<int> procesarFecha(string fechaParaProcesar);
	void separarHeader();
private:
	string nombrearch;
	ifstream archivocsv;
	vector<string> headerCSV;
	vector<vector<string>> listaADevolver;
};

#endif /* LECTORCSV_H_ */
