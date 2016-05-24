#include "ODE.h"

/**
	Methods For the ODE:

      		dE/dx = ρ(x)

**/

dEdx::dEdx( double k ):
	h(k){
		name = "dE/dx = rho(x)";
	}

std::string dEdx::getName(){
	return name;
}


double* dEdx::initialValue(){
	initial = new double[2];
	initial[0] = 0;
	initial[1] = 0;
	return initial;
}

double dEdx::eval(double* CoOrd ){

	if (CoOrd[0]<1.) 
	{		
		return 0.;
	}

	else if(CoOrd[0]>=1. && CoOrd[0]<2.)
	{		
		return h;
	}
	else if(CoOrd[0]>=2. && CoOrd[0]<3.)
	{		
		return -h;
	}
	else
	{
		return 0.;
	}
}

/**
	Methods For the ODE:

      		dV/dx = -E(x)

**/

dVdx::dVdx(mat EField):E(EField)
{
	name = "dV/dx = -E(x)";
	initial = new double[2];
	initial[0] =0;
	initial[1] =0;
}

std::string dVdx::getName(){
	return name;
}

double dVdx::eval(double *CoOrd){

	int BestValIndex =0;
	double diff =.1;

	for(int i=0;i<E.n_rows;i++){
		
		if(E(i,0) - CoOrd[0] < diff ){
			diff = std::abs(CoOrd[0] -E(i,0));
			BestValIndex = i;
		}
	}
	return E(BestValIndex,1);
}

double* dVdx::initialValue(){

	return initial;
}

