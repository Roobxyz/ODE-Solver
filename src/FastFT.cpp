#include "FastFT.h"
#include <fftw3.h>

using namespace std;
#define k_n ((double)ii*3.14159265)

//===================================================================
fftw_complex * FastFT::fftSolve(IODE* ODE, int N ) {

	//Create some pointers to fftw_complex objects
	fftw_complex *ChargeDensity, *ChargeDensityCoefs, *EField, *EFieldCoefs;

	//crete fft_plans - one for forward fft one for backward fft
	fftw_plan p, q;

	//allocate memory to fftw objects
	ChargeDensity = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	ChargeDensityCoefs = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	EField = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	EFieldCoefs = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

	//define the fft processes, dimensions, data containers, fft properties
	p = fftw_plan_dft_1d(N, ChargeDensity, ChargeDensityCoefs, FFTW_FORWARD, FFTW_ESTIMATE);
	q = fftw_plan_dft_1d(N, EFieldCoefs, EField,  FFTW_BACKWARD, FFTW_ESTIMATE);

	//define initial array 
	double* X = new double[2];

	for(int ii=0; ii < N ; ++ii) { 
		X[0] = 4.*ii/N;
		X[1] = 0.;
		
		//Fill the Charge Density fftw 
		ChargeDensity[ii][0]=ODE->eval(X) ;
	}

        //do the fft -- populate ChargeDensityCoefs
	fftw_execute(p);
	
	//release the memoy req'd for ChargeDensity
	fftw_free(ChargeDensity); 

	//calcing coefficients for next fft
	for(int ii=1; ii < N ; ++ii) {
		EFieldCoefs[ii][1] = ChargeDensityCoefs[ii][0]/(-1.*k_n); 		
		EFieldCoefs[ii][0] = ChargeDensityCoefs[ii][1]/(k_n); 		
	}

	//release the memoy
	fftw_free(ChargeDensityCoefs);

	//cheat -- set offst by a factor N/8, ensure graph will be centred around 0
	EFieldCoefs[0][0] = 0.25*N/4;
	
	//do fft -- populate EField
	fftw_execute(q); 

	fftw_free(EFieldCoefs);
	fftw_free(EField);

	fftw_destroy_plan(p);
	fftw_destroy_plan(q);

	cout<< "E(x) by Fourier Transform method "<<endl;
	return EField;
}


