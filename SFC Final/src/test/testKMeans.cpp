#include "test.h"

void testKMeans(){
	Punto* p1 = new Punto{1,5};
	Punto* p2 = new Punto{3,2};
	Punto* p3 = new Punto{4,6};
	Punto* p4 = new Punto{10,5};
	Punto* p5 = new Punto{7,3};

	vector<Punto*> puntos {p1,p2,p3,p4,p5};

	KMeans* clf = new KMeans(2);

	clf->fit(puntos);

	clf->viewCentroides();

	for (size_t i = 0; i < puntos.size(); i++){
		cout << "P: (" << puntos[i]->x << "," << puntos[i]->y << ") \t ->";
		cout << clf->predict(puntos[i]) << endl;

		delete puntos[i];
	}
	puntos.clear();
	delete clf;

}
