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
	int clusteMasCercano = kmeans->predict(punto);
	delete punto;
	return double(clusteMasCercano);
}

vector<long double> features::_procesarDate(string fechaParaProcesar){
	vector<long double> fechaProcesada;
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

vector<vector<long double> > features::transform_feacture(vector<vector<string> > X, bool Test){
	//Si test es True se leen rows del archivo test (para kaggle)
	vector<vector<long double> >resultado;

	if (!Test){
		//See le Row del TRAIN
		for(size_t i=0; i< X.size();i++){
			//por cada linea
			vector<long double> linea;

			//Fecha en columnas diferentes
			vector<long double> date = _procesarDate(X[i][POS_DATE]);
			for(size_t j = 0; j < date.size(); j++){
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
		for(size_t j = 0; j < date.size(); j++){
			linea.push_back(date[j]);
		}
		linea.push_back(_procesarDayOfWeek(X[i][POS_tDAYOFWEEK]));
		linea.push_back(_procesarDistrict(X[i][POS_tDISTRICT]));
		//linea.push_back(_procesarAdress(X[i][POS_ADRESS]));;
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
