/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>


static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy k�ty obrotu
GLfloat przestrzen = 100.0;
typedef float point3[3]; 
/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych



void Axes(void)
{

    point3  x_min = {-50.0, 0.0, 0.0};
    point3  x_max = { 50.0, 0.0, 0.0};
    // pocz�tek i koniec obrazu osi x

    point3  y_min = {0.0, -50.0, 0.0};
    point3  y_max = {0.0,  50.0, 0.0};
    // pocz�tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -50.0};
    point3  z_max = {0.0, 0.0,  50.0};
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
void trojkat(){
	GLfloat x1 = 0.0;
	GLfloat y1 = 50.0;
	GLfloat z1 = 0.0;

	GLfloat x2 = y1 * 2.0 / sqrt(3.0);
	GLfloat y2 = -50.0;
	GLfloat z2 = y1 * 2.0 / sqrt(3.0);

	GLfloat x3 = - (y1 * 2.0 / sqrt(3.0));
	GLfloat y3 = -50.0;
	GLfloat z3 = (y1 * 2.0 / sqrt(3.0));


	GLfloat x4 =  -(y1 * 2.0 / sqrt(3.0));
	GLfloat y4 = -50.0;
	GLfloat z4 =  -(y1 * 2.0 / sqrt(3.0));

	GLfloat x5 = (y1 * 2.0 / sqrt(3.0));
	GLfloat y5 = -50.0;
	GLfloat z5 = -(y1 * 2.0 / sqrt(3.0));


	glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 

	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glVertex3f(x1,y1,z1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glVertex3f(x4,y4,z4);
	glVertex3f(x5,y5,z5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,z1);
	glVertex3f(x3,y3,z3);
	glVertex3f(x4,y4,z4);
	glVertex3f(x1,y1,z1);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,z1);
	glVertex3f(x4,y4,z4);
	glVertex3f(x5,y5,z5);
	glVertex3f(x1,y1,z1);
	glEnd();



	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,z1);
	glVertex3f(x5,y5,z5);
	glVertex3f(x2,y2,z2);
	glVertex3f(x1,y1,z1);
	glEnd();

}


void RenderScene(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz�cym
    glLoadIdentity();
    // Czyszczenie macierzy bie��cej


    // Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej 
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y 
	glTranslatef(0,-5,0.0);
	Axes();
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	
	trojkat();






    glFlush();
    // Przekazanie polece� rysuj�cych do wykonania

 

    glutSwapBuffers();
    // 

 }

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania


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

        glOrtho(-przestrzen,przestrzen,-przestrzen/AspectRatio,przestrzen/AspectRatio,przestrzen, -przestrzen); 

    else

        glOrtho(-przestrzen*AspectRatio,przestrzen*AspectRatio,-przestrzen,przestrzen,przestrzen,-przestrzen);                      

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
    glutInitWindowSize(300, 300);

    glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");
    glutIdleFunc(spinEgg);  
    glutDisplayFunc(RenderScene);
    // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
    // (callback function).  Bedzie ona wywo�ywana za ka�dym razem
    // gdy zajdzie potrzba przeryswania okna

 
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


