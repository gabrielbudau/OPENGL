#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glut.h> 
#include <utility>
#include "V3.h"
using namespace std;



#ifndef UTILS_H
#define UTILS_H
vector<V3> readFromFile();
int testCC(vector<V3>& V);//test daca punctele date formeaza un poligon convex sau concav
int testC(vector<V3>& V);//testarea coplanaritatii
int ClockWise(vector<V3>& P, vector<double>& PointsType);//testeaza daca un poligon este Clockwise sau CounterClockwise
bool checkTriangle(unsigned int i, unsigned int j, unsigned int k, vector<V3> Points);
bool isInside(V3 a, V3 b, V3 c, V3 point);
float area(V3 a, V3 b, V3 c);
#endif

#ifndef NOT_POLYGON
#define NOT_POLYGON 0
#endif

#ifndef CONVEX
#define CONVEX 1
#endif

#ifndef CONCAVE
#define CONCAVE 2
#endif

#ifndef NECOPLANARE
#define NECOPLANARE 0
#endif

#ifndef COPLANARE
#define COPLANARE 1
#endif

#ifndef COUNTERCLOCKWISE
#define COUNTERCLOCKWISE 3
#endif

#ifndef CLOCKWISE
#define CLOCKWISE 4
#endif
