/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define N 100.0
#define PI 3.1415
typedef float point3[3];
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy k�ty obrotu
int model = 1;
/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

class punkt{
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat r;
		GLfloat g;
		GLfloat b;
};

punkt **tab;

void spinEgg()
{

    theta[0] -= 0.1;
    if( theta[0] > 360.0 ) theta[0] -= 360.0;

    theta[1] -= 0.1;
    if( theta[1] > 360.0 ) theta[1] -= 360.0;

    theta[2] -= 0.1;
    if( theta[2] > 360.0 ) theta[2] -= 360.0;

    glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    // pocz�tek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    // pocz�tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    //  pocz�tek i koniec obrazu osi y

    glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
    glBegin(GL_LINES); // rysowanie osi x

        glVertex3fv(x_min);
        glVertex3fv(x_max);

    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
    glBegin(GL_LINES);  // rysowanie osi y

        glVertex3fv(y_min);
        glVertex3fv(y_max);                            

    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
    glBegin(GL_LINES); // rysowanie osi z

        glVertex3fv(z_min);
        glVertex3fv(z_max); 

    glEnd();

}

GLfloat f_x(GLfloat u,GLfloat v){
return cos(PI*v)*(-90.0*u*u*u*u*u + 225.0*u*u*u*u - 270.0*u*u*u + 180.0*u*u - 45*u);
}

GLfloat f_y(GLfloat u,GLfloat v){
return 160.0*u*u*u*u -320.0*u*u*u + 160.0*u*u;
}

GLfloat f_z(GLfloat u,GLfloat v){
return sin(PI*v)*(-90.0*u*u*u*u*u + 225.0*u*u*u*u - 270.0*u*u*u + 180.0*u*u - 45.0*u);
}
/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)

void jajko_pkt(){

	glBegin(GL_POINTS);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			glColor3f(tab[i][j].r, tab[i][j].g, tab[i][j].b);
			glVertex3f(tab[i][j].x,tab[i][j].y,tab[i][j].z);
		}
	}
	glEnd();
}
void jajko_lines(){

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			glColor3f(tab[i][j].r, tab[i][j].g, tab[i][j].b);
			glVertex3f(tab[i][j].x,tab[i][j].y,tab[i][j].z);
		}
	}

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			glColor3f(tab[j][i].r, tab[j][i].g, tab[j][i].b);
			glVertex3f(tab[j][i].x,tab[j][i].y,tab[j][i].z);
		}
	}
	glEnd();
}
void jajko_troj(){

	glBegin(GL_TRIANGLE_STRIP);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(i<N-1){
				glColor3f(tab[i][j].r, tab[i][j].g, tab[i][j].b);
				glVertex3f(tab[i][j].x,tab[i][j].y,tab[i][j].z);
				glColor3f(tab[i+1][j].r, tab[i+1][j].g, tab[i+1][j].b);
				glVertex3f(tab[i+1][j].x,tab[i+1][j].y,tab[i+1][j].z);
			}
			if(i==N-1){
				glColor3f(tab[i][j].r, tab[i][j].g, tab[i][j].b);
				glVertex3f(tab[i][j].x,tab[i][j].y,tab[i][j].z);

			}
		}
	}


	glEnd();
}

void jajko(){
	GLfloat krok = 1.0 / N;
	GLfloat u = 0.0;
	GLfloat v = 0.0;
	
	tab = new punkt *[N];
	for ( int i = 0; i < N; i++ )
		tab[i] = new punkt [N]; 
	

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			tab[i][j].x = f_x(u,v);
			tab[i][j].y = f_y(u,v);
			tab[i][j].z = f_z(u,v);
			tab[i][j].r = rand()%100 /100.0;
			tab[i][j].g = rand()%100 /100.0;
			tab[i][j].b = rand()%100 /100.0;

			v+= krok;
		}
		u += krok;
		v = 0.0;
	}
}


void RenderScene(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz�cym
    glLoadIdentity();
    // Czyszczenie macierzy bie��cej

    Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej 
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y 
	glTranslatef(0,-5,0.0);

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	
	switch(model){
	case 1: jajko_pkt();
			break;
	case 2: jajko_lines();
			break;	
	case 3: jajko_troj();
			break;	
	default: jajko_troj();
	
	}
	


	



	//glRotated(60.0, 1.0, 1.0, 1.0 );  // Obr�t o 60 stopni
	//glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty


	/*
	glutSolidCone (GLdouble base, GLdouble height, GLint slices, GLint stacks)
	glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty
	glutSolidCube (GLdouble width)
	glutSolidCylinder (GLdouble radius, GLdouble height, GLint slices, GLint stacks)
	glutSolidDodecahedron (void)
	glutSolidIcosahedron (void)
	glutSolidOctahedron (void)
	glutSolidRhombicDodecahedron (void)
	glutSolidSierpinskiSponge (int num_levels, const GLdouble offset[3], GLdouble scale)
	glutSolidSphere (GLdouble radius, GLint slices, GLint stacks)
	glutSolidTeapot (GLdouble size)
	glutSolidTetrahedron (void)
	glutSolidTorus (GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings)
	glutWireCone (GLdouble base, GLdouble height, GLint slices, GLint stacks)
	glutWireCube (GLdouble width)
	glutWireCylinder (GLdouble radius, GLdouble height, GLint slices, GLint stacks)
	glutWireDodecahedron (void)
	glutWireIcosahedron (void)
	glutWireOctahedron (void)
	glutWireRhombicDodecahedron (void)
	glutWireSierpinskiSponge (int num_levels, const GLdouble offset[3], GLdouble scale)
	glutWireSphere (GLdouble radius, GLint slices, GLint stacks)
	glutWireTeapot (GLdouble size)
	glutWireTetrahedron (void)
	glutWireTorus (GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings) 
	*/









    glFlush();
    // Przekazanie polece� rysuj�cych do wykonania

 

    glutSwapBuffers();
    // 

 }

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania

 void keys(unsigned char key, int x, int y)
{
    if(key == 'p') model = 1;
    if(key == 'w') model = 2;
    if(key == 's') model = 3;
   
    RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{

glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.

 

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
    // wymiar�w okna 

 

    if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

        vertical = 1;

 

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielko�ciokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

 

    glMatrixMode(GL_PROJECTION);
    // Prze��czenie macierzy bie��cej na macierz projekcji

 

    glLoadIdentity();
    // Czyszcznie macierzy bie��cej           

 

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie wsp�czynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
    // przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
    // glOrtho(...)            

 

    if(horizontal <= vertical)

        glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,7.5, -7.5); 

    else

        glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,7.5,-7.5);                      

    glMatrixMode(GL_MODELVIEW);
    // Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

    glLoadIdentity();
    // Czyszcenie macierzy bie��cej

}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli

 

void main(void)
{          
	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	jajko();
    glutInitWindowSize(300, 300);

    glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");
    glutIdleFunc(spinEgg);  
    glutDisplayFunc(RenderScene);
    // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
    // (callback function).  Bedzie ona wywo�ywana za ka�dym razem
    // gdy zajdzie potrzba przeryswania okna

 
	glutKeyboardFunc(keys);
    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
    // zazmiany rozmiaru okna                        

 

    MyInit();
    // Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przyst�pieniem do renderowania

    glEnable(GL_DEPTH_TEST);
    // W��czenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}

 

/*************************************************************************************/


