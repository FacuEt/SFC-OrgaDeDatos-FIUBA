/*
 * lectorCSV.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: xx
 */

#include "lectorCSV.h"


lectorCSV::lectorCSV(string nombrearchivo) {
		this->nombrearch = nombrearchivo;
		this->headerCSV = string();
}

void lectorCSV::levantarArchivo()
{
	this->archivocsv.open(this->nombrearch.c_str(),ifstream::in);
	if (!this->archivocsv.is_open()){
		cout << "ERROR AL CARGAR EL CSV" << endl;
	}
}

string lectorCSV::devolverNombreArchivo()
{
	return this->nombrearch;
}

list<string> lectorCSV::devolverLineas()
{
	string linea;
	typedef tokenizer<escaped_list_separator<char> > Tokenizador; //lo que va a parsear el csv
	levantarArchivo();
	if (!this->archivocsv.is_open())
		{
		cout << "HAY QUE ABRIR EL ARCHIVO PRIMERO" << endl;
		return this->listaADevolver;
		}
	while (getline(this->archivocsv,linea))
	{
		Tokenizador tok(linea);
		this->listaADevolver.assign(tok.begin(),tok.end());
	}
	return this->listaADevolver;
}

void lectorCSV::separarHeader(){
	if (!this->headerCSV.empty()){
		cout << "Ya separaste el header lince" << endl;
		return;
	}

}
string lectorCSV::devolverHeader(){
	return this->headerCSV;
}

lectorCSV::~lectorCSV() {
	this->archivocsv.close();
	this->listaADevolver.clear();
}

