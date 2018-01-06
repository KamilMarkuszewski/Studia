

 

 /*************************************************************************************/


// Troch� bardziej skomplikowany program wykorzystuj�cy funkcje biblioteki OpenGL

 

/*************************************************************************************/
#define GLEBOKOSC 7
#define PETURB 1

#include <windows.h>
#include <math.h>
#include <gl/gl.h>

#include <gl/glut.h>

/*************************************************************************************/


// Funkcaja okre�laj�ca, co ma by� rysowane
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)
GLfloat w(GLfloat a){
	return 0.002 * (250.00 - a);
}

void mist(GLfloat x1,GLfloat x2,GLfloat y1,GLfloat y2, int gleb, GLfloat clewyg, GLfloat cprawyg, GLfloat clewyd, GLfloat cprawyd){

	gleb++; // inkrementacja glebokosci
	if(gleb<GLEBOKOSC+1){
	

		GLfloat clg = clewyg;
		GLfloat cpg = cprawyg;
		


		GLfloat cld = clewyd;
		GLfloat cpd = cprawyd;

		// rysowanie prostok�ta z losowymi kolorami
		glBegin(GL_TRIANGLE_FAN);

		//clg = (double)(rand()%100)/100;

		glColor3f(clg,clg, clg); // wierzcho�ek losowego koloru


		glVertex2f(x1, y1);
		
		//cpd = (double)(rand()%100)/100;

		glColor3f(cpg, cpg, cpg); // wierzcho�ek losowego koloru


		glVertex2f(x2, y1);

		//cld = (double)(rand()%100)/100;

		glColor3f(cpd, cpd, cpd); // wierzcho�ek losowego koloru

		glVertex2f(x2, y2);



		//cpg = (double)(rand()%100)/100;

		glColor3f(cld, cld, cld); // wierzcho�ek losowego koloru


		glVertex2f(x1, y2);

		glEnd();
		

		// dzielenie kwadratu
		GLfloat xsr = x1 + (x2-x1)/2;
		GLfloat ysr= y1 + (y2-y1)/2;

		GLfloat iks= (x2-x1)/2;

		GLfloat kolor_lewy =  (1 - 2*w(iks))*((double)(rand()%100)/100)+ w(iks)*clewyg + w(iks)*clewyd;
		GLfloat kolor_prawy = (1 - 2*w(iks))*((double)(rand()%100)/100)+ w(iks)*cprawyg + w(iks)*cprawyd;
		//GLfloat kolor_dolny = (double)(rand()%100)/100;
		//GLfloat kolor_gorny = (double)(rand()%100)/100;
		GLfloat kolor_gorny = (1 - 2*w(iks))*((double)(rand()%100)/100)+ w(iks)*clewyg + w(iks)*cprawyg;
		GLfloat kolor_dolny = (1 - 2*w(iks))*((double)(rand()%100)/100)+ w(iks)*clewyd + w(iks)*cprawyd;
		GLfloat kolor_srodek = (1-2*w(iks))*((double)(rand()%100)/100) + 2*w(iks)*clewyg + 2*w(iks)*cprawyg + 2*w(iks)*clewyd + 2*w(iks)*cprawyd ;

		mist(x1,xsr,y1,ysr,gleb,clg,kolor_gorny,kolor_lewy,kolor_srodek);
		mist(xsr,x2,y1,ysr,gleb,kolor_gorny,cpg,kolor_srodek, kolor_prawy);
		mist(x1,xsr,ysr,y2,gleb,kolor_lewy,kolor_srodek,cld,kolor_dolny);
		mist(xsr,x2,ysr,y2,gleb,kolor_srodek,kolor_prawy,kolor_dolny,cpd);
	
	} 

}


void dywan(GLfloat x1,GLfloat x2,GLfloat y1,GLfloat y2, int gleb){

	gleb++; // inkrementacja glebokosci
	if(gleb<GLEBOKOSC+1){
	

		GLfloat r = (double)(rand()%100)/100;
		GLfloat g = (double)(rand()%100)/100;
		GLfloat b = (double)(rand()%100)/100;

		GLfloat pet= (float)(rand() % PETURB*10) /10.0;
		if(rand()%1) pet *= -1;
		// rysowanie prostok�ta z losowymi kolorami
		glBegin(GL_POLYGON);

		r = (double)(rand()%100)/100;
		g = (double)(rand()%100)/100;
		b = (double)(rand()%100)/100;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru


		glVertex2f(x1+pet, y1+pet);

		r = (double)(rand()%100)/100;
		g = (double)(rand()%100)/100;
		b = (double)(rand()%100)/100;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru


		glVertex2f(x1+pet, y2+pet);

		r = (double)(rand()%100)/100;
		g = (double)(rand()%100)/100;
		b = (double)(rand()%100)/100;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru

		glVertex2f(x2+pet, y2+pet);



		r = (double)(rand()%100)/100;
		g = (double)(rand()%100)/100;
		b = (double)(rand()%100)/100;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru


		glVertex2f(x2, y1);

		glEnd();
		

		// dzielenie kwadratu
		GLfloat xlewy = x1 + (x2-x1)/3;
		GLfloat xprawy = x1 + 2*((x2-x1)/3);
		GLfloat ygorny = y1 + (y2-y1)/3;
		GLfloat ydolny = y1 + 2*((y2-y1)/3);
		
		
		//bia�y prostok�t
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru
		glBegin(GL_POLYGON);
		glVertex2f(xlewy, ygorny);
		glVertex2f(xlewy, ydolny);
		glVertex2f(xprawy, ydolny);
		glVertex2f(xprawy, ygorny);
		glEnd();
		
		dywan(x1,xlewy,y1,ygorny,gleb);
		dywan(xlewy,xprawy,y1,ygorny,gleb);
		dywan(xprawy,x2,y1,ygorny,gleb);



		dywan(x1,xlewy,ygorny,ydolny,gleb);
		//dywan(xlewy,xprawy,y1,ygorny,gleb); // ten srodkowy
		dywan(xprawy,x2,ygorny,ydolny,gleb);


		dywan(x1,xlewy,ydolny,y2,gleb);
		dywan(xlewy,xprawy,ydolny,y2,gleb);
		dywan(xprawy,x2,ydolny,y2,gleb);
	
	} 

}
void star(){
	GLfloat daleko = 80.0f;
	GLfloat blisko = daleko/4.0;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);	

	glVertex2f(0.0f, 0.0f);			
	
	glColor3f(1.0f, 1.0f, 0.0f);

	glVertex2f(0.0f, daleko);		
	glVertex2f(blisko, blisko);

	glVertex2f(daleko, 0.0f);	
	glVertex2f(blisko, -blisko);

	glVertex2f(0.0f, -daleko );	
	glVertex2f(-blisko, -blisko);


	glVertex2f( -daleko,0.0f);		
	glVertex2f(-blisko, blisko);
	glVertex2f(0.0f, daleko);	


	glEnd();

}
void sniezynka_odc(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat p0x, GLfloat p0y, int gleb){
	gleb++;
	// definiuje podzial odcinka na 3
	GLfloat dl_x = (x2 - x1) ;
	GLfloat dl_y = (y2 - y1);
	GLfloat x_new_sr = x1 + dl_x/2.0f;
	GLfloat y_new_sr = y1 + dl_y/2.0f;
	GLfloat x_new1 = x1 + dl_x/3.0f;
	GLfloat y_new1 = y1 + dl_y/3.0f;
	GLfloat x_new2 = x1 + 2.0f*dl_x/3.0f;
	GLfloat y_new2 = y1 + 2.0f*dl_y/3.0f;
	//definiuje  wypukly wierzcholek
	GLfloat dl_x_t = (x_new2 - x_new1) ;
	GLfloat dl_y_t = (y_new2 - y_new1);
	GLfloat a = sqrt((float)(dl_x_t*dl_x_t+dl_y_t*dl_y_t));
	GLfloat h = sqrt(3.0) * a/2.0f;
	GLfloat x_sr = 0.0f;
	GLfloat y_sr = 0.0f;
	GLfloat wspl_a = (x1-x2);
	if(wspl_a == 0){
		;
	}
	else{
		wspl_a = (y1-y2)/wspl_a;
	}
	if (wspl_a != 0){
		GLfloat wspl_pr = -1/wspl_a;
		GLfloat ha = h*wspl_pr / (sqrt(wspl_pr*wspl_pr+1));
		GLfloat hb = ha/wspl_pr;
		GLfloat x_sr_b = x_new_sr - hb;
		GLfloat y_sr_b = y_new_sr - ha;
		GLfloat x_sr_a = x_new_sr + hb;
		GLfloat y_sr_a = y_new_sr + ha;
		GLfloat da = sqrt((p0x-x_sr_a)*(p0x-x_sr_a)+(p0y-y_sr_a)*(p0y-y_sr_a));
		GLfloat db = sqrt((p0x-x_sr_b)*(p0x-x_sr_b)+(p0y-y_sr_b)*(p0y-y_sr_b));
		if (da > db){
			y_sr = y_sr_a;
			x_sr = x_sr_a;
		}
		else{
			y_sr = y_sr_b;
			x_sr = x_sr_b;
		}

	}
	if (wspl_a == 0){
		GLfloat y_sr_a = y_new_sr + h;
		GLfloat y_sr_b = y_new_sr - h;
		x_sr = x_new_sr ;
		GLfloat da = sqrt((p0x-x_sr)*(p0x-x_sr)+(p0y-y_sr_a)*(p0y-y_sr_a));
		GLfloat db = sqrt((p0x-x_sr)*(p0x-x_sr)+(p0y-y_sr_b)*(p0y-y_sr_b));
		if (da > db){
			y_sr = y_sr_a;
		}
		else{
			y_sr = y_sr_b;
		}
	}
	//rysuje ;)
	if(gleb<GLEBOKOSC)sniezynka_odc(x1, y1, x_new1, y_new1,0.0f,0.0f,gleb);
	glVertex2f(x_new1, y_new1);	
	if(gleb<GLEBOKOSC)sniezynka_odc(x_new1, y_new1, x_sr, y_sr,x_new_sr,y_new_sr,gleb);
	glVertex2f(x_sr, y_sr);
	if(gleb<GLEBOKOSC)sniezynka_odc(x_sr, y_sr, x_new2, y_new2,x_new_sr,y_new_sr,gleb);
	glVertex2f(x_new2, y_new2);	
	if(gleb<GLEBOKOSC)sniezynka_odc(x_new2, y_new2, x2, y2,0.0f,0.0f,gleb);
}

void trojkat(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat x3,GLfloat y3, int gleb){

	gleb++;						//inkrementacja glebokosci
	if(gleb<GLEBOKOSC+1){


		if(gleb==1){
			glColor3f(1.0f,1.0f,1.0f); 
			glBegin(GL_POLYGON);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);
			glVertex2f(x1, y1);
			glEnd();
		
		}


		GLfloat dl_x = (x2 - x1);
		GLfloat dl_y = (y2 - y1);
		GLfloat a_sr_x = x1 + dl_x/2.0f;
		GLfloat a_sr_y = y1 + dl_y/2.0f;
		
		dl_x = (x3 - x2);
		dl_y = (y3 - y2);
		GLfloat b_sr_x = x2 + dl_x/2.0f;
		GLfloat b_sr_y = y2 + dl_y/2.0f;
		
		dl_x = (x1 - x3);
		dl_y = (y1 - y3);
		GLfloat c_sr_x = x3 + dl_x/2.0f;
		GLfloat c_sr_y = y3 + dl_y/2.0f;

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_POLYGON);
		glVertex2f(a_sr_x, a_sr_y);
		glVertex2f(b_sr_x, b_sr_y);
		glVertex2f(c_sr_x, c_sr_y);
		glVertex2f(a_sr_x, a_sr_y);
		glEnd();

		trojkat(x1, y1, a_sr_x, a_sr_y, c_sr_x, c_sr_y, gleb);
		trojkat(a_sr_x, a_sr_y, x2, y2, b_sr_x, b_sr_y, gleb);
		trojkat(c_sr_x, c_sr_y, b_sr_x, b_sr_y, x3, y3, gleb);

		/*
		// dzielenie kwadratu
		GLfloat xlewy = x1 + (x2-x1)/3;
		GLfloat xprawy = x1 + 2*((x2-x1)/3);
		GLfloat ygorny = y1 + (y2-y1)/3;
		GLfloat ydolny = y1 + 2*((y2-y1)/3);
		
		
		//bia�y prostok�t
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		glColor3f(r, g, b); // wierzcho�ek losowego koloru
		glBegin(GL_POLYGON);
		glVertex2f(xlewy, ygorny);
		glVertex2f(xlewy, ydolny);
		glVertex2f(xprawy, ydolny);
		glVertex2f(xprawy, ygorny);
		glEnd();
		
		dywan(x1,xlewy,y1,ygorny,gleb);
		dywan(xlewy,xprawy,y1,ygorny,gleb);
		dywan(xprawy,x2,y1,ygorny,gleb);



		dywan(x1,xlewy,ygorny,ydolny,gleb);
		//dywan(xlewy,xprawy,y1,ygorny,gleb); // ten srodkowy
		dywan(xprawy,x2,ygorny,ydolny,gleb);


		dywan(x1,xlewy,ydolny,y2,gleb);
		dywan(xlewy,xprawy,ydolny,y2,gleb);
		dywan(xprawy,x2,ydolny,y2,gleb);
		*/
	
	} 

}
 void troj(){
	
	// definiuje rogi trojkata
	GLfloat bok = 100.0f;
	GLfloat h = bok * sqrt(3.0) / 2.0f ;
	GLfloat x1 = 0.0f;
	GLfloat y1 = h - h/3; //50.0f;
	GLfloat x2 = -50.0f;
	GLfloat y2 = - h/3; // -50.0f;
	GLfloat x3 = 50.0f;
	GLfloat y3 = - h/3;; 
	trojkat(x1, y1, x2, y2, x3, y3, 0);

}

 void sniezynka(){
	
	// definiuje rogi trojkata
	GLfloat bok = 100.0f;
	GLfloat h = bok * sqrt(3.0) / 2.0f ;

	GLfloat x1 = 0.0f;
	GLfloat y1 = h - h/3; //50.0f;

	GLfloat x2 = -50.0f;
	GLfloat y2 = - h/3; // -50.0f;

	GLfloat x3 = 50.0f;
	GLfloat y3 = - h/3;; 


	glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_LINE_STRIP);


	glVertex2f(x1, y1);	
	sniezynka_odc(x1, y1, x2, y2,0.0f, 0.0f,0);
	glVertex2f(x2, y2);		
	sniezynka_odc(x2, y2, x3, y3,0.0f, 0.0f,0);
	glVertex2f(x3,y3);
	sniezynka_odc(x3, y3, x1, y1,0.0f, 0.0f,0);
	glVertex2f(x1, y1);

	glEnd();

}
 

/*************************************************************************************/
void RenderScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT);   
	GLfloat x1 = -90.0f;
	GLfloat x2 = 90.0f;
	GLfloat y1 = -90.0f;
	GLfloat y2 = 90.0f;


	GLfloat c = (double)(rand()%100)/100;
	GLfloat c2 = (double)(rand()%100)/100;
	GLfloat c3 = (double)(rand()%100)/100;
	GLfloat c4 = (double)(rand()%100)/100;
	//dywan(x1,x2,y1,y2,0);
	//star();
	//mist(x1,x2,y1,y2,0,c,c2,c3,c4);
	//sniezynka();
	troj();
	
	glFlush(); 
                                      

}

/*************************************************************************************/

 

/*************************************************************************************/


// Funkcja ustalaj�ca stan renderowania


 

void MyInit(void)

{

   glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
   // Kolor okna wn�trza okna - ustawiono na szary

}

/*************************************************************************************/


// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna

{

     GLfloat AspectRatio;

     // Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

 

    if(vertical==0)
    // Zabezpieczenie pzred dzieleniem przez 0

        vertical = 1;

     glViewport(0, 0, horizontal, vertical);
     // Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
     // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION); 
    // Okre�lenie uk�adu wsp�rz�dnych obserwatora

    glLoadIdentity();
    // Okre�lenie przestrzeni ograniczaj�cej

    AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
    // Wyznaczenie wsp�czynnika proporcji okna

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // okre�lenie okna obserwatora.
    // Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
    // Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)


    if(horizontal <= vertical)

    glOrtho(-100.0,100.0,-100.0/AspectRatio,100.0/AspectRatio,1.0,-1.0);  

     else

    glOrtho(-100.0*AspectRatio,100.0*AspectRatio,-100.0,100.0,1.0,-1.0);

 

    glMatrixMode(GL_MODELVIEW);
    // Okre�lenie uk�adu wsp�rz�dnych    

    glLoadIdentity(); 

}

/*************************************************************************************/


// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli


 

void main(void)

{

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   // Ustawienie trybu wy�wietlania
   // GLUT_SINGLE - pojedynczy bufor wy�wietlania
   // GLUT_RGBA - model kolor�w RGB


   glutCreateWindow("lalala");
   // Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

   glutDisplayFunc(RenderScene);
   // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
   // Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
   // trzeba b�dzie przerysowa� okno


   glutReshapeFunc(ChangeSize);
   // Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
   // zmiany rozmiaru okna

   MyInit();
   // Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie 
   // inicjalizacje konieczneprzed przyst�pieniem do renderowania


   glutMainLoop();
   // Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/


