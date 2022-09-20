#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0;
GLboolean bRotate = false, uRotate = false, tRotate = false;

GLfloat eyeX = 0;
GLfloat eyeY = 3;
GLfloat eyeZ = 40;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;


GLfloat upx = 0;
GLfloat upy = 1;
GLfloat upz = 0;



GLfloat scale_x = 1;
GLfloat scale_y = 1;
GLfloat scale_z = 1;

double limit = 360;
double roll_value = 5;
GLfloat angleYaw = 90.0, anglePitch = 90.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 180.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 0.0, angleRollLimit2 = -90.0;

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

void drawcube(GLint c1, GLint c2, GLint c3)
{
    glColor3f(1,0,0);


    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        if((c1+i*10)>255 || (c1+i*10)>255 || (c1+i*10)>255){
            c1 = (c1+i*10)%255+200;
            c2 = (c2+i*10)%255+200;
            c3 = (c3+i*10)%255+200;
        }
        glColor3ub((c1+i*10),(c2+i*10),(c3+i*10));
        glVertex3fv(&cube[quadIndices[i][0]][0]);
        glVertex3fv(&cube[quadIndices[i][1]][0]);
        glVertex3fv(&cube[quadIndices[i][2]][0]);
        glVertex3fv(&cube[quadIndices[i][3]][0]);
        glEnd();
    }



}

void draw_room()
{

    //floor
    glPushMatrix();
    glScalef(20,0.1,20);
    drawcube(168, 168, 168);
    glPopMatrix();


    //tiles
    for(GLint hCount=1; hCount<26; hCount+=4)
    {
        for(GLint vCount=1; vCount<26; vCount+=4)
        {
            if((hCount+vCount)%2==0)
            {
                glPushMatrix();
                glScalef(1.5,0.05,1.5);
                glTranslatef(-(20-hCount*1.5)/1.5,0.105/0.05,-(20-vCount*1.5)/1.5);
                drawcube(25,25,25);
                glPopMatrix();
            }

        }

    }


    //left wall
    glPushMatrix();
    glScalef(.1,10,20);
    glTranslatef(-20/0.1,1,0);
    drawcube(104,139,153);
    glPopMatrix();

//
    //right wall
//    glPushMatrix();
//    glScalef(.005,10,20);
//    glTranslatef(20/0.005,1,0);
//    drawcube(35, 89, 92);
//    glPopMatrix();
//


    //back wall left
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(-1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();

    //backwall upper
    glPushMatrix();
    glScalef(8,10,.1);
    glTranslatef(1.5,1,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();
    //backwall bottom
    glPushMatrix();
    glScalef(8,2.5,.1);
    glTranslatef(0,1,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();
    //backwall top
    glPushMatrix();
    glScalef(8,2.5,.1);
    glTranslatef(0,7,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();


    //windowframe
    glPushMatrix();
    glScalef(.5,5,.1);
    glTranslatef(0,2,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glScalef(4,0.5,.1);
    glTranslatef(0,4*2.5/0.5,-20/0.1);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,5,.3);
    glTranslatef(-8,2,-20/0.3);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,5,.3);
    glTranslatef(8,2,-20/0.3);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.9,0.5,.3);
    glTranslatef(0,5*3/0.5,-20/0.3);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();
    glPushMatrix();
    glScalef(4.9,0.5,.3);
    glTranslatef(0,1.5*3/0.5,-20/0.3);
    glRotatef(180,0,1,0);
    drawcube(173, 123, 7);
    glPopMatrix();

}



void draw_cabinet(){
    //left cabinet
    glPushMatrix();
    glScalef(2,2,4);
    glTranslatef(-8.99,1,-4);
    drawcube(161,72,15);
    glPopMatrix();
    //middle portion
    glPushMatrix();
    glScalef(2,1,4);
    glTranslatef(-8.99,1,-2);
    drawcube(40,40,40);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,2,4);
    glTranslatef(-8.99,1,0);
    drawcube(161,72,15);
    glPopMatrix();

    //details for left cabinet
    glPushMatrix();
    glScalef(.2,1.5,1.9);
    glTranslatef(-16/.2,1.4,-7.4);
    drawcube(200, 140, 81);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,1.5);
    drawcube(200, 140, 81);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,-1.5);
    drawcube(200, 140, 81);
    glPopMatrix();

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
    glPushMatrix();
    glRotatef(-90,0,1,0);
    glScalef(2,2,12);
    glTranslatef(-8.99,1,0.33);
    drawcube(161,72,15);
    glPopMatrix();

    //details for back cabinet
    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(-4.5,1.4,-16/0.2);
    drawcube(200, 162, 81);
    glPopMatrix();


    //oven
    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(-2,1.4,-16/0.2);
    drawcube(74, 187, 199);
    glPopMatrix();
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





    glPushMatrix();
    glScalef(2.5,1.3,.2);
    glTranslatef(.5,1.4,-16/0.2);
    drawcube(200, 162, 81);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.3,1.7,.2);
    glTranslatef(4.8,1.18,-16/0.2);
    drawcube(200, 162, 81);
    glPopMatrix();

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


void draw_basin(){
    glPushMatrix();
    glScalef(2,.1,3);
    glTranslatef(-9,10/.4,-2.65);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-5/.1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.8,.1);
    glTranslatef(-9,3.2/.8,-11/.1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(.1,.8,3);
    glTranslatef(-16/.1,3.2/0.8,-2.65);
    drawcube(170,170,170);
    glPopMatrix();




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

void draw_racks(){
    glPushMatrix();
    glScalef(2,2,3.5);
    glTranslatef(-8.99,1,4);
    drawcube(161,72,15);
    glPopMatrix();


    glPushMatrix();
    glScalef(1.5,6,3.5);
    glTranslatef(-12.35,1.5,4);
    drawcube(161,72,15);
    glPopMatrix();


    glPushMatrix();
    glScalef(2,.5,3.7);
    glTranslatef(-9.0,30,3.77);
    drawcube(161,72,15);
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

void draw_fridge(){

    glPushMatrix();
    glTranslatef(15,4,-16.8);
    glScalef(3,4,3);
    drawcube(200,200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,8.5,-16.8);
    glScalef(3.01,.5,3.01);
    drawcube(20,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,9,-16.8);
    glScalef(3,4,3);
    drawcube(200,200,200);
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


void draw_switch(){
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
    drawcube(222,0,0);
    glPopMatrix();

    //light
    glPushMatrix();
    glTranslatef(0.0,18,-19.8);
    glScalef(4,.5,.12);
    drawcube(222,222,222);
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


void draw_shelf(){
    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,1);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-3);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.1,-7);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-.8);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-8.8);
    drawcube(170,170,170);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.1,2);
    glTranslatef(-9,10/.15,-4.8);
    drawcube(170,170,170);
    glPopMatrix();

}


void draw_kettle(){
    glPushMatrix();
    glTranslatef(-18,10.8,-5.8);
    glColor3ub(125, 66, 32);
    glutSolidTeapot(0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,10.8,2);
    glColor3ub(66, 125, 32);
    glutSolidTeapot(0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,10.8,-13.5);
    glColor3ub(66, 32, 125);
    glutSolidTeapot(0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,7.3,-17.5);
    glColor3ub(125, 32, 66);
    glutSolidTeapot(0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,7.3,-9.5);
    glColor3ub(32, 125,66);
    glutSolidTeapot(0.7);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-18,7.3,-1.5);
    glColor3ub(32, 66, 125);
    glutSolidTeapot(0.7);
    glPopMatrix();

}


void draw_stove(){

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
//    glScalef()
    glColor3ub(32, 66, 125);
    glutSolidTeapot(1.5);
    glPopMatrix();


}


void draw_circle(void){
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
    for (i=0;i<=triangleAmount;i++);
    {
        glVertex3f(
                    x+(radius*cos(i*twicePI/triangleAmount)),
                   y+(radius*sin(i*twicePI/triangleAmount)),
                   1
                   );

    }
    glEnd();

}


void draw_fan(){
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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 4, 200);
    gluPerspective(60,1,5,200);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upx, upy, upz);

    glScalef(scale_x, scale_y, scale_z);
    glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta, axis_x, axis_y, axis_z);
    glRotatef(beta, axis_x, axis_y, axis_z);


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
//    glTranslatef(0,-30,-25);
    draw_shelf();
    glPopMatrix();


    glPushMatrix();

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

//    glPushMatrix();
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(0.1,20,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//    glPushMatrix();
//    glScalef(20,0.1,0.1);
//    drawcube(50,50,50);
//    glPopMatrix();
//
//
//    glPushMatrix();
//    glScalef(0.1,0.1,20);
//    drawcube(50,50,50);
    glPopMatrix();




    glFlush();
    glutSwapBuffers();
}



void init(int d)
{
    if(d!=f)
    {
        angleYaw = 90.0;
        anglePitch = 270.0;
        angleRoll = 90.0;
        eyeX = 0;
        eyeY = 0;
        eyeZ = 80;
        lookX = 0;
        lookY = 0;
        lookZ = 0;
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

    init(1);
    f = 1;
    lookX = 100.0*(cos(angleYaw*3.1416/180.0));

}

void setCameraEye_Roll()
{

    upx = (cos(angleRoll*3.1416/180.0));
    upy = (sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch()
{
    init(3);
    f=3;

    lookY = 100.0*(cos(anglePitch*3.1416/180.0));
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'l':
        if(anglePitch>=anglePitchLimit1)
                break;
        anglePitch += roll_value;
        setCameraEye_Pitch();
        glutPostRedisplay();

        break;
    case 'j':
        if(anglePitch<=anglePitchLimit2)
                break;
        anglePitch -= roll_value;
        setCameraEye_Pitch();
        glutPostRedisplay();
        break;
    case 'i':
        if(angleYaw==angleYawLimit1)
            break;
        angleYaw += roll_value;
        setCameraEye_Yaw();
        glutPostRedisplay();

        break;
    case 'k':
        if(angleYaw==angleYawLimit2)
            break;
        angleYaw -= roll_value;
        setCameraEye_Yaw();
        glutPostRedisplay();
        break;
    case 'o':

        angleRoll += roll_value;
        printf("%lf\n", angleRoll);
        setCameraEye_Roll();
        glutPostRedisplay();


        break;
    case 'u':
        angleRoll -= roll_value;
        setCameraEye_Roll();
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
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        tRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        break;

    case 't':
    case 'T':
        tRotate = !tRotate;
        uRotate = false;
        bRotate = false;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        break;

    case 'w':
    case 'W':
            eyeY++;
            lookY++;
            glutPostRedisplay();
            break;
        case 's':
        case 'S':
            eyeY--;
            lookY--;
            glutPostRedisplay();
            break;
        case '+':
            eyeZ++;
            lookZ++;
            glutPostRedisplay();
            break;
        case '-':
            eyeZ--;
            lookZ--;
            glutPostRedisplay();
            break;

        case 'd':
        case 'D':
            eyeX++;
            lookX++;
            glutPostRedisplay();
            break;
        case 'a':
        case 'A':
            eyeX--;
            lookX--;
            glutPostRedisplay();
            break;

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
    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("kitchen");
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
