#ifndef STEPENGINE_H
#define STEPENGINE_H

#include "IODE.h"

using namespace std;

class StepEngine{

	public:
		StepEngine(IODE *,double, int );
		double* incriment( double* );
		mat run();
		void PrintFile(std::string, mat);
	private:
		IODE *ode;
		double dx;
		int n;

};
#endif
