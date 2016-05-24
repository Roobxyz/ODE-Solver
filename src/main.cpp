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
	system("python MyPlot.py EField.txt V.txt Rho.txt FFT_EField.txt");
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
	PrintFile("Rho.txt",rho,nSteps);

	//Fourier Solver
	FastFT fourierSolver;
	fftw_complex *FFTEField = fourierSolver.fftSolve(rho, nSteps);
	PrintFile("FFT_EField.txt",FFTEField,nSteps);

	//StepEngine; implicitly utilizes rk4 
	StepEngine* Stepper = new StepEngine(rho, StepSize,nSteps);

	//stepper results stored in matrix 
	mat EField = Stepper->run();

	//E Matrix printed to file 
	PrintFile("EField.txt",EField);

	//Negate the E values while keeping the x constant
	mat minusE = negateEField(EField);
	
	//new ODE object -- instantiated with the numerical values of E found from previous integration
	IODE *MinusEofX = new dVdx(minusE);

	//Stepper points to a new step object
	Stepper = new StepEngine(MinusEofX,StepSize,nSteps);

	//V values stored in a matrix
	mat V = Stepper->run();

	//V Matrix printed to file 
	PrintFile("V.txt",V);

	//display the results via python's matplotlib
	display();

	return 0;

}
