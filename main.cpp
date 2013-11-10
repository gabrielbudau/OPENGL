#include "utils.h"

GLdouble *red, *blue, *yellow, *black, *green, *v;
vector<V3> Points;  //vertices
vector<vector<V3> > Edges; //edges
vector<vector<V3> > Tris; //triangles
vector<double> pointsType;
int type;
int direction;

void initColors();

void initGL() {
   // Set "clearing" or background color
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Black and opaque
}

int getPointType(int i);

vector<double> ShiftVector(const vector<double>& vec);
void preprocesareInformatii();
void triangulate();
void setRandomColor();
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {

   
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
   // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);
      glColor3f(0.7f, 0.7f, 0.7f);
      glVertex2f(0.0f, 1.0f);
      glColor3f(0.5f, 0.5f, 0.5f);
      glVertex2f(0.0f, 0.0f);
      glColor3f(0.7f, 0.7f, 0.7f);
      glVertex2f(1.0f, 0.0f);
      glColor3f(0.5f, 0.5f, 0.5f);
      glVertex2f(1.0f, 1.0f);
   glEnd();

   for(float i = 0.0; i < 1.0; i += 0.05){
      glBegin(GL_LINES);
      glColor3f(0.3f, 0.3f, 0.3f);
      glVertex2f(0.0f, i);
      glVertex2f(1.0f, i);
      glEnd();
   }

   for(float i = 0.0; i < 1.0; i += 0.05){
      glBegin(GL_LINES);
      glColor3f(0.3f, 0.3f, 0.3f);
      glVertex2f(i, 0.0f);
      glVertex2f(i, 1.0f);
      glEnd();
   }
   /*****************************************************************************/
   /* AFISARE TRIUNGHIURI
   */
   
   glBegin(GL_TRIANGLES);
      for(unsigned int i = 0; i < Tris.size(); i ++){
         setRandomColor();
         glVertex2f(Tris.at(i).at(0).getX(), Tris.at(i).at(0).getY());
         glVertex2f(Tris.at(i).at(1).getX(), Tris.at(i).at(1).getY());
         glVertex2f(Tris.at(i).at(2).getX(), Tris.at(i).at(2).getY());
      }
   glEnd();
   /*****************************************************************************/
   /* AFISARE LINII
   concav concav = blue
   convex convex = red
   concav convex = yellow */
   glEnable(GL_LINE_SMOOTH);
   glColor3dv(black);
   //glLineWidth(1.0);
   glBegin(GL_LINE_STRIP);
   for (unsigned int i = 0; i < Points.size(); i++){
      if (i == (Points.size() - 1)){
         if ((getPointType(i) == CONVEX) && (getPointType(0) == CONVEX)){
            glColor3dv(red);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(0).getX(), Points.at(0).getY());
         }
         else if ((getPointType(i) == CONCAVE) && (getPointType(0) == CONCAVE)){
            glColor3dv(blue);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(0).getX(), Points.at(0).getY());
         }
         else{
            glColor3dv(yellow);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(0).getX(), Points.at(0).getY());
         }
      }
      else{
         if ((getPointType(i) == CONVEX) && (getPointType(i + 1) == CONVEX)){
            glColor3dv(red);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(i + 1).getX(), Points.at(i + 1).getY());
         }
         else if ((getPointType(i) == CONCAVE) && (getPointType(i + 1) == CONCAVE)){
            glColor3dv(blue);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(i + 1).getX(), Points.at(i + 1).getY());
         }
         else{
            glColor3dv(yellow);
            glVertex2f(Points.at(i).getX(), Points.at(i).getY());
            glVertex2f(Points.at(i + 1).getX(), Points.at(i + 1).getY());
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
   for (unsigned int i = 0; i < Points.size(); i++){
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

   //glLineWidth(1.0);
   glFlush();  // Render now
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix

   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(0.0 * aspect, 0.5 * aspect, 0.0, 0.5);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(0.0, 0.5, 0.0 / aspect, 0.5 / aspect);
   }
}


int main(int argc, char** argv) {
   initColors();
   preprocesareInformatii();
   triangulate();
   glutInit(&argc, argv);          // Initialize GLUT
   glutInitWindowSize(480, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("OPENGL_2D");  // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   
   initGL();                        // Our own OpenGL initialization
   glutMainLoop();                 // Enter the event-processing loop
   return 0;
}


vector<double> ShiftVector(const vector<double>& vec){
   vector<double> temp;
   temp.push_back(vec.at(vec.size() - 1));
   for (unsigned int i = 0; i < vec.size() - 1; i++)
      temp.push_back(vec.at(i));
   return temp;
}

void preprocesareInformatii(){
   Points = readFromFile();
   type = testCC(Points);
   direction = ClockWise(Points, pointsType);
   pointsType = ShiftVector(pointsType);
   
}

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

void setRandomColor(){
   glColor3f((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
}

void triangulate(){
   bool pit;
   pit = true;//points in triangle, assume there are points in the given tri
   unsigned int i = 0;
   vector<V3> vec;
   vector<V3> temp(Points);
   vector<double> temp1(pointsType);
   if(Points.size()>0){
      while(Points.size() > 2 && i < Points.size()){
         pit = true;
         if(Points.size() == 3){
            vec.push_back(Points.at(0)); vec.push_back(Points.at(1)); vec.push_back(Points.at(2));
            Tris.push_back(vec);
            vec.clear();
            break;
         }
         if(getPointType(i) == CONVEX){
            cout<<"CONVEX\n";
            if(i == 0)
               pit = checkTriangle(i, i + 1, Points.size() - 1, Points);
            else
               pit = checkTriangle(i, i + 1, i - 1, Points);

            if(pit){
               if(i == 0){
                  vec.push_back(Points.at(i)); vec.push_back(Points.at(i + 1)); vec.push_back(Points.at(Points.size() - 1));
                  Tris.push_back(vec);
                  vec.clear();
               }else{
                  vec.push_back(Points.at(i)); vec.push_back(Points.at(i + 1));vec.push_back(Points.at(i - 1));
                  Tris.push_back(vec);
                  vec.clear();
               }
               Points.erase (Points.begin() + i);
               pointsType.erase (pointsType.begin() + i);
            }else{
               i++;
            }
         }else{
            i++;
         }
      }
   }
   pointsType = temp1;
   Points = temp;
}