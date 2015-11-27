/*
 * lectorCSV.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: xx
 */

#include "lectorCSV.h"


lectorCSV::lectorCSV(string nombrearchivo) {
		this->nombrearch = nombrearchivo;
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

vector<vector<string>> lectorCSV::devolverLineas()
{

	string linea;
	typedef tokenizer<escaped_list_separator<char> > Tokenizador; //lo que va a parsear el csv
	levantarArchivo();
	if (!this->archivocsv.is_open())
		{
		cout << "HAY QUE ABRIR EL ARCHIVO PRIMERO" << endl;
		return this->listaADevolver;
		}
	//vector<vector<string> >::iterator it = this->listaADevolver.begin();
	while (getline(this->archivocsv,linea))
	{
		cout << "ENTRE AL WHILE" << endl;

		Tokenizador tok(linea);
		vector<string> vector_token;
		for(Tokenizador::iterator tok_it = tok.begin();tok_it != tok.end();++tok_it)
		{
			vector_token.push_back(*tok_it);
		}
		this->listaADevolver.push_back(vector_token);
	}
	return this->listaADevolver;
}

void lectorCSV::separarHeader(){
	if (!this->headerCSV.empty()){
		cout << "Ya separaste el header lince" << endl;
		return;
	this->headerCSV = this->listaADevolver[0];
	this->listaADevolver.erase(this->listaADevolver.begin());
	}

}
vector<string> lectorCSV::devolverHeader(){
	return this->headerCSV;
}

lectorCSV::~lectorCSV() {
	this->archivocsv.close();
	this->listaADevolver.clear();
}

