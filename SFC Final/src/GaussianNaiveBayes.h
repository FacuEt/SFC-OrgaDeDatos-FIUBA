/*
 * GaussianNaiveBayes.h
 *
 *  Created on: 25/11/2015
 *      Author: facu
 */

#ifndef GAUSSIANNAIVEBAYES_H_
#define GAUSSIANNAIVEBAYES_H_
#include <vector>
#include <cmath>

namespace std {

class GaussianNaiveBayes {
private:
	long double evidencia;
	int cant_feactures;
	int cant_categories;
	vector< vector<long double> > media;
	vector< vector<long double> > varianza;
	vector<long double> prob_por_categoria;
	vector<int> cant_por_categoria;

	long double _calculoGaussiano(int categoria, int feacture);

public:
	GaussianNaiveBayes(int cant_de_categorias);
	bool fit(vector< vector<long double> > X,vector<int> Y);
	vector<long double> predict(vector<long double> X);
	long double predict_feacture(vector<long double> X);
	virtual ~GaussianNaiveBayes();
};

} /* namespace std */

#endif /* GAUSSIANNAIVEBAYES_H_ */
