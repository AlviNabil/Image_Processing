#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"


#include <iostream>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0, theta_fan_rotate = 0.0, tap_dis1 = 4.5, tap_dis2 = 4.3;
GLboolean bRotate = false, uRotate = false, tRotate = false, fan_Rotate = false,light_0_on = false, light_1_on = false, light_2_on = false, light_toggle = false, tap_open = false;
GLboolean  amb_light_0 = true, dif_light_0 = true, spec_light_0 = true, amb_light_1 = true, dif_light_1 = true, spec_light_1 = true, amb_light_2 = true, dif_light_2 = true, spec_light_2 = true;
GLboolean activate_pitch = false, activate_yaw = false, activate_roll = false;


GLfloat eyeX = 0;
GLfloat eyeY = 3;
GLfloat eyeZ = 120;

GLfloat lookX = 0;
GLfloat lookY = 3;
GLfloat lookZ = 50;


GLfloat upx = 0;
GLfloat upy = 1;
GLfloat upz = 0;



GLfloat scale_x = 1;
GLfloat scale_y = 1;
GLfloat scale_z = 1;

double limit = 360;
double roll_value = 5;
GLfloat angleYaw =90.0, anglePitch = 0.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 90.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = -90.0, angleRollLimit2 = -90.0;

int f = 0;




GLfloat PI = 3.14159265;
static GLfloat cube[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0},
    {-1.0, 1.0, -1.0},

};



//static GLubyte p_Indices[2][3] =
//{
//    {0, 1, 2},
//    {3, 4, 5}
//};

static GLubyte quadIndices[6][4] =
{
    {0,1,2,3},
    {7,6,5,4},
    {2,6,7,3},

    {0,4,5,1},
    {2,1,5,6},
    {7,4,0,3},

};

static GLfloat colors[6][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.5,0.5,0.5},
};

void drawcube(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {r,g,b,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);




    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);

        glVertex3fv(&cube[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();
    }



}

int i = 1;
GLuint ID_[100];

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID_[i]);
    glBindTexture(GL_TEXTURE_2D, ID_[i]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[i++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}



void draw_room()
{

    //floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,0.1,20);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(168, 168, 168);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //tiles
    for(GLint hCount=1; hCount<26; hCount+=4)
    {
        for(GLint vCount=1; vCount<26; vCount+=4)
        {
            if((hCount+vCount)%2==0)
            {
                glEnable(GL_TEXTURE_2D);
                glPushMatrix();
                glScalef(1.5,0.05,1.5);
                glTranslatef(-(20-hCount*1.5)/1.5,0.105/0.05,-(20-vCount*1.5)/1.5);
                glBindTexture(GL_TEXTURE_2D, 2);
                drawcube(255,255,255);
                glPopMatrix();
                glDisable(GL_TEXTURE_2D);
            }

        }

    }


    //left wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,10,0);
    glRotatef(-90,0,1,0);
    glScalef(20,10,.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//
    //right wall
//    glPushMatrix();
//    glScalef(.005,10,20);
//    glTranslatef(20/0.005,1,0);
//    drawcube(35, 89, 92);
//    glPopMatrix();
//


    //back wall left
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(-1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawcube(255,255,255);
    glPopMatrix();

    //backwall upper
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawcube(255,255,255);
    glPopMatrix();
    //backwall bottom
    glPushMatrix();
    glScalef(8,2.5,.1);
    glTranslatef(0,1,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawcube(255,255,255);
    glPopMatrix();
    //backwall top
    glPushMatrix();
    glScalef(8,2.5,.1);
    glTranslatef(0,7,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 9);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //windowframe
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.5,5,.1);
    glTranslatef(0,2,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(4,0.5,.1);
    glTranslatef(0,4*2.5/0.5,-20/0.1);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,5,.3);
    glTranslatef(-8,2,-20/0.3);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,5,.3);
    glTranslatef(8,2,-20/0.3);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.9,0.5,.3);
    glTranslatef(0,5*3/0.5,-20/0.3);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glScalef(4.9,0.5,.3);
    glTranslatef(0,1.5*3/0.5,-20/0.3);
    glRotatef(180,0,1,0);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}



void draw_cabinet()
{
    //left cabinet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,2,4);
    glTranslatef(-8.99,1,-4);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //middle portion

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,1,4);
    glTranslatef(-8.99,1,-2);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,2,4);
    glTranslatef(-8.99,1,0);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //details for left cabinet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.2,1.5,1.9);
    glTranslatef(-16/.2,1.4,-7.4);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,1.5);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,-1.5);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //detail for middle portion
    glPushMatrix();
    glScalef(.2,.5,1.4);
    glTranslatef(-16/.2,2.1,-4.3);
    drawcube(125, 125, 125);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,.5,1.4);
    glTranslatef(-16/.2,2.1,-7.2);
    drawcube(125, 125, 125);
    glPopMatrix();
    //handles
    glPushMatrix();
    glTranslatef(-15.75,2.5,-12.6);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.75,2.5,-1.1);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.75,2.5,1.1);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();




    //back cabinet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glScalef(2,2,12);
    glTranslatef(-8.99,1,0.33);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //details for back cabinet
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(-4.5,1.4,-16/0.2);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //oven
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(-2,1.4,-16/0.2);
    glBindTexture(GL_TEXTURE_2D, 6);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //oven switch
    glPushMatrix();
    glTranslatef(-3,3.5,-15.6);
    glScalef(.165,.165,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.75,3.5,-15.6);
    glScalef(.165,.165,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.5,3.5,-15.6);
    glScalef(.165,.165,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.25,3.5,-15.6);
    glScalef(.165,.165,.25);
    drawcube(200,200,200);
    glPopMatrix();





    //handles
    glPushMatrix();
    glTranslatef(-3,2.5,-15.6);
    glScalef(.4,.165,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.8,2,-15.6);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.3,2,-15.6);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.3,2,-15.6);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(.5,1.4,-16/0.2);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.3,1.7,.2);
    glTranslatef(4.8,1.18,-16/0.2);
    glBindTexture(GL_TEXTURE_2D, 7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //strips
    glPushMatrix();
    glTranslatef(-8.2,2,-16);
    glScalef(0.1, 2, .1);
    drawcube(200, 180, 161);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.9,2,-16);
    glScalef(0.1, 2, .1);
    drawcube(200, 180, 161);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.3,2,-16);
    glScalef(0.1, 2, .1);
    drawcube(200, 180, 161);
    glPopMatrix();

}


void draw_basin()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,.1,3);
    glTranslatef(-9,10/.4,-2.65);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-5/.1);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-11/.1);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.8,3);
    glTranslatef(-16/.1,3.2/0.8,-2.65);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //tap
    glPushMatrix();
    glTranslatef(-19.6,6,-9);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-19.6,6,-7.2);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-19.1,5.5,-8.1);
    glScalef(.8,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.7,5.1,-8.1);
    glScalef(.2,.2,.2);
    drawcube(50,50,50);
    glPopMatrix();






}

void tap_water()
{
    glPushMatrix();
    glTranslatef(-18.7,tap_dis1,-8.2);
    glScalef(.2,.6,.1);
    drawcube(50,80,250);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-18.7,tap_dis2,-8.0);
    glScalef(.2,.6,.1);
    drawcube(50,50,250);
    glPopMatrix();
}

void draw_racks()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,2,3.6);
    glTranslatef(-8.99,1,3.9);
    glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glScalef(1.5,6,3.5);
    glTranslatef(-12.35,1.5,4);
    glBindTexture(GL_TEXTURE_2D, 4);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glScalef(2,.5,3.7);
    glTranslatef(-9.0,30,3.77);
    glBindTexture(GL_TEXTURE_2D, 5);
    drawcube(255,255,255);
    glPopMatrix();

    //details for racks
    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,12);
    drawcube(200, 162, 81);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,9.75);
    drawcube(200, 162, 81);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //strips for racks

    glPushMatrix();
    glTranslatef(-17,8,14);
    glScalef(.1,6,.1);
    drawcube(200, 180, 161);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-17,6,14);
    glRotatef(90,1,0,0);
    glScalef(.1,3.4,.1);
    drawcube(200, 180, 161);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17,8,14);
    glRotatef(90,1,0,0);
    glScalef(.1,3.4,.1);
    drawcube(200, 180, 161);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17,10,14);
    glRotatef(90,1,0,0);
    glScalef(.1,3.4,.1);
    drawcube(200, 180, 161);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-17,12,14);
    glRotatef(90,1,0,0);
    glScalef(.1,3.4,.1);
    drawcube(200, 180, 161);
    glPopMatrix();


    //handles
    glPushMatrix();
    glTranslatef(-15.75,2.5,13.5);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.75,2.5,14.75);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(200,200,200);
    glPopMatrix();
}

void draw_fridge()
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(15,4,-16.8);
    glScalef(3,4,3);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15,9,-16.8);
    glScalef(3,4,3);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(255,255,255);;
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(15,8.5,-16.8);
    glScalef(3.01,.5,3.01);
    drawcube(20,20,20);
    glPopMatrix();


    //handles
    glPushMatrix();
    glTranslatef(12.5,6.25,-13.75);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12.5,10.25,-13.75);
    glRotatef(90, 0,0,1);
    glScalef(.8,.15,.25);
    drawcube(22,22,22);
    glPopMatrix();


}


void draw_switch()
{
    glPushMatrix();
    glTranslatef(10,8,-19.8);
    glScalef(1,1,.1);
    drawcube(222,222,222);
    glPopMatrix();
    //fridge wires
    glPushMatrix();
    glTranslatef(10,4.5,-19.8);
    glScalef(.1,2.5,.1);
    drawcube(22,22,22);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(11,2,-19.8);
    glScalef(1,.1,.1);
    drawcube(22,22,22);
    glPopMatrix();

    //switches
    glPushMatrix();
    glTranslatef(10,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.6,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.4,8,-19.8);
    glScalef(.15,.4,.12);
    drawcube(122,72,222);
    glPopMatrix();
    //redLight
    glPushMatrix();
    glTranslatef(10.7,8.6,-19.8);
    glScalef(.15,.15,.12);
    drawcube(222,0,0,(light_0_on | light_1_on | light_2_on));
    glPopMatrix();

    //light
    glPushMatrix();
    glTranslatef(0.0,18,-19.8);
    glScalef(4,.5,.12);
    drawcube(222,222,222,light_1_on);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-19.8,18,2);
    glRotatef(90,0,1,0);
    glScalef(4,.5,.12);
    drawcube(222,222,222,light_2_on);
    glPopMatrix();

    //light wires
    glPushMatrix();
    glTranslatef(7,18,-19.8);
    glScalef(3,.1,.1);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,13,-19.8);
    glScalef(.1,5,.1);
    drawcube(22,22,22);
    glPopMatrix();
}


void draw_shelf()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,1);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-3);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-7);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-.8);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-8.8);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-4.8);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Teapot(GLint c1, GLint c2, GLint c3, GLfloat a)
{

    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidTeapot(a);

}
void draw_kettle()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,10.6,-5.8);
    glBindTexture(GL_TEXTURE_2D, 12);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,10.6,2);

    glBindTexture(GL_TEXTURE_2D, 14);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,10.6,-13.5);
    glBindTexture(GL_TEXTURE_2D, 15);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,7.3,-17.5);
    glBindTexture(GL_TEXTURE_2D, 14);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,7.3,-9.5);
    glBindTexture(GL_TEXTURE_2D, 15);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-18,7.3,-1.5);
    glBindTexture(GL_TEXTURE_2D, 12);
    Teapot(255, 255, 255,0.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void draw_stove()
{

    glPushMatrix();
    glTranslatef(-5,4.5,-18);
    glScalef(5,.5,1.7);
    drawcube(230,230,230);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,4.5,-16.2);
    glScalef(5,.5,.1);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.5,4.5,-16.2);
    glScalef(.1,.1,.25);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,4.5,-16.2);
    glScalef(.1,.1,.25);
    drawcube(200,200,200);
    glPopMatrix();

    //details
    glPushMatrix();
    glTranslatef(-7.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();





    glPushMatrix();
    glTranslatef(-7.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();





    glPushMatrix();
    glTranslatef(-0.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,5.0,-17.2);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,5.0,-19);
    glScalef(.2,.2,.2);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5,6.1,-18);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    Teapot(255, 255, 255,1.5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}


void draw_circle(void)
{
    float x, y;
    int i;
    GLfloat radius;
    int triangleAmount = 40;
    GLfloat twicePI = 2.0*PI;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(200,200,200);
    x = 0;
    y = 0;
    radius = 20;

    glVertex2f(x,y);
    for (i=0; i<=triangleAmount; i++);
    {
        glVertex3f(
            x+(radius*cos(i*twicePI/triangleAmount)),
            y+(radius*sin(i*twicePI/triangleAmount)),
            1
        );

    }
    glEnd();

}


void draw_fan()
{
    glPushMatrix();
    glTranslatef(-15.5,16,-19.8);
    glScalef(1.5,1.5,.2);
    drawcube(222,222,222);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15.5,16,-19.78);
    glScalef(1.2,1.2,.22);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glScalef(.2,.2,.3);
    drawcube(222,222,222);
    glPopMatrix();



    //fan wire
    glPushMatrix();
    glTranslatef(-3,16.5,-19.8);
    glScalef(12.2,.1,.1);
    drawcube(22,22,22);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.3,12.75,-19.8);
    glScalef(.1,3.75,.1);
    drawcube(22,22,22);
    glPopMatrix();
}

void fan_blade()
{
    glPushMatrix();

    //fanBlade
    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(45,0,0,1);
    glScalef(1.15,.2,.3);
    drawcube(222,222,222);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(45,0,0,1);
    glScalef(.2,1.15,.3);
    drawcube(222,222,222);
    glPopMatrix();
    glPopMatrix();

}


void draw_Cone(GLint c1, GLint c2, GLint c3,GLfloat a, GLfloat h)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();


    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);




    glutWireCone(a,h,100,100);
    glPopMatrix();


}
void draw_bulb()
{

    glPushMatrix();
    glTranslatef(-18, 16, -7);
    glScalef(2,.3,.3);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-17, 15, -7);
    glRotatef(-90, 1,0,0);
    draw_Cone(120,120,120,1,1);
    glPopMatrix();
}



void draw_Sphere(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {r,g,b,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);


    glutSolidSphere(2,100,100);
    glPopMatrix();


}


void light(double x, double y, double z, GLenum L, bool light_on, bool spot, GLfloat r=1.0, GLfloat g=1.0, GLfloat b=1.0)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {r*0.3, g*0.3, b*0.3, 1.0};
    GLfloat light_diffuse[]  = { r*0.6, g*0.6, b*0.6, 1.0 };
    GLfloat light_specular[] = { r*0.6, g*0.6, b*0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);

    if(light_on)
    {

        if(L==GL_LIGHT0)
        {
            if(amb_light_0) glLightfv( L, GL_AMBIENT, light_ambient);
            else glLightfv( L, GL_AMBIENT, no_light);

            if(dif_light_0) glLightfv( L, GL_DIFFUSE, light_diffuse);
            else glLightfv( L, GL_DIFFUSE, no_light);

            if(spec_light_0) glLightfv( L, GL_SPECULAR, light_specular);
            else glLightfv( L, GL_SPECULAR, no_light);

        }
        else if(L==GL_LIGHT1)
        {
            if(amb_light_1) glLightfv( L, GL_AMBIENT, light_ambient);
            else glLightfv( L, GL_AMBIENT, no_light);

            if(dif_light_1) glLightfv( L, GL_DIFFUSE, light_diffuse);
            else glLightfv( L, GL_DIFFUSE, no_light);

            if(spec_light_1) glLightfv( L, GL_SPECULAR, light_specular);
            else glLightfv( L, GL_SPECULAR, no_light);

        }
        else if(L==GL_LIGHT2)
        {
            if(amb_light_2) glLightfv( L, GL_AMBIENT, light_ambient);
            else glLightfv( L, GL_AMBIENT, no_light);

            if(dif_light_2) glLightfv( L, GL_DIFFUSE, light_diffuse);
            else glLightfv( L, GL_DIFFUSE, no_light);

            if(spec_light_2) glLightfv( L, GL_SPECULAR, light_specular);
            else glLightfv( L, GL_SPECULAR, no_light);

        }



        glLightfv( L, GL_POSITION, light_position);
    }

    else
    {
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }
//    glPushMatrix();
//    glTranslatef(x,y,z);
//    drawcube(0,0,0);
//    glPopMatrix();

    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 70);
    }

}



void draw_all()
{
    glPushMatrix();
//    glTranslatef(0,-30,-25);
    draw_room();
    glPopMatrix();


    glPushMatrix();
//    glTranslatef(0,-30,-25);
    draw_cabinet();
    glPopMatrix();


    glPushMatrix();
//    glTranslatef(0,-30,-25);
    draw_basin();
    glPopMatrix();
    glPushMatrix();
    tap_water();
    glPopMatrix();


    glPushMatrix();
//    glTranslatef(0,-30,-25);
    draw_shelf();
    glPopMatrix();


    glPushMatrix();
//    glTranslatef(14,0,-13);
//    glRotatef( alpha,axis_x, axis_y, axis_z );
//    glRotatef( theta, axis_x, axis_y, axis_z);
//    glRotatef(beta, axis_x, axis_y, axis_z);
//    glTranslatef(-14,0,13);
    draw_fridge();


    glPopMatrix();


    glPushMatrix();
    draw_switch();
    glPopMatrix();


    glPushMatrix();
    draw_racks();
    glPopMatrix();


    glPushMatrix();
    draw_kettle();
    glPopMatrix();

    glPushMatrix();
    draw_stove();
    glPopMatrix();


    glPushMatrix();
    draw_fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15.5,16,-19.7);
    glRotatef(theta_fan_rotate, 0.0, 0.0, 1.0);
    glTranslatef(+15.5,-16,+19.7);
    fan_blade();
    glPopMatrix();



    glPushMatrix();
    draw_bulb();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17, 15.3, -7);
    glScalef(.2,.2,.2);
    draw_Sphere(102, 242, 238, light_0_on);

    glPopMatrix();
}




int state = 1;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 4, 200);
    gluPerspective(60,1,5,300);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upx, upy, upz);
    glViewport(0,0, windowHeight, windowWidth);
    glScalef(scale_x, scale_y, scale_z);
    glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta,axis_x, axis_y, axis_z );
    glRotatef( beta,axis_x, axis_y, axis_z );



    glPushMatrix();

    draw_all();
    glPopMatrix();


//    glPushMatrix();
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(0.1,60,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(60,0.1,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(0.1,0.1,60);
//    drawcube(50,50,50);
//    glPopMatrix();

    light(-17, 15.3, -7,GL_LIGHT0, light_0_on, true, 102/255.0,242/255.0,238/255.0);
    light(0.0,18,-19.7, GL_LIGHT1,light_1_on, false);
    light(-19.7,18,2, GL_LIGHT2,light_2_on, false);

    glFlush();
    glutSwapBuffers();
}



void init(int d)
{
    if(d!=f)
    {
        angleYaw = 90.0;
        anglePitch = 90.0;
        angleRoll = 90.0;
        eyeX = 0;
        eyeY = 3;
        eyeZ = 80;
        lookX = 0;
        lookY = 0;
        lookZ = 50;
        upx = 0;
        upy = 1;
        upz = 0;
        f=d;
        scale_x=1;
        scale_y=1;
        scale_z=1;
    }
//     b_swap();
}


void setCameraEye_Yaw()
{

//    init(1);
//    f = 1;
//    std::cout<<"before-----------"<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
    lookX = 50.0*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookZ = 50.0*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
//    std::cout<<"after============="<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
//    std::cout<<angleYaw<<std::endl;
//    (cos(anglePitch*3.1416/180.0))
}

void setCameraEye_Roll()
{

    upx = (cos(angleRoll*3.1416/180.0));
    upy = (sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch()
{
//    init(3);
//    f=3;
//    std::cout<<"before-----------"<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
    lookX = 50.0*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookY = 50.0*(sin(anglePitch*3.1416/180.0));
    lookZ = 50.0*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
//    std::cout<<"after============="<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;

}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'l':
        if(anglePitch<anglePitchLimit1)
        {
            anglePitch += roll_value;
            setCameraEye_Pitch();
        }


        glutPostRedisplay();

        break;
    case 'j':
        if(anglePitch>anglePitchLimit2)
        {
            anglePitch -= roll_value;
            setCameraEye_Pitch();
        }

        glutPostRedisplay();
        break;
    case 'i':
        if(angleYaw<angleYawLimit1)
        {
            angleYaw += roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();

        break;
    case 'k':
        if(angleYaw>angleYawLimit2)
        {
            angleYaw -= roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();
        break;
    case 'o':
        if(angleRoll<angleRollLimit1)
        {
            angleRoll += roll_value;
            setCameraEye_Roll();
        }



        glutPostRedisplay();


        break;
    case 'u':

        if(angleRoll>angleRollLimit2)
        {
            angleRoll -= roll_value;
            setCameraEye_Roll();
        }



        glutPostRedisplay();


        break;






    case 'q':
    case 'Q':
        bRotate = !bRotate;
        uRotate = false;
        tRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        tRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 't':
    case 'T':
        tRotate = !tRotate;
        uRotate = false;
        bRotate = false;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        glutPostRedisplay();
        break;

    case '[':
        eyeY++;
        lookY++;
        glutPostRedisplay();
        break;

    case ']':
        eyeY--;
        lookY--;
        glutPostRedisplay();
        break;
    case 's':


        if(activate_roll)
        {
            if(angleRoll>angleRollLimit2)
            {
                eyeZ++;
                angleRoll -= roll_value;
                setCameraEye_Roll();
            }


        }
        if(activate_pitch)
        {
            if(anglePitch>anglePitchLimit2)
            {
                eyeZ++;
                anglePitch -= roll_value;
                setCameraEye_Pitch();
            }

        }
        if(activate_yaw)
        {
            if(angleYaw>angleYawLimit2)
            {
                eyeZ++;
                angleYaw -= roll_value;
                setCameraEye_Yaw();
            }

        }
        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ++;
            lookZ++;
        }
        glutPostRedisplay();
        break;
    case 'w':


        if(activate_roll)
        {
            if(angleRoll<angleRollLimit1)
            {
                eyeZ--;
                angleRoll += roll_value;
                setCameraEye_Roll();
            }

        }
        if (activate_pitch)
        {
            if(anglePitch<anglePitchLimit1)
            {
                eyeZ--;
                anglePitch += roll_value;
                setCameraEye_Pitch();
            }
        }
        if(activate_yaw)
        {
            if(angleYaw<angleYawLimit1)
            {
                eyeZ--;
                angleYaw += roll_value;
                setCameraEye_Yaw();
            }
        }



        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ--;
            lookZ--;
        }
        glutPostRedisplay();
        break;

    case 'd':
        eyeX++;
        lookX++;
        glutPostRedisplay();
        break;
    case 'a':
        eyeX--;
        lookX--;
        glutPostRedisplay();
        break;
    case '%':
        activate_roll = !activate_roll;
        break;
    case '^':
        activate_pitch = !activate_pitch;
        break;
    case '&':
        activate_yaw = !activate_yaw;

    case 'z':
    case 'Z':
        //eyez-=2;
        //init(4);
        f=4;
        scale_x+=0.05;
        scale_y+=0.05;
        scale_z+=0.05;
        glutPostRedisplay();
        break;
    case 'c':
    case 'C':
        //eyez-=2;
        //init(4);
        f=4;
        if(scale_x==0.05)break;
        scale_x-=0.05;
        scale_y-=0.05;
        scale_z-=0.05;
        glutPostRedisplay();
        break;
    //light 1 toggle
    case '1':
        light_0_on = !light_0_on;
        break;
    case '2':
        light_1_on = !light_1_on;
        break;
    case '3':
        light_2_on = !light_2_on;
        break;
    case '8':
        if (light_toggle)
        {
            amb_light_1 = !amb_light_1;
            break;
        }
        else
        {
            amb_light_0 = !amb_light_0;
            break;
        }

    //diffusion light toggle
    case '9':
        if (light_toggle)
        {
            dif_light_1 = !dif_light_1;
            break;
        }
        else
        {
            dif_light_0 = !dif_light_0;
            break;
        }
    //specular light toggle
    case '0':
        if (light_toggle)
        {
            spec_light_1 = !spec_light_1;
            break;
        }
        else
        {
            spec_light_0 = !spec_light_0;
            break;
        }
    case '5':
        amb_light_2 = !amb_light_2;
        break;
    //diffusion light toggle
    case '6':
        dif_light_2 = !dif_light_2;
        break;
    //specular light toggle
    case '7':
        spec_light_2 = !spec_light_2;
        break;

    case '.':
        light_toggle = !light_toggle;
        break;



    case '4':
        fan_Rotate = !fan_Rotate;
        break;
    case 'n':
        tap_open = !tap_open;
        break;


    case 27:	// Escape key
        exit(1);
    }
}



void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);

    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);

    }

    if (tRotate == true)
    {
        beta += 0.2;
        if(beta > 360.0)
            beta -= 360.0*floor(beta/360.0);

    }

    if (fan_Rotate == true)
    {
        theta_fan_rotate += 5.0;
        if(theta_fan_rotate >= 360) theta_fan_rotate = 0.0;
    }

    if(tap_open == true)
    {
        tap_dis1 -= .01;
        tap_dis2-=.01;
        if(tap_dis1<=4) tap_dis1=4.5;
        if(tap_dis2<=4) tap_dis2=4.5;
    }
    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("kitchen");

    std::cout << glGetString(GL_RENDERER) << std::endl;

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wood.bmp"); //texture 1
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\blacktiles.bmp");//texture 2
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\basin.bmp"); //texture 3
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wood2.bmp"); //texture 4
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wood3.bmp"); //texture 5
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\glass.bmp"); //texture 6
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wood4.bmp"); //texture 7
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\blackT.bmp"); //texture 8
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wallTilesB.bmp"); //texture 9
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\wallTilesW4.bmp"); //texture 10
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\floor3.bmp"); //texture 11
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\teapot1.bmp"); //texture 12
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\teapot2.bmp"); //texture 13
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\teapot3.bmp"); //texture 14
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\teapot4.bmp"); //texture 15
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\fridge.bmp"); //texture 16
    LoadTexture("E:\\GX\\abc\\abc\\asset\\img\\windowFrame.bmp"); //texture 17
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
