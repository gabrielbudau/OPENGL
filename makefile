exec: \
compile
	./main

compile: \
main.cpp
	echo "Compiling..."
	g++ \
	V3.cpp \
	utils.cpp \
	main.cpp \
	-g -Wall -lGL -lGLU -lglut -lm -o main
	
