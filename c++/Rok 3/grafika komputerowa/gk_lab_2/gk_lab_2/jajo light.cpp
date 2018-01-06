/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

/*************************************************************************************/
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define N 100.0
#define PI 3.1415
typedef float point3[3];
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy k¹ty obrotu
int model = 1;
/*************************************************************************************/

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych

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

    glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    // pocz¹tek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    // pocz¹tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    //  pocz¹tek i koniec obrazu osi y

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

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)

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
    // Czyszczenie okna aktualnym kolorem czyszcz¹cym
    glLoadIdentity();
    // Czyszczenie macierzy bie¿¹cej

    Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej 
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y 
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
	


	



	//glRotated(60.0, 1.0, 1.0, 1.0 );  // Obrót o 60 stopni
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
    // Przekazanie poleceñ rysuj¹cych do wykonania

 

    glutSwapBuffers();
    // 

 }

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania

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
// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.

 

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
    // wymiarów okna 

 

    if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

        vertical = 1;

 

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkoœciokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

 

    glMatrixMode(GL_PROJECTION);
    // Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

 

    glLoadIdentity();
    // Czyszcznie macierzy bie¿¹cej           

 

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie wspó³czynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
    // przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
    // glOrtho(...)            

 

    if(horizontal <= vertical)

        glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,7.5, -7.5); 

    else

        glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,7.5,-7.5);                      

    glMatrixMode(GL_MODELVIEW);
    // Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   

    glLoadIdentity();
    // Czyszcenie macierzy bie¿¹cej

}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli

 

void main(void)
{          
	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	jajko();
    glutInitWindowSize(300, 300);

    glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");
    glutIdleFunc(spinEgg);  
    glutDisplayFunc(RenderScene);
    // Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
    // (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
    // gdy zajdzie potrzba przeryswania okna

 
	glutKeyboardFunc(keys);
    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
    // zazmiany rozmiaru okna                        

 

    MyInit();
    // Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przyst¹pieniem do renderowania

    glEnable(GL_DEPTH_TEST);
    // W³¹czenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}

 

/*************************************************************************************/


