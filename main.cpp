#include <GL/glut.h>
#include "tema1.h"

V3VECTOR Points;
vector<double> pointsType;
int type;
int direction;
GLdouble *red, *blue, *yellow, *black, *green, *v;
bool lbuttonDown = false;


void initColors(){
	red = (GLdouble*) malloc(3 * sizeof(GLdouble));
	blue = (GLdouble*) malloc(3 * sizeof(GLdouble));
	yellow = (GLdouble*) malloc(3 * sizeof(GLdouble));
	black = (GLdouble*) malloc(3 * sizeof(GLdouble));
	green = (GLdouble*) malloc(3 * sizeof(GLdouble));
	v = (GLdouble*) malloc(3 * sizeof(GLdouble));
	red[0] = 1.00; red[1] = 0.00; red[2] = 0.00;
	black[0] = 0.00; black[1] = 0.00; black[2] = 0.00;
	blue[0] = 0.00; blue[1] = 0.00; blue[2] = 1.00;
	yellow[0] = 1.00; yellow[1] = 1.00; yellow[2] = 0.00;
	green[0] = 0.00; green[1] = 1.00; green[2] = 0.00;
	v[0] = 0.50; v[1] = 0.50; v[2] = 0.50;
}

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

vector<double> ShiftVector(const vector<double>& vec){
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
	type = testCC(Points);
	int direction = ClockWise(Points, pointsType);
	pointsType = ShiftVector(pointsType);
}

int getPointType(int i){
	if (direction == CLOCKWISE){
		if (pointsType.at(i) < 0){
			return CONVEX;
		}
		else {
			return CONCAVE;
		}
	}
	else{
		if (pointsType.at(i) > 0){
			return CONVEX;
		}
		else {
			return CONCAVE;
		}
	}
}

void reshape (int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void drawPoligon(){
	preprocesareInformatii();
	if(type != NOT_POLYGON){
		/* AFISARE LINII
		concav concav = blue
		convex convex = red
		concav convex = yellow */
		glColor3dv(black);
		glLineWidth(2.0);
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
		/*****************************************************************************/
		/* AFISARE PUNCTE 
		convex = green
		concav = black */
		glColor3dv(v);
		glPointSize(4.0);
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
		/*****************************************************************************/
	} else {
		glColor3dv(black);
		glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i < Points.size() - 1; i ++){
			glVertex2i(Points.at(i).getX(), Points.at(i).getY());
			glVertex2i(Points.at(i + 1).getX(), Points.at(i + 1).getY());
		}
		glEnd();
	}
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_RIGHT_BUTTON){
		if (state == GLUT_DOWN)
			cout << "Right button pressed"<< endl;
		else
			cout << "Right button lifted "<< "at (" << x << "," << y<< ")" << endl;
	}else if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN)
			lbuttonDown = true;
		else
			lbuttonDown = false;
	}
}

void motion(int x, int y)
{
	if (lbuttonDown)
		cout << "Mouse dragged with left button at "<< "(" << x << "," << y << ")" << endl;
}

void motionPassive(int x, int y)
{
	cout << "Mouse moved at "
		<< "(" << x << "," << y << ")" << endl;
}

void entry(int state)
{
	if (state == GLUT_ENTERED)
		cout << "Mouse Entered" << endl;
	else
		cout << "Mouse Left" << endl;
}

void DRAW(){

	//drawPoligon();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(0, 0); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(500, 500); // dimensiunile ferestrei 
	glutCreateWindow("Puncte & Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	//glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
	glutDisplayFunc(DRAW);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(motionPassive);
	glutEntryFunc(entry);
	//glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	return 0;
}