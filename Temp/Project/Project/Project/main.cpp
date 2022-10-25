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
GLfloat alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0, theta_fan_rotate = 0.0, tap_dis1 = 4.5, tap_dis2 = 4.3;
GLboolean bRotate = false, uRotate = false, tRotate = false, fan_Rotate = false,light_0_on = true, light_1_on = true, light_2_on = true, light_toggle = false, tap_open = false;
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
        glVertex3fv(&cube[quadIndices[i][1]][0]);
        glVertex3fv(&cube[quadIndices[i][2]][0]);
        glVertex3fv(&cube[quadIndices[i][3]][0]);
        glEnd();
    }



}
void draw_room()
{

    //ceil
    glPushMatrix();
    glTranslatef(0,20,0);
    glScalef(20,0.1,20);
    drawcube(168, 168, 168);
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
    glScalef(8,2.5,.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();

    //backwall top
    glPushMatrix();
    glTranslatef(0,17.5,-20);
    glScalef(8,2.5,.1);
    glRotatef(180,0,1,0);
    drawcube(104-25,139-25,153-25);
    glPopMatrix();


    //windowframe
    glPushMatrix();
    glTranslatef(0,10,-20);
    glScalef(.5,5,.1);
    glRotatef(180,0,1,0);
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

//bed floor
    glPushMatrix();

    glTranslatef(14,6,0);
    glScalef(4,.2,10);
    drawcube(200,75,75);

    glPopMatrix();

    //bed uporer wall
    glPushMatrix();
    glTranslatef(14,7,-10);
    glScalef(4,1,.1);
    drawcube(200,75,75);

    glPopMatrix();
//bed nicher wall
    glPushMatrix();
    glTranslatef(14,6,10);
    glScalef(4,.8,.1);
    drawcube(200,75,75);
    glPopMatrix();
//bed nicher paa
    glPushMatrix();
    glTranslatef(11,4,9);
    glScalef(.5,2,.5);
    drawcube(200,75,75);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(17,4,9);
    glScalef(.5,2,.5);
    drawcube(200,75,75);
    glPopMatrix();
    glPushMatrix();

    //bed uporer paa
    glTranslatef(11,4,-8);
    glScalef(.5,2,.5);
    drawcube(200,75,75);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(17,4,-8);
    glScalef(.5,2,.5);
    drawcube(200,75,75);
    glPopMatrix();


    //bed uporer mattress
    glPushMatrix();

    glTranslatef(14,7,.5);
    glScalef(3.8,.4,9.3);
    drawcube(255,255,255);

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
}

void secondFloor()
{
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
}


void shiri()
{
    glPushMatrix();
    glTranslatef(-65,-28,0);
    glScalef(5,.5,2);
    drawcube(244,201,105);
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
    glTranslatef(0,-30,-25);
    firstFloor();
    secondFloor();
    glPopMatrix();
    shiri();





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
        theta += 1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);

    }

    if (uRotate == true)
    {
        alpha += 1;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);

    }

    if (tRotate == true)
    {
        beta += 1;
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


    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
