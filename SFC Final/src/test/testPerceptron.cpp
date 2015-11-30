#include "test.h"
#include "../Perceptron.h"


void testPerceptron(){
	lectorCSV ParserCSV("datos/Street_Names.csv");
	lectorCSV ParserCSV2("datos/train_FIX.csv");
	lectorCSV ParserCSV3("datos/test_reduced.csv");
	cout << "CARGUE LAS CALLES" << endl;
	vector<vector<string> > set_train = ParserCSV2.devolverLineas();
	vector<vector<string> > set_calles = ParserCSV.devolverLineas();
	vector<vector<string> > set_test = ParserCSV3.devolverLineas();
	vector<string> header = set_calles[0];
	vector<vector<string>> calles_parseadas;
	for(size_t i = 1; i < set_calles.size();i++){
		cout << ParserCSV.procesarAddressEnString(set_calles[i][0])[0] << endl;
		calles_parseadas.push_back(ParserCSV.procesarAddressEnString(set_calles[i][0]));
	}
	//cout << calles_parseadas[0][0] << endl;
	Perceptron percep(set_train,calles_parseadas);
	percep.entrenarPerceptron();
	for(size_t i = 0; i < set_test.size();i++)
	{
		cout << set_test[i][1]  << " ES LA QUE ES Y PERCEPTRON DICE QUE ES " << percep.emitirCategoria(set_test[i]) << endl;
	}

	cout << "CARGO TODO BIEN" << endl;
}



