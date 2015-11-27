/*
 * testNaiveBayes.h
 *
 *  Created on: 26 de nov. de 2015
 *      Author: tomi
 */

#ifndef TESTNAIVEBAYES_H_
#define TESTNAIVEBAYES_H_



#include <iostream>
#include <vector>
#include <string>
#include "../lectorCSV.h"
#include "../GaussianNaiveBayes.h"
#include "../features.h"
#include "../KMeans.h"
using namespace std;

void testNaiveBayes();
void testKMeans();
void testParser();
void testGeneral(int cantidad_datos = 0,int cantidad_test = 0, int cant_centroides = 300);

#endif /* TESTNAIVEBAYES_H_ */

