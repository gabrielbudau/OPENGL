#include <iostream>
#include <fstream>
#include <vector>
#include "V3.h"
using namespace std;

typedef vector<V3> V3VECTOR;

#ifndef TEMA1
#define TEMA1
V3VECTOR readFromFile();
int testCC(V3VECTOR& V);//test daca punctele date formeaza un poligon convex sau concav
int testC(V3VECTOR& V);//testarea coplanaritatii
int ClockWise(V3VECTOR& P, vector<double>& PointsType);//testeaza daca un poligon este Clockwise sau CounterClockwise
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
