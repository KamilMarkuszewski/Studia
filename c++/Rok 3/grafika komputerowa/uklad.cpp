
/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi 
//  układu współrzednych

/*************************************************************************************/
#include <math.h>
#include <ctime>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>

#define UKL 5000.0
#define PI 3.1415
#define KROK 0.1 
typedef float point3[3];
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy kąty obrotu
int model = 1;
GLfloat skala = 200.0;

GLfloat tr_x = 0.0;
GLfloat tr_y = 0.0;
GLfloat tr_z = 0.0;
GLfloat a[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLfloat b[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
GLfloat kat[] = {1.0, 0.3, 1.2, 2.0, 0.9, 1.1, 0.5, 1.7, 1.5};
clock_t czas;
GLfloat rozmiar = 0.0;
GLfloat odl_c;



/*************************************************************************************/

// Funkcja rysująca osie układu współrzędnych


void spinEgg()
{
	if(rand()%999==0){
			if(rand()%490==0){
				theta[0] -= 0.1;
				if( theta[0] > 360.0 ) theta[0] -= 360.0;

				theta[1] -= 0.1;
				if( theta[1] > 360.0 ) theta[1] -= 360.0;

				theta[2] -= 0.1;
				if( theta[2] > 360.0 ) theta[2] -= 360.0;
				glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
	}

	if(clock() - czas > 10 ){

			GLfloat stosunek = 1.0; 
			
			
			for(int i=0; i<10;i++){
				GLfloat polos = a[0];
				
				if(i!=0){
					polos = pow((double)a[i],3.0);
					GLfloat polos_stara = pow((double)a[i-1],3.0);
					stosunek =  1.0 /sqrt(polos/polos_stara); 
					if(stosunek < 1.0) stosunek = 1.0;
				}
				// 2 prawo keplera
				GLfloat kroczek =  KROK/10.0;
				GLfloat alfa = 0.0;
				GLfloat pole = 0.0;

				GLfloat wzor_pole = 0.0;
				GLfloat wzor_tmp1_x = a[0] * cos(0.0);
				GLfloat wzor_tmp1_y = b[0] * sin(0.0);
				GLfloat wzor_d = sqrt(pow((double)wzor_tmp1_x-odl_c,2.0) + pow((double)wzor_tmp1_y,2.0));

				GLfloat wzor_tmp2_x = a[0] * cos(kroczek);
				GLfloat wzor_tmp2_y = b[0] * sin(kroczek);
				GLfloat wzor_d2 = sqrt(pow((double)wzor_tmp2_x-odl_c,2.0) + pow((double)wzor_tmp2_y,2.0));
				wzor_pole = abs(wzor_d * wzor_d2 * 0.5 * sin(kroczek));

				do{
					if(alfa >= 2*PI) alfa = 0.0f;
					alfa += kroczek;
					GLfloat tmp1_x = a[0] * cos(kat[i]);
					GLfloat tmp1_y = b[0] * sin(kat[i]);
					GLfloat d = sqrt(pow((double)tmp1_x-odl_c,2.0) + pow((double)tmp1_x,2.0));

					GLfloat tmp2_x = a[0] * cos(kat[i] + alfa);
					GLfloat tmp2_y = b[0] * sin(kat[i] + alfa);
					GLfloat d2 = sqrt(pow((double)tmp2_x-odl_c,2.0) + pow((double)tmp2_y,2.0));
					pole = abs(d * d2 * 0.5 * sin(alfa));
					
					
				} while(pole<wzor_pole*10.0);
				
			
				kat[i] += alfa*stosunek;
				if(kat[i] >= 2* PI) kat[i] =0.0f;
			
			}
			glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
			czas = clock();
		}

	}
}


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};
    // początek i koniec obrazu osi x

    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};
    // początek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};
    //  początek i koniec obrazu osi y

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

void uklad(){

	//
	// glutSolidSphere (GLdouble radius, GLint slices, GLint stacks)

	// pierwsza orbita
	GLfloat el_a = 6.0f;
	GLfloat el_b = 4.0f;
	a[0] = el_a;
	b[0] = el_b;
	GLfloat wspl_el = 4.0 / 6.0;
	odl_c = sqrt(abs(el_b * el_b - el_a * el_a));

	GLfloat planeta_x = 0.0f;
	GLfloat planeta_y = 0.0f;



	// slonce
	glTranslatef(odl_c, 0,0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(0.7f+rozmiar,100,100);
	glTranslatef(-odl_c, 0,0);


	
	// orbita merkury
	glColor3f(1.0, 1.0, 1.0);
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = el_a * cos(t);
		GLfloat y = el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 1.0, 0.5);
	planeta_x = el_a * cos(kat[0]);
	planeta_y = el_b * sin(kat[0]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.1f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);



	// orbita wenus
	glColor3f(1.0, 1.0, 1.0);
	GLfloat wenus_el_a = 10.0;
	GLfloat wenus_el_b = wspl_el * wenus_el_a;
	a[1] = wenus_el_a;
	b[1] = wenus_el_b;

	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = wenus_el_a * cos(t);
		GLfloat y = wenus_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 1.0, 0.3);
	planeta_x = wenus_el_a * cos(kat[1]);
	planeta_y = wenus_el_b * sin(kat[1]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.1f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);




	// orbita ziemia
	glColor3f(1.0, 1.0, 1.0);
	GLfloat ziemia_el_a = 15.0;
	GLfloat ziemia_el_b = wspl_el * ziemia_el_a;
	a[2] = ziemia_el_a;
	b[2] = ziemia_el_b;

	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = ziemia_el_a * cos(t);
		GLfloat y = ziemia_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(0.0, 0.0, 1.0);
	planeta_x = ziemia_el_a * cos(kat[2]);
	planeta_y = ziemia_el_b * sin(kat[2]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.2f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);


	// orbita mars
	glColor3f(1.0, 1.0, 1.0);
	GLfloat mars_el_a = 22.0;
	GLfloat mars_el_b = wspl_el * mars_el_a;
	a[3] = mars_el_a;
	b[3] = mars_el_b;
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = mars_el_a * cos(t);
		GLfloat y = mars_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 0.0, 0.0);
	planeta_x = mars_el_a * cos(kat[3]);
	planeta_y = mars_el_b * sin(kat[3]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.1f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);


	// orbita jowisz
	glColor3f(1.0, 1.0, 1.0);
	GLfloat jowisz_el_a = 778.0;
	GLfloat jowisz_el_b = wspl_el * jowisz_el_a;
	a[4] = jowisz_el_a;
	b[4] = jowisz_el_b;
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = jowisz_el_a * cos(t);
		GLfloat y = jowisz_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 1.0, 0.3);
	planeta_x = jowisz_el_a * cos(kat[4]);
	planeta_y = jowisz_el_b * sin(kat[4]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(1.1f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);

	// orbita saturn
	glColor3f(1.0, 1.0, 1.0);
	GLfloat saturn_el_a = 1427.0;
	GLfloat saturn_el_b = wspl_el * saturn_el_a;
	a[5] = saturn_el_a;
	b[5] = saturn_el_b;
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = saturn_el_a * cos(t);
		GLfloat y = saturn_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 1.0, 0.3);
	planeta_x = saturn_el_a * cos(kat[5]);
	planeta_y = saturn_el_b * sin(kat[5]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.8f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);


	// orbita uran
	glColor3f(1.0, 1.0, 1.0);
	GLfloat uran_el_a = 2871.0;
	GLfloat uran_el_b = wspl_el * uran_el_a;
	a[6] = uran_el_a;
	b[6] = uran_el_b;
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = uran_el_a * cos(t);
		GLfloat y = uran_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 0.3, 0.3);
	planeta_x = uran_el_a * cos(kat[6]);
	planeta_y = uran_el_b * sin(kat[6]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.6f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);



	// orbita neptun
	glColor3f(1.0, 1.0, 1.0);
	GLfloat neptun_el_a = 4500.0;
	GLfloat neptun_el_b = wspl_el * neptun_el_a;
	a[8] = neptun_el_a;
	b[8] = neptun_el_b;
	for(float t=0; t<2*PI; t+=KROK){
		GLfloat x = neptun_el_a * cos(t);
		GLfloat y = neptun_el_b * sin(t);
		glBegin(GL_POINTS);
		glVertex3f(x, y, 0.0f);
		glEnd();
	}
	glColor3f(1.0, 0.3, 0.3);
	planeta_x = neptun_el_a * cos(kat[7]);
	planeta_y = neptun_el_b * sin(kat[7]);
	glTranslatef(planeta_x, planeta_y,0);
	glutSolidSphere(0.3f+rozmiar,10,10);
	glTranslatef(-planeta_x, -planeta_y,0);




}





/*************************************************************************************/

// Funkcja określająca co ma być rysowane (zawsze wywoływana gdy trzeba
// przerysować scenę)

void RenderScene(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszczącym
    glLoadIdentity();
    // Czyszczenie macierzy bieżącej

    //Axes();
    // Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej 

	glTranslatef(tr_x, tr_y, 0.0f);
	glScalef (skala,skala,skala);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na biały 
	uklad();
	


	










    glFlush();
    // Przekazanie poleceń rysujących do wykonania

 

    glutSwapBuffers();
    // 

 }

/*************************************************************************************/

// Funkcja ustalająca stan renderowania

 void keys(unsigned char key, int x, int y)
{
    if(key == '+' || key == '=') skala += 1.0;

    if(key == '-' || key == '_') skala -= 1.0;
	if(key == 'd' ) tr_x -= 50.0 ;
	if(key == 'a' ) tr_x += 50.0 ;

	if(key == 'w' ) tr_y += 50.0 ;
	if(key == 's' ) tr_y -= 50.0 ;

	if(key == 'r' ) rozmiar += 0.1 ;
	
	if(rozmiar > 20.0 ) rozmiar = 20.0;
	if(skala< 1.0) skala =1.0;
   
    RenderScene(); // przerysowanie obrazu sceny
}

void MyInit(void)
{

glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcący (wypełnienia okna) ustawiono na czarny

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

 

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

    GLfloat AspectRatio;
    // Deklaracja zmiennej AspectRatio  określającej proporcję
    // wymiarów okna 

 

    if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0

        vertical = 1;

 

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna widoku (viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

 

    glMatrixMode(GL_PROJECTION);
    // Przełączenie macierzy bieżącej na macierz projekcji

 

    glLoadIdentity();
    // Czyszcznie macierzy bieżącej           

 

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie współczynnika  proporcji okna
    // Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
    // przestrzeni ograniczającej pozwalającej zachować właściwe
    // proporcje rysowanego obiektu.
    // Do okreslenia przestrzeni ograniczjącej służy funkcja
    // glOrtho(...)            

 

    if(horizontal <= vertical)

        glOrtho(-UKL,UKL,-UKL/AspectRatio,UKL/AspectRatio,UKL, -UKL); 

    else

        glOrtho(-UKL*AspectRatio,UKL*AspectRatio,-UKL,UKL,UKL,-UKL);                      

    glMatrixMode(GL_MODELVIEW);
    // Przełączenie macierzy bieżącej na macierz widoku modelu                                   

    glLoadIdentity();
    // Czyszcenie macierzy bieżącej

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli

 

void main(void)
{          
	srand(time(NULL));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Układ sloneczny 3-D");
    glutIdleFunc(spinEgg);  
    glutDisplayFunc(RenderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną
    // (callback function).  Bedzie ona wywoływana za każdym razem
    // gdy zajdzie potrzba przeryswania okna

 
	glutKeyboardFunc(keys);
    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
    // zazmiany rozmiaru okna                        

 

    MyInit();
    // Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczne  przed przystąpieniem do renderowania

    glEnable(GL_DEPTH_TEST);
    // Włączenie mechanizmu usuwania powierzchni niewidocznych

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}

 

/*************************************************************************************/


