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
#include <time.h>

#include "../lectorCSV.h"
#include "../GaussianNaiveBayes.h"
#include "../features.h"
#include "../KMeans.h"

using namespace std;

#define TRAIN "datos/train_FIX.csv"
#define TEST "datos/test.csv"
#define OK "\033[1;32mOK\033[0m"
#define PUNTOS_PROCESADOS "datos/puntos.csv"


void testNaiveBayes();
void testKMeans();
void testParser();
void testGeneral(int cantidad_datos = 0,int cantidad_test = 20, int cant_centroides = 20, bool kmeansConPuntosProcesados = true);
void testPerceptron();

#endif /* TESTNAIVEBAYES_H_ */

