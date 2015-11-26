/*
 * lectorCSV.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: xx
 */

#include "lectorCSV.h"
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

lectorCSV::lectorCSV(std::string nombrearchivo) {
		this->nombrearch = nombrearchivo;
		this->archivo = NULL;
		this->headerCSV = NULL;
		this->listaADevolver = NULL;

}
ifstream lectorCSV::darArchivoAbierto()
{

	if (!this->archivo.is_open()) return 1; //pifiaste maquinola
	return archivo;
}

void lectorCSV::levantarArchivo()
{
	this->archivo(this->nombrearch.c_str());
	if (!this->archivo.is_open()){
		cout << "ERROR AL CARGAR EL CSV" << endl;
	}
}

list<string> lectorCSV::devolverLineas()
{
	string linea;
	typedef tokenizer<escaped_list_separator<char> > Tokenizador; //lo que va a parsear el csv

	if (!this->archivo == NULL || !this->archivo.is_open())
		{
		cout << "HAY QUE ABRIR EL ARCHIVO PRIMERO" << endl;
		return 1; //dale boludo, abri el archivo primero
		}
	while (getline(this->archivo,linea))
	{
		Tokenizador tok(linea);
		this->listaADevolver.assign(tok.begin(),tok.end());
	}
	return this->listaADevolver;
}

void lectorCSV::separarHeader(){
	if (!this->headerCSV == NULL){
		cout << "Ya separaste el header lince" << endl;
		return;
	}
	this->headerCSV = this->listaADevolver.pop_front();
}
string lectorCSV::devolverHeader(){
	return this->headerCSV;
}

lectorCSV::~lectorCSV() {
	this->archivo.close();
	this->listaADevolver.clear();
}

