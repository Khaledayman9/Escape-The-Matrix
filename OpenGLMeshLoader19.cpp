#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>
#include <Windows.h>
#include <Mmsystem.h>
#include <playsoundapi.h>
#include <dsound.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;


#define SPACEBAR 32

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex1;
GLuint tex2;
GLuint texEarthID;
char title[] = "Escape the Matrix";

GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.001;
GLdouble zFar = 500;

GLboolean frontView = false;
GLboolean backView = false;
GLboolean reachHigh = false;
GLboolean inAir = false;

GLdouble translateCam = 0;
float playerX = 0;
float playerZ = 0;
float playerY = 0;
float rotateAngel = 0.01;
float Jumpboost = 0;
float hovered = 0;

float value = 0;
float incremetVal = 0.6;
float playerRotate = 0;
bool playerRot = false;
int playerHealth = 100;
int hovercounter = 0;
bool victory2 = false;
bool inbetween = false;
bool generatedAidkits = false;
bool generatedTimes = false;
bool generatedSpeeds = false;
bool generatedHearts = false;
bool generatedJumps = false;
bool setLives = false;


bool cameraFixed = false;
bool endOfGame = false;
bool victory1 = false;
bool extralife = false;
bool flagleft1 = false;
bool flagright1 = false;
bool flagleft2 = false;
bool flagright2 = false;
bool flagleft3 = false;
bool flagright3 = false;
bool flagleft4 = false;
bool flagright4 = false;
bool flagleft5 = false;
bool flagright5 = false;
bool scene2 = false;

float sz1 = 9;
float sz2 = -9;
float sz3 = -9;
float sz4 = 9;
float sz5 = -9;

float fireball1 = -10;
float fireball2 = -10;
float fireball3 = -10;
float threshhold = 50;
float moveBox = 0;
float moveBox2 = 0;
int choice = 0;
int choice2 = 0;

int counter1 = 0;
int counter2 = 0;
int time1 = 0;
int time2 = 0;
float playerSpeed = 0;
int noOfLives = 1;

float hearts[2][3] = {};
float bandages[3][3] = {};
float speeds[4][3] = {};
float jumps[3][3] = {};
float times[2][3] = {};


bool firstperson = false;
bool thirdperson = false;
int light = 0;

int playerFrame = 5;
int frequency = 10;
int frameDirection = 1;
bool moving = false;
float rotateObject = 0;


int light_alt1 = 0;
int light_alt2 = 0;
int light_alt3 = 0;

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};



Vector Eye(20, 7, 0);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

vector<Model_3DS> model_player;
Model_3DS model_idleplayer;
Model_3DS model_clock;
Model_3DS model_fireball;
Model_3DS model_speed;
Model_3DS model_aidkit;
Model_3DS model_jump;
Model_3DS model_heart;
Model_3DS model_spikes;
Model_3DS model_door;
Model_3DS model_box;
Model_3DS model_saw;
Model_3DS model_cannon;
Model_3DS model_skyscraper;
Model_3DS model_fbuilding;
Model_3DS model_lightlamp;

// Textures
GLTexture tex_ground;
GLTexture tex_street;
GLTexture tex_newstreet;
GLTexture tex_newground;




//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void displayText(int x, int y, int z, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void displayHealth() {
	char* health[1000];
	sprintf((char*)health, "Health: %i", playerHealth);
	displayText(0, 7, -10, (char*)health);
}

void displaySpeed() {
	char* speed[1000];
	float displayNum = 1 + playerSpeed;
	sprintf((char*)speed, "Speed: x%f", displayNum);
	displayText(0, 5, -10, (char*)speed);
}


void displayTime1() {
	char* time[1000];
	sprintf((char*)time, "Time: %i", time1);
	displayText(0, 6, -10, (char*)time);
}

void displayTime2() {
	char* time[1000];
	sprintf((char*)time, "Time: %i", time2);
	displayText(0, 6, -10, (char*)time);
}

void displayLives() {
	char* time[1000];
	int x = noOfLives - 1;
	sprintf((char*)time, "Extra Lives: %i", x);
	displayText(0, 5, -10, (char*)time);
}

void displayJump() {
	char* time[1000];
	float displayNum = 1 + Jumpboost;
	sprintf((char*)time, "Jump boost: %f %", displayNum);
	displayText(0, 4, -10, (char*)time);
}


//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

void RenderLaserBeam(double x, double y, double z)
{
	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glTranslatef(x, y, z);
	glScaled(0.5, 1.4, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(x, y, z);
	glRotated(90, 0, 0, 1);
	GLUquadricObj* quadraticObj1 = gluNewQuadric();
	gluCylinder(quadraticObj1, 0.04, 0.04, 20, 20, 20);
	glPopMatrix();
}

void drawArrow(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glColor3f(0.0, 0.0f, 1.0f);
	glTranslatef(x, y - 0.2, z);
	glScaled(0.5, 1.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0f, 1.0f);
	glTranslatef(x, y, z);
	glRotatef(-90, 1, 0, 0);
	glScalef(10, 10, 10);
	glutSolidCone(0.05, 0.1, 20, 20);
	glPopMatrix();
}


void RenderGravel()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-600, 0.25, -10);
	glTexCoord2f(5, 0);
	glVertex3f(600, 0.25, -10);
	glTexCoord2f(5, 5);
	glVertex3f(600, 0.25, 10);
	glTexCoord2f(0, 5);
	glVertex3f(-600, 0.25, 10);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}



void RenderStreet()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_street.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-600, 0, -600);
	glTexCoord2f(5, 0);
	glVertex3f(600, 0, -600);
	glTexCoord2f(5, 5);
	glVertex3f(600, 0, 600);
	glTexCoord2f(0, 5);
	glVertex3f(-600, 0, 600);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}
void RenderNewStreet()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_newstreet.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-600, 0.25, -10);
	glTexCoord2f(5, 0);
	glVertex3f(600, 0.25, -10);
	glTexCoord2f(5, 5);
	glVertex3f(600, 0.25, 10);
	glTexCoord2f(0, 5);
	glVertex3f(-600, 0.25, 10);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void RenderNewGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_newground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-600, 0, -600);
	glTexCoord2f(5, 0);
	glVertex3f(600, 0, -600);
	glTexCoord2f(5, 5);
	glVertex3f(600, 0, 600);
	glTexCoord2f(0, 5);
	glVertex3f(-600, 0, 600);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}



void RenderOneSpike(double x, double z, double rotAngle, double rotx, double rotz, double base = 0.10, double height = 1)
{
	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, 0);
	glutSolidCone(base, height, 50, 50);
	glPopMatrix();
}

void RenderSpikes(int x, int z)
{
	glPushMatrix();
	glTranslatef(x, 0, z);
	//base
	RenderOneSpike(0, 0, 0, 1, 0);
	RenderOneSpike(0.5, 0, 0, 1, 0);
	RenderOneSpike(1, 0, 0, 1, 0);

	RenderOneSpike(0, 0.5, 0, 1, 0);
	RenderOneSpike(0.5, 0.5, 0, 1, 0);
	RenderOneSpike(1, 0.5, 0, 1, 0);

	RenderOneSpike(0, 1, 0, 1, 0);
	RenderOneSpike(0.5, 1, 0, 1, 0);
	RenderOneSpike(1, 1, 0, 1, 0);

	RenderOneSpike(0, -0.5, 0, 1, 0);
	RenderOneSpike(0.5, -0.5, 0, 1, 0);
	RenderOneSpike(1, -0.5, 0, 1, 0);

	RenderOneSpike(0, -1, 0, 1, 0);
	RenderOneSpike(0.5, -1, 0, -1, 0);
	RenderOneSpike(1, -1, 0, -1, 0);
	glPopMatrix();
}




float generateRandom1(int upper, int lower) {
	int diff = upper - lower;
	int numberZ = (rand() % diff) + lower;
	float x = (float)(numberZ)+1;
	return x;
}


float generateRandom2(int upper, int lower) {
	int diff = upper - lower;
	int numberZ = (rand() % diff) + lower;
	float x = (float)(numberZ);
	return x;
}


float generateRandom3(int upper, int lower) {
	int diff = upper - lower;
	int numberZ = (rand() % diff) + lower;
	float x = (float)(numberZ)+-1;
	return x;
}


float generateRandom4(int upper, int lower) {
	int diff = upper - lower;
	int numberZ = (rand() % diff) + lower;
	float x = (float)(numberZ)+-2;
	return x;
}

float generateRandom5(int upper, int lower) {
	int diff = upper - lower;
	int numberZ = (rand() % diff) + lower;
	float x = (float)(numberZ)+-2;
	return x;
}

void generateAidKits() {

	for (int i = 0; i < 3; i++) {
		float upperX = -30;
		float lowerX = -410;
		float upperZ = 7;
		float lowerZ = -7;
		float x = generateRandom1(upperX, lowerX);
		float z = generateRandom1(upperZ, lowerZ);
		bandages[i][0] = x;
		bandages[i][1] = 0.65;
		bandages[i][2] = z;
	}
	generatedAidkits = true;
}

void generateSpeeds() {
	for (int i = 0; i < 4; i++) {
		float upperX = -30;
		float lowerX = -410;
		float upperZ = 7;
		float lowerZ = -7;
		float x = generateRandom2(upperX, lowerX);
		float z = generateRandom2(upperZ, lowerZ);
		speeds[i][0] = x;
		speeds[i][1] = 0.65;
		speeds[i][2] = z;
	}
	generatedSpeeds = true;
}

void generateTimes() {
	for (int i = 0; i < 2; i++) {
		float upperX = -40;
		float lowerX = -410;
		float upperZ = 7;
		float lowerZ = -7;
		float x = generateRandom3(upperX, lowerX);
		float z = generateRandom3(upperZ, lowerZ);
		times[i][0] = x;
		times[i][1] = 0.65;
		times[i][2] = z;
	}
	generatedTimes = true;
}

void generateHearts() {
	for (int i = 0; i < 2; i++) {
		float upperX = -200;
		float lowerX = -400;
		float upperZ = 7;
		float lowerZ = -7;
		float x = generateRandom4(upperX, lowerX);
		float z = generateRandom4(upperZ, lowerZ);
		hearts[i][0] = x;
		hearts[i][1] = 1;
		hearts[i][2] = z;
	}
	generatedHearts= true;
}

void generateJumps() {
	for (int i = 0; i < 3; i++) {
		float upperX = -40;
		float lowerX = -310;
		float upperZ = 7;
		float lowerZ = -7;
		float x = generateRandom5(upperX, lowerX);
		float z = generateRandom5(upperZ, lowerZ);
		jumps[i][0] = x;
		jumps[i][1] = 1;
		jumps[i][2] = z;
	}
	generatedJumps = true;
}



void drawSpikeLine(float x) {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, 0);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, -2);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, 2);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, -4);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, 4);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, -6);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	RenderSpikes(-40 + x, 6);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void setCamera() {
	Eye.x = 1000;
	Eye.y = 1000;
	Eye.z = 1000;
	cameraFixed = true;
}


void displayGameOver() {
	char* endScore[50];
	sprintf((char*)endScore, "GAME OVER! You LOST!");
	displayText(0, -20, 20, (char*)endScore);

	char* endText[50];
	sprintf((char*)endText, "Press R to try again");
	displayText(0, -40, 20, (char*)endText);
};

void displayFirstWin() {
	char* endScore[50];
	sprintf((char*)endScore, "You completed the first chapter,");
	displayText(0, -20, 20, (char*)endScore);

	char* endText[50];
	sprintf((char*)endText, "Press N to go to the next chapter");
	displayText(0, -40, 20, (char*)endText);
};

void displayLiveLost() {
	if (noOfLives > 1) {
		char* endScore[50];
		sprintf((char*)endScore, "You Lost one live, You still have %i lives. Good Luck ;)", noOfLives);
		displayText(0, -20, 0, (char*)endScore);
	}
	else {
		char* endScore[50];
		sprintf((char*)endScore, "This is your last chance, YOU GOT THIS ^_^");
		displayText(0, -20, 0, (char*)endScore);
	}
	char* endText[50];
	sprintf((char*)endText, "Press M to try again.");
	displayText(0, -40, 0, (char*)endText);
}

void displayWin() {
	int result = time1 + time2;
	char* endScore[50];
	sprintf((char*)endScore, "YOU HAVE ESCAPED THE MATRIX !!! With total time record equal to : %i seconds.", result);
	displayText(-200, -120, -50, (char*)endScore);

	char* endText[50];
	sprintf((char*)endText, "Press R to try beating that record :P");
	displayText(-200, -140, -50, (char*)endText);
}



void sawLine(float x) {
	glPushMatrix();
	glTranslatef(x, 0, -8);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, -6);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, -4);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, -2);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, 2);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, 4);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, 6);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, 8);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(-90, 0, 1, 0);
	model_saw.Draw();
	glPopMatrix();

}
void displayBegin1() {
	char* endScore[50];
	sprintf((char*)endScore, "Objective: Get to the door before 25 Seconds !!", endScore);
	displayText(0, 5, 5, (char*)endScore);
}

void displayBegin2() {
	char* endScore[50];
	sprintf((char*)endScore, "Objective: Get to the door before 35 Seconds !!", endScore);
	displayText(0, 5, 5, (char*)endScore);
}

void setNoOfLives() {
	noOfLives--;
	setLives = true;
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (light == 0) {
		GLfloat lightIntensity[] = { 1.0, 1.0 ,1.0, 1.0f };
		GLfloat lightPosition[] = { 0.0f,0.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}

	if (light == 1) {
		GLfloat lightIntensity[] = { 1.0, 0.2 ,0.2, 1.0f };
		GLfloat lightPosition[] = { -20.0f, 0.0f,0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}
	if (light == 2) {
		GLfloat lightIntensity[] = { 0.2, 1.0 ,0.2, 1.0f };
		GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}
	if (light == 3) {
		GLfloat lightIntensity[] = { 1.0, 1.0 ,0.5, 0.5f };
		GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}
	if (light == 4) {
		GLfloat lightIntensity[] = { 1.0, 0.5 ,1, 0.5 };
		GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}
	if (light == 5) {
		GLfloat lightIntensity[] = { 0.2, 0.2 ,1, 1 };
		GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	}
	if (light == 6) {
		if (light_alt2 == 0) {
			GLfloat lightIntensity[] = { 1.0, 0.2 ,0.2, 1.0f };
			GLfloat lightPosition[] = { -20.0f, 0.0f,0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt2 == 1) {
			GLfloat lightIntensity[] = { 0.2, 1.0 ,0.2, 1.0f };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt2 == 2) {
			GLfloat lightIntensity[] = { 1.0, 1.0 ,0.5, 0.5f };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt2 == 3) {
			GLfloat lightIntensity[] = { 1.0, 0.5 ,1, 0.5 };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt2 == 4) {
			GLfloat lightIntensity[] = { 0.2, 0.2 ,1, 1 };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
	}

	if (light == 7) {
		if (light_alt3 >= 0 && light_alt3 <= 5) {
			GLfloat lightIntensity[] = { 1.0, 0.2 ,0.2, 1.0f };
			GLfloat lightPosition[] = { -20.0f, 0.0f,0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt3 >= 6 && light_alt3 <= 11) {
			GLfloat lightIntensity[] = { 0.2, 1.0 ,0.2, 1.0f };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt3 >= 12 && light_alt3 <=17) {
			GLfloat lightIntensity[] = { 1.0, 1.0 ,0.5, 0.5f };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt3 >= 18 && light_alt3 <= 23) {
			GLfloat lightIntensity[] = { 1.0, 0.5 ,1, 0.5 };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
		if (light_alt3 >= 24 && light_alt3 <= 29) {
			GLfloat lightIntensity[] = { 0.2, 0.2 ,1, 1 };
			GLfloat lightPosition[] = { -20.0f, 0.0f, 0.0f, 0.0f };
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		}
	}

	
	if (light == 8) {
		if (light_alt1 >= 0 && light_alt1 <= 5) {
			GLfloat l0Diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
			GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
			GLfloat l0Position[] = { -20, 0.0f, 0.0f, 1 };
			GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
			glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
		}
		if (light_alt1 >= 6 && light_alt1 <= 11) {
			GLfloat l0Diffuse[] = { 0, 1, 0.0f, 1.0f };
			GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
			GLfloat l0Position[] = { -20, 0.0f, 0.0f, 1 };
			GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
			glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
		}
		if (light_alt1 >= 12 && light_alt1 <= 17) {
			GLfloat l0Diffuse[] = { 0, 0, 1.0f, 1.0f };
			GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
			GLfloat l0Position[] = { -20, 0.0f, 0.0f, 1 };
			GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
			glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
		}
	}


	if (scene2) {
		RenderNewGround();

		if (playerX <= -430 && scene2) {
			victory2 = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayWin();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/win.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (playerHealth <= 0 && noOfLives == 0) {
			endOfGame = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayGameOver();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/gameover.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (time2 > 35 && noOfLives == 0) {
			endOfGame = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayGameOver();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/gameover.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (playerHealth <= 0 && noOfLives >= 1) {
			extralife = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayLiveLost();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			if (!setLives) {
				setNoOfLives();
			}
			sndPlaySound(TEXT("music/extralife.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (time2 > 35 && noOfLives >= 1) {
			extralife = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayLiveLost();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			if (!setLives) {
				setNoOfLives();
			}
			sndPlaySound(TEXT("music/extralife.wav"), SND_ASYNC | SND_FILENAME);
		}


		if (!generatedAidkits) {
			generateAidKits();
		}

		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			glTranslatef(bandages[i][0], 0.7, bandages[i][2]);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glRotatef(90.0, 0, 1, 0);
			model_aidkit.Draw();
			glPopMatrix();
		}

		if (!generatedHearts) {
			generateHearts();
		}

		for (int i = 0; i < 2; i++) {
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 0, 0);
			glTranslatef(hearts[i][0], 2, hearts[i][2]);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(1, 1, 1);
			model_heart.Draw();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
		}

		if (!generatedTimes) {
			generateTimes();
		}

		for (int i = 0; i < 2; i++) {
			glPushMatrix();
			glTranslatef(times[i][0], 1.65, times[i][2]);
			glRotatef(90.0, 0, 1, 0);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(0.1, 0.1, 0.1);
			model_clock.Draw();
			glPopMatrix();
		}

		if (!generatedJumps) {
			generateJumps();
		}

		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			glTranslatef(jumps[i][0], 2, jumps[i][2]);
			glRotatef(rotateObject, 0, 1, 0);
			glRotatef(90.0, 0, 1, 0);
			glScalef(1, 1, 1);
			drawArrow(0,0,0);
			glPopMatrix();
		}
        glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-105, 0.7, 11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-105, 0.7, -11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-105, 0.7, 0);
		glScaled(0.2, 0.2, 26);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glRotatef(rotateAngel, 1, 1, 0);
		sawLine(-105);
		glPopMatrix();
		
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-50, 0.7, 11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-50, 0.7, -11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-50, 0.7, 0);
		glScaled(0.2, 0.2, 26);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glRotatef(rotateAngel, 1, 1, 0);
		sawLine(-50);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(-5, 0, -1);
		displayBegin2();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}

	if (!scene2) {
		RenderStreet();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(-5, 0, -1);
		displayBegin1();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		if (playerX <= -430 && !scene2) {
			victory1 = true;
			inbetween = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayFirstWin();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/win.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (playerHealth <= 0) {
			endOfGame = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayGameOver();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/gameover.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (time1 > 25) {
			endOfGame = true;
			if (!cameraFixed) {
				setCamera();
			}
			glPushMatrix();
			glDisable(GL_LIGHTING);
			glColor3f(1, 1, 0);
			glTranslatef(905, 950, 905);
			displayGameOver();
			glEnable(GL_LIGHTING);
			glColor3f(1, 1, 1);
			glPopMatrix();
			sndPlaySound(TEXT("music/gameover.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (!generatedAidkits) {
			generateAidKits();
		}

		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			glTranslatef(bandages[i][0], 0.65, bandages[i][2]);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glRotatef(90.0, 0, 1, 0);
			model_aidkit.Draw();
			glPopMatrix();
		}

		if (!generatedSpeeds) {
			generateSpeeds();
		}

		for (int i = 0; i < 4; i++) {
			glPushMatrix();
			glTranslatef(speeds[i][0], 3.65, speeds[i][2]);
			glRotatef(90.0, 0, 1, 0);
			glRotatef(60, 0, 1, 0);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(0.3, 0.3, 0.3);
			model_speed.Draw();
			glPopMatrix();
		}

		if (!generatedTimes) {
			generateTimes();
		}

		for (int i = 0; i < 2; i++) {
			glPushMatrix();
			glTranslatef(times[i][0], 1.65, times[i][2]);
			glRotatef(90.0, 0, 1, 0);
			glRotatef(rotateObject, 0, 1, 0);
			glScalef(0.1, 0.1, 0.1);
			model_clock.Draw();
			glPopMatrix();
		}
	}

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0, 0);
	glTranslatef(-300, 0, sz1);
	glScalef(0.1, 0.14, 0.1);
	model_spikes.Draw();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	if (sz1 > 8) {
		flagleft1 = true;
		flagright1 = false;
	}
	if (sz1 < -8) {
		flagleft1 = false;
		flagright1 = true;
	}
	if (!flagleft1 && flagright1) {
		sz1 += 0.7;
	}
	else if (flagleft1 && !flagright1) {
		sz1 -= 0.7;
	}

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0, 0);
	glTranslatef(-340, 0, sz2);
	glScalef(0.1, 0.14, 0.1);
	model_spikes.Draw();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	if (sz2 > 8) {
		flagleft2 = true;
		flagright2 = false;
	}
	if (sz2 < -8) {
		flagleft2 = false;
		flagright2 = true;
	}
	if (!flagleft2 && flagright2) {
		sz2 += 1.1;
	}
	else if (flagleft2 && !flagright2) {
		sz2 -= 1.1;
	}

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0, 0);
	glTranslatef(-320, 0, sz3);
	glScalef(0.1, 0.14, 0.1);
	model_spikes.Draw();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	if (sz3 > 8) {
		flagleft3 = true;
		flagright3 = false;
	}
	if (sz3 < -8) {
		flagleft3 = false;
		flagright3 = true;
	}
	if (!flagleft3 && flagright3) {
		sz3 += 1.5;
	}
	else if (flagleft3 && !flagright3) {
		sz3 -= 1.5;
	}

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0, 0);
	glTranslatef(-360, 0, sz4);
	glScalef(0.1, 0.14, 0.1);
	model_spikes.Draw();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	if (sz4 > 8) {
		flagleft4 = true;
		flagright4 = false;
	}
	if (sz4 < -8) {
		flagleft4 = false;
		flagright4 = true;
	}
	if (!flagleft4 && flagright4) {
		sz4 += 2;
	}
	else if (flagleft4 && !flagright4) {
		sz4 -= 2;
	}


	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0, 0);
	glTranslatef(-280, 0, sz5);
	glScalef(0.1, 0.14, 0.1);
	model_spikes.Draw();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	if (sz5 > 8) {
		flagleft5 = true;
		flagright5 = false;
	}
	if (sz5 < -8) {
		flagleft5 = false;
		flagright5 = true;
	}
	if (!flagleft5 && flagright5) {
		sz5 += 1.5;
	}
	else if (flagleft5 && !flagright5) {
		sz5 -= 1.5;
	}

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0, 1, 0);
	glTranslatef(translateCam + playerX, playerY, playerZ);
	displayHealth();
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	
	if (!scene2) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(translateCam + playerX, playerY, playerZ);
		displayTime1();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(translateCam + playerX, playerY, playerZ);
		displaySpeed();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();
	}
	if (scene2) {
		glPushMatrix();
		glTranslatef(-60, -2, 35);
		glScalef(0.7, 0.4, 0.4);
		glRotatef(90, 1, 0, 0);
		model_fbuilding.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-130, -2, -35);
		glScalef(0.7, 0.4, 0.4);
		glRotatef(90, 1, 0, 0);
		model_fbuilding.Draw();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-230, -2, 35);
		glScalef(0.7, 0.4, 0.4);
		glRotatef(90, 1, 0, 0);
		model_fbuilding.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-330, -2, -35);
		glScalef(0.7, 0.4, 0.4);
		glRotatef(90, 1, 0, 0);
		model_fbuilding.Draw();
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(translateCam + playerX, playerY, playerZ);
		displayLives();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(translateCam + playerX, playerY, playerZ);
		displayJump();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glTranslatef(translateCam + playerX, playerY, playerZ);
		displayTime2();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(1, 0.43, 0.78);
		glTranslatef(-105, 3, 0);
		glScalef(1, 1, 1);
		model_box.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(1, 0.43, 0.78);
		glTranslatef(-50, 3, 0);
		glScalef(1, 1, 1);
		model_box.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.3, 0.3, 1);
		glTranslatef(-140 + moveBox, 3, 0);
		glScalef(2, 1, 1.5);
		model_box.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.3, 0.3, 1);
		glTranslatef(-360 + moveBox2, 3, 0);
		glScalef(2, 1, 1.5);
		model_box.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.89, 0.47, 0.2);
		glTranslatef(-40, 0.5, fireball1);
		glScalef(0.1, 0.1, 0.1);
		model_fireball.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-35, 0, -15);
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		glScalef(0.2, 0.2, 0.2);
		model_cannon.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.89, 0.47, 0.2);
		glTranslatef(-65, 0.5, fireball2);
		glScalef(0.1, 0.1, 0.1);
		model_fireball.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-60, 0, -15);
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		glScalef(0.2, 0.2, 0.2);
		model_cannon.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.89, 0.47, 0.2);
		glTranslatef(-85, 0.5, fireball2);
		glScalef(0.1, 0.1, 0.1);
		model_fireball.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-80, 0, -15);
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		glScalef(0.2, 0.2, 0.2);
		model_cannon.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0.89, 0.47, 0.2);
		glTranslatef(-125, 0.5, fireball3);
		glScalef(0.1, 0.1, 0.1);
		model_fireball.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();


		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-120, 0, -15);
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 0, 1);
		glRotatef(15, 0, 1, 0);
		glScalef(0.2, 0.2, 0.2);
		model_cannon.Draw();
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glScalef(1, 2, 1);
		drawSpikeLine(-80);
		glPopMatrix();
		glPushMatrix();
		glScalef(1, 2, 1);
		drawSpikeLine(-50);
		glPopMatrix();
		
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-130, 0.7, 11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-140, 0.7, -11);
		glScaled(0.5, 1.5, 0.3);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);
		glTranslatef(-140, 0.7, 0);
		glScaled(0.2, 0.2, 26);
		glutSolidCube(1.0);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glRotatef(rotateAngel, 1, 1, 0);
		sawLine(-140);
		glPopMatrix();
	}
	

	if (!scene2) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		RenderLaserBeam(-10, 1.5, -10);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		RenderLaserBeam(-30, 1.5, -10);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		RenderLaserBeam(-100, 1.5, -10);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		RenderLaserBeam(-120, 1.5, -10);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glDisable(GL_LIGHTING);
		RenderLaserBeam(-140, 1.5, -10);
		glEnable(GL_LIGHTING);
		glColor3f(1, 1, 1);
		glPopMatrix();

		
		glPushMatrix();
		glTranslatef(0, 0, 60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-150, 0, 60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-300, 0, 60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(0, 0, -60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-150, 0, -60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-300, 0, -60);
		glScalef(0.7, 0.5, 0.5);
		model_skyscraper.Draw();
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(playerX + hovered, 2 + playerY, playerZ);
	glRotatef(90, 1, 0, 0);
	glRotatef(90-playerRotate, 0, 0, 1);
	glScalef(3.5, 3.5, 3.5);
	if (moving) {
		model_player[playerFrame].Draw();
	}
	else {
		model_idleplayer.Draw();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 0, -5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(-90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 0, 5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-150, 0, -5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(-90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200, 0, 5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-250, 0, -5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(-90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-300, 0, 5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-350, 0, -5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(-90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-400, 0, 5);
	glScalef(0.05, 0.03, 0.05);
	glRotatef(90, 0, 1, 0);
	model_lightlamp.Draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-442, 0, 0);
	glScalef(0.05, 0.05, 0.05);
	glRotatef(-90, 0, 1, 0);
	model_door.Draw();
	glPopMatrix();

	if (!scene2) {
		glPushMatrix();
		drawSpikeLine(0);
		glPopMatrix();

		glPushMatrix();
		drawSpikeLine(-100);
		glPopMatrix();
	}
	if (!scene2) {
		glPushMatrix();
		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex1);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 500, 500, 500);
		gluDeleteQuadric(qobj);
		glPopMatrix();

		RenderGravel();
	}

	if (scene2) {
		glPushMatrix();
		GLUquadricObj* qobj;
		qobj = gluNewQuadric();
		glTranslated(50, 0, 0);
		glRotated(90, 1, 0, 1);
		glBindTexture(GL_TEXTURE_2D, tex2);
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 500, 500, 500);
		gluDeleteQuadric(qobj);
		glPopMatrix();

		RenderNewStreet();
	}
	glutSwapBuffers();
}

void myKeyboard(unsigned char button, int x, int y)
{
	if (button == '1') {
		light = 0;
	}
	if (button == '2') {
		light = 1;
	}
	if (button == '3') {
		light = 2;
	}
	if (button == '4') {
		light = 3;
	}
	if (button == '5') {
		light = 4;
	}
	if (button == '6') {
		light = 5;
	}
	if (button == '7') {
		light = 6;
	}
	if (button == '8') {
		light = 7;
	}
	if (button == '9') {
		light = 8;
	}

	if (!victory2 && !inbetween && !endOfGame && (button == 'W' || button == 'w')) {
		frontView = true;
		backView = false;
		playerRotate = 0;
		playerX = playerX - 1 - playerSpeed;
		Eye.x = Eye.x - 1 - playerSpeed;
		At.x = At.x - 1 - playerSpeed;
		Up.z = 0;
		incremetVal = 0.6;
		moving = true;
	}

	if (!victory2 && !inbetween && !endOfGame && (button == 'd' || button == 'D')) {
		if (playerZ > -9 && frontView) {
			playerRotate = -30;
			playerZ--;
			Eye.z--;
			At.z--;
		}
		else if (playerZ > -9 && backView) {
			playerRotate = -120;
			playerZ--;
			Eye.z--;
			At.z--;
		}
		moving = true;
	}
	if (!victory2 && !inbetween && !endOfGame && (button == 'a' || button == 'A')) {
		if (playerZ < 9 && frontView) {
			playerRotate = 30;
			playerZ++;
			Eye.z++;
			At.z++;
		}
		if (playerZ < 9 && backView) {
			playerRotate = 120;
			playerZ++;
			Eye.z++;
			At.z++;
		}
		moving = true;
	}


	if (!victory2 && !inbetween && !endOfGame && playerX <= 3 && (button == 's' || button == 'S')) {
		backView = true;
		frontView = false;
		playerRotate = 180;
		playerX = playerX + 1 + playerSpeed;
		Eye.x = Eye.x + 1 + playerSpeed;
		At.x = At.x + 1 + playerSpeed;
		incremetVal = -0.6;
		moving = true;
	}
	if (!victory2 && !inbetween && !endOfGame && (button == 't' || button == 'T')) {
		translateCam = 0;
		Eye.y = 7;
		thirdperson = true;
		firstperson = false;
	}
	if (!victory2 && !inbetween && !endOfGame && (button == 'f' || button == 'F')) {	
		thirdperson = false;
		firstperson = true;
		translateCam = -21.5;
		Eye.y = 4.5;
	}
	if (!victory2 && !inbetween && !endOfGame && playerX <= 3 && (button == SPACEBAR)) {
		if (!inAir) {
			inAir = true;
			reachHigh = false;
			for (int i = 0; i < (4.2+ Jumpboost); i++) {
				playerY += 0.4;
				playerX -= incremetVal;
				Eye.y += 0.4;
				Eye.x -= incremetVal;
				At.y += 0.4;
				At.x -= incremetVal;
			}
		} 
	}

	if ((!inbetween && endOfGame && (button == 'r' || button == 'R')) || (!inbetween && !endOfGame && victory2 && (button == 'r' || button == 'R'))) {
		frontView = false;
		backView = false;
		reachHigh = false;
		inAir = false;
		translateCam = 0;
		hovercounter = 0;
		playerX = 0;
		playerZ = 0;
		playerY = 0;
		incremetVal = 0.6;
		Jumpboost = 0;
		hovered = 0;
		rotateAngel = 0.01;
		playerRotate = 0;
		playerRot = false;
		playerHealth = 100;
		inbetween = false;
		generatedAidkits = false;
		generatedTimes = false;
		generatedSpeeds = false;
		generatedHearts = false;
		generatedJumps = false;
		cameraFixed = false;
		endOfGame = false;
		victory1 = false;
		victory2 = false;
		flagleft1 = false;
		flagright1 = false;
		flagleft2 = false;
		flagright2 = false;
		flagleft3 = false;
		flagright3 = false;
		flagleft4 = false;
		flagright4 = false;
		flagleft5 = false;
		flagright5 = false;
		setLives = false;
		extralife = false;
		scene2 = false;
		sz1 = 9;
		sz2 = -9;
		sz3 = -9;
		sz4 = 9;
		sz5 = -9;
		fireball1 = -10;
		fireball2 = -10;
		fireball3 = -10;
		threshhold = 50;
		moveBox = 0;
		moveBox2 = 0;
		choice = 0;
		choice2 = 0;
		counter1 = 0;
		counter2 = 0;
		time1 = 0;
		time2 = 0;
		playerSpeed = 0;
		noOfLives = 1;
		hearts[2][3] = {};
		bandages[3][3] = {};
		speeds[4][3] = {};
		jumps[3][3] = {};
		times[2][3] = {};
		Eye.x = 20;
		Eye.y = 7;
		Eye.z = 0;
		At.x = 0;
		At.y = 0;
		At.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
		firstperson = false;
		thirdperson = false;
		light = 0;
		playerFrame = 5;
		frequency = 10;
		frameDirection = 1;
		moving = false;
		rotateObject = 0;
		light_alt1 = 0;
		light_alt2 = 0;
		light_alt3 = 0;
	}

	if (!victory2 && victory1 && (button == 'n' || button == 'N')) {
		frontView = false;
		backView = false;
		reachHigh = false;
		inAir = false;
		translateCam = 0;
		hovercounter = 0;
		playerX = 0;
		playerZ = 0;
		playerY = 0;
		incremetVal = 0.6;
		Jumpboost = 0;
		hovered = 0;
		rotateAngel = 0.01;
		playerRotate = 0;
		playerRot = false;
		inbetween = false;
		generatedAidkits = false;
		generatedTimes = false;
		generatedHearts = false;
		generatedJumps = false;
		cameraFixed = false;
		setLives = false;
		endOfGame = false;
		victory1 = false;
		victory2 = false;
		flagleft1 = false;
		flagright1 = false;
		flagleft2 = false;
		flagright2 = false;
		flagleft3 = false;
		flagright3 = false;
		flagleft4 = false;
		flagright4 = false;
		flagleft5 = false;
		flagright5 = false;
		extralife = false;
		scene2 = true;
		sz1 = 9;
		sz2 = -9;
		sz3 = -9;
		sz4 = 9;
		sz5 = -9;
		fireball1 = -10;
		fireball2 = -10;
		fireball3 = -10;
		threshhold = 50;
		moveBox = 0;
		moveBox2 = 0;
		choice = 0;
		choice2 = 0;
		counter1 = 0;
		counter2 = 0;
		time2 = 0;
		playerSpeed = 0;
		noOfLives = 1;
		hearts[2][3] = {};
		bandages[3][3] = {};
		jumps[3][3] = {};
		times[2][3] = {};
		Eye.x = 20;
		Eye.y = 7;
		Eye.z = 0;
		At.x = 0;
		At.y = 0;
		At.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
		firstperson = false;
		thirdperson = false;
		playerFrame = 5;
		frequency = 10;
		frameDirection = 1;
		moving = false;
		rotateObject = 0;
		light_alt1 = 0;
		light_alt2 = 0;
		light_alt3 = 0;
	}
	if (!victory2 && !inbetween && !endOfGame && extralife && (button == 'm' || button == 'M')) {
		extralife = false;
		frontView = false;
		backView = false;
		reachHigh = false;
		inAir = false;
		translateCam = 0;
		hovercounter = 0;
		playerX = 0;
		playerZ = 0;
		playerY = 0;
		incremetVal = 0.6;
		Jumpboost = 0;
		hovered = 0;
		rotateAngel = 0.01;
		playerRotate = 0;
		playerRot = false;
		inbetween = false;
		playerHealth = 100;
		generatedAidkits = false;
		generatedTimes = false;
		generatedHearts = false;
		generatedJumps = false;
		cameraFixed = false;
		endOfGame = false;
		victory1 = false;
		victory2 = false;
		setLives = false;
		flagleft1 = false;
		flagright1 = false;
		flagleft2 = false;
		flagright2 = false;
		flagleft3 = false;
		flagright3 = false;
		flagleft4 = false;
		flagright4 = false;
		flagleft5 = false;
		flagright5 = false;
		scene2 = true;
		sz1 = 9;
		sz2 = -9;
		sz3 = -9;
		sz4 = 9;
		sz5 = -9;
		fireball1 = -10;
		fireball2 = -10;
		fireball3 = -10;
		threshhold = 50;
		moveBox = 0;
		moveBox2 = 0;
		choice = 0;
		choice2 = 0;
		counter1 = 0;
		counter2 = 0;
		time2 = 0;
		playerSpeed = 0;
		hearts[2][3] = {};
		bandages[3][3] = {};
		jumps[3][3] = {};
		times[2][3] = {};
		Eye.x = 20;
		Eye.y = 7;
		Eye.z = 0;
		At.x = 0;
		At.y = 0;
		At.z = 0;
		Up.x = 0;
		Up.y = 1;
		Up.z = 0;
		firstperson = false;
		thirdperson = false;
		playerFrame = 5;
		frequency = 10;
		frameDirection = 1;
		moving = false;
		rotateObject = 0;
		light_alt1 = 0;
		light_alt2 = 0;
		light_alt3 = 0;
	}
	if (button == 27) {
		exit(0);
	}
	glLoadIdentity();	//Clear Model_View Matrix
	gluLookAt(Eye.x + translateCam, Eye.y, Eye.z, At.x + translateCam, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//Re-draw scene 
	glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y) {
	moving = false;
	glutPostRedisplay();
}
	

void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	Model_3DS c_6;
	c_6.Load("Models/player/-6.3DS");
	Model_3DS c_5;
	c_5.Load("Models/player/-5.3DS");
	Model_3DS c_4;
	c_4.Load("Models/player/-4.3DS");
	Model_3DS c_3;
	c_3.Load("Models/player/-3.3DS");
	Model_3DS c_2;
	c_2.Load("Models/player/-2.3DS");
	Model_3DS c_1;
	c_1.Load("Models/player/-1.3DS");
	Model_3DS c1;
	c1.Load("Models/player/1.3DS");
	Model_3DS c2;
	c2.Load("Models/player/2.3DS");
	Model_3DS c3;
	c3.Load("Models/player/3.3DS");
	Model_3DS c4;
	c4.Load("Models/player/4.3DS");
	Model_3DS c5;
	c5.Load("Models/player/5.3DS");
	model_player.push_back(c_6);
	model_player.push_back(c_5);
	model_player.push_back(c_4);
	model_player.push_back(c_3);
	model_player.push_back(c_2);
	model_player.push_back(c_1);
	model_player.push_back(c1);
	model_player.push_back(c2);
	model_player.push_back(c3);
	model_player.push_back(c4);
	model_idleplayer.Load("Models/player/1.3DS");
	model_aidkit.Load("Models/aidkit/MedBox1.3DS");
	model_clock.Load("Models/clock/Clock 4.3DS");
	model_speed.Load("Models/speed/missile.3DS");
	model_heart.Load("Models/heart/heart_ts01.3DS");
	model_fireball.Load("Models/fireball/Ball N280313.3DS");
	model_spikes.Load("Models/spikes/spike.3DS");
	model_door.Load("Models/door/add073.3DS");
	model_box.Load("Models/crate/Floor_plate.3DS");
	model_saw.Load("Models/blade/shrknlw.3DS");
	model_cannon.Load("Models/cannon/top.3DS");
	model_skyscraper.Load("Models/skyscraper/SkyA.3DS");
	model_fbuilding.Load("Models/building/building.3DS");
	model_lightlamp.Load("Models/lamp/Lamppost N140708.3DS");
	

	// Loading texture files0
	tex_ground.Load("Textures/gravel.bmp");
	tex_street.Load("Textures/asphaltPlain.bmp");
	tex_newstreet.Load("Textures/newstreet.bmp");
	tex_newground.Load("Textures/newground.bmp");
	
	loadBMP(&tex1, "Textures/matrix2.bmp", true);
	loadBMP(&tex2, "Textures/newcyber.bmp", true);
}

void Idle() {

	if (light_alt1 >= 18) {
		light_alt1 = 0;
	}
	else {
		light_alt1++;
	}
	

	if (light_alt2 >= 5) {
		light_alt2 = 0;
	}
	else {
		light_alt2++;
	}

	if (light_alt3 >= 30) {
		light_alt3 = 0;
	}
	else {
		light_alt3++;
	}

	rotateAngel += 180;
	rotateObject += 5;
	if (scene2 && fireball1 <= threshhold) {
		fireball1 += 1;
	}
	if (scene2 && fireball1 >= threshhold) {
		fireball1 = -10;
	}
	if (scene2 && fireball2 <= threshhold) {
		fireball2 += 2;
	}
	if (scene2 && fireball2 >= threshhold) {
		fireball2 = -10;
	}

	if (scene2 && fireball3 <= threshhold) {
		fireball3 += 2.5;
	}
	if (scene2 && fireball3 >= threshhold) {
		fireball3 = -10;
	}

	if (scene2 && playerX <= -35 && playerX >= -40 && (playerZ <= fireball1 && playerZ >= (fireball1 - 0.6) || playerZ >= fireball1 && playerZ <= (fireball1 + 0.6)) && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -60 && playerX >= -65 && (playerZ <= fireball2 && playerZ >= (fireball1 - 0.6) || playerZ >= fireball2 && playerZ <= (fireball1 + 0.6)) && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -80 && playerX >= -85 && (playerZ <= fireball2 && playerZ >= (fireball1 - 0.6) || playerZ >= fireball2 && playerZ <= (fireball1 + 0.6)) && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -120 && playerX >= -125 && (playerZ <= fireball3 && playerZ >= (fireball1 - 0.6) || playerZ >= fireball3 && playerZ <= (fireball1 + 0.6)) && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -102 && playerX >= -106 && playerY >= 0 && playerY <= 2 && playerZ <= 10 && playerZ >= -10 && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -47 && playerX >= -51 && playerY >= 0 && playerY <= 2 && playerZ <= 10 && playerZ >= -10 && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}
	if (scene2 && playerX <= -138 && playerX >= -141 && playerY >= 0 && playerY <= 2 && playerZ <= 10 && playerZ >= -10 && playerY <= 2 && playerY >= 0) {
		playerHealth -= 50;
		sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
	}

	if (playerX != 0) {
		if (playerX <= -298 && playerX >= -305 && (playerZ <= sz1 && playerZ >= (sz1 - 0.5) || playerZ >= sz1 && playerZ <= (sz1 + 0.5)) && playerY <= 0.6 && playerY >= 0) {
			playerHealth -= 50;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
	}
	if (playerX != 0) {
		if (playerX <= -338 && playerX >= -345 && (playerZ <= sz2 && playerZ >= (sz2 - 0.5) || playerZ >= sz2 && playerZ <= (sz2 + 0.5)) && playerY <= 0.6 && playerY >= 0) {
			playerHealth -= 50;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
	}
	if (playerX != 0) {
		if (playerX <= -318 && playerX >= -325 && (playerZ <= sz3 && playerZ >= (sz3 - 0.5) || playerZ >= sz3 && playerZ <= (sz3 + 0.5)) && playerY <= 0.6 && playerY >= 0) {
			playerHealth -= 50;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
	}
	if (playerX != 0) {
		if (playerX <= -358 && playerX >= -365 && (playerZ <= sz4 && playerZ >= (sz4 - 0.5) || playerZ >= sz4 && playerZ <= (sz4 + 0.5)) && playerY <= 0.6 && playerY >= 0) {
			playerHealth -= 50;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
	}
	if (playerX != 0) {
		if (playerX <= -278 && playerX >= -285 && (playerZ <= sz5 && playerZ >= (sz5 - 0.5) || playerZ >= sz5 && playerZ <= (sz5 + 0.5)) && playerY <= 0.6 && playerY >= 0) {
			playerHealth -= 50;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
	}

	if (playerX != 0) {
		if (!scene2 && playerX <= -9.5 && playerX >= -10.5 && playerY <= 1.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (!scene2 && playerX <= -29.5 && playerX >= -30.5 && playerY <= 1.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (!scene2 && playerX <= -95.5 && playerX >= -100.5 && playerY <= 1.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (!scene2 && playerX <= -115.5 && playerX >= -120.5 && playerY <= 1.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (!scene2 && playerX <= -135.5 && playerX >= -140.5 && playerY <= 1.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}

		if (!scene2 && playerX <= -45 && playerX >= -50 && playerY <= 0.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (!scene2 && playerX <= -166 && playerX >= -170 && playerY <= 0.5 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		

		if (scene2 && playerX <= -105 && playerX >= -113 && playerY <= 1 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}
		if (scene2 && playerX <= -140 && playerX >= -146 && playerY <= 1 && playerY >= 0) {
			playerHealth -= 15;
			sndPlaySound(TEXT("music/hurt.wav"), SND_ASYNC | SND_FILENAME);
		}

		for (int i = 0; i < 3; i++) {
			if (playerX <= (bandages[i][0] + 3) && playerX >= (bandages[i][0] - 2) && playerZ <= (bandages[i][2] + 2) && playerZ >= (bandages[i][2]-3) && playerY <= 2 && playerY >= 0) {
				if ((playerHealth + 10) <= 100) {
					playerHealth += 10;
				}
				else if ((playerHealth + 10) > 100) {
					playerHealth = 100;
				}
				bandages[i][0] = 2000;
				sndPlaySound(TEXT("music/aidkit.wav"), SND_ASYNC | SND_FILENAME);
			}
		}
	}

	if (playerX != 0) {
		for (int i = 0; i < 4; i++) {
			if (!scene2 && playerX <= (speeds[i][0] + 2) && playerX >= (speeds[i][0] - 2) && playerZ <= (speeds[i][2] + 2) && playerZ >= (speeds[i][2]-3) && playerY <= 2 && playerY >= 0) {
				playerSpeed += 0.2;
				speeds[i][0] = 2000;
				sndPlaySound(TEXT("music/speed.wav"), SND_ASYNC | SND_FILENAME);
			}
		}
	}

	if (playerX != 0 && scene2) {
		for (int i = 0; i < 2; i++) {
			if (playerX <= (hearts[i][0] + 2) && playerX >= (hearts[i][0] - 3) && playerZ <= (hearts[i][2] + 2) && playerZ >= (hearts[i][2]-3) && playerY <= 2 && playerY >= 0) {
				noOfLives += 1;
				hearts[i][0] = 2000;
				sndPlaySound(TEXT("music/heart.wav"), SND_ASYNC | SND_FILENAME);
			}
		}
	}

	if (playerX != 0 && scene2) {
		for (int i = 0; i < 3; i++) {
			if (playerX <= (jumps[i][0]+2) && playerX >= (jumps[i][0] - 2) && playerZ <= (jumps[i][2] + 2) && playerZ >= (jumps[i][2]-3) && playerY <= 2 && playerY >= 0) {
				Jumpboost += 1;
				sndPlaySound(TEXT("music/jump.wav"), SND_ASYNC | SND_FILENAME);
				jumps[i][0] = 2000;
			}
		}
	}

	if (playerX != 0) {
		for (int i = 0; i < 2; i++) {
			if (playerX <= (times[i][0] + 2) && playerX >= (times[i][0] - 2) && playerZ <= (times[i][2] + 2) && playerZ >= (times[i][2] - 1) && playerY <= 2 && playerY >= 0) {
				if (scene2) {
					if ((time2 - 5) >= 0) {
						time2 -= 5;
					}
					else {
						time2 = 0;
					}
				}
				else {
					if ((time1 - 5) >= 0) {
						time1 -= 5;
					}
					else {
						time1 = 0;
					}
				}
				sndPlaySound(TEXT("music/time.wav"), SND_ASYNC | SND_FILENAME);
				times[i][0] = 2000;
			}
		}
	}


	hovercounter++;
	if (hovercounter % 120 == 0) {
		if (choice % 2 == 0) {
			moveBox = 0;
		}
		else {
			moveBox = 2000;
		}
		choice++;	
	}
	if (hovercounter % 100 == 0) {
		if (choice2 % 2 == 0) {
			moveBox2 = 0;
		}
		else {
			moveBox2 = 2000;
		}
		choice2++;
	}
	if (moveBox2 == 0 && scene2 && playerX <= -357 && playerX >= -363 && playerY >= 3 && playerZ <= 1 && playerZ >= -1) {
		hovered = 3;
	}
	else if (moveBox == 0 && scene2 && playerX <= -137 && playerX >= -143 && playerY >= 3 && playerZ <= 1 && playerZ >= -1) {
		hovered = 3;
	}
	else if (scene2 && playerX <= -102 && playerX >= -106 && playerY >= 3 && playerZ <= 1 && playerZ >= -1 || scene2 && playerX <= -47 && playerX >= -51 && playerY >= 3 && playerZ <= 1 && playerZ >= -1) {
		hovered = 3;
	}
	else {
		hovered = 0;
		if (playerY >= (4 + Jumpboost)) {
			reachHigh = true;
		}
		if (inAir && playerY < (4.1 + Jumpboost) && !reachHigh) {
			playerY += 0.4;
			playerX -= incremetVal;
			Eye.y += 0.4;
			Eye.x -= incremetVal;
			At.y += 0.4;
			At.x -= incremetVal;
		}
		if (reachHigh && inAir && playerY >= 0.4) {
			playerY -= 0.4;
			playerX -= incremetVal;
			Eye.y -= 0.4;
			Eye.x -= incremetVal;  
			At.y -= 0.4;
			At.x -= incremetVal;
		}
		if (playerY <= 0.4) {
			reachHigh = false;
			inAir = false;
		}
	}
	glLoadIdentity();	//Clear Model_View Matrix
	gluLookAt(Eye.x + translateCam, Eye.y , Eye.z, At.x + translateCam, At.y, At.z, Up.x, Up.y, Up.z);	//Setup Camera with modified paramters
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glutPostRedisplay();
}

void Anim(int value) {

	counter1++;
	if (!scene2) {
		if (counter1 % 30 == 0) {
			time1++;
		}
	}

	if (!victory2 && scene2) {
		counter2++;
		if (counter2 % 30 == 0) {
			time2++;
		}
	}

	if (frequency == 0)
	{
		frequency = 2;
		playerFrame += frameDirection;

		if (playerFrame == 0 || playerFrame == model_player.size() - 1)
		{
			frameDirection *= -1;
		}

	}

	frequency--;

	glutPostRedisplay();
	glutTimerFunc(1, Anim, 0);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 150);
	WCHAR music1[] = L"music/backgroundmusic.wav";
	LPCSTR const Back_ground_music1 = "open music/backgroundmusic.wav type mpegvideo alias Sound";
	mciSendStringA(Back_ground_music1, NULL, 0, NULL);
	MCIERROR onrepeat1 = mciSendStringA("play Sound repeat", NULL, 0, NULL);
	glutCreateWindow(title);
	glutDisplayFunc(myDisplay);
	glutKeyboardUpFunc(KeyUp);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	myInit();
	LoadAssets();
	glutIdleFunc(Idle);
	glutTimerFunc(1, Anim, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glutMainLoop();
}