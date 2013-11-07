#include <GL/glut.h>
#include "tema1.h"

V3VECTOR Points;
vector<double> pointsType;
int type;
int direction;
GLdouble *red, *blue, *yellow, *black, *green, *v;

void initColors(){
	red = (GLdouble*) malloc(3 * sizeof(GLdouble));
	blue = (GLdouble*) malloc(3 * sizeof(GLdouble));
	yellow = (GLdouble*) malloc(3 * sizeof(GLdouble));
	black = (GLdouble*) malloc(3 * sizeof(GLdouble));
	green = (GLdouble*) malloc(3 * sizeof(GLdouble));

	red[0] = 1.00; red[1] = 0.00; red[2] = 0.00;
	black[0] = 0.00; black[1] = 0.00; black[2] = 0.00;
	blue[0] = 0.00; blue[1] = 0.00; blue[2] = 1.00;
	yellow[0] = 1.00; yellow[1] = 1.00; yellow[2] = 0.00;
	green[0] = 0.00; green[1] = 1.00; green[2] = 0.00;
}

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

vector<double> ShiftVector(const vector<double>& vec)
{
	vector<double> temp;
	temp.push_back(vec.at(vec.size() - 1));
	for (int i = 0; i < vec.size() - 1; i++)
		temp.push_back(vec.at(i));
	return temp;
}

void preprocesareInformatii(void){
	v = (GLdouble*) malloc(3 * sizeof(GLdouble));
	v[0] = 0.00;
	v[1] = 1.00;
	v[2] = 0.00;
	double mult = 1.00;
	initColors();
	Points = readFromFile();
	for (int i = 0; i < Points.size(); ++i){
		cout << Points.at(i) << "\n";
	}
	type = testCC(Points);
	if (type == NOT_POLYGON)
		cout << "Nu este polygon.\n";
	else if (type == CONVEX)
		cout << "Poligonul este convex.\n";
	else if (type == CONCAVE)
		cout << "Poligonul este concav.\n";
	
	int direction = ClockWise(Points, pointsType);
	pointsType = ShiftVector(pointsType);
	for (int i = 0; i < pointsType.size(); i++)
		cout << pointsType.at(i) << " ";
	cout << "\n";

}

int getPointType(int i){
	if (direction == CLOCKWISE){
		if (pointsType.at(i) > 0){
			return CONVEX;
		}
		else {
			return CONCAVE;
		}
	}
	else{
		if (pointsType.at(i) < 0){
			return CONVEX;
		}
		else {
			return CONCAVE;
		}
	}
}

void DRAW(){
	/*AFISARE PUNCTE ********************START*********************/
	//convex = green
	//concav = black
	glColor3dv(v);
	glPointSize(12.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < Points.size(); i++){
		if (getPointType(i) == CONVEX){
			glColor3dv(green);
			glVertex2d(Points.at(i).getX(), Points.at(i).getY());
		}
		else{
			glColor3dv(black);
			glVertex2d(Points.at(i).getX(), Points.at(i).getY());
		}
	}
	glEnd();
	/*AFISARE PUNCTE ********************END*********************/

	/*AFISARE LINII ********************START*********************/
	//concav concav = blue
	//convex convex = red
	//concav convex = yellow
	glColor3dv(black);
	glLineWidth(6.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < Points.size(); i++){
		if (i == (Points.size() - 1)){
			if ((getPointType(i) == CONVEX) && (getPointType(0) == CONVEX)){
				glColor3dv(red);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(0).getX(), Points.at(0).getY());
			}
			else if ((getPointType(i) == CONCAVE) && (getPointType(0) == CONCAVE)){
				glColor3dv(blue);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(0).getX(), Points.at(0).getY());
			}
			else{
				glColor3dv(yellow);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(0).getX(), Points.at(0).getY());
			}
		}
		else{
			if ((getPointType(i) == CONVEX) && (getPointType(i + 1) == CONVEX)){
				glColor3dv(red);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(i + 1).getX(), Points.at(i + 1).getY());
			}
			else if ((getPointType(i) == CONCAVE) && (getPointType(i + 1) == CONCAVE)){
				glColor3dv(blue);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(i + 1).getX(), Points.at(i + 1).getY());
			}
			else{
				glColor3dv(yellow);
				glVertex2i(Points.at(i).getX(), Points.at(i).getY());
				glVertex2i(Points.at(i + 1).getX(), Points.at(i + 1).getY());
			}
		}
	}
	glEnd();
	/*AFISARE LINII **********************END********************/
	glFlush();
}

int main(int argc, char** argv)
{
	preprocesareInformatii();
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(800, 600); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	//glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutDisplayFunc(DRAW);
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	return 0;
}