/*
 * Perceptron.cpp
 *
 *  Created on: Nov 29, 2015
 *      Author: xx
 */

#include "Perceptron.h"
#include "lectorCSV.h"
#define POS_CALLE  6
#define POS_CATEGORY 1

Perceptron::Perceptron(vector<vector<string>> set_train,vector<vector<string> > set_features) {
	this->train = set_train;
	this->crime_cat = {"ARSON","ASSAULT","BAD CHECKS","BRIBERY","BURGLARY","DISORDERLY CONDUCT","DRIVING UNDER THE INFLUENCE","DRUG/NARCOTIC","DRUNKENNESS","EMBEZZLEMENT","EXTORTION","FAMILY OFFENSES","FORGERY/COUNTERFEITING","FRAUD","GAMBLING","KIDNAPPING","LARCENY/THEFT","LIQUOR LAWS","LOITERING","MISSING PERSON","NON-CRIMINAL","OTHER OFFENSES","PORNOGRAPHY/OBSCENE MAT","PROSTITUTION","RECOVERED VEHICLE","ROBBERY","RUNAWAY","SECONDARY CODES","SEX OFFENSES FORCIBLE","SEX OFFENSES NON FORCIBLE","STOLEN PROPERTY","SUICIDE","SUSPICIOUS OCC","TREA","TRESPASS","VANDALISM","VEHICLE THEFT","WARRANTS","WEAPON LAWS"};
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0,1);
	for (int i = 0; i < 39 ; i++){
		this->prod_internos.push_back(0.0); //inicializo el vector de productos internos en 0
		map<string,long double> weights;
		for(size_t k = 0; k < set_features.size();k++){
			cout << "VOY A GUARDAR LA CALLE" << set_features[k][0].c_str() << endl;
			weights[set_features[k][0]] = dis(gen);//peso aleatorio entre -1 y 1
			}
			this->pesos.push_back(weights);
			}
		}

void Perceptron::resetearProductosInternos(){
	for (size_t i = 0; i < this->prod_internos.size();i++) this->prod_internos[i] = 0.0;
}
void Perceptron::generarIndexesDeFeatures(){
		this->categorias["ARSON"] = 0;
		this->categorias["ASSAULT"] = 1;
		this->categorias["BAD CHECKS"] = 2;
		this->categorias["BRIBERY"] = 3;
		this->categorias["BURGLARY"] = 4;
		this->categorias["DISORDERLY CONDUCT"] = 5;
		this->categorias["DRIVING UNDER THE INFLUENCE"] = 6;
		this->categorias["DRUG/NARCOTIC"] = 7;
		this->categorias["DRUNKENNESS"] = 8;
		this->categorias["EMBEZZLEMENT"] = 9;
		this->categorias["EXTORTION"] = 10;
		this->categorias["FAMILY OFFENSES"] = 11;
		this->categorias["FORGERY/COUNTERFEITING"] = 12;
		this->categorias["FRAUD"] = 13;
		this->categorias["GAMBLING"] = 14;
		this->categorias["KIDNAPPING"] = 15;
		this->categorias["LARCENY/THEFT"] = 16;
		this->categorias["LIQUOR LAWS"] = 17;
		this->categorias["LOITERING"] = 18;
		this->categorias["MISSING PERSON"] = 19;
		this->categorias["NON-CRIMINAL"] = 20;
		this->categorias["OTHER OFFENSES"] = 21;
		this->categorias["PORNOGRAPHY/OBSCENE MAT"] = 22;
		this->categorias["PROSTITUTION"] = 23;
		this->categorias["RECOVERED VEHICLE"] = 24;
		this->categorias["ROBBERY"] = 25;
		this->categorias["RUNAWAY"] = 26;
		this->categorias["SECONDARY CODES"] = 27;
		this->categorias["SEX OFFENSES FORCIBLE"] = 28;
		this->categorias["SEX OFFENSES NON FORCIBLE"] = 29;
		this->categorias["STOLEN PROPERTY"] = 30;
		this->categorias["SUICIDE"] = 31;
		this->categorias["SUSPICIOUS OCC"] = 32;
		this->categorias["TREA"] = 33;
		this->categorias["TRESPASS"] = 34;
		this->categorias["VANDALISM"] = 35;
		this->categorias["VEHICLE THEFT"] = 36;
		this->categorias["WARRANTS"] = 37;
		this->categorias["WEAPON LAWS"] = 38;
}
void Perceptron::generarMapeoDeDatos(){

}

void Perceptron::entrenarPerceptron(){
	lectorCSV ParserCSV("train_reduced.csv");
	for (size_t i = 1; i < this->train.size();i++){ //recorro el train set
		long double cont;
		size_t idx_propuesto = 0; //es la rta que tira el percep
		vector<string> linea = this->train[i];
		string category;
		vector<string> address;
		category = linea[POS_CATEGORY];
		address = ParserCSV.procesarAddressEnString(linea[POS_CALLE]);
		size_t idx_correcto = this->categorias[category]; //cual es la respuesta correcta,para saber si updateo o no
		for(size_t j = 0; j < this->categorias.size();j++){ //arranco con el vector de pesos
			for(size_t k = 0; k < address.size();k++){ //hago el producto interno
				cont += this->pesos[this->categorias[category]][address[k]]; //acumulo el prod interno
				cout << "EL PESO DEL PROD INT ES " << cont << " PARA " << category << endl;
			}
			this->prod_internos[j] = cont;
			if (this->prod_internos[idx_propuesto] <= cont) idx_propuesto = j; //hay un vec con mayor weight
			//politica de manejo de empate simple, si es mayor o igual reemplazo index
			cont = 0.0;
		}
		if (idx_propuesto == idx_correcto){
			resetearProductosInternos();
			continue;//esta bien,clasificaste bien
		}
		else {
			updatePesos(category,address); //no clasificaste bien, updatea pesos y segui
			resetearProductosInternos();
		}

	}
}

void Perceptron::updatePesos(string category, vector<string> address){
		size_t idx_a_sumar = this->categorias[category];
		long double aux;
		for (size_t i = 0; i < this->pesos.size();i++){
			if (i == idx_a_sumar) aux = 1; //a este le quiero meter mas peso
			else aux = -1; //al resto les resto

			for ( size_t j = 0; j < address.size(); j++){
				this->pesos[i][address[j]] += aux;
			}
		}
}

string Perceptron::emitirCategoria(vector<string> test_a_clasificar){
	lectorCSV ParserCSV("train_reduced.csv");
	vector<string> address;
	long double cont;
	size_t idx_propuesto = 0;
	address = ParserCSV.procesarAddressEnString(test_a_clasificar[POS_CALLE]);
	for(size_t j = 0; j < this->crime_cat.size();j++){ //arranco con el vector de pesos
				for(size_t k = 0; k < address.size();k++){ //hago el producto interno
					cont += this->pesos[this->categorias[this->crime_cat[j]]][address[k]]; //acumulo el prod interno
					cout << "VOY A ACCEDER A LA CALLE" << address[k] << " Y EL PROD INT ME DIO "<<cont << endl;
				}
				this->prod_internos[j] = cont;
				if (this->prod_internos[idx_propuesto] <= cont) idx_propuesto = j;

	}
	return this->crime_cat[idx_propuesto];
}
Perceptron::~Perceptron() {
	// TODO Auto-generated destructor stub
}

