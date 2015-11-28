/*
 * features.cpp
 *
 *  Created on: 27/11/2015
 *      Author: facu
 */

#include "features.h"

namespace std {

features::features(KMeans* un_kmeans) {
	kmeans = un_kmeans;

	//ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS
	categorias["ARSON"] = 0;
	categorias["ASSAULT"] = 1;
	categorias["BAD CHECKS"] = 2;
	categorias["BRIBERY"] = 3;
	categorias["BURGLARY"] = 4;
	categorias["DISORDERLY CONDUCT"] = 5;
	categorias["DRIVING UNDER THE INFLUENCE"] = 6;
	categorias["DRUG/NARCOTIC"] = 7;
	categorias["DRUNKENNESS"] = 8;
	categorias["EMBEZZLEMENT"] = 9;
	categorias["EXTORTION"] = 10;
	categorias["FAMILY OFFENSES"] = 11;
	categorias["FORGERY/COUNTERFEITING"] = 12;
	categorias["FRAUD"] = 13;
	categorias["GAMBLING"] = 14;
	categorias["KIDNAPPING"] = 15;
	categorias["LARCENY/THEFT"] = 16;
	categorias["LIQUOR LAWS"] = 17;
	categorias["LOITERING"] = 18;
	categorias["MISSING PERSON"] = 19;
	categorias["NON-CRIMINAL"] = 20;
	categorias["OTHER OFFENSES"] = 21;
	categorias["PORNOGRAPHY/OBSCENE MAT"] = 22;
	categorias["PROSTITUTION"] = 23;
	categorias["RECOVERED VEHICLE"] = 24;
	categorias["ROBBERY"] = 25;
	categorias["RUNAWAY"] = 26;
	categorias["SECONDARY CODES"] = 27;
	categorias["SEX OFFENSES FORCIBLE"] = 28;
	categorias["SEX OFFENSES NON FORCIBLE"] = 29;
	categorias["STOLEN PROPERTY"] = 30;
	categorias["SUICIDE"] = 31;
	categorias["SUSPICIOUS OCC"] = 32;
	categorias["TREA"] = 33;
	categorias["TRESPASS"] = 34;
	categorias["VANDALISM"] = 35;
	categorias["VEHICLE THEFT"] = 36;
	categorias["WARRANTS"] = 37;
	categorias["WEAPON LAWS"] = 38;

	DayOfWeek["Monday"] = 0;
	DayOfWeek["Tuesday"] = 1;
	DayOfWeek["Wednesday"] = 2;
	DayOfWeek["Thursday"] = 3;
	DayOfWeek["Friday"] = 4;
	DayOfWeek["Saturday"] = 5;
	DayOfWeek["Sunday"] = 6;

	District["NORTHERN"] = 0;
	District["PARK"] = 1;
	District["INGLESIDE"] = 2;
	District["BAYVIEW"] = 3;
	District["RICHMOND"] = 4;
	District["CENTRAL"] = 5;
	District["TARAVAL"] = 6;
	District["TENDERLOIN"] = 7;
	District["MISSION"] = 8;
	District["SOUTHERN"] = 9;

}

long double features::_procesarDayOfWeek(string day){
	return double(DayOfWeek[day]);
}
long double features::_procesarDistrict(string district){
	return double(District[district]);
}

long double features::_procesarXY(string X,string Y){
	if (kmeans == NULL) return 1.0;
	Punto* punto = new Punto{ stold(X), stold(Y)};
	return double(kmeans->predict(punto));
}

vector<long double> features::_procesarDate(string date){
	vector<long double> fecha;
	/*
	INFOS:
		-FORMATO: ANIO-MES-DIA HS:MIN:SG
		-RANGO ANIOS = (2015,2003)
		-SG es siempre 00

	*/
	string aux;
	for ( string::iterator it=date.begin(); it!=date.end(); ++it){

		//anio-mes-dia
		if (strcmp(&*it,"-") || strcmp(&*it," ")){
			fecha.push_back(stod(aux));
			aux.clear();
		}
		else if (strcmp(&*it,":")){
			fecha.push_back(stod(aux));
			break;
		}

		aux.push_back(*it);
	}

	return fecha;
}

vector<vector<long double> > features::transform_feacture(vector<vector<string> > X, bool Test){
	//Si test es True se leen rows del archivo test (para kaggle)
	vector<vector<long double> >resultado;

	if (!Test){
		//Row del TRAIN
		for(size_t i=0; i< X.size();i++){
			//por cada linea
			vector<long double> linea;

			//Fecha en columnas diferentes
			vector<long double> date = _procesarDate(X[i][POS_DATE]);
			for(size_t j = 0; i < date.size(); j++){
				linea.push_back(date[j]);
			}

			linea.push_back(_procesarDayOfWeek(X[i][POS_DAYOFWEEK]));
			linea.push_back(_procesarDistrict(X[i][POS_DISTRICT]));
			//linea.push_back(_procesarAdress(X[i][POS_ADRESS]));
			linea.push_back(_procesarXY(X[i][POS_X],X[i][POS_Y]));

			resultado.push_back(linea);
		}

		return resultado;
	}

	//Se lee un Row del TEST
	for(size_t i=0; i< X.size();i++){
		//por cada linea
		vector<long double> linea;

		vector<long double> date = _procesarDate(X[i][POS_tDATE]);
		for(size_t j = 0; i < date.size(); j++){
			linea.push_back(date[j]);
			cout << date[j] << endl ;
		}

		linea.push_back(_procesarDayOfWeek(X[i][POS_DAYOFWEEK]));
		linea.push_back(_procesarDistrict(X[i][POS_tDISTRICT]));
		//linea.push_back(_procesarAdress(X[i][POS_ADRESS]));
		linea.push_back(_procesarXY(X[i][POS_tX],X[i][POS_tY]));

		resultado.push_back(linea);
	}
	return resultado;
}

vector<int> features::transform_categories(vector<vector<string> > X){
	vector<int> resultado;

	for (size_t i = 0; i < X.size(); i++){
		resultado.push_back(categorias[X[i][POS_CATEGORIA]]);
	}

	return resultado;
}

features::~features() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
