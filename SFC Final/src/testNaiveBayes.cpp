#include "GaussianNaiveBayes.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

	cout << "SFC FME" << endl;

	GaussianNaiveBayes* clf = new GaussianNaiveBayes(2);

	// https://es.wikipedia.org/wiki/Clasificador_bayesiano_ingenuo#Ejemplo
	enum Categorias {Hombre, Mujer};

	vector<vector<long double> > train;
	train.push_back(vector<long double> {6.0,180.0,12.0});
	train.push_back(vector<long double> {5.92,190.0,11.0});
	train.push_back(vector<long double> {5.58,170.0,12.0});
	train.push_back(vector<long double> {5.92,165.0,10.0});
	train.push_back(vector<long double> {5.0,100.0,6.0});
	train.push_back(vector<long double> {5.5,150.0,8.0});
	train.push_back(vector<long double> {5.42,130.0,7.0});
	train.push_back(vector<long double> {5.75,150.0,9.0});

	vector<int> Y;
	Y.push_back(Hombre);
	Y.push_back(Hombre);
	Y.push_back(Hombre);
	Y.push_back(Hombre);
	Y.push_back(Mujer);
	Y.push_back(Mujer);
	Y.push_back(Mujer);
	Y.push_back(Mujer);

	cout << "Entrenar...." << endl;
	clf->fit(train,Y);



	return 0;
}
