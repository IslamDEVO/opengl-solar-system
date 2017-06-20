#include<iostream>
#include<math.h>
#include <gl/glut.h>
using namespace std;

#pragma region Variables
GLfloat numPlanets;
GLfloat numMoons;
// Translation & Rotation amounts of the Planets
GLfloat xPlanets = 2.0;
GLfloat rPlanets = 45;
// Translation & Rotation amounts of the Moons
GLfloat xMoons = 0.5;
GLfloat rMoons = 45;
// Rotation amounts of the plane about x_axis and y_axis
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
#pragma endregion

#pragma region Declare Methods
void RenderScene(void);
void SetupRC(void);
void ChangeSize(GLsizei w, GLsizei h);
void idleFunc(void);
void SpecialKeys(int key, int x, int y);
#pragma endregion

// Main program entry point
int main(int argc, char* argv[])
{
	cout<<"Enter number of planets to draw && The Max is 8 planets \n ";
	cin>>numPlanets;
	cout<<"------------------------------- \n ";
	cout<<"Enter number of moons to draw && The Max is 8 moons\n ";
	cin>>numMoons;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow(" Assignment 2 ");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutIdleFunc(idleFunc);
	glutSpecialFunc(SpecialKeys);

	glutMainLoop();
	return 0;
}

void RenderScene(void){

#pragma region Draw sun
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.8,0.3);
	glutWireSphere(1.0, 20, 16);   /* draw sun */
    glPushMatrix();	//1 push
#pragma endregion

	#pragma region Draw Planets and Moons
	for(int j=0 , f=-45 ; j<numPlanets ; j++)
	{
	glPushMatrix();
	glColor3f(0.0,0.0,0.8);	// blue
	glRotatef (rPlanets+f, 0.0, 1.0, 0.0);
	glTranslatef (2.0, 0.0, 0.0);
	glutWireSphere(0.35, 10, 8);    /* draw smaller planet */
	#pragma region Draw Moons
	for(int i=0 , r=-45 ; i<numMoons ; i++ )
	{
	glPushMatrix();
	glRotatef (rMoons+r, 0.0, 1.0, 0.0);
	glTranslatef (0.5, 0.0, 0.0);
	glColor3f(1.0,1.0,1.0);
	glutWireSphere(0.05, 10, 8);		/* draw smaller moon */
	glPopMatrix();
	r +=45;
	}
	#pragma endregion
	glPopMatrix();
	f +=45;
	}
	#pragma endregion
	
	glPopMatrix();

   glPopMatrix();	// 1 pop
   
   glutSwapBuffers();

}

// Set up the rendering state
void SetupRC(void) {
	// Set clear color to blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Called by GLUT library when the window has chanaged size
void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat aspectRatio;
	// Prevent a divide by zero
	if(h == 0) h = 1;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);
	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho (-5.0, 5.0, -5 / aspectRatio, 5.0 / aspectRatio,5.0, -5.0);
	else
		glOrtho (-5.0 * aspectRatio, 5.0 * aspectRatio,-5.0, 5.0, 5.0, -5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idleFunc(void)
{
    // idle event call back in animation , here we increase the values and redisply .
    rPlanets += 0.10;
    rMoons += 0.50;

	RenderScene();
} 

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP) xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)  xRot += 5.0f;
	if(key == GLUT_KEY_LEFT) yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT) yRot += 5.0f;

	if(xRot > 356.0f) xRot = 0.0f;
	if(xRot < -1.0f) xRot = 355.0f;
	if(yRot > 356.0f) yRot = 0.0f;
	if(yRot < -1.0f) yRot = 355.0f;

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Refresh the Window
	glutPostRedisplay();
}

