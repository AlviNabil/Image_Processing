#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

#include <iostream>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0, theta_fan_rotate = 0.0, tap_dis1 = 4.5, tap_dis2 = 4.3, door_theta = 0;
GLboolean bRotate = false, uRotate = false, tRotate = false, dRotate = false,dRotate2 = false, fan_Rotate = false,light_0_on = true, light_1_on = true, light_2_on = true, light_toggle = false, tap_open = false;
GLboolean  amb_light_0 = true, dif_light_0 = true, spec_light_0 = true, amb_light_1 = true, dif_light_1 = true, spec_light_1 = true, amb_light_2 = true, dif_light_2 = true, spec_light_2 = true;
GLboolean activate_pitch = false, activate_yaw = false, activate_roll = false;

GLfloat  ttx =0.0, tty = 0, ttz=0;
GLfloat eyeX = 0;
GLfloat eyeY = 3;
GLfloat eyeZ = 200;

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
        glVertex3fv(&cube[quadIndices[i][1]][0]);
        glVertex3fv(&cube[quadIndices[i][2]][0]);
        glVertex3fv(&cube[quadIndices[i][3]][0]);
        glEnd();
    }



}


void bed()
{
    //bed

//bed floor
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(5,.2,10);
    drawcube(200,75,75);
    glPopMatrix();

    //bed uporer wall
    glPushMatrix();
    glTranslatef(0,6,-9.9);
    glScalef(5,1.2,.1);
    drawcube(200,75,75);
    glPopMatrix();

//bed nicher wall
    glPushMatrix();
    glTranslatef(0,6,9.9);
    glScalef(5,.8,.1);
    drawcube(200,75,75);
    glPopMatrix();
//bed nicher paa
    glPushMatrix();
    glTranslatef(4,3.1,9);
    glScalef(.5,2,.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,3.1,9);
    glScalef(.5,2,.5);
    drawcube(255,255,255);
    glPopMatrix();




    //bed uporer paa
    glPushMatrix();
    glTranslatef(4,3.1,-8);
    glScalef(.5,2,.5);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4,3.1,-8);
    glScalef(.5,2,.5);
    drawcube(255,255,255);
    glPopMatrix();


    //bed uporer mattress
    glPushMatrix();
    glTranslatef(0,5.6,.5);
    glScalef(4.7,.75,9.3);
    drawcube(255,255,255);
    glPopMatrix();


    //blanket
    glPushMatrix();
    glTranslatef(0,5.6+.75+.2,7);
    glScalef(4.3,.4, 2);

    drawcube(255,255, 0);
    glPopMatrix();

    //pillow
    glPushMatrix();
    glTranslatef(-2.1,5.6+.75+.2,-7);
    glScalef(1.9,.5, 2);
    drawcube(255,0, 255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.1,5.6+.75+.2,-7);
    glScalef(1.9,.5, 2);
    drawcube(255,0, 255);
    glPopMatrix();
}


void draw_almirah()
{

    glPushMatrix();
    glScalef(2,2,3.6);
    glTranslatef(-8.99,1,3.9);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glScalef(1.5,6,3.5);
    glTranslatef(-12.35,1.5,4);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,.5,3.7);
    glTranslatef(-9.0,30,3.77);
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




void windowFrame()
{
    //windowframe
    glPushMatrix();
    glTranslatef(0,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.1);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,4*2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,0.5,.1);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    drawcube(173, 123, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    drawcube(173, 123, 7);
    glPopMatrix();


}

void draw_door()
{
    //door

    glPushMatrix();
    glTranslatef(0,7,20);
    glScalef(4,7,.3);
    drawcube(183,159,127);
    glPopMatrix();
}


void corridor()
{

    glPushMatrix();
    glTranslatef(-4,20,25.2);
    glScalef(66,.6,5);
    drawcube(220,220,0);
    glPopMatrix();
}

void roof()
{

    glPushMatrix();
    glTranslatef(0,40.2,1);
    glScalef(64,.4,22);
    drawcube(166,166,166);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-5,41,5);
    glScalef(70,.6,30);
    drawcube(66,66,66);
    glPopMatrix();

}


void base()
{
    glPushMatrix();
    glTranslatef(-5,0,5);
    glScalef(66,.5,30);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5,-5.5,5);
    glScalef(70,5,33);
    drawcube(55,55,55);
    glPopMatrix();



    //ground stairs
    glPushMatrix();
    glTranslatef(0,0,2);

    glPushMatrix();
    glTranslatef(0,-9.9,48);
    glScalef(10,.4,3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-8.5,45);
    glScalef(10,1,3);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-6.5,42);
    glScalef(10,1,3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-4.5,39);
    glScalef(10,1,3);
    drawcube(0,0,0);
    glPopMatrix();
    glPopMatrix();




}

void draw_room()
{


    ///frontwalls
    //front leftwall
    glPushMatrix();
    glTranslatef(-12,10,20);
    glScalef(8,10,.2);
    drawcube(149,146,140);
    glPopMatrix();
    //front rightwall
    glPushMatrix();
    glTranslatef(12,10,20);
    glScalef(8,10,.2);
    drawcube(149,146,140);
    glPopMatrix();

    //front topwall
    glPushMatrix();
    glTranslatef(0,17,20);
    glScalef(4,3,.2);
    drawcube(149,146,140);
    glPopMatrix();


    ///front Door
    //door frame
    glPushMatrix();
    glTranslatef(4.1,7,20);
    glScalef(.5,7,.3);
    drawcube(173, 123, 7);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.1,7,20);
    glScalef(.5,7,.3);
    drawcube(173, 123, 7);
    glPopMatrix();
    //doorframe top bar
    glPushMatrix();
    glTranslatef(0,14,20);
    glScalef(4.8,.5,.3);
    drawcube(173, 123, 7);
    glPopMatrix();


    //door
    glPushMatrix();
    glTranslatef(-4,7,20);
    glRotatef(door_theta, 0,1,0);
    glTranslatef(4,-7,-20);
    draw_door();
    glPopMatrix();






    //ceil
    glPushMatrix();
    glTranslatef(0,20,0);
    glScalef(20,0.4,20);
    drawcube(168, 168, 168);
    glPopMatrix();

    //ceil frame
//    glPushMatrix();
//    glTranslatef(0, 20, 20.2);
//    glScalef(22, .5, .2);
//    drawcube(25,25,25);
//    glPopMatrix();


    //room frame
    glPushMatrix();
    glTranslatef(18,10,20);
    glScalef(.2, 10, .3);
    drawcube(30,30,30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,10,20);
    glScalef(.2, 10, .3);
    drawcube(30,30,30);
    glPopMatrix();

    //floor
    glPushMatrix();
    glScalef(20,0.1,20);
    drawcube(168, 168, 168);
    glPopMatrix();




    //tiles
    glPushMatrix();
    for(GLint hCount=1; hCount<40; hCount+=4)
    {
        for(GLint vCount=1; vCount<40; vCount+=4)
        {
            if((hCount+vCount)%2==0)
            {
                glPushMatrix();
                glTranslatef(-19+hCount,0.1,-19+vCount);
                glScalef(1.5,0.1,1.5);

                drawcube(25,25,25);
                glPopMatrix();
            }

        }

    }
    glPopMatrix();


    //left wall
    glPushMatrix();
    glTranslatef(-20,10,0);
    glScalef(.1,10,20);
    drawcube(104,139,153);
    glPopMatrix();

    //right wall
    glPushMatrix();
    glTranslatef(20,10,0);
    glScalef(.1,10,20);
    drawcube(104,139,153);
    glPopMatrix();



    //back wall left
    glPushMatrix();
    glTranslatef(-12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();

    //backwall right
    glPushMatrix();
    glTranslatef(12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();


    //backwall bottom
    glPushMatrix();
    glTranslatef(0,2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();

    //backwall top
    glPushMatrix();
    glTranslatef(0,17.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();

    glPushMatrix();
    windowFrame();
    glPopMatrix();


    //bathroom
    glPushMatrix();
    glTranslatef(-10, 10, -10);
    glScalef(0.2, 10, 10);
    drawcube(200,200,125);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,10,0);
    glScalef(5,10,.2);
    drawcube(200,200,125);
    glPopMatrix();

    //bathroom door

    glPushMatrix();
    glTranslatef(-15,6,0.1);
    glScalef(3,6,.2);
    drawcube(200,75,75);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13,6,0.1);
    glScalef(.2,.5,.3);
    drawcube(100,37,37);
    glPopMatrix();


    //bed
    glPushMatrix();
    glTranslatef(14,-1.1,-3);
    bed();
    glPopMatrix();


    //almirah
    glPushMatrix();
    draw_almirah();
    glPopMatrix();



}

void ground()
{
    glPushMatrix();
    glTranslatef(0,-11,0);
    glScalef(100000,1,100000);
    drawcube(60,240,60);
    glPopMatrix();

}


void sky(){
    glPushMatrix();
    glTranslatef(0,150,0);
    glScalef(100000,0,100000);
    drawcube(135,206,235);
    glPopMatrix();
}



void firstFloor()
{
    glPushMatrix();
    draw_room();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(40,0,0);
    draw_room();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,0,0);
    draw_room();
    glPopMatrix();


    //base
    glPushMatrix();
    base();
    glPopMatrix();


    //ground
    glPushMatrix();
    ground();
    glPopMatrix();

}

void secondFloor()
{
    //rooms
    glPushMatrix();
    glTranslatef(0,20,0);
    draw_room();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(40,20,0);
    draw_room();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-40,20,0);
    draw_room();
    glPopMatrix();

    //corridor
    glPushMatrix();
    corridor();
    glPopMatrix();


    //roof
    glPushMatrix();
    roof();
    glPopMatrix();

}


void shiri()
{
    //halfway base
    glPushMatrix();
    glTranslatef(-65,10,-16);
    glScalef(7,.5,4);
    drawcube(244,201,105);
    glPopMatrix();




    //stairs top



    glPushMatrix();
    glTranslatef(-61.5,10.5,-11);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-61.5,11.5,-7);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-61.5,12.5,-3);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-61.5,13.5,1);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-61.5,14.5,5);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-61.5,15.5,9);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-61.5,16.5,13);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-61.5,17.5,17);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-61.5,19,19);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();





    //stairs bottom
    glPushMatrix();
    glTranslatef(-68.5,9.5,-11);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,8.5,-7);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,7.5,-3);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-68.5,6.5,1);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-68.5,5.5,5);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-68.5,4.5,9);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,3.5,13);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,2.5,17);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,1.5,21);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,0.5,25);
    glScalef(3.5, .75,2.5);
    drawcube(255,255,255);
    glPopMatrix();


}


void pillars()
{

    glPushMatrix();
    glTranslatef(20,20.2,29);
    glScalef(1,20,1);
    drawcube(188,188,188);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-20,20.2,29);
    glScalef(1,20,1);
    drawcube(188,188,188);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-60,20.2,29);
    glScalef(1,20,1);
    drawcube(188,188,188);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(60,20.2,29);
    glScalef(1,20,1);
    drawcube(188,188,188);
    glPopMatrix();

}

void firstFloorFence()
{


    //horizontal lines
    glPushMatrix();
    glTranslatef(-5.5,27,29);
    glScalef(64,.4,.4);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(58,27,24.5);
    glScalef(.4,.4,4.5);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68,27,24.5);
    glScalef(.4,.4,4.5);
    drawcube(50,50,50);
    glPopMatrix();



    //vertical lines

    for(GLint i = 0; i<64; i++)
    {
        glPushMatrix();
        glTranslatef(58-i*2,23.5,29);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
    //fence towards z axis right
    for(GLint i = 1; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(58,23.5,29-i*2);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
    //fence towards z axis left
    for(GLint i = 1; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(-68,23.5,29-i*2);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }





}


void groundFence()
{

    //horizontal lines
    //right
    glPushMatrix();
    glTranslatef(40.5,7,29);
    glScalef(20,.4,.4);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(58,7,24.5);
    glScalef(.4,.4,4.5);
    drawcube(50,50,50);
    glPopMatrix();


    //left
    glPushMatrix();
    glTranslatef(-45.5,7,29);
    glScalef(25,.4,.4);
    drawcube(50,50,50);
    glPopMatrix();


    //vertical fences
    //right
    for(GLint i = 0; i<20; i++)
    {
        glPushMatrix();
        glTranslatef(58-i*2,3.5,29);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }
    //left
    for(GLint i = 40; i<65; i++)
    {
        glPushMatrix();
        glTranslatef(58-i*2,3.5,29);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }



    //fence towards z axis right
    for(GLint i = 1; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(58,3.5,29-i*2);
        glScalef(.4,3.2,.4);
        drawcube(255,255,255);
        glPopMatrix();
    }




}


void stairFence()
{


    for (GLint i = 0; i<14; i++)
    {

        glPushMatrix();
        glTranslatef(-70,3.5+i*.75,25-i*3);
        glScalef(.4,3.2,.4);
        drawcube(0,255,255);
        glPopMatrix();


    }

    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1);
    glScalef(.4,3.2,.4);
    drawcube(0,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1-2);
    glScalef(.4,3.2,.4);
    drawcube(0,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1-3.5);
    glScalef(.4,3.2,.4);
    drawcube(0,255,255);
    glPopMatrix();



    for(GLint i = 0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(-70+i*2,3.5+13*.75,25-14*3+1-3.5);
        glScalef(.4,3.2,.4);
        drawcube(0,255,255);
        glPopMatrix();
    }


    //inclined line
    glPushMatrix();
    glTranslatef(-70,11.5,7);
    glRotatef(13.5, 1,0,0);
    glScalef(.6,.6,20);
    drawcube(50,50,50);
    glPopMatrix();
    //


    glPushMatrix();
    glTranslatef(-70, 7,27.4);
    glScalef(.6,.6,2);
    drawcube(40,40,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, 16,-15.8);
    glScalef(.6,.6,4.5);
    drawcube(40,40,40);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-65.0002, 16, -19.4);
    glScalef(5,.6,.6);
    drawcube(50,50,50);
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
    firstFloor();
    secondFloor();
    pillars();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-13.5,0,0);
    glScalef(.8,1,1);
    shiri();
    glPopMatrix();

    glPushMatrix();
    firstFloorFence();
    glPopMatrix();


    glPushMatrix();
    groundFence();
    glPopMatrix();

    glPushMatrix();
    stairFence();
    glPopMatrix();

    glPushMatrix();
    sky();
    glPopMatrix();



}
int state = 1;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 4, 200);
    gluPerspective(60,1,5,200000);
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

//    std::cout<<"before-----------"<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
    lookX = 50.0*(cos(anglePitch*3.1416/180.0))*(cos(angleYaw*3.1416/180.0));
    lookZ = 50.0*(cos(anglePitch*3.1416/180.0))*(sin(angleYaw*3.1416/180.0));
//    std::cout<<"after============="<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<" "<<upx<<" "<<upy<<" "<<upz<<std::endl;
//    std::cout<<angleYaw<<std::endl;

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
    case 'm':
        dRotate = !dRotate;
        dRotate2 = false;
        break;
    case 'M':
        dRotate2 = !dRotate2;
        dRotate = false;
        break;

    case '\'':
        tty -= 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case '"':
        tty += 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case ';':
        ttx -= 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case ':':
        ttx += 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;

    case '\\':
        ttz -= 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case '|':
        ttz += 0.2;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case 27:	// Escape key
        exit(1);
    }
}


//void SpecialInput(int key, int x, int y)
//{
//    switch(key)
//    {
//    case GLUT_KEY_UP:
//        ttz -= 0.2;
//        break;
//    case GLUT_KEY_DOWN:
////do something here
//        ttz += 0.2;
//        break;
//    case GLUT_KEY_LEFT:
////do something here
//        ttx -= 0.2;
//        break;
//    case GLUT_KEY_RIGHT:
////do something here
//        ttx += 0.2;
//        break;
//    }
//    std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
//
//    glutPostRedisplay();
//}



void animate()
{
    if (bRotate == true)
    {
        theta += .2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);

    }

    if (uRotate == true)
    {
        alpha += .2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);

    }

    if (tRotate == true)
    {
        beta += .2;
        if(beta > 360.0)
            beta -= 360.0*floor(beta/360.0);

    }
    if(dRotate == true)
    {

        if(door_theta>-120)
        {
            door_theta-=0.5;

        }

    }
    if(dRotate2==true)
    {
        if(door_theta<0)
        {
            door_theta+=0.5;
        }
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


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
