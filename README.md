# ODE-Solver
The purpose of this programme is to numerically solve ODEs. Specifically it was designed to solve two differential equations one after the other. The equations are show below;
dE/dx = ρ(x)
dV/dx =−E(x) 
The equations were solved using a Runge-Kutta 4th order algorithm and the first equation was also solved via an FFT method.
The programme utilised a base interface ODE class that declared methods used in solution algorithms.
Eqn. 1 was solved first and then the results were used to solve Eqn. 2. Hence, the two ODEs have different properties, for example the dVdx class is initialised with the use of an arma::mat1 object whereas the dEdx class is initialised with a single double value.

##Step Engine
The StepEngine class utilised an rk4 algorithm to increment the ODE. It was decided that an interface for different step algorithms would be superfluous, given that the rk4 is the most accurate integration stepper.The Runge-Kutta method increments the function by utilising the derivative at a series of points along a line segment. The rk4 method hence takes into account four points along the line segment(beginning, two mid-points and an end point). The weighted derivative at each point is then multiplied by the step size (giving an incremented area), and the result is added on to the current value of the function.
The algorithm constructs, from the current value, the next value of the integrated function. It is imperative, then, that the initial conditions are known when using this method so that the integration has somewhere physical to start building the function.

Storing each step gives the integration function. Here the whole function was stored in a 2 × n matrix with the x values in one column and the f (x) in the other.
The matrix package “Armadillo” was selected as it allowed easy manipulation of the data and straightforward print methods. One of the minor drawbacks of this method was that it was computationally expensive and for large n the calculation could be quite slow.

##FastFT
The FastFT class is a one method class which solves Eqn. 1 via FFT methods. Its only method ”fftSolve(IODE * , int)" takes the interface pointer to the ODE and the number of steps to calculate it over. It is a void method for solving Eqn. 1 via Fourier methods, then printing E(x) to a file (“FFT_EField.txt”). For consistency the number of steps,n is kept the same in the rk4 and FFT methods. The FastFT class utilises the Fastest Fourier Transform in the West (FFTW) package in order to solve the ODE. To do this, it must first be realised that the Fourier coefficients of the series describing ρ(x) can be written in terms of the coefficients of the series describing E(x).
One simply Fourier transforms (forward) ρ(x), scales each of the coefficients by a factor N/4 × ik_n and then Fourier transforms (backward) the Eˆn coefficients. This gives the function E(x) out.
The because fast Fourier transforms work with discrete data, there are some nuances with respect to the sum (it obviously can’t be infinite) and the zeroth coefficient( which controls the offset). These are determined by the method of Fourier transform and are accounted for in the FastFT class to ensure that scaled and properly shifted results are observed. The zeroth coefficient is set as 0.25 and the normalisation is set as N/4 (N/2 per FFT and two FFTs).



