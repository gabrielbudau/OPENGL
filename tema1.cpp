#include "tema1.h"
using namespace std;

V3VECTOR readFromFile(){
	V3VECTOR V;
	ifstream f("puncte.txt");
	float x, y, z;
	while (f >> x >> y >> z)
		V.push_back(V3(x, y, z));
	f.close();
	return V;
}

int testCC(V3VECTOR& P){
	V3VECTOR V;
	int pos = 0, neg = 0, max;
	/*how many negative and positive elements are in V <0, 0, pos/neg> */

	if (P.size() > 2){
		for (int i = 0; i < P.size(); i++){
			if (i == P.size() - 2)
				V.push_back((P.at(i + 1) - P.at(i)) * ((P.at(0) - P.at(i + 1))));
			else if (i == P.size() - 1)
				V.push_back((P.at(0) - P.at(i)) * ((P.at(1) - P.at(0))));
			else
				V.push_back((P.at(i + 1) - P.at(i)) * ((P.at(i + 2) - P.at(i + 1))));
		}
	}
	else{
		return NOT_POLYGON;
	}



	for (int i = 0; i < V.size(); i++){
		if (V.at(i).getZ() < 0)
			neg++;
		else pos++;
	}
	max = pos;
	max = (neg > max) ? neg : max;
	for (int i = 0; i < V.size(); i++){
		if (max == pos)
			if (V.at(i).getZ() < 0)
				return CONCAVE;
		if (max == neg)
			if (V.at(i).getZ() >= 0)
				return CONCAVE;
	}
	return CONVEX;
	return 0;
}

int testC(V3VECTOR& P){
	V3VECTOR V;
	bool flag = true; //presupunem ca punctele sunt coplanare
	for (int i = 1; i < P.size(); i++){
		V.push_back(P.at(i) - P.at(0));
	}
	cout << "\n";
	for (int i = 0; i < V.size(); i++){
		cout << V.at(i);
		cout << "\n";
	}

	for (int i = 0; i < V.size(); i++){
		if (!(V.at(i).getZ() == 0.0)){
			flag = false;
			break;
			
		}
	}
	return flag ? COPLANARE : NECOPLANARE;
}

int ClockWise(V3VECTOR& P, vector<double>& PointsType)
{
	int i, j, k;
	int n = P.size();
	int count = 0;
	double z;

	if (n < 3)
		return -1;

	for (i = 0; i < n; i++) {
		j = (i + 1) % n;
		k = (i + 2) % n;
		z = (P.at(j).getX() - P.at(i).getX()) * (P.at(k).getY() - P.at(j).getY());
		z -= (P.at(j).getY() - P.at(i).getY()) * (P.at(k).getX() - P.at(j).getX());
		PointsType.push_back(z);
		if (z < 0)
			count--;
		else if (z > 0)
			count++;
	}
	if (count > 0)
		return(COUNTERCLOCKWISE);
	else if (count < 0)
		return(CLOCKWISE);
	else
		return -1;
}