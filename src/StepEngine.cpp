#include "StepEngine.h"

StepEngine::StepEngine(IODE *pode,double deltax, int nSteps):
	ode(pode),
	dx(deltax),
	n(nSteps){

	}

double* StepEngine::incriment( double* CoOrd ){

	//x and y value set then feed to d1, d2 etc...
	
	//rk4 Method used here for integration

	double xx = CoOrd[0];
	double yy = CoOrd[1];
	double d1 = ode->eval( CoOrd ) ;
	
	CoOrd[0] = xx + dx/2;
	CoOrd[1] = yy + dx/2*d1;
	double d2 = ode->eval( CoOrd ) ;

	CoOrd[1] = yy + dx/2*d2;
	double d3 = ode->eval( CoOrd ) ;

	CoOrd[0] = xx + dx/2;
	CoOrd[1] = xx + dx*d3;
	double d4 = ode->eval( CoOrd ) ;

	double dy = dx*(1./6.)*(d1 + 2*d2 + 2*d3 + d4);
	
	double* inc = new double[2];
	inc[0] = dx;
	inc[1] = dy;	
	return inc ;
}

mat StepEngine::run(){
	
	mat Results(n,2);
	Results(0,0)= ode->initialValue()[0];
	Results(0,1)= ode->initialValue()[1];

	for (int i=0; i < n-1; i++ ) {
		double* current = new double[2];
		
		current[1] = Results(i,1);
		current[0] = Results(i,0);


		double* change = this->incriment( current);

		//Update the next entry in the results matrix 
		Results(i+1,0)= Results(i,0)+change[0];
		Results(i+1,1)= Results(i,1)+change[1]; 
	
	}

	std::cout<<"Finished Integrating Function "<<ode->getName()<<std::endl;
	return Results;
}
