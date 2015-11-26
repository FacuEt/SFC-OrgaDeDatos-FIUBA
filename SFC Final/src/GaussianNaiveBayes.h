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
	int cant_feactures;
	int cant_categories;
	vector< vector<long double> > media;
	vector< vector<long double> > varianza;
	vector<long double> prob_por_categoria;
	vector<int> cant_por_categoria;

	long double _calculoGaussiano(int categoria, int feacture, long double new_ft);

public:
	GaussianNaiveBayes(int cant_de_categorias);
	bool fit(vector< vector<long double> > X,vector<int> Y);
	vector<long double> predict(vector<long double> X);
	int predict_feacture(vector<long double> X);
	virtual ~GaussianNaiveBayes();
};

} /* namespace std */

#endif /* GAUSSIANNAIVEBAYES_H_ */
