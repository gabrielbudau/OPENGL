exec: \
compile
	./main

compile: \
main.cpp
	echo "Compiling..."
	g++ \
	V3.cpp \
	tema1.cpp \
	main.cpp \
	-lGL -lGLU -lglut -lm -o main
	touch compile
