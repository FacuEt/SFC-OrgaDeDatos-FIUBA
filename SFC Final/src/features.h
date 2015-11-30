/*
 * features.h
 *
 *  Created on: 27/11/2015
 *      Author: facu
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#include <map>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <boost/tokenizer.hpp>
#include "KMeans.h"

//train
#define POS_DATE 0
#define POS_CATEGORIA 1
#define POS_DESCRIPT 2
#define POS_DAYOFWEEK 3
#define POS_DISTRICT 4
#define POS_RESOLUTION 5
#define POS_ADRESS 6
#define POS_X 7
#define POS_Y 8

//Test
#define POS_tID 0
#define POS_tDATE 1
#define POS_tDAYOFWEEK 2
#define POS_tDISTRICT 3
#define POS_tADRESS 4
#define POS_tX 5
#define POS_tY 6

#define NOCHE_INICIO 18
#define NOCHE_FIN 7

namespace std{

using namespace boost;

typedef tokenizer<char_separator<char> > Tokenizadorfecha;
typedef tokenizer<escaped_list_separator<char> > Tokenizador;

class features {
private:
	map<string,int> categorias;
	map<string,int> DayOfWeek;
	map<string,int> District;
	KMeans* kmeans;

	vector<long double> _procesarDate(string date);
	long double _procesarDayOfWeek(string day);
	long double _procesarDistrict(string district);
	long double _procesarAdress(string adress);
	long double _procesarXY(string X,string Y);
	long double _esDeNoche(int hora);
	long double _esFinDeSemana(int hora);

public:
	features(KMeans* un_kmeans);
	vector<vector<long double> > transformFeature(vector<vector<string> > X, bool Test = false);
	vector<int> transform_categories(vector<vector<string> > X);
	virtual ~features();
};

}

#endif /* FEATURES_H_ */
