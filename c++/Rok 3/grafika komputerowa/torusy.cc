

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>

typedef float point3[3];
static GLfloat theta2 = 0.0;   // kat obrotu obiektu y
static GLfloat viewer[]= {0.0, 0.0, 10.0};
static GLfloat theta = 0.0;   // kat obrotu obiektu
static GLfloat pix2angle;     // przelicznik pikseli na stopnie
static GLint status = 0;      // stan klawiszy myszy
static int x_pos_old=0;       // poprzednia pozycja kursora myszy
static int delta_x = 0;       
GLfloat skala = 1.0;
int ile = 0;
static int y_pos_old=0;       // poprzednia pozycja kursora myszy
static int delta_y = 0;     
GLfloat an = 0.0;
GLfloat sz = 0.0;
/*************************************************************************************/


void Axes(void)
{

    point3  x_min = {-5.0, 0.0, 0.0};
    point3  x_max = { 5.0, 0.0, 0.0};


    point3  y_min = {0.0, -5.0, 0.0};
    point3  y_max = {0.0,  5.0, 0.0};


    point3  z_min = {0.0, 0.0, -5.0};
    point3  z_max = {0.0, 0.0,  5.0};


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
void TorusString(){
	//glRotatef(45.0, 1.0, 1.0, 1.0);  
	
	for(int i =0;i<ile;i++){
		GLfloat kolor = 0.0 + i%11 /10.0; 
		if(i%3==0) glColor3f(kolor, kolor, 1.0);
		if(i%3==1) glColor3f(1.0, kolor, kolor);
		if(i%3==2) glColor3f(kolor,1.0, kolor);

		GLfloat przesuniecie =  (-1.5 + sz) * i;
		glTranslatef(przesuniecie,0,0);
		glRotatef(25.0+an, 1.0, 0.0, 0.0);  
		glRotatef(5.0, 1.0, 0.0, 1.0);  
		glutWireTorus(0.1, 1.0, 10,10);
		glTranslatef(-przesuniecie,0,0);
	
	}




	}


 

void RenderScene(void)
{
	if(status == 1)                    
	{
	   theta += delta_x*pix2angle;   
	}     

	if(status == 1)                    
	{
	   theta2 += delta_y*pix2angle;   
	}   

	//glRotatef(theta, 1.0, 1.0, 1.0);  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glScalef (skala,skala,skala);
	glRotatef(theta, 1.0, 1.0, 1.0);  
	glRotatef(theta2, 0.0, 1.0, 0.0);  
    Axes();



    glColor3f(1.0f, 1.0f, 1.0f);

    TorusString();
    // Narysowanie czajnika

    glFlush();


 

    glutSwapBuffers();


 }
/*************************************************************************************/



 

void MyInit(void)
{

glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}

/*************************************************************************************/



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0/(float)horizontal; 
    glMatrixMode(GL_PROJECTION);


    glLoadIdentity();


    gluPerspective(70, 1.0, 1.0, 300.0);



    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);

    else
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);


    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();


}

/*************************************************************************************/
 void keys(unsigned char key, int x, int y)
{
    if(key == '+' || key == '=') skala += 0.2*skala;

    if(key == '-' || key == '_') skala -= 0.2*skala;
	if(key == 'w') an += 5.0;
	if(key == 's') an -= 5.0;
	if(key == 'a') sz += 0.2;
	if(key == 'd') sz -= 0.2;

	if(key == 'n') ile += 1;

    if(key == 'u') ile -= 1;
	if(ile< 0) ile = 0;
	//if(ile> 10) ile = 10;
	if(skala< 1.0) skala =1.0;
	
    RenderScene(); // przerysowanie obrazu sceny
}

void Mouse(int btn, int state, int x, int y)
{


    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)       
    {
        x_pos_old=x;        
                            
        status = 1;   
		
    }
    else
        status = 0;         
}

void Motion( GLsizei x, GLsizei y )
{
    delta_y=y-y_pos_old;   

    y_pos_old=y;  

    delta_x=x-x_pos_old;   

    x_pos_old=x;            
	std::cout << "motion \n";
    glutPostRedisplay();    
}

 

void main(void)
{          

	
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

    glutInitWindowSize(300, 300);

    glutCreateWindow("Rzutowanie perspektywiczne");
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);      
	glutKeyboardFunc(keys);
    glutDisplayFunc(RenderScene);


 

    glutReshapeFunc(ChangeSize);
    

 

    MyInit();


    glEnable(GL_DEPTH_TEST);
    

    glutMainLoop();


}

 

/*************************************************************************************/


