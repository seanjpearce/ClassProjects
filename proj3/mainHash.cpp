// Name: Sean Pearce and Anthony Ferraro

#include <iostream>
#include "MakeModel.hpp"
#include <ctime>
#include <cstdlib>

using namespace std;
int main() {
	srand(time(NULL));
	
	// Choose one of the 2 blocks to uncomment, depending on which input file
	// you'd like to run your hashmap on

    ///*
	makeModel voice1("DrSeuss.txt","Seussout1.txt",true,true);
	makeModel voice2("DrSeuss.txt","Seussout2.txt",false,true);
    makeModel voice3("DrSeuss.txt","Seussout3.txt",true,false);
	makeModel voice4("DrSeuss.txt","Seussout4.txt",false,false);
	//*/
    /*
	makeModel voice5("GEChap.txt","GEout1.txt",true,true);
	makeModel voice6("GEChap.txt","GEout2.txt",false,true);
	makeModel voice7("GEChap.txt","GEout3.txt",true,false);
	makeModel voice8("GEChap.txt","GEout4.txt",false,false);
    */
    /*
    makeModel voice9("readme.txt","readout.txt",true,true);
    makeModel voice10("readme.txt","readout.txt",false,true);
    makeModel voice11("readme.txt","readout.txt",true,false);
    makeModel voice12("readme.txt","readout.txt",false,false);
	*/
    //makeModel voice13("in.txt","out.txt",true,true);
    return 0;
}
