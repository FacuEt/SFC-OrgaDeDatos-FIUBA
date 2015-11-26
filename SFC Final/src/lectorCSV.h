/*
 * lectorCSV.h
 *
 *  Created on: Nov 25, 2015
 *      Author: xx
 */

#ifndef LECTORCSV_H_
#define LECTORCSV_H_
#include <iostream>
#include <fstream>;

using namespace std;
class lectorCSV {
public:
	lectorCSV(std::string nombrearchivo);
	virtual ~lectorCSV();
	ifstream darArchivoAbierto();
	list<string> devolverLineas();
	void levantarArchivo();
	string devolverHeader();
	void separarHeader();
private:
	std::string nombrearch;
	ifstream archivo;
	string headerCSV;
	list<string> listaADevolver;
};

#endif /* LECTORCSV_H_ */
