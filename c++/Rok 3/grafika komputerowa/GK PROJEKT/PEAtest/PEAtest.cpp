// RAY TRACING 
// KAMIL MARKUSZEWSKI 171016

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

/*************************************************************************************/
using namespace std;

typedef float punkt[3];
#define SKALA 1
#define MAX 2
#define R 5
#define PI 3.14

/*************************************************************************************/
punkt pkt;
int krok = 0;
float viewport_size =20.0;
int x_im_size = 0;
int y_im_size = 0;
float light_position[5][3]; 
float light_specular[5][3];
float light_diffuse[5][3];   
float light_ambient[5][3];
float tlo[3];
float sphere_radius[9];
float kula_wspl[9][3];
float sphere_specular[9][3];
float sphere_diffuse[9][3];
float sphere_ambient[9][3];
float sphere_specularhininess[9];
float theta = 360.0;
float global_a[3];
punkt starting_punkt;
punkt starting_directions = {0.0, 0.0, -1.0};
GLubyte pixel[1][1][3];

/*************************************************************************************/
struct punktTabsphere{
	punkt pkt;
	int light;
	int status;
	int nr_kuli;
};

struct struct_punkt{
	punkt pkt;
};
/*************************************************************************************/


void wczytaj(void);
float dl_vector(struct_punkt vec);
float dotProduct(punkt p1, punkt p2);
struct_punkt Normalization(punkt q);
struct_punkt Normal(punkt q , int nr_kuli);
struct_punkt Reflect(punkt startpunkt, punkt qsphere, punkt normal);
punktTabsphere Intersect(punkt punktStart, punkt direct);
struct_punkt Phong(punkt qsphere, punkt normal, punkt dest, int nr_sphere);
struct_punkt Trace(punkt startpunkt, punkt dest, int krok_loc);
void RenderScene( void);
void wczytaj(void);
void Myinit(void);
double rad(float stopien);
void spinEgg();

/*************************************************************************************/
double rad(float stopien){
	return (stopien*PI)/180;
}
void spinEgg(){
	glFlush();
	theta += 1.0;
	if( theta > 360.0 ) theta -= 360.0;

	kula_wspl[2][0] = R * cos(rad(theta-60.0));
	kula_wspl[2][1] = R * sin(rad(theta-60.0));

	kula_wspl[3][0] = R * cos(rad(theta));
	kula_wspl[3][1] = R * sin(rad(theta));

	kula_wspl[4][0] = R * cos(rad(theta+60.0));
	kula_wspl[4][1] = R * sin(rad(theta+60.0));

	kula_wspl[5][0] = R * cos(rad(theta+60.0+60.0));
	kula_wspl[5][1] = R * sin(rad(theta+60.0+60.0));

	kula_wspl[6][0] = R * cos(rad(theta+60.0+60.0+60.0));
	kula_wspl[6][1] = R * sin(rad(theta+60.0+60.0+60.0));

	kula_wspl[7][0] = R * cos(rad(theta+60.0+60.0+60.0+60.0));
	kula_wspl[7][1] = R * sin(rad(theta+60.0+60.0+60.0+60.0));

	cout << "Kat: " << theta << endl;
	glutPostRedisplay();

}

float dl_vector(struct_punkt vec){
	return (vec.pkt[0]*vec.pkt[0]+vec.pkt[1]*vec.pkt[1]+vec.pkt[2]*vec.pkt[2]);
}

float dotProduct(punkt p1, punkt p2){
	return (p1[0]*p2[0]+p1[1]*p2[1]+p1[2]*p2[2]);
}
struct_punkt Normal(punkt q , int nr_kuli){
	struct_punkt ret;
	ret.pkt[0] = (q[0] - kula_wspl[nr_kuli][0])/sphere_radius[nr_kuli];
	ret.pkt[1] = (q[1] - kula_wspl[nr_kuli][1])/sphere_radius[nr_kuli];
	ret.pkt[2] = (q[2] - kula_wspl[nr_kuli][2])/sphere_radius[nr_kuli];   
	return ret;
}

struct_punkt Normalization(punkt q){
	struct_punkt ret;
	ret.pkt[0] = 0.0;
	ret.pkt[1] = 0.0;
	ret.pkt[2] = 0.0;
	float d = 0.0;
	int i;
	for( i=0; i<3; i++){
		d += q[i] * q[i];
	}
    d = sqrt(d);
	if(0.0 < d){
		for( i=0; i<3; i++){
			ret.pkt[i] = q[i] / (d*1.0);
		}
	}
	return ret;
}



struct_punkt Reflect(punkt startpunkt, punkt qsphere, punkt normal){
	struct_punkt ret;
	punkt dv;
    dv[0] = startpunkt[0] - qsphere[0];
    dv[1] = startpunkt[1] - qsphere[1];
    dv[2] = startpunkt[2] - qsphere[2];

	struct_punkt direct_vec_loc;
    direct_vec_loc = Normalization(dv);   

	dv[0] = direct_vec_loc.pkt[0];
	dv[1] = direct_vec_loc.pkt[1];
	dv[2] = direct_vec_loc.pkt[2];
	float n_dot_l;
    n_dot_l = dotProduct(dv, normal);

	ret.pkt[0] = 2 * (n_dot_l) * normal[0]  - dv[0];
	ret.pkt[1] = 2 * (n_dot_l) * normal[1]  - dv[1];
	ret.pkt[2] = 2 * (n_dot_l) * normal[2]  - dv[2];
   
	if( 1.0 > dl_vector(ret) ){
		return ret;
	}
	else{
		return Normalization(ret.pkt);
	} 
}



punktTabsphere Intersect(punkt punktStart, punkt direct){
	punktTabsphere ret;
	ret.pkt[0] = 0.0;
	ret.pkt[1] = 0.0;
	ret.pkt[2] = 0.0;
	ret.nr_kuli = 0;
	ret.light = 0;
	ret.status = 0;

	int status = 0;
	int light = 0;

	float a, b, c, dl, r;

	for( int light = 0; light < 6; light++){
		float x,y,z;
		x = light_position[light][0] - punktStart[0];
		y = light_position[light][1] - punktStart[1];
		z = light_position[light][2] - punktStart[2];

		if( (x/direct[0]) == (y/direct[1]) && (y/direct[1]) == (z/direct[2]) ){
            ret.pkt[0] = light_position[light][0];
            ret.pkt[1] = light_position[light][1];
            ret.pkt[2] = light_position[light][2];
            ret.status = 2;
            return ret;
         }
   }

   for( int nr_kuli = 0; nr_kuli < 9; nr_kuli++){
		a = direct[0]*direct[0] + direct[1]*direct[1] + direct[2]*direct[2];

		b = 2*((punktStart[0] - kula_wspl[nr_kuli][0])*direct[0] + (punktStart[1] - kula_wspl[nr_kuli][1])*direct[1] + (punktStart[2] - kula_wspl[nr_kuli][2])*direct[2]);

		float c1 = (punktStart[0] * punktStart[0]  + punktStart[1] * punktStart[1]  + punktStart[2] * punktStart[2]);
		float c2 = (kula_wspl[nr_kuli][0] * kula_wspl[nr_kuli][0] + kula_wspl[nr_kuli][1] * kula_wspl[nr_kuli][1]+ kula_wspl[nr_kuli][2] * kula_wspl[nr_kuli][2]);
		float c3 = 2 * (punktStart[0] * kula_wspl[nr_kuli][0] + punktStart[1] * kula_wspl[nr_kuli][1] + punktStart[2] * kula_wspl[nr_kuli][2]);
		c = c1 + c2 - c3 - sphere_radius[nr_kuli]*sphere_radius[nr_kuli];
		dl = pow((double)b,2.0)-4*a*c; 

		if (dl>=0){
			r =( -b - sqrt(dl))/(2*a);   
            if( r > 0 ){
				ret.pkt[0] = punktStart[0] + r*direct[0];
				ret.pkt[1] = punktStart[1] + r*direct[1];
				ret.pkt[2] = punktStart[2] + r*direct[2];
				ret.nr_kuli = nr_kuli;
				ret.status = 3;
				break;
			}
		}
	}
	if( ret.status == 0){
		ret.status = 1;
	}
	return ret;
}


struct_punkt Phong(punkt qsphere, punkt normal, punkt dest, int nr_sphere){
	punkt light_vec;                   
	punkt reflection_vector;            

	float n_dot_l, v_dot_r;         
	struct_punkt kolor;
	kolor.pkt[0] = 0.0;
	kolor.pkt[1] = 0.0;
	kolor.pkt[2] = 0.0;
	punkt viewer_v = {0.0, 0.0, 1.0};  

	float a,b,c,wspl;
	a = 1.0;
	b = 0.1;
	c = 0.01;
	wspl = 1/(a+b+c);

	for( int k = 0; k < 5; k++){
		light_vec[0] = light_position[k][0] - qsphere[0];
		light_vec[1] = light_position[k][1] - qsphere[1];
		light_vec[2] = light_position[k][2] - qsphere[2];
      
		struct_punkt light_vec_loc;
		light_vec_loc = Normalization(light_vec);   
		light_vec[0] = light_vec_loc.pkt[0];
		light_vec[1] = light_vec_loc.pkt[1];
		light_vec[2] = light_vec_loc.pkt[2];

		n_dot_l = dotProduct(light_vec, normal);
                                  
		reflection_vector[0] = 2*(n_dot_l)*normal[0] - light_vec[0];
		reflection_vector[1] = 2*(n_dot_l)*normal[1] - light_vec[1];
		reflection_vector[2] = 2*(n_dot_l)*normal[2] - light_vec[2];

		struct_punkt reflection_vector_loc;
		reflection_vector_loc = Normalization(reflection_vector);   
		reflection_vector[0] = reflection_vector_loc.pkt[0];
		reflection_vector[1] = reflection_vector_loc.pkt[1];
		reflection_vector[2] = reflection_vector_loc.pkt[2];

		v_dot_r = dotProduct(reflection_vector, viewer_v);

		if( v_dot_r < 0){
			v_dot_r = 0;
		}
        
		if( n_dot_l > 0){                   
			kolor.pkt[0] += wspl*(sphere_diffuse[nr_sphere][0]*light_diffuse[k][0]*n_dot_l + sphere_specular[nr_sphere][0]*light_specular[k][0]*pow(double(v_dot_r), double(sphere_specularhininess[nr_sphere])) ) + sphere_ambient[nr_sphere][0]*light_ambient[k][0] + sphere_ambient[nr_sphere][0]*global_a[0];
			kolor.pkt[1] += wspl*(sphere_diffuse[nr_sphere][1]*light_diffuse[k][1]*n_dot_l + sphere_specular[nr_sphere][1]*light_specular[k][1]*pow(double(v_dot_r), double(sphere_specularhininess[nr_sphere])) ) + sphere_ambient[nr_sphere][1]*light_ambient[k][1] + sphere_ambient[nr_sphere][1]*global_a[1];
			kolor.pkt[2] += wspl*(sphere_diffuse[nr_sphere][2]*light_diffuse[k][2]*n_dot_l + sphere_specular[nr_sphere][2]*light_specular[k][2]*pow(double(v_dot_r), double(sphere_specularhininess[nr_sphere])) ) + sphere_ambient[nr_sphere][2]*light_ambient[k][2] + sphere_ambient[nr_sphere][2]*global_a[2];
		}
		else{                 
			kolor.pkt[0] += sphere_ambient[nr_sphere][0]*global_a[0];
			kolor.pkt[1] += sphere_ambient[nr_sphere][1]*global_a[1];
			kolor.pkt[2] += sphere_ambient[nr_sphere][2]*global_a[2];
		}
	}
	return kolor;
}

struct_punkt Trace(punkt startpunkt, punkt dest, int krok_loc){
	punkt qsphere; 
	punkt normal; 
	punkt reflect; 
	int status;
	int nr_light; 
	int nr_sphere; 

	struct_punkt local;
	local.pkt[0] = 0.0;         
    local.pkt[1] = 0.0;         
    local.pkt[2] = 0.0;

	struct_punkt reflected;
	reflected.pkt[0] = 0.0;         
    reflected.pkt[1] = 0.0;         
    reflected.pkt[2] = 0.0;

   if( krok_loc > MAX){
		local.pkt[0] += tlo[0];         
		local.pkt[1] += tlo[1];         
		local.pkt[2] += tlo[2];
		return local;
	}

	punktTabsphere q_loc;
	q_loc = Intersect(startpunkt,dest);   
	qsphere[0] = q_loc.pkt[0];
	qsphere[1] = q_loc.pkt[1];
	qsphere[2] = q_loc.pkt[2];
	nr_sphere = q_loc.nr_kuli;
	nr_light = q_loc.light;
	status = q_loc.status;

	if( status == 2){
		local.pkt[0] += light_specular[nr_light][0];         
        local.pkt[0] += light_specular[nr_light][1];         
        local.pkt[0] += light_specular[nr_light][2];
        return local;
	}

	if( status == 1){
		local.pkt[0] += tlo[0];         
		local.pkt[0] += tlo[1];         
		local.pkt[0] += tlo[2];
		return local;
	}
	struct_punkt n_loc;
    n_loc = Normal(qsphere,nr_sphere);
    normal[0] = n_loc.pkt[0];
    normal[1] = n_loc.pkt[1];
    normal[2] = n_loc.pkt[2];
    struct_punkt r_loc;
    r_loc = Reflect(startpunkt,qsphere,normal);
    reflect[0] = r_loc.pkt[0];
    reflect[1] = r_loc.pkt[1];
    reflect[2] = r_loc.pkt[2];
    local = Phong(qsphere,normal,dest, nr_sphere);
    reflected = Trace(qsphere, reflect, krok_loc+1);
	local.pkt[0] += reflected.pkt[0];         
    local.pkt[1] += reflected.pkt[1];
	local.pkt[2] += reflected.pkt[2];
	return local;
};


void RenderScene( void){
	int  x, y;
	float x_fl, y_fl;
	int x_im_size_2;
	int y_im_size_2;

	x_im_size_2 = x_im_size/2;   
	y_im_size_2 = y_im_size/2;
    glClear(GL_COLOR_BUFFER_BIT);





    for( y = y_im_size_2; y > -y_im_size_2; y--){
		for( x = -x_im_size_2; x < x_im_size_2; x++){
			x_fl = (float)x/(x_im_size/viewport_size);       
			y_fl = (float)y/(y_im_size/viewport_size);       
			starting_punkt[0] =  x_fl;           
			starting_punkt[1] =  y_fl;
			starting_punkt[2] =  viewport_size;

			struct_punkt kolor;
			kolor = Trace(starting_punkt, starting_directions, krok);

			if( kolor.pkt[0] > 1){
				pixel[0][0][0] = 255;
			}
			else{
				pixel[0][0][0] = kolor.pkt[0]*255;
			}
       

			if( kolor.pkt[1] > 1){
				pixel[0][0][1] = 255;
			}
			else{
				pixel[0][0][1] = kolor.pkt[1]*255;
			}
       

			if( kolor.pkt[2] > 1){
				pixel[0][0][2] = 255;
			}
			else{
				pixel[0][0][2] = kolor.pkt[2]*255;
			}
       

        glRasterPos3f(x_fl, y_fl, 0);
        glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        }
    }


	glFlush();  
}

void wczytaj(void){
	string szukaj;
	ifstream plik;
	plik.open( "scene.txt" );
	if( plik.is_open() == false){
		cout << "Nie znaleziono pliku :( buuu " << endl;
	}
	else{
		while( szukaj.find("dimensions") == string::npos ){
			plik >> szukaj;
		}
		plik >> x_im_size;
		plik >> y_im_size;
		x_im_size = x_im_size/SKALA;
		y_im_size = y_im_size/SKALA;


		while( szukaj.find("background") == string::npos ){
			plik >> szukaj;
		}

		plik >> tlo[0];
		plik >> tlo[1];
		plik >> tlo[2];

		while( szukaj.find("global") == string::npos ){
			plik >> szukaj;
		}

		plik >> global_a[0];
		plik >> global_a[1];
		plik >> global_a[2];
		int i_sp = 0;
		int i_so = 0;

		do{
			plik >> szukaj;

			if( szukaj == "sphere"){
				plik >> sphere_radius[i_sp];

				plik >> kula_wspl[i_sp][0];
				plik >> kula_wspl[i_sp][1];
				plik >> kula_wspl[i_sp][2];

				plik >> sphere_specular[i_sp][0];
				plik >> sphere_specular[i_sp][1];
				plik >> sphere_specular[i_sp][2];

				plik >> sphere_diffuse[i_sp][0];
				plik >> sphere_diffuse[i_sp][1];
				plik >> sphere_diffuse[i_sp][2];

				plik >> sphere_ambient[i_sp][0];
				plik >> sphere_ambient[i_sp][1];
				plik >> sphere_ambient[i_sp][2];
				plik >> sphere_specularhininess[i_sp];

				i_sp++;
		}
		else{
			if( szukaj == "source"){

				plik >> light_position[i_so][0]; 
				plik >> light_position[i_so][1];
				plik >> light_position[i_so][2];
				plik >> light_specular[i_so][0]; 
				plik >> light_specular[i_so][1];
				plik >> light_specular[i_so][2];
				plik >> light_diffuse[i_so][0];
				plik >> light_diffuse[i_so][1];
				plik >> light_diffuse[i_so][2];
				plik >> light_ambient[i_so][0];
				plik >> light_ambient[i_so][1];
				plik >> light_ambient[i_so][2];
				i_so++;
			}
		} 

	}while( szukaj.find("eof") == string::npos );
      
    cout << "Wczytywanie zakonczone" << endl;
      
	plik.close();
	}
}


void Myinit(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-viewport_size/2.0f, viewport_size/2.0f, -viewport_size/2.0f, viewport_size/2.0f, -viewport_size/2.0f, viewport_size/2.0f);
    glMatrixMode(GL_MODELVIEW);
}


void main(void){

	system("Pause");
	wczytaj();
	glutInitWindowSize(x_im_size, y_im_size);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   
	glutCreateWindow("Kulki Kamil Markuszewski");
	glutIdleFunc(spinEgg); 
	Myinit();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
	int a;
	cin >> a;
}








