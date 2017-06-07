#include "matrixTest.h"


int 
main(int argc, char const *argv[]){
	mat A = randu<mat>(4,5);
	mat B = randu<mat>(4,5);

	cout << A*B.t() << endl;
	
	return 0;
}