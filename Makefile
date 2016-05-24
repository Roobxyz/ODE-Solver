#######################		
#  MakeFile Template  #
#  Created by me,     # 
#	Reuben Taylor # 
#######################

CC= 		g++
CFLAGS= 	-c -Wall
LDFLAGS=	-l "armadillo" -l "fftw3"
SOURCES=	src/main.cpp src/ODE.cpp src/StepEngine.cpp src/FastFT.cpp 
INC= 		-I include
OBJECTS=	$(SOURCES:.cpp=.o)
EXECUTABLE=	bin/solve
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INC) $< -o $@ 
clean:
	rm -rf src/*.o $(EXECUTABLE)

.PHONY: clean
