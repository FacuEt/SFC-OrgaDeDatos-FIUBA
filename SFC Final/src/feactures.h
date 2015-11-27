/*
 * feactures.h
 *
 *  Created on: 27/11/2015
 *      Author: facu
 */

#ifndef FEACTURES_H_
#define FEACTURES_H_

#include <map>
#include <vector>

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

namespace std {

class feactures {
private:
	map<string,int> categorias;

public:
	feactures();
	vector<vector<long double> > transform_feacture(vector<vector<string> > X, bool Test = false);
	vector<int> transform_categories(vector<vector<string> > X);
	virtual ~feactures();
};

} /* namespace std */

#endif /* FEACTURES_H_ */
