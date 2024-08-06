
#ifndef MAKEMODEL_HPP_
#define MAKEMODEL_HPP_


#include "HashMap.hpp"
#include <iostream>
using namespace std;

class makeModel {
	hashMap *ht;
	string fn;
	string newfile;
	bool hashfn;
	bool collfn;
public:
	makeModel(string file,string newf, bool hash1, bool coll1);
	void readFile();
	void writeFile();
};




#endif /* makeModel_HPP_ */
