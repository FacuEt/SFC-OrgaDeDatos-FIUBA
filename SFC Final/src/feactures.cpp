/*
 * feactures.cpp
 *
 *  Created on: 27/11/2015
 *      Author: facu
 */

#include "feactures.h"

namespace std {

feactures::feactures() {

	//ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS
	categorias['ARSON'] = 0;
	categorias['ASSAULT'] = 1;
	categorias['BAD CHECKS'] = 2;
	categorias['BRIBERY'] = 3;
	categorias['BURGLARY'] = 4;
	categorias['DISORDERLY CONDUCT'] = 5;
	categorias['DRIVING UNDER THE INFLUENCE'] = 6;
	categorias['DRUG/NARCOTIC'] = 7;
	categorias['DRUNKENNESS'] = 8;
	categorias['EMBEZZLEMENT'] = 9;
	categorias['EXTORTION'] = 10;
	categorias['FAMILY OFFENSES'] = 11;
	categorias['FORGERY/COUNTERFEITING'] = 12;
	categorias['FRAUD'] = 13;
	categorias['GAMBLING'] = 14;
	categorias['KIDNAPPING'] = 15;
	categorias['LARCENY/THEFT'] = 16;
	categorias['LIQUOR LAWS'] = 17;
	categorias['LOITERING'] = 18;
	categorias['MISSING PERSON'] = 19;
	categorias['NON-CRIMINAL'] = 20;
	categorias['OTHER OFFENSES'] = 21;
	categorias['PORNOGRAPHY/OBSCENE MAT'] = 22;
	categorias['PROSTITUTION'] = 23;
	categorias['RECOVERED VEHICLE'] = 24;
	categorias['ROBBERY'] = 25;
	categorias['RUNAWAY'] = 26;
	categorias['SECONDARY CODES'] = 27;
	categorias['SEX OFFENSES FORCIBLE'] = 28;
	categorias['SEX OFFENSES NON FORCIBLE'] = 29;
	categorias['STOLEN PROPERTY'] = 30;
	categorias['SUICIDE'] = 31;
	categorias['SUSPICIOUS OCC'] = 32;
	categorias['TREA'] = 33;
	categorias['TRESPASS'] = 34;
	categorias['VANDALISM'] = 35;
	categorias['VEHICLE THEFT'] = 36;
	categorias['WARRANTS'] = 37;
	categorias['WEAPON LAWS'] = 38;


}


vector<vector<long double> > feactures::transform_feacture(vector<vector<string> > X, bool Test = false){
	vector<vector<long double> >resultado;

	for(size_t i=0; i< X.size();i++){
		//por cada linea
		vector<long double> linea;
		//linea.push_back(_procesarDate(X[i][POS_DATE]));

	}

	return resultado;
}

vector<int> feactures::transform_categories(vector<vector<string> > X){
	vector<int> resultado;

	for (size_t i = 0; i < X.size(); i++){
		resultado.push_back(categorias[X[i][POS_CATEGORIA]]);
	}

	return resultado;
}

feactures::~feactures() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
