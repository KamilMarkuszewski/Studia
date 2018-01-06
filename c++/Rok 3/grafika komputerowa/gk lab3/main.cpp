/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

/*************************************************************************************/
#include <math.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>


static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy k¹ty obrotu
GLfloat przestrzen = 100.0;
typedef GLfloat point3[3]; 

#define GLEBOKOSC 5
/*************************************************************************************/

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych



void Axes(void)
{

    point3  x_min = {-50.0, 0.0, 0.0};
    point3  x_max = { 50.0, 0.0, 0.0};
    // pocz¹tek i koniec obrazu osi x

    point3  y_min = {0.0, -50.0, 0.0};
    point3  y_max = {0.0,  50.0, 0.0};
    // pocz¹tek i koniec obrazu osi y

    point3  z_min = {0.0, 0.0, -50.0};
    point3  z_max = {0.0, 0.0,  50.0};
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
void troj_rekur(point3 gora, point3 pp, point3 pl, point3 tl, point3 tp, int gleb){
	gleb++;
	if(gleb < GLEBOKOSC){
		point3 sr_pp;
		sr_pp[0]= gora[0] + (pp[0]-gora[0])/2.0;
		sr_pp[1]= gora[1] + (pp[1]-gora[1])/2.0;
		sr_pp[2]= gora[2] + (pp[2]-gora[2])/2.0;

		point3 sr_pl;
		sr_pl[0]= gora[0] + (pl[0]-gora[0])/2.0;
		sr_pl[1]= gora[1] + (pl[1]-gora[1])/2.0;
		sr_pl[2]= gora[2] + (pl[2]-gora[2])/2.0;

		point3 sr_tl;
		sr_tl[0]= gora[0] + (tl[0]-gora[0])/2.0;
		sr_tl[1]= gora[1] + (tl[1]-gora[1])/2.0;
		sr_tl[2]= gora[2] + (tl[2]-gora[2])/2.0;

		point3 sr_tp;
		sr_tp[0]= gora[0] + (tp[0]-gora[0])/2.0;
		sr_tp[1]= gora[1] + (tp[1]-gora[1])/2.0;
		sr_tp[2]= gora[2] + (tp[2]-gora[2])/2.0;
		troj_rekur(gora, sr_pp, sr_pl, sr_tl, sr_tp, gleb);



		point3 sr_srodek;
		sr_srodek[0]= pp[0] -((pp[0] - pl[0])/2.0);			//gora[0];
		sr_srodek[1]= pl[1];
		sr_srodek[2]= pp[2] -((pp[2] - tp[2])/2.0);


		point3 sd_prz;
		sd_prz[0]= gora[0];
		sd_prz[1]= pp[1];
		sd_prz[2]= pp[2];


		point3 sd_l;
		sd_l[0]= tl[0];
		sd_l[1]= tl[1];
		sd_l[2]= gora[2];

		point3 sd_r;
		sd_r[0]= pp[0];
		sd_r[1]= pp[1];
		sd_r[2]= gora[2];

		point3 sd_tyl;
		sd_tyl[0]= gora[0];
		sd_tyl[1]= tl[1];
		sd_tyl[2]= tl[2];





		troj_rekur(sr_pl, sd_prz, pl, sd_l, sr_srodek, gleb);
		troj_rekur(sr_tl, sr_srodek, sd_l, tl, sd_tyl, gleb);
		troj_rekur(sr_tp, sd_r, sr_srodek, sd_tyl, tp, gleb);
		troj_rekur(sr_pp, pp, sd_prz, sr_srodek, sd_r, gleb);

	}
	else if(gleb == GLEBOKOSC){
		
		
		// przod
		glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_POLYGON);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_LINE_STRIP);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();

		


		//dol
		glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_POLYGON);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_LINE_STRIP);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glEnd();

		
		//lewa
		glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_POLYGON);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_LINE_STRIP);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(pl[0],pl[1],pl[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();

		
		//tyl
		glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_POLYGON);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_LINE_STRIP);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(tl[0],tl[1],tl[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();

		
		//prawa
		glColor3f(1.0f, 1.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_POLYGON);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);  // kolor rysowania 
		glBegin(GL_LINE_STRIP);
		glVertex3f(gora[0],gora[1],gora[2]);
		glVertex3f(tp[0],tp[1],tp[2]);
		glVertex3f(pp[0],pp[1],pp[2]);
		glVertex3f(gora[0],gora[1],gora[2]);
		glEnd();

		
	}

}


void trojkat(){
	point3 gora, pp, pl, tl, tp;
	
	GLfloat x1 = 0.0;
	GLfloat y1 = 50.0;
	GLfloat z1 = 0.0;
	gora[0] = x1;
	gora[1] = y1;
	gora[2] = x1;


	GLfloat x2 = y1 * 2.0 / sqrt(3.0);
	GLfloat y2 = -50.0;
	GLfloat z2 = y1 * 2.0 / sqrt(3.0);
	pp[0] = x2;
	pp[1] = y2;
	pp[2] = z2;


	GLfloat x3 = - (y1 * 2.0 / sqrt(3.0));
	GLfloat y3 = -50.0;
	GLfloat z3 = (y1 * 2.0 / sqrt(3.0));
	pl[0] = x3;
	pl[1] = y3;
	pl[2] = z3;



	GLfloat x4 =  -(y1 * 2.0 / sqrt(3.0));
	GLfloat y4 = -50.0;
	GLfloat z4 =  -(y1 * 2.0 / sqrt(3.0));
	tl[0] = x4;
	tl[1] = y4;
	tl[2] = z4;


	GLfloat x5 = (y1 * 2.0 / sqrt(3.0));
	GLfloat y5 = -50.0;
	GLfloat z5 = -(y1 * 2.0 / sqrt(3.0));
	tp[0] = x5;
	tp[1] = y5;
	tp[2] = z5;

	troj_rekur(gora, pp, pl, tl, tp, 0);


}


void RenderScene(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz¹cym
    glLoadIdentity();
    // Czyszczenie macierzy bie¿¹cej


    // Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej 
    glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y 
	glTranslatef(0,-5,0.0);
	
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	Axes();
	trojkat();






    glFlush();
    // Przekazanie poleceñ rysuj¹cych do wykonania

 

    glutSwapBuffers();
    // 

 }

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania


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

        glOrtho(-przestrzen,przestrzen,-przestrzen/AspectRatio,przestrzen/AspectRatio,przestrzen, -przestrzen); 

    else

        glOrtho(-przestrzen*AspectRatio,przestrzen*AspectRatio,-przestrzen,przestrzen,przestrzen,-przestrzen);                      

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
    glutInitWindowSize(300, 300);

    glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");
    glutIdleFunc(spinEgg);  
    glutDisplayFunc(RenderScene);
    // Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
    // (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
    // gdy zajdzie potrzba przeryswania okna

 
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


