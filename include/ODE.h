#include "IODE.h"


//Class for dE/dx ODE
class dEdx : public IODE{

	public:
		dEdx( double );
		std::string getName();
		double eval( double* );
		double* initialValue();
	private:
		double h;
		double* initial;
		std::string name;

};

//Class For dV/dx ODE
class dVdx : public IODE{ 

	public:
		dVdx ( mat);
		std::string getName();
		double eval(double *);
		double* initialValue();

	private:
		mat E;
		double* initial;
		std::string name;

};

