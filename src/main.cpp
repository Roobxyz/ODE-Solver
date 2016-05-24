#include <fstream>
#include <iostream>
#include <fftw3.h>
#include "ODE.h"
#include "StepEngine.h"
#include "FastFT.h"

using namespace std;

mat negateEField(mat E){
	mat minusE(E.n_rows,E.n_cols);
	minusE.col(0) = E.col(0);
	minusE.col(1) = -1*E.col(1);
	return minusE;
}

void display(){
	cout<<"Plotting Results..."<<endl;
	system("python python/multiplot.py outputs/Rho.txt outputs/EField.txt outputs/FFT_EField.txt outputs/V.txt ");
}

void PrintFile(std::string T, mat Res){

	std::ofstream OFile;

	OFile.precision(4);
	OFile.setf(ios::fixed);	

	OFile.open(T.c_str());

	Res.raw_print(OFile, "");

	std::cout<<"Printed Results to file: "<<T<<std::endl;
	OFile.close();
}

void PrintFile(std::string T, fftw_complex* Res,int N){

	std::ofstream OFile;

	OFile.precision(4);
	OFile.setf(ios::fixed);	

	OFile.open(T.c_str());
	double X  = 0;
	for(int ii=0; ii < N ; ++ii) {
		X = 4.*ii/N;
		//print to file		
		OFile << X <<" "<<Res[ii][0] << endl ;
	}
	
	std::cout<<"Printed Results to file: "<<T<<std::endl;
	OFile.close();
}


void PrintFile(std::string T, IODE* Res,int N){

	std::ofstream OFile;

	OFile.precision(4);
	OFile.setf(ios::fixed);	
	OFile.open(T.c_str());

	double* X = new double[2];
	for(int ii=0; ii < N ; ++ii) { 
		X[0] = 4.*ii/N;
		X[1] = 0.;
		OFile << X[0] << " "  << Res->eval(X) << endl ;

	}
	
	std::cout<<"Printed Results to file: "<<T<<std::endl;
	OFile.close();
}

int main(){

	
	//number of Steps
	int nSteps =1000;

	//interval of steps
	double StepSize = 4./(double)nSteps;

	//Differential Equation instantiated dE/dx = ρ(x)
	IODE *rho = new dEdx(1.); 
	
	//generate data for ρ(x) which is 
	//defined as 0 until x=1 and then a constant after,
	//in this case dE/dx = ρ(1)
	PrintFile("outputs/Rho.txt",rho,nSteps);

	//Fourier Solver -- solving ∫ dE = ∫ ρ(1) dx by fourier methods
	FastFT fourierSolver;
	fftw_complex *FFTEField = fourierSolver.fftSolve(rho, nSteps);
	PrintFile("outputs/FFT_EField.txt",FFTEField,nSteps);

	//StepEngine; implicitly utilizes rk4 -- 
	//solving ∫ dE = ∫ ρ(1) dx by incrimental methods
	StepEngine* Stepper = new StepEngine(rho, StepSize,nSteps);

	//stepper results stored in matrix 
	mat EField = Stepper->run();

	//E Matrix printed to file 
	PrintFile("outputs/EField.txt",EField);

	//Negate the E values while keeping the x constant
	mat minusE = negateEField(EField);
	
	//new ODE object -- instantiated with the numerical values of E found from previous integration
	IODE *MinusEofX = new dVdx(minusE);

	//Stepper points to a new step object
	Stepper = new StepEngine(MinusEofX,StepSize,nSteps);

	//V values stored in a matrix
	mat V = Stepper->run();

	//V Matrix printed to file 
	PrintFile("outputs/V.txt",V);

	//display the results via python's matplotlib
	display();

	return 0;

}
