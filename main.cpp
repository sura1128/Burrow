#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;
GLuint texSet[45];
bool MAGIC = false;

// You may add more functions here if you like
// ========================================================================


// ========================================================================

// SHAPES USED = plane, cuboid, cylinder, quad, circle and sphere
void drawPlane(GLuint texSet) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet);	

	glPushMatrix();	
	glBegin(GL_POLYGON);
		
		glTexCoord2d(0.0, 0.0);
		glVertex3f(2, 1, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex3f(-2, 1, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-2, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(2, 0, 0);
	
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawCuboid(bool isExtended) {
	drawPlane(texSet[37]);
	glPushMatrix();
		glTranslatef(-2, 0, 2);
		glRotatef(90, 0, 1, 0);
		drawPlane(texSet[37]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2, 0, 2);
		glRotatef(90, 0, 1, 0);
		drawPlane(texSet[37]);
	glPopMatrix();
	if (isExtended == false) {
		glPushMatrix();
		glTranslatef(0, 0, 4);
		drawPlane(texSet[37]);
		glPopMatrix();
	}
	
}

void drawCylinder(float height, float radius, float degrees,GLuint texSet) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet);

	glColor3f(0, 0, 0);
	GLfloat x, y, z;
	float s, t;


	for (t = 0.0; t<1.0; t += 0.05)
		for (s = 0.0; s<1.0; s += 0.05)
		{

			glBegin(GL_POLYGON);
				
			x = radius*cos(degrees*s);
			y = radius*sin(degrees*s);
				z = t*height;
				glTexCoord2f(s, t);
				glVertex3f(x,y,z);

				x = radius*cos(degrees*(s + 0.05));
				y = radius*sin(degrees*(s + 0.05));
				z = t*height;
				glTexCoord2f(s + 0.05, t);
				glVertex3f(x, y, z);

				x = radius*cos(degrees*(s + 0.05));
				y = radius*sin(degrees*(s + 0.05));
				z = (t+0.05)*height;
				glTexCoord2f(s + 0.05, t + 0.05);
				glVertex3f(x, y, z);

				x = radius*cos(degrees*s);
				y = radius*sin(degrees*s);
				z = (t + 0.05)*height;
				glTexCoord2f(s, t + 0.05);
				glVertex3f(x, y, z);

			glEnd();
		}
	glDisable(GL_TEXTURE_2D);
}


void drawQuad(bool isExtended, GLuint texSet) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet);


	glPushMatrix();
	glTranslatef(0, 2, 1);
	glRotatef(45, 1, 0, 0);

	if (isExtended == false) {
		glBegin(GL_QUADS);
		glTexCoord2d(0.25, 0.0);
		glVertex3f(1, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(2.45, -2, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-2.45, -2, 0);

		glTexCoord2d(0.75, 0.0);
		glVertex3f(-1, 0, 0);
		glEnd();
	}
	else {
		glBegin(GL_QUADS);
		glTexCoord2d(0.25, 0.0);
		glVertex3f(1, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(1, -2, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-2.45, -2, 0);

		glTexCoord2d(0.75, 0.0);
		glVertex3f(-1, 0, 0);
		glEnd();
	}	

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawCircle(float degrees, GLuint texSet) {
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texSet);	

	glPushMatrix();
	float tx, ty;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		float rad = i*M_PI/ 180;
		tx = cos(rad)*0.5 + 0.5;
		ty = sin(rad)*0.5 + 0.5;
		
		glTexCoord2d(tx, ty);
		glVertex2f(cos(rad) * 5, sin(rad) * 5);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawSphere(double r, bool isSmoke, GLuint texSet)
{	
	glPushMatrix();
	
	if (isSmoke) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.658824, 0.658824, 0.658824, 0.9);
	}
	else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texSet);
	}
	

    int i,j;
	int n = 10;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++) {
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
				glTexCoord2d(0.0, 0.0);
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glTexCoord2d(0.0, 1.0);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glTexCoord2d(1.0, 1.0);
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glTexCoord2d(1.0, 0.0);
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}
	if (!isSmoke) {
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();

}

// HOUSE PARTS CREATED: Roof, floor, window, door, chimney, stilts, extended roof, extended house, extended window, extended floor

void drawRoof() {
	
	drawQuad(false, texSet[18]);
	glPushMatrix();
		glTranslatef(-2, 0, 2);
		glRotatef(90, 0, 1, 0);
		glColor3f(1, 0, 1);
		drawQuad(false, texSet[18]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0, 4);
		glRotatef(180, 0, 1, 0);
		glColor3f(0, 0, 1);
		drawQuad(false, texSet[18]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2, 0, 2);
	glRotatef(-90, 0, 1, 0);	
	drawQuad(false, texSet[18]);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[18]);
		
		glTranslatef(0, 2, 1);
		glBegin(GL_QUADS);

		glTexCoord2d(1.0, 0.0);
		glVertex3f(-1, 0, 0);

		glTexCoord2d(0.0, 0.0);
		glVertex3f(1, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(1, 0, 2);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-1, 0, 2);

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawFloor(GLuint texSet) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet);

	glPushMatrix();
	glBegin(GL_QUADS);

		glTexCoord2d(0.0, 0.0);
		glVertex3f(-1, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(1, 0, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(1, 0, 2);

		glTexCoord2d(1.0, 0.0);
		glVertex3f(-1, 0, 2);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void drawWindow(GLuint texSetW) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSetW);

	glPushMatrix();
	glTranslatef(0, 6.5, 3.01);
	glBegin(GL_POLYGON);	

		glTexCoord2d(0.1, 0.0);
		glVertex3f(0.5, 1, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex3f(-0.5, 1, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-0.5, 0, 0);

		glTexCoord2d(0.1, 1.0);
		glVertex3f(0.5, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7, 3.01);
	drawCylinder(0.2, 0.7, M_PI,texSet[34]);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawDoor(GLuint texSet) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet);

	glPushMatrix();
	glBegin(GL_POLYGON);

		glTexCoord2d(0.0, 0.0);
		glVertex3f(0.5, 1, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex3f(-0.5, 1, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex3f(-0.5, 0, 0);

		glTexCoord2d(0.0, 1.0);
		glVertex3f(0.5, 0, 0);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawChimney() {
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawCylinder(1.5,0.2, 2*M_PI,texSet[34]);
	glPopMatrix();
}

void drawStilts(float length) {	

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.7,-1.9,-6.75);
	drawCylinder(length, 0.06, 2*M_PI,texSet[34]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-0.7, -1.9, -6.75);
	drawCylinder(length, 0.06, 2*M_PI,texSet[34]);
	glPopMatrix();	

}

void drawBaseHouse() {
	drawCuboid(false);
	drawRoof();

	glPushMatrix();
	glTranslatef(0, 0, 4.1);
	glScalef(0.8, 0.8, 0.8);
	drawDoor(texSet[41]);
	glPopMatrix();
}

void drawTopHouse(bool isStilts, bool isChimney) {
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 4, 1);
		glScalef(0.75, 4, 0.5);
		drawCuboid(false);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 7.5, 1);
		glScalef(0.75, 0.75, 0.5);
		drawRoof();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 4, 1);
		glScalef(1.5, 1, 1);
		drawFloor(texSet[37]);
	glPopMatrix();
	
	glPushMatrix();
	drawWindow(texSet[40]);
	glPushMatrix();
	glTranslatef(-1.5, 0, 2);
	glRotatef(90, 0, 1, 0);
	drawWindow(texSet[40]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 0, 2);
	glRotatef(-90, 0, 1, 0);
	drawWindow(texSet[40]);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();

	if (isStilts) {
		glTranslatef(0, -2.7, 4.8);
		drawStilts(3.2);
	}
	glPopMatrix();

	glPushMatrix();
	if (isChimney) {
		glTranslatef(0, 9.9, 1.3);
		drawChimney();
	}
	glPopMatrix();

	glPopMatrix();
}

void drawBackHouse() {
	glPushMatrix();
	glTranslatef(0, -6, -3.5);
	glScalef(1, 1.2, 1);
	drawTopHouse(false, false);
	glPopMatrix();
}

void drawExtendedRoof() {
	glPushMatrix();
	drawQuad(false, texSet[18]);
	glPushMatrix(); //left
		glTranslatef(-3, 1, 2);
		glRotatef(-90, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		drawQuad(false, texSet[18]);
	glPopMatrix();
	glPushMatrix();   //right
		glTranslatef(2, 0, 2);
		glRotatef(-90, 0, 1, 0);
		drawQuad(false, texSet[18]);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texSet[18]);

		glTranslatef(0, 2, 1);
		glBegin(GL_QUADS);

			glTexCoord2d(1.0, 0.0);
			glVertex3f(-1, 0, 0);

			glTexCoord2d(0.0, 0.0);
			glVertex3f(1, 0, 0);

			glTexCoord2d(0.0, 1.0);
			glVertex3f(1, 0, 2);

			glTexCoord2d(1.0, 1.0);
			glVertex3f(-1, 0, 2);

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawExtendedHouse(bool isStilts) {
	glPushMatrix();
	glTranslatef(0, 0, 0.8);
	glPushMatrix();
		glTranslatef(0, 7.6, -2);
		glScalef(0.5, 0.75, 0.55);
		drawCuboid(true);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 8, -2);
		glScalef(0.5, 0.5, 0.75);
		drawExtendedRoof();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 7.7, -2);
		glScalef(1, 1, 1.1);
		drawFloor(texSet[37]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 3.7, -0.4);
	glScalef(0.8, 0.6, 0.8);
	drawWindow(texSet[40]);
	glPopMatrix();

	if (isStilts) {
		glPushMatrix();
		glTranslatef(0, 1, 0);
		drawStilts(1.75);
		glPopMatrix();
	}

	glPopMatrix();
}

void drawExtendedWindow() {
	glPushMatrix();
	glTranslatef(0, -4.75, 3.5);
	glRotatef(180, 0, 1, 0);
	glScalef(0.4, 0.75, 0.4);
	drawExtendedHouse(false);
	glPopMatrix();
}

void drawExtendedFloor() {
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 4.8, 0.8);
	glScalef(0.5, 0.45, 0.75);
	drawBackHouse();
	glPopMatrix();
}

// Environment: Pen (gate of house), grove of trees, lake, smoke

void drawPen() {
	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-5, 0, -1);
		glScalef(0.4, 0.5, 1);	
		drawPlane(texSet[34]);   //texset[34] is a type of wood
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glTranslatef(5, 0, -1);
		glScalef(0.4, 0.5, 1);
		drawPlane(texSet[34]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.6, 0, 5.8);
		glScalef(0.2, 0.5, 1);
		drawPlane(texSet[34]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.6, 0, 5.8);
		glScalef(0.2, 0.5, 1);
		drawPlane(texSet[34]);
	glPopMatrix();
}
void drawLeaves() {
	glPushMatrix();
	glScalef(1.5, 1.5, 1.5);
	glRotatef(90, 1, 0, 0);
	drawSphere(0.5,false,texSet[43]);
	glPopMatrix();
}

void drawLake() {
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glScalef(0.3, 0.3, 0.3);
		glTranslatef(11, 0, -0.1);
		drawCircle(M_PI, texSet[42]);
	glPopMatrix();
	
	glPushMatrix();
	glPushMatrix();
	glTranslatef(3.5, 0, 0);
	glRotatef(90, 0, 0, 1);	
	float angle = 10;
	for (int i = 0; i < 36; i++) {
		glRotatef(angle, 1, 0, 0);
		glPushMatrix();
		glTranslatef(0.1, 1.5, 0);
		glScalef(0.2, 0.2, 0.2);
		drawLeaves();
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();
}


void drawTree() {
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawCylinder(1.5, 0.1, 2 * M_PI,texSet[44]);
	glPopMatrix();
	drawLeaves();
}

void drawGrove() {
	glPushMatrix();
	glTranslatef(-4.5, 1.5, 4);
	drawTree();
	for (int i = 0; i < 5; i++) {
		glTranslatef(0, 0, -1.5);
		drawTree();
	}	
	glPopMatrix();
}

void drawSmoke() {
	glPushMatrix();
	glScalef(1, 0.6, 1);
	glTranslatef(0, 7, -0.1);
	glPushMatrix();
	glTranslatef(-0.5, 12.3, 0);
	drawSphere(0.3, true, texSet[43]);
	glTranslatef(0.1, 0.2, 0);
	drawSphere(0.3, true, texSet[43]);
	glTranslatef(0.1, -0.5, 0);
	drawSphere(0.3, true, texSet[43]);
	glTranslatef(0.1, 0, 0);
	drawSphere(0.3, true, texSet[43]);
	glTranslatef(0.1, 0, 0);
	drawSphere(0.2, true, texSet[43]);
	glTranslatef(0.1,0.1,0);
	drawSphere(0.3,true, texSet[43]);
	glTranslatef(0.1,-0.3,0);
	glScalef(0.8, 0.8, 0.8);
	drawSphere(0.3,true, texSet[43]);

	for (int i = 0; i < 4; i++) {
		glRotatef(-5, 0, 0, 1);
		glTranslatef(0, -0.3, 0);
		glScalef(0.8, 0.8, 0.8);
		drawSphere(0.3, true, texSet[43]);
	}
	glPopMatrix();
	glPopMatrix();
}

// Houses which appear on toggling 'M' key
void animatedHouse() {
	if (MAGIC == true) {
		glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 7.7, -3);
			glScalef(1.2, 1.2, 1.2);
			drawExtendedWindow();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0, 1, 0);
			glTranslatef(-0.5, 4.5, -2.5);
			glScalef(1.2, 1.2, 1.2);
			drawExtendedWindow();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90, 0, 1, 0);
			glTranslatef(0.5, 4.5, -2.5);
			glScalef(1.2, 1.2, 1.2);
			drawExtendedWindow();
		glPopMatrix();
	glPopMatrix();
	}	
}

// The Main House

void drawBurrow() {	
	glPushMatrix();
	glTranslatef(0, 0, -1.5);
		drawBaseHouse();
		drawTopHouse(true,true);
		drawBackHouse();
		drawExtendedHouse(true);
		drawExtendedWindow();
		drawExtendedFloor();
		drawPen();
	glPopMatrix();

	drawLake();
	glPushMatrix();
		drawGrove();
		glTranslatef(0, 0, -9);
		glRotatef(90, 0, 1, 0);
		drawGrove();
	glPopMatrix();
	drawSmoke();
	animatedHouse(); // MAGIC HOUSE

}




void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -5:5
	//y: >= 0
	//z: -5:5

	// Your main drawing code goes here
	// =========================================
	drawBurrow();
	// floor plane (you may remove this)

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texSet[9]);

	glBegin(GL_POLYGON);
		glColor3f(0.3, 0.73, 0.1);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(-5, -0.02, -5);
		glTexCoord2d(0.0, 0);
		glVertex3f( 5, -0.02, -5);
		glTexCoord2d(0.0, 1.0);
		glVertex3f( 5, -0.02,  5);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(-5, -0.02,  5);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	

	// =========================================
}

// ********** You do not need to edit any code beyond this point **********

// The following code supports loading textures from disk
// ========================================================================

GLuint loadMyTextures(char *filename)
{
	GLuint myTexture;
	FILE * file;
	unsigned char *tex, *tex2;

	// texture data
	int width = 256;
	int height = 256; 

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	file = fopen(filename, "rb");

	if (file == NULL)
		cout << "Error! Missing texture!\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}
// ========================================================================

// The following code is used to support rotation of the scene with your mouse
// ========================================================================
bool isDraggingLeft = false;
bool isDraggingRight = false;
int prevX = 0, prevY = 0;
int curX = 0, curY = 0;
float angle1 = M_PI, angle2 = -1;	// angles are in radians
float dist = 12.0;
float lookY = 5;
float aspectRatio = 1.0;

void LMBDragged(float dx, float dy) {
	angle1 -= ((float)dx) / 150.0;
	angle2 += ((float)dy) / 150.0;

	if (angle1 < 0)	angle1 += 2 * M_PI;
	else if (angle1 > 2 * M_PI) angle1 -= 2 * M_PI;
	if (angle2 < 0)	angle2 += 2 * M_PI;
	else if (angle2 > 2 * M_PI) angle2 -= 2 * M_PI;
}

void RMBDragged(float dx, float dy) {
	dist += ((float)dx) / 100.0;
	lookY += ((float)dy) / 50.0;
}

void computeCameraPosition() {
	float camX = dist * sin(angle1) * sin(angle2);
	float camY = dist * cos(angle2);
	float camZ = dist * cos(angle1) * sin(angle2);

	float upVectorY = 1.0;
	if (angle2 >= 0 && angle2 < M_PI) {
		upVectorY = -1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	gluLookAt(camX, camY+lookY, camZ, 0, lookY, 0, 0, upVectorY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetCamera() {
	angle1 = M_PI;
	angle2 = -1;
	lookY = 5;
	dist = 15.0;
}
// ========================================================================


// The following code is the usual stuff you give OpenGL
// ========================================================================

void init(void)
{
	glClearColor (0.73, 0.90, 0.96, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);

	texSet[0] = loadMyTextures("brick1.bmp");
	texSet[1] = loadMyTextures("brick2.bmp");
	texSet[2] = loadMyTextures("brick3.bmp");
	texSet[3] = loadMyTextures("brick4.bmp");
	texSet[4] = loadMyTextures("door1.bmp");
	texSet[5] = loadMyTextures("door2.bmp");
	texSet[6] = loadMyTextures("flower1.bmp");
	texSet[7] = loadMyTextures("flower2.bmp");
	texSet[8] = loadMyTextures("flower3.bmp");
	texSet[9] = loadMyTextures("grass1.bmp");

	texSet[10] = loadMyTextures("grass2.bmp");
	texSet[11] = loadMyTextures("leaves1.bmp");
	texSet[12] = loadMyTextures("leaves2.bmp");
	texSet[13] = loadMyTextures("roof1.bmp");
	texSet[14] = loadMyTextures("roof2.bmp");
	texSet[15] = loadMyTextures("roof3.bmp");
	texSet[16] = loadMyTextures("roof4.bmp");
	texSet[17] = loadMyTextures("roof5.bmp");
	texSet[18] = loadMyTextures("roof6.bmp");
	texSet[19] = loadMyTextures("stone1.bmp");

	texSet[20] = loadMyTextures("stone2.bmp");
	texSet[21] = loadMyTextures("tile1.bmp");
	texSet[22] = loadMyTextures("tile2.bmp");
	texSet[23] = loadMyTextures("tile3.bmp");
	texSet[24] = loadMyTextures("tile4.bmp");
	texSet[25] = loadMyTextures("tile5.bmp");
	texSet[26] = loadMyTextures("tile6.bmp");
	texSet[27] = loadMyTextures("water0.bmp");
	texSet[28] = loadMyTextures("window2.bmp");
	texSet[29] = loadMyTextures("window3.bmp");

	texSet[30] = loadMyTextures("window4.bmp");
	texSet[31] = loadMyTextures("window5.bmp");
	texSet[32] = loadMyTextures("window6.bmp");
	texSet[33] = loadMyTextures("wood1.bmp");
	texSet[34] = loadMyTextures("wood2.bmp");
	texSet[35] = loadMyTextures("wood3.bmp");
	texSet[36] = loadMyTextures("wood4.bmp");
	texSet[37] = loadMyTextures("wood5.bmp");
	texSet[38] = loadMyTextures("wood6.bmp");
	texSet[39] = loadMyTextures("wood7.bmp");

	texSet[40] = loadMyTextures("custom/WindowWood.bmp");  //Custom Texture
	texSet[41] = loadMyTextures("custom/door3.bmp");
	texSet[42] = loadMyTextures("custom/river.bmp");
	texSet[43] = loadMyTextures("custom/bush.bmp");
	texSet[44] = loadMyTextures("custom/bark.bmp");

	cout << "Texture loading complete" << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1.0, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspectRatio = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int startTime=glutGet(GLUT_ELAPSED_TIME);
	int counter = 1;
	
	glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawMyHouse(texSet);
	
	int endTime=glutGet(GLUT_ELAPSED_TIME);
	// cout<<"Frame Rate: "<<(float)1000/(endTime-startTime)<<"\n";
	glFlush();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)
{

	if(!isDraggingLeft && button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		isDraggingLeft = true;
		isDraggingRight = false;
		prevX = x;
		prevY = y;
	}

	else if(button == GLUT_LEFT_BUTTON && state==GLUT_UP)
	{		
		isDraggingLeft = false;
		prevX = 0;
		prevY = 0;
	}

	if (!isDraggingRight && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = false;
		isDraggingRight = true;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isDraggingRight = false;
		prevX = 0;
		prevY = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		resetCamera();
		computeCameraPosition();
		glutPostRedisplay();
	}

}

void mouseMotion(int x, int y) {
	if (isDraggingLeft) {
		float dx = x - prevX;
		float dy = y - prevY;

		LMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}

	if (isDraggingRight) {
		float dx = x - prevX;
		float dy = y - prevY;

		RMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		dist -= 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 's' || key == 'S') {
		dist += 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}
	
	if (key == 27) {
		exit(0);
	}

	if (key == 'm' || key == 'M') {
		MAGIC = !MAGIC;
		glutPostRedisplay();		
	}
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 5\n\n";
	cout << "+++++CONTROLS+++++++\n\n";
	cout << "Left Click and Drag: Rotate camera\n";
	cout << "Right Click and Drag:\n";
	cout << "\tVertical: Change camera elevation\n";
	cout << "\tHorizontal: Zoom in and out\n";
	cout << "Middle Click: Reset camera\n";
	cout << "W: Zoom In\n";
	cout << "S: Zoom Out\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);

	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

// ========================================================================

