#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
int letak = 0;
string notif;
bool smooth = 1, bertukar = 1, state_red = 0;
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 10.0 };
GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light_position2[] = { -1.0, -1.0, -1.0, 0.0 };

GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red_light[] = { 9.,0.,0.,1. };
GLfloat blue_light[] = { 0.,0.,1.,1. };
GLfloat white_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

void update(int);

void write(float x, float y, float z, void* font, const char* string) {
	const char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
void init(void)
{

	glClearColor(0.0, 1.0, 1.0, 0.0);

	glShadeModel(GL_SMOOTH);

	//material
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
}

void pesan() {
	write(50, 21, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Bawa mobil sampai ujung jalan");//key a untuk mundur
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	glPushMatrix();
	glPushMatrix();                   // badan mobil teko
	glScalef(4, 1, 2);
	glutSolidTeapot(.5);
	glTranslatef(-.05, .3, 0);
	glScalef(0.6, 3, 2);
	glutSolidTeapot(.25);
	glTranslatef(-.12, .001, -.001);
	glScalef(1, 1.8, 2.48);
	glRotatef(230, 0, 0, 250);
	glutSolidTeapot(.1);
	glPopMatrix();
	glTranslatef(0, 0, .5);
	glPushMatrix();
	glTranslatef(-.4, -.2, 0);
	glutSolidTorus(.1, .2, 8, 8);       // ban teko
	glTranslatef(1, 0, 0);
	glutSolidTorus(.1, .2, 8, 8);       // ban teko
	glPopMatrix();
	glTranslatef(0, 0, -1);
	glPushMatrix();
	glTranslatef(-.4, -.2, 0);
	glutSolidTorus(.1, .2, 8, 8);       // ban teko
	glTranslatef(1, 0, 0);
	glutSolidTorus(.1, .2, 8, 8);       // ban teko
	glPopMatrix();

	glPopMatrix();


	glPopMatrix();

	glFlush();
}
void alas() {
	glBegin(GL_POLYGON);
	glColor3ub(39, 216, 50);
	glVertex3f(0, -21, -250);
	glVertex3f(380, -21, -250);
	glVertex3f(380, -21, -250);
	glVertex3f(0, -21, -250);
}


void GL_keyboard(unsigned char key, int x, int y)  // GLUT keyboard function
{
	switch (key)
	{
	case 't':                              //ganti warna lampu menjadi kedap kedip
		bertukar = 1;
		glutTimerFunc(10, update, 0);
		break;
	case 'd':                              //key d untuk maju
		letak--;
		glTranslatef(-0.05, 0.0, 0.0);
		if (letak <= -100) {
			cout << "sudah sampai"<<endl;
			cout << "Pesan : " << notif<<endl;
			cout << "tekan d sekali lagi untuk keluar";
			cout << endl << "langkah mobil : " << letak << endl;
		}
		if (letak < -100) {
			exit(0);
		}
	case 'y':                              //key y untuk mendarat
		letak--;
		glTranslatef(0.00, -0.05, 0.0);
		display();
		break;
	case 'j':                              //key j untuk ke kiri
		letak++;
		glTranslatef(0.00, 0.0, -0.05);
		display();
		break;
	case 'a':                              //key a untuk mundur
		letak++;
		glTranslatef(0.05, 0.0, 0.0);
		display();
		break;
	case 'h':                              //key h untuk terbang
		letak++;
		glTranslatef(0.00, 0.05, 0.0);
		display();
	case 'l':                              //key l untuk ke kanan
		letak++;
		glTranslatef(0.00, 0.0, 0.05);
		display();
		break;
	case 'n':
		notif = "KGV LAB 2 181401118";
		cout << endl<<"pesan dibawa,bawa mobil sampai ujung jalan";
		break;
	case 'o':
		cout << "Screenshot Berhasil";
		alas();
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w,
			2.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.5 * (GLfloat)w / (GLfloat)h,
			2.5 * (GLfloat)w / (GLfloat)h, -2.5, 2.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 0., 1., -1., 1., 0., 1., 0.);
}

void update(int value)
{
	if (state_red == 1)
	{
		glLightfv(GL_LIGHT0, GL_DIFFUSE, blue_light);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, blue_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, red_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_ambient);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		state_red = 0;
	}
	else {
		glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, red_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_ambient);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		state_red = 1;
	}
	glutPostRedisplay();

	if (bertukar) {
		glutTimerFunc(1000, update, 0);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("KGV_UAS_118");
	init();
	cout << "Nama : Mhd Iqbal Maulana"<<endl;
	cout << "NIM : 181401118"<<endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(GL_keyboard);
	glutMainLoop();
	return 0;
}
