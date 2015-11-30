/*
 * Perceptron.h
 *
 *  Created on: Nov 29, 2015
 *      Author: xx
 */

#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_
#include <vector>
#include <iostream>
#include <map>
#include <random>
#include <string>
using namespace std;

class Perceptron {
public:
	Perceptron(vector<vector<string>> set_train,vector<vector<string> > set_features);
	//void generarVectorPesos(int cant_cat);
	void generarMapeoDeDatos();
	void generarIndexesDeFeatures();
	void entrenarPerceptron();
	string emitirCategoria(vector<string> test_a_clasificar);
	int productoInterno(); //porque devuelvo el indice del vector de peso que elegi como maximo
	void updatePesos(string category, vector<string> address);
	void resetearProductosInternos();
	virtual ~Perceptron();

private:
	vector<vector<string>> train;
	vector<map<string,long double> > pesos;
	map<string,int> categorias;
	vector<long double> prod_internos;
	vector<string> crime_cat;
	map<string,int> idx_calles;
};

#endif /* PERCEPTRON_H_ */
