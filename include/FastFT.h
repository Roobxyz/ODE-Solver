#ifndef FASTFT_H
#define FASTFT_H
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <fftw3.h>
#include "IODE.h"


class FastFT{
	public:
		fftw_complex* fftSolve(IODE*, int);
};
#endif


