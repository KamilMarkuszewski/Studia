/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj? osi 
//  uk?adu wsp�?rz?dnych dla rzutowania perspektywicznego

/*************************************************************************************/

#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

typedef float point3[3];

static GLfloat viewer[]= {0.0, 0.0, 17.0};
// inicjalizacja po?o?enia obserwatora
static GLfloat theta3 = 0.0;   // k?t obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie
static GLfloat theta2 = 0.0;   // k?t obrotu obiektu
static GLfloat pix2angle2;     // przelicznik pikseli na stopnie
static GLint status = 0;      // stan klawiszy myszy
                              // 0 - nie naci?ni?to ?adnego klawisza
                              // 1 - naci?ni?ty zosta? lewy klawisz

static int x_pos_old=0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;       // r�?nica pomi?dzy pozycj? bie??c?
                              // i poprzedni? kursora myszy 
static int y_pos_old=0;       // poprzednia pozycja kursora myszy

static int delta_y = 0;       // r�?nica pomi?dzy pozycj? bie??c?
                              // i poprzedni? kursora myszy 
/*************************************************************************************/
    GLfloat light_ambient[] = {0.1, 0.3, 0.1, 1.0};
    // sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};       
    // sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
    // sk�adowe intensywno�ci �wiecenia �r�d�a �wiat�a powoduj�cego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]
/*************************************************************************************/ 
// Definicja materia�u z jakiego zrobiony jest czajnik

    GLfloat mat_ambient[]  = {1.0, 1.0, 1.0, 1.0};       
    // wsp�czynniki ka =[kar,kag,kab] dla �wiat�a otoczenia

    GLfloat mat_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    // wsp�czynniki kd =[kdr,kdg,kdb] �wiat�a rozproszonego

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // wsp�czynniki ks =[ksr,ksg,ksb] dla �wiat�a odbitego               
   
    GLfloat mat_shininess  = {20.0};
    // wsp�czynnik n opisuj�cy po�ysk powierzchni

// Funkcja rysuj?ca osie uk?adu wsp�?rz?dnych
#define N 100.0
#define PI 3.1415
typedef float point3[3];
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy k�ty obrotu
int model = 1;
/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych

GLfloat f_x(GLfloat u,GLfloat v){
return cos(PI*v)*(-90.0*u*u*u*u*u + 225.0*u*u*u*u - 270.0*u*u*u + 180.0*u*u - 45*u);
}

GLfloat f_y(GLfloat u,GLfloat v){
return 160.0*u*u*u*u -320.0*u*u*u + 160.0*u*u;
}

GLfloat f_z(GLfloat u,GLfloat v){
return sin(PI*v)*(-90.0*u*u*u*u*u + 225.0*u*u*u*u - 270.0*u*u*u + 180.0*u*u - 45.0*u);
}
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


 void Mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)       
    {
        y_pos_old=y;        // przypisanie aktualnie odczytanej pozycji kursora
        x_pos_old=x;        // przypisanie aktualnie odczytanej pozycji kursora
                            // jako pozycji poprzedniej
        status = 1;         // wci?ni?ty zosta? lewy klawisz myszy
    }
    else

        status = 0;         // nie zosta? wci?ni?ty ?aden klawisz
	
}

/*************************************************************************************/

// Funkcja "monitoruje" po?o?enie kursora myszy i ustawia warto?ci odpowiednich
// zmiennych globalnych

void Motion( GLsizei x, GLsizei y )
{
    delta_y=y-y_pos_old;    // obliczenie r�?nicy po?o?enia kursora myszy
	
    y_pos_old=y;  
	cout << delta_y;
	// podstawienie bie?acego po?o?enia jako poprzednie
    delta_x=x-x_pos_old;    // obliczenie r�?nicy po?o?enia kursora myszy
    x_pos_old=x;            // podstawienie bie?acego po?o?enia jako poprzednie

    glutPostRedisplay();    // przerysowanie obrazu sceny
}


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    // pocz?tek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    // pocz?tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    //  pocz?tek i koniec obrazu osi y

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

/*************************************************************************************/

// Funkcja okre?laj?ca co ma by? rysowane (zawsze wywo?ywana, gdy trzeba
// przerysowa? scen?)

 

void RenderScene(void)
{
	if(status == 1)                    // je?li lewy klawisz myszy wci?ni?ty
      {
         theta3 += delta_x*pix2angle;    // modyfikacja k?ta obrotu o k?t proporcjonalny
		 theta2 += delta_y*pix2angle2;    // modyfikacja k?ta obrotu o k?t proporcjonalny
      }                                 // do r�?nicy po?o?e? kursora myszy



     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz?cym

    glLoadIdentity();
    // Czyszczenie macierzy bie??cej

    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // Zdefiniowanie po?o?enia obserwatora

    Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej powy?ej

	
    glColor3f(1.0f, 1.0f, 1.0f);
    // Ustawienie koloru rysowania na bia?y
	glRotatef(theta3, 0.0, 1.0, 0.0);  //obr�t obiektu o nowy k?t
	glRotatef(theta2, 1.0, 0.0, 0.0);  //obr�t obiektu o nowy k?t

	

	jajko_troj();
	
    // Narysowanie czajnika

    glFlush();
    // Przekazanie polece? rysuj?cych do wykonania

 

    glutSwapBuffers();
    // 

 }
/*************************************************************************************/

// Funkcja ustalaj?ca stan renderowania

 

void MyInit(void)
{

/*************************************************************************************/

//  Definicja materia�u z jakiego zrobiony jest czajnik
//  i definicja �r�d�a �wiat�a

/*************************************************************************************/


/*************************************************************************************/
// Definicja �r�d�a �wiat�a

     GLfloat light_position[] = {10.0, 6.0, 10.0, 1.0};   
    // po�o�enie �r�d�a




    GLfloat att_constant  = {1.0};
    // sk�adowa sta�a ds dla modelu zmian o�wietlenia w funkcji
    // odleg�o�ci od �r�d�a

    GLfloat att_linear    = {0.05};
    // sk�adowa liniowa dl dla modelu zmian o�wietlenia w funkcji
    // odleg�o�ci od �r�d�a

    GLfloat att_quadratic  = {0.001};
    // sk�adowa kwadratowa dq dla modelu zmian o�wietlenia w funkcji
    // odleg�o�ci od �r�d�a

/*************************************************************************************/
                                      
// Ustawienie parametr�w materia�u i �r�d�a �wiat�a

/*************************************************************************************/
// Ustawienie patrametr�w materia�u


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

/*************************************************************************************/
// Ustawienie parametr�w �r�d�a

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


/*************************************************************************************/
// Ustawienie opcji systemu o�wietlania sceny

    glShadeModel(GL_SMOOTH); // w�aczenie �agodnego cieniowania
    glEnable(GL_LIGHTING);   // w�aczenie systemu o�wietlenia sceny
    glEnable(GL_LIGHT0);     // w��czenie �r�d�a o numerze 0
    glEnable(GL_DEPTH_TEST); // w��czenie mechanizmu z-bufora

/*************************************************************************************/
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcz?cy (wype?nienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta?ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko?? i szeroko?? okna) s?
// przekazywane do funkcji za ka?dym razem gdy zmieni si? rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0/(float)horizontal; // przeliczenie pikseli na stopnie
	pix2angle2 = 360.0/(float)vertical; // przeliczenie pikseli na stopnie
    glMatrixMode(GL_PROJECTION);
    // Prze??czenie macierzy bie??cej na macierz projekcji
	
    glLoadIdentity();
    // Czyszcznie macierzy bie??cej
	
    gluPerspective(70, 1.0, 1.0, 30.0);
    // Ustawienie parametr�w dla rzutu perspektywicznego


    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);

    else
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);
    // Ustawienie wielko?ci okna okna widoku (viewport) w zale?no?ci
    // relacji pomi?dzy wysoko?ci? i szeroko?ci? okna

    glMatrixMode(GL_MODELVIEW);
    // Prze??czenie macierzy bie??cej na macierz widoku modelu  

    glLoadIdentity();
    // Czyszczenie macierzy bie??cej

}
void keys(unsigned char key, int x, int y)
{
	GLfloat r= 1.0;
	GLfloat g= 1.0;
	GLfloat b= 1.0;
	if(key == 'r') {
		r = 1.0;
		g = 0.0;
		b = 0.0;
	}
	if(key == 'g'){
     	r = 0.0;
		g = 1.0;
		b = 0.0;
	}
	if(key == 'b'){
		r = 0.0;
		g = 0.0;
		b = 1.0;
	}
   	mat_ambient[0]=r;     
	mat_diffuse[0]=r;
	mat_specular[0]=r;  

   	mat_ambient[1]=g;     
	mat_diffuse[1]=g;
	mat_specular[1]=g;   

   	mat_ambient[2]=b;     
	mat_diffuse[2]=b;
	mat_specular[2]=b;   

    light_ambient[0]= r; 
    light_diffuse[0] = r;       
	light_specular[0]= r;

    light_ambient[1]= g; 
    light_diffuse[1] = g;       
	light_specular[1]= g;

    light_ambient[2]= b; 
    light_diffuse[2] = b;       
	light_specular[2]= b;


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

/*************************************************************************************/
// Ustawienie parametr�w �r�d�a

    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    RenderScene(); // przerysowanie obrazu sceny
}
/*************************************************************************************/

// G?�wny punkt wej?cia programu. Program dzia?a w trybie konsoli

 

void main(void)
{          

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	jajko();
    glutInitWindowSize(300, 300);

    glutCreateWindow("Rzutowanie perspektywiczne");
      

      
    glutDisplayFunc(RenderScene);
    // Okre?lenie, ?e funkcja RenderScene b?dzie funkcj? zwrotn?
    // (callback function).  B?dzie ona wywo?ywana za ka?dym razem
    // gdy zajdzie potrzeba przerysowania okna

	glutKeyboardFunc(keys);
 	glutMouseFunc(Mouse);
	// Ustala funkcj? zwrotn? odpowiedzialn? za badanie stanu myszy
	glutMotionFunc(Motion);
	// Ustala funkcj? zwrotn? odpowiedzialn? za badanie ruchu myszy


    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcj? zwrotn? odpowiedzialn?
    // za zmiany rozmiaru okna                        

    MyInit();
    // Funkcja MyInit() (zdefiniowana powy?ej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przyst?pieniem do renderowania

    glEnable(GL_DEPTH_TEST);
    // W??czenie mechanizmu usuwania niewidocznych element�w sceny

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}

 

/*************************************************************************************/

 