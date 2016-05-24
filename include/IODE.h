#ifndef IODE_H
#define IODE_H
#include <cstdlib>
#include <math.h>
#include "armadillo"

using namespace arma;

class IODE {

	public:
	virtual std::string getName()=0;
	virtual double eval( double* )=0;
	virtual double* initialValue()=0;
};
#endif
