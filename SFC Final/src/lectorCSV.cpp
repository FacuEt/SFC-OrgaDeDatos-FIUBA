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
	 //lo que va a parsear el csv
	levantarArchivo();
	if (!this->archivocsv.is_open())
		{
		cout << "HAY QUE ABRIR EL ARCHIVO PRIMERO" << endl;
		return this->listaADevolver;
		}
	//vector<vector<string> >::iterator it = this->listaADevolver.begin();
	while (getline(this->archivocsv,linea))
	{
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

vector<int> lectorCSV::procesarFecha(string fechaParaProcesar){
	vector<int> fechaProcesada;
	//1er parametro dice que se suprime. 2do parametro los char que muestra
	//3er parametro si muestro o no casos en donde aparece por ej ,, eso tiraria
	//un str vacio
	char_separator<char> sep{" "};
	char_separator<char> sep_primer{"-"};
	char_separator<char> sep_segundo{":"};
	Tokenizadorfecha tok{fechaParaProcesar,sep};
	vector<string> fechaTrabajada;
	vector<string> fechaParseada; //2015-11-27 15:38:27
	string primeraParte; //2015-11-27
	string segundaParte; // 15:38:27
	for (const auto &t : tok){
		fechaParseada.push_back(t);
	}
	vector<string>::iterator it = fechaParseada.begin();
	primeraParte = *it;
	++it;
	segundaParte = *it;
	Tokenizadorfecha tok2{primeraParte,sep_primer};
	for (const auto &t : tok2){
		fechaTrabajada.push_back(t); // 2015 , 11 , 27
	}
	Tokenizadorfecha tok3{segundaParte,sep_segundo};
	for (const auto &t : tok3){
		fechaTrabajada.push_back(t); // 2015 , 11 , 27 , 15 , 38 , 27
	}

	for (int i = 0; i < 4; i++){
		fechaProcesada.push_back(atoi(fechaTrabajada[i].c_str()));
	}
	return fechaProcesada;
}

void lectorCSV::generarArchivoCSV(vector<vector<long double>> vector_probas){
	//Para correr este metodo tenes que tener una instancia de lectorCSV entonces el nombre se lo pasamaos cuando creamos la isntancia

	string headerDelArchivo = "Id,ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS";
	ofstream outputFile;
	string lineaDeArchivo;
	outputFile.open(nombrearch.c_str());
	outputFile << headerDelArchivo << endl;
	for (size_t i = 0; i < vector_probas.size();i++){
		lineaDeArchivo = to_string(i) + ",";
		for (size_t j = 0; j< vector_probas[i].size();j++){
				lineaDeArchivo += to_string(vector_probas[i][j]);
				if (j < (vector_probas[i].size()-1)) lineaDeArchivo += ",";
		}
		outputFile << lineaDeArchivo << endl;
	}
	outputFile.close();
}
vector<string> lectorCSV::procesarAddressEnString(string addressAProcesar){

	char_separator<char> sepBlock{" "};
	char_separator<char> sepCorner{"/"};
	Tokenizadorfecha tokenizadorCalle{addressAProcesar,sepBlock};
	Tokenizadorfecha tokenizadorCorner{addressAProcesar,sepCorner};
	string calle1,calle2;
	vector<string> addressParaDevolver;
	size_t of = addressAProcesar.find(" of ");
		if (of != string::npos){ //es una sola calle con altura
			Tokenizadorfecha::iterator it = tokenizadorCalle.begin(); //esto me indicaria toda la bola del num y eso
			++it; // ahora estoy parado en el nombre propiamente dicho
			++it;
			++it;
			addressParaDevolver.push_back(*it);
			++it;
			addressParaDevolver[0] += *it;
			}
		else{ //calle1 / calle 2
			for (const auto &t : tokenizadorCorner){
				string a = t.c_str();
				erase_all(a," ");
				addressParaDevolver.push_back(a); //addressParaDevolver[0]=calle1,addressParaDevolver[1]= calle2
			}
		}
	return addressParaDevolver;
	}

lectorCSV::~lectorCSV()
{
	this->archivocsv.close();
	this->listaADevolver.clear();
}

