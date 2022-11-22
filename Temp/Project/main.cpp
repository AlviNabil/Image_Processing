#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"
#include <iostream>
#include <mmsystem.h>





bool keyState[256];
double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1000;
GLfloat sr=1,sg=1,sb=1,alpha = 0.0, theta = 0.0, beta = 0.0, axis_x=0.0, axis_y=0.0, axis_z=0.0,t = 40, t2=9,theta_fan_rotate = 0.0, tap_dis1 = 4.5, tap_dis2 = 4.3, door_theta = 0, sunx=0, suny=0,doorDistx1 = 0, doorDistx2 =   0,var=0.0, treeTheta=0.0, leafTheta=0.0,carTheta =  0.0,carx=0.0,carz=0.0,car2z=0.0, car3z=3200,car4z=1600, car5z=700,doorDistz=0,nightTheta = 0.0, skyTheta = 0.0,lidTheta = 0, diskTheta = 0.0, pinTheta=0.0;
GLboolean bRotate = false, uRotate = false, tRotate = false, dRotate = false,dRotate2 = false, lidOpen = false, mPlay = false, mPause = false,skyRotate= false, lidClose=false,treeMove = false,carMove = true, night = false, fan_Rotate = false,light_0_on = true,  light_1_on = false, light_2_on = false,light_3_on=false, light_4_on=false, light_toggle = false, tap_open = false, doorOpen= false, doorClose=false;
GLboolean  amb_light_0 = true, dif_light_0 = true, spec_light_0 = true, amb_light_1 = true, dif_light_1 = true, spec_light_1 = true, amb_light_2 = true, dif_light_2 = true, spec_light_2 = true;
GLboolean activate_pitch = false, activate_yaw = false, activate_roll = false;
GLint stateqP = 0, stateeP = 0, staterP = 0;
GLint var2 = 0;
GLfloat  ttx =0.0, tty = 0, ttz=0;
GLfloat eyeX = 0;
GLfloat eyeY = 3;
GLfloat eyeZ = 400;

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
double roll_value = 3;
GLfloat angleYaw =90.0, anglePitch = 0.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 360.0, anglePitchLimit1 = 360.0, angleRollLimit1 = 270.0;
GLfloat angleYawLimit2 = -360.0, anglePitchLimit2 = -360.0, angleRollLimit2 = -90.0;

int f = 0;


void init()
{

        angleYaw = 90.0;
        anglePitch = 0;
        angleRoll = 90.0;
        eyeX = 0;
        eyeY = 3;
        eyeZ = 400;
        lookX = 0;
        lookY = 3;
        lookZ = 50;
        upx = 0;
        upy = 1;
        upz = 0;



}



void init2()
{

        angleYaw = 90.0;
        anglePitch = 0;
        angleRoll = 90.0;
        eyeX = -32;
        eyeY =  21;
        eyeZ = 591;
        lookX = -32;
        lookY = 21;
        lookZ = 241;
        upx = 0;
        upy = 1;
        upz = 0;
        theta = 17.5;




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



void keyFunc()
{

    if(keyState['w'])
    {
        if(activate_roll)
        {
            if(angleRoll<angleRollLimit1)
            {
                eyeZ-=.5;
                angleRoll += roll_value;
                setCameraEye_Roll();
            }

        }
        if (activate_pitch)
        {
            if(anglePitch<anglePitchLimit1)
            {
                eyeZ-=.5;
                anglePitch += roll_value;
                setCameraEye_Pitch();
            }
        }
        if(activate_yaw)
        {
            if(angleYaw<angleYawLimit1)
            {
                eyeZ-=.5;
                angleYaw += roll_value;
                setCameraEye_Yaw();
            }
        }



        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ-=.5;
            lookZ-=.5;

        }


        glutPostRedisplay();
    }

    if(keyState['W'])
    {
        if(activate_roll)
        {
            if(angleRoll<angleRollLimit1)
            {
                eyeZ-=2;
                angleRoll += roll_value;
                setCameraEye_Roll();
            }

        }
        if (activate_pitch)
        {
            if(anglePitch<anglePitchLimit1)
            {
                eyeZ-=2;
                anglePitch += roll_value;
                setCameraEye_Pitch();
            }
        }
        if(activate_yaw)
        {
            if(angleYaw<angleYawLimit1)
            {
                eyeZ-=2;
                angleYaw += roll_value;
                setCameraEye_Yaw();
            }
        }



        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ-=2;
            lookZ-=2;

        }


        glutPostRedisplay();
    }


    if(keyState['s'])
    {
        if(activate_roll)
        {
            if(angleRoll>angleRollLimit2)
            {
                eyeZ+=.5;
                angleRoll -= roll_value;
                setCameraEye_Roll();
            }


        }
        if(activate_pitch)
        {
            if(anglePitch>anglePitchLimit2)
            {
                eyeZ+=.5;
                anglePitch -= roll_value;
                setCameraEye_Pitch();
            }

        }
        if(activate_yaw)
        {
            if(angleYaw>angleYawLimit2)
            {
                eyeZ+=.5;
                angleYaw -= roll_value;
                setCameraEye_Yaw();
            }

        }
        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ+=.5;
            lookZ+=.5;
        }
        glutPostRedisplay();
    }

    if(keyState['S'])
    {
        if(activate_roll)
        {
            if(angleRoll>angleRollLimit2)
            {
                eyeZ+=2;
                angleRoll -= roll_value;
                setCameraEye_Roll();
            }


        }
        if(activate_pitch)
        {
            if(anglePitch>anglePitchLimit2)
            {
                eyeZ+=2;
                anglePitch -= roll_value;
                setCameraEye_Pitch();
            }

        }
        if(activate_yaw)
        {
            if(angleYaw>angleYawLimit2)
            {
                eyeZ+=2;
                angleYaw -= roll_value;
                setCameraEye_Yaw();
            }

        }
        if(!activate_roll && !activate_pitch && !activate_yaw)
        {
            eyeZ+=2;
            lookZ+=2;
        }
        glutPostRedisplay();
    }
    if(keyState['a'])
    {
        eyeX-=.5;
        lookX-=.5;
        glutPostRedisplay();
    }

    if(keyState['A'])
    {
        eyeX-=2;
        lookX-=2;
        glutPostRedisplay();
    }
    if(keyState['d'])
    {
        eyeX+=.5;
        lookX+=.5;
        glutPostRedisplay();
    }
    if(keyState['D'])
    {
        eyeX+=2;
        lookX+=2;
        glutPostRedisplay();
    }


    if(keyState['z'])
    {
        scale_x+=0.01;
        scale_y+=0.01;
        scale_z+=0.01;
        glutPostRedisplay();
    }
    if(keyState['c'])
    {
//        std::cout<<scale_x<<std::endl;
        if(scale_x>0.021)
        {
            scale_x-=0.01;
            scale_y-=0.01;
            scale_z-=0.01;
            glutPostRedisplay();
        }

    }

    if(keyState['l'])
    {
        if(anglePitch<anglePitchLimit1)
        {
            anglePitch += roll_value;
            setCameraEye_Pitch();
        }
        glutPostRedisplay();
    }

    if(keyState['j'])
    {
        if(anglePitch>anglePitchLimit2)
        {
            anglePitch -= roll_value;
            setCameraEye_Pitch();
        }
        glutPostRedisplay();
    }

    if(keyState['i'])
    {
        if(angleYaw<angleYawLimit1)
        {
            angleYaw += roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();
    }

    if(keyState['k'])
    {
        if(angleYaw>angleYawLimit2)
        {
            angleYaw -= roll_value;
            setCameraEye_Yaw();
        }

        glutPostRedisplay();
    }

    if(keyState['o'])
    {
        if(angleRoll<angleRollLimit1)
        {
            angleRoll += roll_value;
            setCameraEye_Roll();
        }



        glutPostRedisplay();
    }


    if(keyState['u'])
    {
        if(angleRoll>angleRollLimit2)
        {
            angleRoll -= roll_value;
            setCameraEye_Roll();
        }
        glutPostRedisplay();
    }


    if(keyState['\]'])
    {

        eyeY--;
        lookY--;
        glutPostRedisplay();
    }


    if(keyState['\['])
    {
        eyeY++;
        lookY++;
        glutPostRedisplay();
    }

//    std::cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<lookX<<" "<<lookY<<" "<<lookZ<<std::endl;

    Sleep(20);

}



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

static GLfloat cube2[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, 1.75, -1.0},
    {-1.0, 1.75, -1.0},

};

static GLfloat cube3[8][3] =
{
    {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},


    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {0.0, 1.75, -1.0},
    {0.0, 1.75, -1.0},

};




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


void draw_TriCube(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
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
        for (GLint i = 0; i <6; i++)
        {
            glBegin(GL_QUADS);

            glVertex3fv(&cube3[quadIndices[i][0]][0]);
            glTexCoord2f(1,1);
            glVertex3fv(&cube3[quadIndices[i][1]][0]);
            glTexCoord2f(1,0);
            glVertex3fv(&cube3[quadIndices[i][2]][0]);
            glTexCoord2f(0,0);
            glVertex3fv(&cube3[quadIndices[i][3]][0]);
            glTexCoord2f(0,1);
            glEnd();
        }

}

void drawcube2(GLint c1, GLint c2, GLint c3, GLboolean emission = false)
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
        for (GLint i = 0; i <6; i++)
        {
            glBegin(GL_QUADS);

            glVertex3fv(&cube2[quadIndices[i][0]][0]);
            glTexCoord2f(1,1);
            glVertex3fv(&cube2[quadIndices[i][1]][0]);
            glTexCoord2f(1,0);
            glVertex3fv(&cube2[quadIndices[i][2]][0]);
            glTexCoord2f(0,0);
            glVertex3fv(&cube2[quadIndices[i][3]][0]);
            glTexCoord2f(0,1);
            glEnd();
        }

}

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


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};


void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}
void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (1.0, 16, 16);
}

void cylinder(GLint c1, GLint c2,GLint c3, GLboolean emission=false)
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

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.1;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    //top Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution)

    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(radius, height, 0);
    glEnd();


    //bottom Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, 0, 0);  /* center */
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), 0, radius * sin(i));
    }
    glEnd();



    //cylinder side
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= 2 * PI; i += resolution)
    {
        const float tc = ( i / (float)( 2 * PI ) );
        glTexCoord2f( tc, 0.0 );
        glVertex3f(radius * cos(i), 0, radius * sin(i));
        glTexCoord2f( tc, 1.0 );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to zero degrees */
    glTexCoord2f( 0.0, 0.0 );
    glVertex3f(radius, 0, 0);
    glTexCoord2f( 0.0, 1.0 );
    glVertex3f(radius, height, 0);
    glEnd();

    glPopMatrix();


}

void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);

    //glutSolidTorus(0.5, 10.0, 16, 12);
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




void bed()
{
    //bed

//bed floor
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(5,.2,10);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bed uporer wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,6,-9.9);
    glScalef(5,1.2,.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//bed nicher wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,6,9.9);
    glScalef(5,.8,.1);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//bed nicher paa
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4,3.1,9);
    glScalef(.5,2,.5);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,3.1,9);
    glScalef(.5,2,.5);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //bed uporer paa
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4,3.1,-8);
    glScalef(.5,2,.5);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,3.1,-8);
    glScalef(.5,2,.5);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //bed uporer mattress
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5.6,.5);
    glScalef(4.7,.75,9.3);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //blanket
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5.6+.75+.2,7);
    glScalef(4.3,.4, 2);
    glBindTexture(GL_TEXTURE_2D, 12);
    drawcube(255,255, 0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //pillow
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-2.1,5.6+.75+.2,-7);
    glScalef(1.9,.5, 2);
    glBindTexture(GL_TEXTURE_2D, 13);
    drawcube(255,255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(2.1,5.6+.75+.2,-7);
    glScalef(1.9,.5, 2);
    glBindTexture(GL_TEXTURE_2D, 13);
    drawcube(255,255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void draw_almirah()
{


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,2,3.6);
    glTranslatef(-8.99,1,3.9);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(1.5,6,3.5);
    glTranslatef(-12.35,1.5,4);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2,.5,3.7);
    glTranslatef(-9.0,30,3.77);
    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //details for racks

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,12);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube(255, 255, 255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.2,1.5,1.3);
    glTranslatef(-16/.2,1.4,9.75);
    glBindTexture(GL_TEXTURE_2D, 14);
    drawcube(255, 255, 255);
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




void windowFrame()
{
    //windowframe
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.1);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,4*2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,0.5,.1);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,1.5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    glBindTexture(GL_TEXTURE_2D, 15);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void draw_door()
{
    //door
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,7,20);
    glScalef(4,7,.3);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void corridor()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4,20,25.2);
    glScalef(66,.6,5);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(220,220,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void vents()
{

    glPushMatrix();
    glTranslatef(-52.3998, 42.5999,0);
    glScalef(2,1,20);
    drawcube(86,95,100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-36.4, 42.5999, -18);
    glScalef(14,1,2);
    drawcube(86,95,100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-14.4,42.5999, -18);
    glScalef(8,2,4);
    drawcube(86,95,100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(11.6,42.5999, -18);
    glScalef(18,1,2);
    drawcube(86,95,100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(33.7,42.5999, -18);
    glScalef(4,1.4,2.8);
    drawcube(86,95,100);
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
    drawcube(147,159,159);
    glPopMatrix();

    glPushMatrix();

    vents();
    glPopMatrix();

}


void base()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-5,0,5);
    glScalef(66,.5,30);
    glBindTexture(GL_TEXTURE_2D, 17);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-5,-5.5,5);
    glScalef(70,5,33);
    drawcube(55,55,55);
    glPopMatrix();



    //ground stairs
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,2);

    glPushMatrix();
    glTranslatef(0,-9.9,48);
    glScalef(10,.4,3);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-8.5,45);
    glScalef(10,1,3);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-6.5,42);
    glScalef(10,1,3);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0,-4.5,39);
    glScalef(10,1,3);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(0,0,0);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



}

void draw_room()
{


    ///frontwalls
    //front leftwall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-12,10,20);
    glScalef(8,10,.2);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(149,146,140);
    glPopMatrix();
    //front rightwall
    glPushMatrix();
    glTranslatef(12,10,20);
    glScalef(8,10,.2);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(149,146,140);
    glPopMatrix();

    //front topwall
    glPushMatrix();
    glTranslatef(0,17,20);
    glScalef(4,3,.2);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(149,146,140);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///front Door
    //door frame
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4.1,7,20);
    glScalef(.5,7,.4);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255, 255, 255);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-4.1,7,20);
    glScalef(.5,7,.4);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(173, 123, 7);
    glPopMatrix();
    //doorframe top bar
    glPushMatrix();
    glTranslatef(0,14,20);
    glScalef(4.8,.5,.4);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(173, 123, 7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

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
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,10,0);
    glScalef(.1,10,20);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();

    //right wall

    glPushMatrix();
    glTranslatef(20,10,0);
    glScalef(.1,10,20);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();



    //back wall left
    glPushMatrix();
    glTranslatef(-12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();

    //backwall right
    glPushMatrix();
    glTranslatef(12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();


    //backwall bottom
    glPushMatrix();
    glTranslatef(0,2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();

    //backwall top
    glPushMatrix();
    glTranslatef(0,17.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();





    //bathroom
    glPushMatrix();
    glTranslatef(-10, 10, -10);
    glScalef(0.2, 10, 10);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,10,0);
    glScalef(5,10,.2);
    glBindTexture(GL_TEXTURE_2D, 19);
    drawcube(255,255,255);
    glPopMatrix();
    //bathroom door


    glPushMatrix();
    glTranslatef(-15,6,0.1);
    glScalef(3,6,.2);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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


    glPushMatrix();
    windowFrame();
    glPopMatrix();



}

void ground()
{
    glPushMatrix();
    glTranslatef(0,-11,0);
    glScalef(10000,1,10000);
    drawcube(60,240,60);
    glPopMatrix();

}


void sky()
{
//    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,150,0);
    glScalef(100000,0,100000);
//    glBindTexture(GL_TEXTURE_2D, 2);
    drawcube(135,206,235);
    glPopMatrix();
//    glDisable(GL_TEXTURE_2D);
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



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(20,20.2,28.5);
    glScalef(3,40,3);
    glBindTexture(GL_TEXTURE_2D, 18);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-20,20.2,28.5);
    glScalef(3,40,3);
    glBindTexture(GL_TEXTURE_2D, 18);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-60,20.2,28.5);
    glScalef(3,40,3);
    glBindTexture(GL_TEXTURE_2D, 18);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(60,20.2,28.5);
    glScalef(3,40,3);
    glBindTexture(GL_TEXTURE_2D, 18);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void firstFloorFence()
{


    //horizontal lines
    glPushMatrix();
    glTranslatef(-5.5,27,29);
    glRotatef(90,0,0,1);
    glScalef(.4*3,64*2,.4*3);
    cylinder(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(58,27,24.5);
    glRotatef(90,1,0,0);
    glScalef(.4*3,4.5*2,.4*3);
    cylinder(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68,27,24.5);
    glRotatef(90,1,0,0);
    glScalef(.4*3,4.5*2,.4*3);
    cylinder(50,50,50);
    glPopMatrix();



    //vertical lines

    for(GLint i = 0; i<64; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(58-i*2,23.5,29);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    //fence towards z axis right
    for(GLint i = 1; i<5; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(58,23.5,29-i*2);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    //fence towards z axis left
    for(GLint i = 1; i<5; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(-68,23.5,29-i*2);
        glScalef(.4*3,3.2*2,.4*2);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }





}


void groundFence()
{

//    glRotatef(90,0,0,1);
//    glScalef(.4*3,64*2,.4*3);
//    cylinder(50,50,50);


    //horizontal lines
    //right
    glPushMatrix();
    glTranslatef(40.5,7,29);
    glRotatef(90,0,0,1);
    glScalef(.4*2,20*2,.4*3);
    cylinder(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(58,7,24.5);
    glRotatef(90,1,0,0);
    glScalef(.4*2,4.5*2,.4*2);
    cylinder(50,50,50);
    glPopMatrix();


    //left
    glPushMatrix();
    glTranslatef(-45.5,7,29);
    glRotatef(90,0,0,1);
    glScalef(.4*3,25*2,.4*3);
    cylinder(50,50,50);
    glPopMatrix();


    //vertical fences
    //right
    glEnable(GL_TEXTURE_2D);
    for(GLint i = 0; i<20; i++)
    {
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();
        glTranslatef(58-i*2,3.5,29);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();

    }
    //left
    for(GLint i = 40; i<65; i++)
    {
        glPushMatrix();
        glTranslatef(58-i*2,3.5,29);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
    }



    //fence towards z axis right
    for(GLint i = 1; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(58,3.5,29-i*2);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);



}


void stairFence()
{

    glEnable(GL_TEXTURE_2D);
    for (GLint i = 0; i<14; i++)
    {

        glPushMatrix();
        glTranslatef(-70,3.5+i*.75,25-i*3);
        glScalef(.4*3,3.2*2,.4*3);

        cylinder(255,255,255);
        glPopMatrix();


    }


    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1);
    glScalef(.4*3,3.2*2,.4*3);
    glBindTexture(GL_TEXTURE_2D, 21);
    cylinder(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1-2);
    glScalef(.4*3,3.2*2,.4*3);
    glBindTexture(GL_TEXTURE_2D, 21);
    cylinder(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-70,3.5+13*.75,25-14*3+1-3.5);
    glScalef(.4*3,3.2*2,.4*3);
    glBindTexture(GL_TEXTURE_2D, 21);
    cylinder(255,255,255);
    glPopMatrix();



    for(GLint i = 0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(-70+i*2,3.5+13*.75,25-14*3+1-3.5);
        glScalef(.4*3,3.2*2,.4*3);
        glBindTexture(GL_TEXTURE_2D, 21);
        cylinder(255,255,255);
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);


    //inclined line
    glPushMatrix();
    glTranslatef(-70,11.5,7);
    glRotatef(13.5, 1,0,0);
    glRotatef(90,1,0,0);
    glScalef(.6*3,20*2,.6*3);
    cylinder(50,50,50);
    glPopMatrix();
    //


    glPushMatrix();
    glTranslatef(-70, 7,27.4);
    glRotatef(90, 1,0,0);
    glScalef(.6*3,2*2,.6*3);
    cylinder(40,40,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70, 16,-15.8);
    glRotatef(90,1,0,0);
    glScalef(.6*3,4.5*2,.6*3);
    cylinder(40,40,40);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-65.0002, 16, -19.4);
    glRotatef(90,0,0,1);
    glScalef(.6*3,5*2,.6*3);
    cylinder(50,50,50);
    glPopMatrix();


}


void drawBuilding()
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

//    glPushMatrix();
//    glRotatef(skyRotate, 0,1,0);
//    sky();
//    glPopMatrix();
    glPushMatrix();
    ground();
    glPopMatrix();

}



void trashLid()
{

    glPushMatrix();
    glTranslatef(0,2.8,0);
    glRotatef(14.036,1,0,0);
    glScalef(3.1,.2,3.1);
    drawcube(255,255,255);
    glPopMatrix();
}

void trash()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3,0,0);
    glScalef(.2,2,3);
    glBindTexture(GL_TEXTURE_2D, 22);
    drawcube2(30,85,41);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3,0,0);
    glScalef(.2,2,3);
    glBindTexture(GL_TEXTURE_2D, 22);
    drawcube2(30,85,41);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2.8);
    glScalef(2.8,2,.2);
    glBindTexture(GL_TEXTURE_2D, 22);
    drawcube(26,72,34);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,.75,-2.8);
    glScalef(2.8,2.75,.2);
    glBindTexture(GL_TEXTURE_2D, 22);
    drawcube(26,72,34);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.8,0);
    glScalef(2.8,.2,2.8);
    glBindTexture(GL_TEXTURE_2D, 22);
    drawcube(147,159,159);
    glPopMatrix();



    //trash lid
    glPushMatrix();
    glTranslatef(0,2.8,-3.1);
    glRotatef(lidTheta, 1,0,0);
    glTranslatef(0,-2.8,3.1);
    glBindTexture(GL_TEXTURE_2D, 23);
    trashLid();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //pivot

    glPushMatrix();
    glTranslatef(-2.2, 3.4,-3.25);
    glRotatef(90,0,0,1);
    glScalef(.5,1,.5);
    cylinder(209,217,216);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2.2, 3.4,-3.25);
    glRotatef(90,0,0,1);
    glScalef(.5,1,.5);
    cylinder(209,217,216);
    glPopMatrix();



}



void filledCircle(GLint c1, GLint c2,GLint c3, GLboolean emission=false)
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

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.1;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    //top Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= 0; i -= resolution)

    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(radius, height, 0);
    glEnd();

}


void chair()
{
    //seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

    //seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.8,0.2,0.4,  0.4,0.1,0.2);
    glPopMatrix();

}

void table()
{
    //table
    glPushMatrix();
    glScalef(4, 0.3, 4);
    drawSphere(0.8,0.4,0.00,  0.4,0.2,0);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    drawCube1(0,0,0, 0,0,0.5);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1, 0.2, 1);
    drawSphere(1,0.549,0.00,  0.5,0.2745,0);
    glPopMatrix();
}


void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    table();
    glPopMatrix();





    for(int i = 0; i <= 360; i+=72)
    {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        glTranslatef(0, -17.3, -4);
        chair();
        glPopMatrix();
    }
}



void sofa()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(4,2,.6);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-4.6, -0.4,1.4);
    glScalef(.6, 1.6, 2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(4.6, -0.4,1.4);
    glScalef(.6, 1.6, 2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-.8,1.8);
    glScalef(4,.4,1.2);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, -1.2, 3);
    glScalef(4,.7,.3);
    glBindTexture(GL_TEXTURE_2D, 10);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //sofa
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.95, 1, 0.8);
    glScalef(1.9,1,.2);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.95, 1, 0.8);
    glScalef(1.9,1,.2);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1.95, -0.2, 1.8);
    glScalef(1.9,.2,1.2);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.95, -0.2, 1.8);
    glScalef(1.9,.2,1.2);
    glBindTexture(GL_TEXTURE_2D, 11);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //cushion
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-3.2, 0.8, 1.8);
    glRotatef(45, 0,1,0);
    glScalef(.8,.8, .3);
    glBindTexture(GL_TEXTURE_2D, 24);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.2, 0.8, 1.8);
    glRotatef(-45, 0,1,0);
    glScalef(.8,.8, .3);
    glBindTexture(GL_TEXTURE_2D, 24);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0.8, 1.3);
    glScalef(.8,.8, .3);
    glBindTexture(GL_TEXTURE_2D, 24);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    //feet


    glPushMatrix();
    glTranslatef(4.9, -2.3, 0);
    glRotatef(15,1,0,0);
    glRotatef(15,0,0,1);
    glScalef(.2,.6,.2);
    cylinder(97, 47, 11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.9, -2.3, 3);
    glRotatef(-15,1,0,0);
    glRotatef(15,0,0,1);
    glScalef(.2,.6,.2);
    cylinder(97, 47, 11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.9, -2.3, 3);
    glRotatef(-15,1,0,0);
    glRotatef(-15,0,0,1);
    glScalef(.2,.6,.2);
    cylinder(97, 47, 11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.9, -2.3, 0);
    glRotatef(15,1,0,0);
    glRotatef(-15,0,0,1);
    glScalef(.2,.6,.2);
    cylinder(97, 47, 11);
    glPopMatrix();


}

void computer()
{

    //monitor
    glPushMatrix();
    glScalef(3.2,1.8,.2);
    drawcube(255,255,255);
    glPopMatrix();
    ///frames
    glPushMatrix();
    glTranslatef( 0, -1.7, 0.3);
    glScalef(3.2,.1,.1);
    drawcube(0,155,100);
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 0, 1.7, 0.3);
    glScalef(3.2,.1,.1);
    drawcube(0,155,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.1, 0, 0.3);
    glScalef(.1,1.6,.1);
    drawcube(0,100,155);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.1, 0, 0.3);
    glScalef(.1,1.6,.1);
    drawcube(0,100,155);
    glPopMatrix();

    //texture
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0, 0, 0.2);
    glRotatef(180,0,1,0);
    glScalef(-3,1.6,.05);
    glBindTexture(GL_TEXTURE_2D, 25);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //neck
    glPushMatrix();
    glTranslatef(0, -2.2, 0);
    glRotatef(15,1,0,0);
    glScalef(.4,.6,.2);
    drawcube(120,120,120);
    glPopMatrix();

    //base plate

    glPushMatrix();
    glTranslatef(0, -2.8, 0);
    glScalef(1.5,.3,1.5);
    cylinder(120,120, 0);
    glPopMatrix();




    //keyboard
    glPushMatrix();
    glTranslatef(0,-2.8, 2.3);
    glScalef(1.8,.15,.8);
    drawcube(120,120,120);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-2.65,2.3);
    glScalef(1.8,.001,.8);
    drawcube(120,0,120);
    glPopMatrix();

    //mouse
    glPushMatrix();
    glTranslatef(2.8,-2.8, 2);
    glScalef(.2,.1,.5);
    drawcube(120,120,120);
    glPopMatrix();

}


void slidingDoor()
{

    glPushMatrix();
    glTranslatef(-0.2, 7.1, 20);
    glScalef(.2,7.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.9, 7.1, 20);
    glScalef(.2,7.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.1, .1,20);
    glScalef(3.7,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.1, 14.1,20);
    glScalef(3.7,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-4, 7.2, 19.9);
    glScalef(3.7,7,.2);
    drawcube(86,134,136);
    glPopMatrix();
}


void draw_counter()
{

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


        //light
         glPushMatrix();
        glTranslatef(19.8 ,16.5, 0);
         glRotatef(-90,0,1,0);
         glScalef(6,.8,.2);
         drawcube(255,255,255, light_3_on);
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
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-20,10,0);
    glScalef(.1,10,20);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    // right wall
    glPushMatrix();
    glTranslatef(20,10,0);
    glScalef(.1,10,20);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();


    ///backwall
    //back wall left

    glPushMatrix();
    glTranslatef(-12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);

    glPopMatrix();

    //backwall right
    glPushMatrix();
    glTranslatef(12,10,-20);
    glRotatef(180,0,1,0);
    glScalef(8,10,.1);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();


    //backwall bottom
    glPushMatrix();
    glTranslatef(0,2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    //backwall top
    glPushMatrix();
    glTranslatef(0,17.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,2.5,.1);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    windowFrame();
    glPopMatrix();


    ///bathroom
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-10, 10, -10);
    glScalef(0.2, 10, 10);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(200,200,125);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,10,0);
    glScalef(5,10,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(200,200,125);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //bathroom door

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-15,6,0.1);
    glScalef(3,6,.2);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13,6,0.1);
    glScalef(.2,.5,.3);
    drawcube(100,37,37);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///counter table

    glPushMatrix();
    glTranslatef(2.2, 3, -2.8);
    glScalef(12, 3, 3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.2, 6.3, -.8);
    glScalef(12, .3, 1);
    drawcube(155,155,155);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.2, 6.9, -.8);
    glScalef(12, .3, 1);
    drawcube(55,55,55);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(11.2, 3, -12.8);
    glScalef(3,3,7.1);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.2, 6.3, -10.9);
    glScalef(1,.3,9.1);
    drawcube(155,155,155);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(13.2, 6.9, -10.9);
    glScalef(1,.3,9.1);
    drawcube(55,55,55);
    glPopMatrix();

    ///sofa
    glPushMatrix();
    glTranslatef(-19.2, 3.1, 12.2);
    glRotatef(90, 0,1,0);
    glScalef(1.2,1.2,1.2);
    sofa();
    glPopMatrix();



    ///computer
    glPushMatrix();
    glTranslatef(7.4, 8.4, -3);
    glRotatef(200,0,1,0);
    glScalef(.8,.8,.8);
    computer();
    glPopMatrix();


    ///frames
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(6.2, 10, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 10, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 13.6, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 17.4, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-3, 17.4, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 17.4, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.2, 17.4, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(6.2, 17.4, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6.2, 13.7, -19.9);
    glScalef(1,-1.4,.05);
    glBindTexture(GL_TEXTURE_2D, 27);
    drawcube(235, 177, 61);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///keyholder
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(10.8, 13.7, -19.9);
    glScalef(2.5,-1.8,.05);
    glBindTexture(GL_TEXTURE_2D, 28);
    drawcube(235, 177, 61);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///clock
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(17, 16, -19.9);
    glRotatef(90,1,0,0);
    glScalef(5,.2,-5);
    glBindTexture(GL_TEXTURE_2D, 26);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///front
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,17.3,20);
    glScalef(20,3,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.1, 2.9,20);
    glScalef(6,3,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.1, 2.9,20);
    glScalef(6,3,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.1,10.1, 20);
    glScalef(1,4.2,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(9.1,10.1, 20);
    glScalef(1,4.2,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-19.1,10.1, 20);
    glScalef(1,4.2,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.1,10.1, 20);
    glScalef(1,4.2,.2);
    glBindTexture(GL_TEXTURE_2D, 29);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //counter window frame
    glPushMatrix();
    glTranslatef(-14.1, 5.7,20.2);
    glScalef(4.5,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.1, 5.7,20.2);
    glScalef(4.5,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.1, 14.5,20.2);
    glScalef(4.5,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.1, 14.5,20.2);
    glScalef(4.5,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.4,10.1,20.2);
    glScalef(.2,4.2,.2);
    drawcube(75,87,87);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(18.4,10.1,20.2);
    glScalef(.2,4.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.8,10.1,20.2);
    glScalef(.2,4.2,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9.8,10.1,20.2);
    glScalef(.2,4.2,.2);
    drawcube(75,87,87);
    glPopMatrix();


    //window
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(14.1, 10.1, 20.1);
    glScalef(4.3,4.3,.2);
    glBindTexture(GL_TEXTURE_2D, 30);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-14.1, 10.1, 20.1);
    glScalef(4.3,4.3,.2);
    glBindTexture(GL_TEXTURE_2D, 30);
    drawcube(255,255,255);
    glPopMatrix();


    //door part left
    glPushMatrix();
    glTranslatef(doorDistx1, 0, doorDistz);
    glScalef(1.01,1.005,1);
    glBindTexture(GL_TEXTURE_2D, 30);

    slidingDoor();
    glPopMatrix();

    //door part right
    glPushMatrix();
    glTranslatef(doorDistx2, 0, doorDistz);
    glTranslatef(8.1,0,0);
    glScalef(1.01,1.005,1);
    glBindTexture(GL_TEXTURE_2D, 30);
    slidingDoor();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //door frame
    glPushMatrix();
    glTranslatef(-8.5, 7.3, 20.2);
    glScalef(.2,7.4,.2);
    drawcube(75,87,87);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(8.5, 7.3, 20.2);
    glScalef(.2,7.4,.2);
    drawcube(75,87,87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 14.7, 20.2);
    glScalef(8.7,.2,.2);
    drawcube(75,87,87);
    glPopMatrix();



}






void draw_Sphere(GLint c1, GLint c2, GLint c3,GLboolean emission = false, GLfloat opacity = 1.0)
{
    GLfloat r = c1/255.0;
    GLfloat g = c2/255.0;
    GLfloat b = c3/255.0;
    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, opacity };
    GLfloat mat_ambient[] = { r, g, b, opacity };
    GLfloat mat_diffuse[] = { r, g, b, opacity };
    GLfloat mat_specular[] = { r, g, b, opacity };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {r,g,b,opacity};

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
        else{
            glLightfv( L, GL_AMBIENT, light_ambient);
            glLightfv( L, GL_DIFFUSE, light_diffuse);
            glLightfv( L, GL_SPECULAR, light_specular);
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
        if(L==GL_LIGHT3){
            GLfloat spot_direction[] = {  -1.0,0.0, 0.0 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 70);
        }
        else{
            GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
            glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
            glLightf( L, GL_SPOT_CUTOFF, 70);
        }

    }

}

void halfCircle(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
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

    const double PI = 3.14159;

    /* top triangle */
    double i, resolution  = 0.005;
    double height = 1;
    double radius = 0.5;

    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    //top Circle
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(0, height, 0);  /* center */
    for (i = 2 * PI; i >= PI-resolution; i -= resolution)

    {
        glTexCoord2f( 0.5f * cos(i) + 0.5f, 0.5f * sin(i) + 0.5f );
        glVertex3f(radius * cos(i), height, radius * sin(i));
    }
    /* close the loop back to 0 degrees */
    glTexCoord2f( 0.5, 0.5 );
    glVertex3f(radius, height, 0);
    glEnd();
    glPopMatrix();

}
void halfCircleUnfilled(GLint c1, GLint c2, GLint c3,GLboolean emission = false)
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
    glBegin(GL_LINE_STRIP);
    //glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    glVertex2f(0,0);

    glEnd();
}


void halfCirclew()
{

    glPushMatrix();
    for (float i=0.005; i<.5; i+=0.005)
    {
        glPushMatrix();
        glTranslatef(-(i+1)*3,0,0);
        glScalef(1+i,1+i,1+i);
        halfCircleUnfilled(104,118,181);
        glPopMatrix();
    }

    glPopMatrix();

}



void tree()
{

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glScalef(.01,.01,.01);
    cylinder(82,138,77);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,14.3,0);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.9, 7.89999, 1.8);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 7.1, -6);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.5, 7.1, -0.6);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, 19.3, -1.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-6.2, 12, 1.7);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 19, 0.4);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5, 19, -4.4);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-5, 13.6, -4.4);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.4, 13.7, -7.1);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.7, 11.5, -4);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.7, 16.9, -4.9);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.1, 11.5, -4);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.1, 7.3, 1.1);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.4, 19.1, 0.5);
    glScalef(.5,.5,.5);
    glBindTexture(GL_TEXTURE_2D, 31);
    glutSolidSphere(5,100,100);
    glPopMatrix();











    glPushMatrix();
    glScalef(4,17,4);
    glBindTexture(GL_TEXTURE_2D, 4);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);



}




void xLeaf1()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-6,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,7);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void xLeaf2()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-4,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,6);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void xLeaf3()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-2,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,5);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void xLeaf4()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-1,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,4);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void xLeaf5()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,1,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,3);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void xLeaf6()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,3,4.4);
    glRotatef(-leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,2);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void xLeaf7()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,5,3);
    glRotatef(leafTheta,1,0,0);
    glRotatef(30, 1,0,0);
    glScalef(.4,.4,1);
    glBindTexture(GL_TEXTURE_2D, 3);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void xtree()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,-6, 0);
    glScalef(4,24,4);
    glBindTexture(GL_TEXTURE_2D,4);
    cylinder(122,64,42);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    for(int i=0; i<360; i+=5)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf1();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();

    for(int i=2.5; i<360; i+=5)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf2();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();

    for(int i=10; i<360; i+=15)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf3();
        glPopMatrix();
    }
    glPopMatrix();


    glPushMatrix();

    for(int i=10; i<360; i+=15)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf4();
        glPopMatrix();
    }
    glPopMatrix();



    glPushMatrix();

    for(int i=10; i<360; i+=15)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf5();
        glPopMatrix();
    }
    glPopMatrix();


    glPushMatrix();

    for(int i=10; i<360; i+=15)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf6();
        glPopMatrix();
    }
    glPopMatrix();


    glPushMatrix();

    for(int i=10; i<360; i+=15)
    {
        glPushMatrix();
        glRotatef(i,0,1,0);
        xLeaf7();
        glPopMatrix();
    }
    glPopMatrix();


    //cone


    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(0,5,0);
    glRotatef(-90,1,0,0);
    glScalef(1,1,1);
    glutSolidCone(3,5,100,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);


}


void LD_back()
{

    //front wall
    glPushMatrix();
    glTranslatef(0,45,70);
    glScalef(70, 15, 1);
    drawcube(133,149,220);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,15,70);
    glScalef(70, 15, 1);
    drawcube(133,149,220);
    glPopMatrix();


    //front 2nd floor
    glPushMatrix();
    glTranslatef(0,75,70);
    glScalef(70, 15, 1);
    drawcube(133,149,220);
    glPopMatrix();

}

void LD_front()
{

    //front wall
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(38,30,70);
    glScalef(32, 30, 1);
    glBindTexture(GL_TEXTURE_2D, 32);
    drawcube(133,149,220);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-38,30,70);
    glScalef(32, 30, 1);
    glBindTexture(GL_TEXTURE_2D, 32);
    drawcube(133,149,220);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,40,70);
    glScalef(6,20,1);
    glBindTexture(GL_TEXTURE_2D, 32);
    drawcube(133,149,220);
    glPopMatrix();


    //front 2nd floor
    glPushMatrix();
    glTranslatef(0,75,70);
    glScalef(70, 15, 1);
    glBindTexture(GL_TEXTURE_2D, 32);
    drawcube(133,149,220);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    door


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-6,10,71);
    glRotatef(-door_theta,0,1,0);
    glTranslatef(6,-10,-71);
    glTranslatef(0,10,71);
    glScalef(6,10,.5);
    glBindTexture(GL_TEXTURE_2D, 16);
    drawcube(119,89,87);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    glTranslatef(8.2,10,71);
    glScalef(1,10,.5);
    drawcube(104,118,181);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-8.2,10,71);
    glScalef(1,10,.5);
    drawcube(104,118,181);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.2,20,71);
    glScalef(1.4,.4,.5);
    drawcube(104,118,181);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.2,20,71);
    glScalef(1.4,.4,.5);
    drawcube(104,118,181);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.2,10,71.2);
    glScalef(.2,10.2,.5);
    drawcube(104,118,181);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.2,10,71.2);
    glScalef(.2,10.2,.5);
    drawcube(104,118,181);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,20,71.2);
    glScalef(6.2,.2,.5);
    drawcube(104,118,181);
    glPopMatrix();

///half circles
    glPushMatrix();
    glTranslatef(0,20.7,71.3+0.4);
    glRotatef(90,1,0,0);
    glScalef(11,.2,7);
    halfCircle(58,64,98);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,20.7,71.2+0.4);
    glRotatef(90,1,0,0);
    glScalef(13,.2,9);
    halfCircle(104,118,181);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,22.8,71.3);
    glScalef(2.1,1.1,1);
    halfCirclew();
    glPopMatrix();

///cone front door
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
    glTranslatef(0, 28.5, 71.2);
    glScalef(12,12,12);
    glRotatef(-90,1,0,0);
    glBindTexture(GL_TEXTURE_2D,1);
    glutSolidCone(2,2,6,10000);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);


    //front door pillars
    glPushMatrix();
    glTranslatef(10,14,89);
    glScalef(3,30,3);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,14,89);
    glScalef(3,30,3);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-10,.6,89);
    glScalef(4,1,4);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,.6,89);
    glScalef(4,1,4);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,22.5,89);
    glScalef(4,1,4);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,22.5,89);
    glScalef(4,1,4);
    cylinder(255,255,255);
    glPopMatrix();


}

void LD_window()
{

    glPushMatrix();
    glTranslatef(0,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.1);
    drawcube(121, 67, 209);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,4*2.5,-20);
    glRotatef(180,0,1,0);
    glScalef(4,0.5,.1);
    drawcube(121, 67, 209);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    drawcube(121, 67, 209);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,10,-20);
    glRotatef(180,0,1,0);
    glScalef(.5,5,.3);
    drawcube(121, 67, 209);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    drawcube(121, 67, 209);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.5*3,-20);
    glRotatef(180,0,1,0);
    glScalef(4.9,0.5,.3);
    drawcube(121, 67, 209);
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,9.4,-20.1);
    glScalef(4,5,.1);
    glBindTexture(GL_TEXTURE_2D,30);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void recordPin()
{
    glPushMatrix();
    glRotatef(90,0,1,0);

    glPushMatrix();
    glTranslatef(.8,3.5,0);
    glRotatef(90,0,0,1);
    glScalef(.08,1,.08);
    cylinder(253,255,247);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(.25,3.5,0);
    glRotatef(90,0,0,1);
    glScalef(.08,.1,.08);
    cylinder(66,45,61);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.25,3.475,0);
    glRotatef(90, 1,0,0);
    glScalef(.05,.1,.05);
    glutSolidCone(1,2,6,4);
    glPopMatrix();
    glPopMatrix();
}


void recordDisk()
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-1.1,3.3,.1);
    glScalef(3,.1,3);
    glBindTexture(GL_TEXTURE_2D,33);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void recordSpeaker()
{

    glPushMatrix();
    glTranslatef(2.5, 3.15, -1);
    glRotatef(90,1,0,0);
    glScalef(.1,.1,.1);
    glutSolidTorus(1,1.5,6,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, 3.5, -1);
    glScalef(.25,.6,.25);
    cylinder(255,205,117);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, 4, -1);
    glScalef(.2,.4,.2);
    cylinder(255,205,117);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.4, 4.3, -1);
    glRotatef(45,0,0,1);
    glScalef(.2,.4,.2);
    cylinder(255,205,117);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.3, 4.95, -1);
    glRotatef(60,0,0,1);
    glRotatef(90,1,0,0);

    glScalef(.5,.4,.5);
    glutWireCone(1,3,8,400);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.2, 5, -1);
    glRotatef(60,0,0,1);
    glRotatef(90,1,0,0);

    glScalef(.7,.7,.2);
    glutWireCone(1,3,8,400);
    glPopMatrix();


}

void recordPlayer()
{

    glPushMatrix();

    glScalef(3,.3,1.5);
    drawcube(199,128,126);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,.3,0);
    glScalef(3,.1,1.5);
    drawcube(58,5,6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.4,0);
    glScalef(2.8,1,1.3);
    drawcube(199,128,126);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,2.6,0);
    glScalef(3,.3,1.5);
    drawcube(199,128,126);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,2.9,0);
    glScalef(3,.1,1.5);
    drawcube(58,5,6);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(2.8,.1,1.3);
    drawcube(199,128,126);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.6, 3.2, 0.3);
    glScalef(1,.1,.7);
    drawcube(63,38,62);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.3,3.4,0);
    glScalef(.15,.4,.15);
    cylinder(126,76,124);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.3,0,1.3);
    glTranslatef(0,0,-1.3);
    glRotatef(-pinTheta, 0,1,0);
    glTranslatef(0,0,1.3);
    recordPin();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.1, 3.2, 0.1);
    glScalef(0.08, .3,.08);
    cylinder(246,228,154);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(diskTheta, 0,1,0);
    glTranslatef(1,0,0);
    recordDisk();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-0.5, -0.3, 0.6);
    glScalef(1.1,1.1,1.1);
    recordSpeaker();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 1.2, 1.3);
    glScalef(.8,.4,.02);
    drawcube(255,255,255);
    glPopMatrix();
}



void bedsideTable()
{

    glPushMatrix();
    glScalef(3,4,3);
    drawcube(197,110,15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-4,0);
    glScalef(3.3,.5,3.3);
    drawcube(210,110,15);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,4,0);
    glScalef(3.5,.2,3.5);
    drawcube(210,110,15);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,1.7,3.1);
    glScalef(1.8,.8,.2);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1.7,3.1);
    glScalef(1.8,.8,.2);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,4.5,0);
    recordPlayer();
    glPopMatrix();

}


void bed2()
{
    //bed headboard
    glPushMatrix();
    glTranslatef(0,1.2,-9);
    glScalef(5,2.2,1);
    drawcube(128,51,51);
    glPopMatrix();

    //bed body
    glPushMatrix();
    glScalef(5,1,8);
    drawcube(210, 180, 128);
    glPopMatrix();

    //pillow right far
    glPushMatrix();
    glTranslatef(-2.4, 2, -7.3);
    glRotatef(-20, 1,0,0);
    glScalef(1.8,1,.4);
    drawcube(160, 82, 45);
    glPopMatrix();

    //pillow left near
    glPushMatrix();
    glTranslatef(2.4, 2, -7.3);
    glRotatef(-20, 1,0,0);
    glScalef(1.8,1,.4);
    drawcube(160, 82, 45);
    glPopMatrix();

    //blanket
    glPushMatrix();
    glTranslatef(0,1.2, 4.6);
    glScalef(5.2,.2,3);
    drawcube(160, 82, 45 );
    glPopMatrix();

    //blanket side left part
    glPushMatrix();
    glTranslatef(-5, 0.2,4.6);
    glScalef(.2,1.2,3);
    drawcube(160, 82, 45);
    glPopMatrix();


    //blanket side left part
    glPushMatrix();
    glTranslatef(5, 0.2,4.6);
    glScalef(.2,1.2,3);
    drawcube(160, 82, 45);
    glPopMatrix();
}


void insideWalls()
{
///frontwalls
    //front leftwall
    glPushMatrix();
    glTranslatef(-12-24.5,10,20);
    glScalef(32.5,15,.8);
    drawcube(149,146,140);
    glPopMatrix();
    //front rightwall
    glPushMatrix();
    glTranslatef(12+24.5,10,20);
    glScalef(32.5,15,.8);
    drawcube(149,146,140);
    glPopMatrix();

    //front topwall
    glPushMatrix();
    glTranslatef(0,20,20);
    glScalef(4,5,.8);
    drawcube(149,146,140);
    glPopMatrix();


    ///front Door
    //door frame
    glPushMatrix();
    glTranslatef(4.1,5,20);
    glScalef(.5,10,.9);
    drawcube(173, 123, 7);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-4.1,5,20);
    glScalef(.5,10,.9);
    drawcube(173, 123, 7);
    glPopMatrix();
    //doorframe top bar
    glPushMatrix();
    glTranslatef(0,14.5,20);
    glScalef(4.8,.5,.9);
    drawcube(173, 123, 7);
    glPopMatrix();


    //door
    glPushMatrix();
    glTranslatef(0,-5,0);
    glScalef(1,10/7.0,1);
    glTranslatef(-4,-5,20);
    glRotatef(door_theta, 0,1,0);
    glTranslatef(4,5,-20);


    draw_door();
    glPopMatrix();


}

void insideStairs()
{


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-68.5,9.5,-11);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,8,-7);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,6.5,-3);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-68.5,5,1);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-68.5,3.5,5);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-68.5,2,9);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,.5,13);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,-1,17);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,-2.5,21);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-68.5,-4,25);
    glScalef(3.5, 1,2.5);
    glBindTexture(GL_TEXTURE_2D, 20);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void lovers_Den()
{


    //ground
    glPushMatrix();
    glScalef(70, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();


    //left wall
    glPushMatrix();
    glTranslatef(-70,30,0);
    glScalef(1, 30,70);
    drawcube(133,149,220);
    glPopMatrix();
    //extension
    glPushMatrix();
    glTranslatef(-70,75,0);
    glScalef(1, 15,70);
    drawcube(133,149,220);
    glPopMatrix();

    //right wall
    glPushMatrix();
    glTranslatef(70,30,0);
    glScalef(1, 30,70);
    drawcube(133,149,220);
    glPopMatrix();
    //extension
    glPushMatrix();
    glTranslatef(70,75,0);
    glScalef(1, 15,70);
    drawcube(133,149,220);
    glPopMatrix();


    //ground base
    glPushMatrix();
    glTranslatef(0,-1,0);
    glScalef(80, 1, 80);
    drawcube(50,50,50);
    glPopMatrix();

    //front extension place
    glPushMatrix();
    glTranslatef(0,-1,90);
    glScalef(18, 1, 10);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,90);
    glScalef(18/1.2, .2, 10/1.2);
    drawcube(133,149,220);
    glPopMatrix();




    ///front
    glPushMatrix();
    LD_front();
    glPopMatrix();



    ///front windows
    glPushMatrix();
    glTranslatef( 46.3, 3.8, 91.2);
    LD_window();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( -46.3, 3.8, 91.2);
    LD_window();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 46.3, 3.8+30, 91.2);
    LD_window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -46.3, 3.8+30, 91.2);
    LD_window();
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 46.3, 3.8+60, 91.2);
    LD_window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -46.3, 3.8+60, 91.2);
    LD_window();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 3.8+40, 91.2);
    glScalef(1.5,2.5,1);
    LD_window();
    glPopMatrix();



    ///back
    glPushMatrix();
    glTranslatef(0,0,-140);
    LD_back();
    glPopMatrix();


    ///floors
    glPushMatrix();
    glTranslatef(-42.5, 30,0);
    glScalef(27, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(42.5, 30,0);
    glScalef(27, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 30,40);
    glScalef(16, 1, 30);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 30,-40);
    glScalef(16, 1, 30);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-9.5, 30,0);
    glScalef(6, 1, 10);
    drawcube(50,50,50);
    glPopMatrix();





    glPushMatrix();
    glTranslatef(-42.5, 60,0);
    glScalef(27, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(42.5, 60,0);
    glScalef(27, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 60,40);
    glScalef(16, 1, 30);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 60,-40);
    glScalef(16, 1, 30);
    drawcube(50,50,50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-9.5, 60,0);
    glScalef(6, 1, 10);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 90,0);
    glScalef(70, 1, 70);
    drawcube(50,50,50);
    glPopMatrix();


    ///inside stairs
    glPushMatrix();
    glTranslatef(77+32.5,9.4,39+28.7-57.5);
    glScalef(1.5,2,1.5);
    insideStairs();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(77+32.5,9.4+30,39+28.7-57.5);
    glScalef(1.5,2,1.5);
    insideStairs();
    glPopMatrix();



    ///cone roof
    //front and back
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,109.5,70);
    glScalef(70.4,20,1);
    glBindTexture(GL_TEXTURE_2D, 32);
    draw_TriCube(163,149,220);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,109.5,-70);
    glScalef(70.4,20,1);
    glBindTexture(GL_TEXTURE_2D, 32);
    draw_TriCube(163,149,220);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//    sides

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(35.2, 117.8,0);
    glRotatef(-38,0,0,1);
    glScalef(45.5, 1, 75);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-35.2, 117.8,0);
    glRotatef(38,0,0,1);
    glScalef(45.5, 1, 75);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(50,50,50);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //indoor walls


    glPushMatrix();
    glTranslatef(4.3, 5.5, .9);
    glRotatef(-90,0,1,0);
    insideWalls();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 5.5, .9);
    glRotatef(90,0,1,0);
    insideWalls();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4.3, 35.5, .9);
    glRotatef(-90,0,1,0);
    insideWalls();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 35.5, .9);
    glRotatef(90,0,1,0);
    insideWalls();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(4.3, 65.5, .9);
    glRotatef(-90,0,1,0);
    insideWalls();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.3, 65.5, .9);
    glRotatef(90,0,1,0);
    insideWalls();
    glPopMatrix();


    //3rd floor
    glPushMatrix();
    glTranslatef(0,81+19.3,0);
    glScalef(35,1,70);
    drawcube(50,50,50);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-35.2,100+8.3,0);
    glScalef(.8,9,70);
    drawcube(50,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35.2,100+8.3,-.9);
    glScalef(.8,9,70);
    drawcube(50,50,50);
    glPopMatrix();


    ///bed->bedside table->dining set
    //1
    glPushMatrix();
    glTranslatef( -48.5, 2.1, -13.7);
    glRotatef(90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-48.5+28.5001, 2.1+3.3, -13.7+58.8997);
    glRotatef(-90,0,1,0);
    bedsideTable();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-31.5001-27, 38.6+9.4, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();

    //2
    glPushMatrix();
    glTranslatef( -48.5, 2.1+61, -13.7);
    glRotatef(90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48.5+28.5001, 2.1+3.3+60, -13.7+58.8997);
    glRotatef(-90,0,1,0);
    bedsideTable();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-31.5001-27, 38.6+9.4+59, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();
    //3
    glPushMatrix();
    glTranslatef( -48.5, 2.1+31, -13.7);
    glRotatef(90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-48.5+28.5001, 2.1+3.3+30, -13.7+58.8997);
    glRotatef(-90,0,1,0);
    bedsideTable();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-31.5001-27, 38.6+9.4+29, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();


    //right 1
    glPushMatrix();
    glTranslatef( 48.5, 2.1, -13.7);
    glRotatef(-90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(48.5-28.5001, 2.1+3.3, -13.7+58.8997);
    glRotatef(90,0,1,0);
    bedsideTable();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+31.5001+27, 38.6+9.4, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();


    //right 2
    glPushMatrix();
    glTranslatef( 48.5, 2.1+61, -13.7);
    glRotatef(-90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(48.5-28.5001, 2.1+3.3+60, -13.7+58.8997);
    glRotatef(90,0,1,0);
    bedsideTable();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+31.5001+27, 38.6+9.4+59, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();
    //right 3
    glPushMatrix();
    glTranslatef( 48.5, 2.1+31, -13.7);
    glRotatef(-90,0,1,0);
    glScalef(2,2,2);
    bed2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(48.5-28.5001, 2.1+3.3+30, -13.7+58.8997);
    glRotatef(90,0,1,0);
    bedsideTable();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(+31.5001+27, 38.6+9.4+29, 17.7+20);
    glScalef(2.5,2.5,2.5);
    diningSet();
    glPopMatrix();







}



void smoke()
{

    glPushMatrix();
    glTranslatef(ttx, tty, ttz);
    draw_Sphere(66,73,78, false, .3);
    glPopMatrix();

}







void gasMchine()
{
    //gasMachineBase

    glPushMatrix();
    glTranslatef(-8,2,0);
    glScalef(5,.3,4);

    drawcube(0,0,0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-8,6.5,0);
    glScalef(3.5,6,2.8);

    drawcube(192,40,41);
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-8,14,0);
    glScalef(3.2,2,2.4);
    drawcube(0,0,0);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,11.6,2.6);
    glScalef(2,-2.1,.4);
    glBindTexture(GL_TEXTURE_2D, 34);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8,8,2.6);
    glScalef(2,.4,.4);
    drawcube(255,255,255);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-8.5,17,0);
    glScalef(1,2,1);
    cylinder(255,255,255);
    glTranslatef(1,0,0);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-8.2,0,-19.2);
    glScalef(7,-1.5,-5);
    glBindTexture(GL_TEXTURE_2D, 35);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void PetrolPump()
{

    glEnable(GL_TEXTURE_2D);
    //top
    glPushMatrix();
    glTranslatef(0,25,0);
    glScalef(20,2,13);
    glBindTexture(GL_TEXTURE_2D, 37);
    drawcube(255,255,255);
    glPopMatrix();




    //bottom
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(20,2,7);
    glBindTexture(GL_TEXTURE_2D, 37);
    drawcube(255,255,255);
    glPopMatrix();

    //piller
    glPushMatrix();
    glTranslatef(-16,12.2,0);
    glScalef(1,25,2);
    glBindTexture(GL_TEXTURE_2D, 36);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(16,12.2,0);
    glScalef(1,25,2);
    glBindTexture(GL_TEXTURE_2D, 36);
    cylinder(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(0,23.1,0);
    glScalef(2,.8,2);
    cylinder(255,55,55,light_2_on);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180,0,1,0);
    gasMchine();
    glPopMatrix();

    glPushMatrix();
    gasMchine();
    glPopMatrix();

}



void roads()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    for(int i =0; i<100; i++)
    {
        glPushMatrix();
        glTranslatef(0,.5,i*20);
        glScalef(1,.2,7);
        drawcube(255,255,255);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0,.5,-i*20);
        glScalef(1,.2,7);
        drawcube(255,255,255);
        glPopMatrix();
    }





    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1000);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1000);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1200);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1400);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);




    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1600);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,1800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,0,-1800);
    glScalef(20,.5,100);
    glBindTexture(GL_TEXTURE_2D,7);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}




void sideRoad()
{



    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-251.901+18.7, -9.6, 223.3);
    glRotatef(90,0,1,0);
    glScalef(20,.5,90);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-163.1, -9.6,273);
//    glRotatef(90,0,1,0);
    glScalef(20,.5,30);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-251.901+18.7, -9.6, 223.3+99.7);
    glRotatef(90,0,1,0);
    glScalef(20,.5,90);
    glBindTexture(GL_TEXTURE_2D, 8);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void pointyPilar()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
    glScalef(1.5,20,1.5);
    glBindTexture(GL_TEXTURE_2D,32);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(0,20,0) ;
    glScalef(2.5,2,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,20,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,21,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,19,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,23,0);
    glScalef(2,4,2);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,24.2,0);
    glRotatef(-90,1,0,0);
    glutWireCone(3,4,4,100);
    glPopMatrix();


}


void roundPilar()
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
//    glTranslatef(ttx,tty,ttz);
    glScalef(1.5,20,1.5);
    glBindTexture(GL_TEXTURE_2D,32);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0,20,0) ;
    glScalef(2.5,2,2.5);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,20,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,21,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,19,0) ;
    glScalef(3,.2,3);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,23,0);
    glScalef(2,4,2);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,26.4,0);

    glutSolidSphere(3,100,100);
    glPopMatrix();

}

void boundaryWalls()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(20,12,1);
    glBindTexture(GL_TEXTURE_2D, 1);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void boundaryLeft()
{

    glPushMatrix();
    glTranslatef(+20,0,0);
    glScalef(1,.8,1);
    pointyPilar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-3.3,0);
    boundaryWalls();
    glPopMatrix();


    for (int i=0; i<7; i++)
    {
        glPushMatrix();
        glTranslatef(-40*i-20,0,0);
        glScalef(1,.8,1);
        roundPilar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(-300,0,0);
    glScalef(1,.8,1);
    pointyPilar();
    glPopMatrix();


}


void boundaryBackLeft()
{
    glPushMatrix();
    for (int i=0; i<7; i++)
    {
        glPushMatrix();
        glTranslatef(-40*i-20,0,0);
        glScalef(1,.8,1);
        roundPilar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }
    glPopMatrix();

}

void boundaryBack()
{

    glPushMatrix();
    for (int i=0; i<10; i++)
    {
        glPushMatrix();
        glTranslatef(-40*i-20,0,0);
        glScalef(1,.8,1);
        roundPilar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }
    glPopMatrix();

}


void boundaryRight()
{
    glPushMatrix();
    for (int i=0; i<10; i++)
    {
        glPushMatrix();
        glTranslatef(-40*i-20,0,0);
        glScalef(1,.8,1);
        roundPilar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }
    glPopMatrix();

}


void boundaryFrontRight()
{
    glPushMatrix();
    for (int i=0; i<10; i++)
    {
        glPushMatrix();
        glTranslatef(-40*i-20,0,0);
        glScalef(1,.8,1);
        roundPilar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }
    glPopMatrix();
}

void boundaryFront()
{
    glPushMatrix();

    glPushMatrix();
    glTranslatef(-40-20,0,0);
    glScalef(1,.8,1);
    roundPilar();
    glPopMatrix();



    glPopMatrix();


    glPushMatrix();
    for (int i=0; i<2; i++)
    {

        glPushMatrix();
        glTranslatef(-40*i-40,-3.3,0);
        boundaryWalls();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,0,0);
    glScalef(1,.8,1);
    pointyPilar();
    glPopMatrix();
}



void boundary()
{

    glPushMatrix();
    boundaryLeft();
    glPopMatrix();

    glPushMatrix();
    glTranslatef( -299.201,0,-300.301);
    glRotatef(90,0,1,0);
    boundaryBackLeft();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-144+115.5,0,-545-58.3);
    glRotatef(50,0,1,0);
    boundaryBack();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(322.301,0,-378.401);
    glRotatef(150+180,0,1,0);
    boundaryRight();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( 305.801,0,34.1-14.3);

    glRotatef(-90,0,1,0);
    glScalef(.97,1,1);
    boundaryFrontRight();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(204.6,0,0);
    glRotatef(180,0,1,0);
    boundaryFront();
    glPopMatrix();


}




void materialProperty_car(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{

    difX = difX /255.0;
    difY = difY /255.0;
    difZ = difZ /255.0;


    ambX = ambX/255.0;
    ambY = ambY/255.0;
    ambZ = ambZ/255.0;

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void car(double pri_x, double pri_y, double pri_z, double sec_x, double sec_y, double sec_z)
{
    glPushMatrix();
    glRotatef(0, 1.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);

    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glEnd();


    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);

    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);

    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);

    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( sec_x, sec_y, sec_z, sec_x, sec_y, sec_z);
    glBegin(GL_POLYGON);

    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);

    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0f,-15.0f,15.0f);
    glVertex3f(-30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,15.0f);
    glEnd();


    glBegin(GL_3D);
//    glColor3f(1, 0, 0);
    glTranslated(-20.0f,-15.0f,15.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);


//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,-30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(45.0f,0.0f,0.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
    glEnd();




    glPushMatrix();
    glColor3f(3.0,4.0,5.0);
    //glRotatef(45,0,0,1);
    glScalef(10,0.3,3);

//    glutWireCube(-20);


    glPopMatrix();

    glPopMatrix();
}


void cokeBottle()
{

    glPushMatrix();

}





void sphere2(GLfloat r,GLfloat g,GLfloat b,GLboolean emission=false)
{
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
    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj,1);
    gluSphere(qobj,10,25,25);
}


void parkingLot()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(180,.4,40);
    glBindTexture(GL_TEXTURE_2D,39);
    drawcube(143,155,154);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    for(int i = 0; i<6; i++)
    {
        glPushMatrix();
        glTranslatef(i*30,.3,19.8);
        glScalef(1,.3,20);
        drawcube(255,255,255);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-i*30,.3,19.8);
        glScalef(1,.3,20);
        drawcube(255,255,255);
        glPopMatrix();
    }


    //cars in parking lot

    for(int i =0; i<3; i++)
    {
        glPushMatrix();
        glTranslatef(-18.7+i*60, 11, 12.1);
        glRotatef(-90,0,1,0);
        glScalef(.5,.5,.5);
        car(255,0,255,0,255,255);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-18.7-i*60, 11, 12.1);
        glRotatef(-90,0,1,0);
        glScalef(.5,.5,.5);
        car(0,0,255,255,255,0);
        glPopMatrix();
    }





}


void carOnRoad()
{

    glPushMatrix();
    glRotatef(30,0,1,0);

    glPushMatrix();
    glTranslatef(-415.1+82.5+carx, .3, 166.1-1650+carz);
    glRotatef(90,0,1,0);
    glScalef(.5,.5,.5);
    car(66,207,222,237,198,45);
    glPopMatrix();
    glPopMatrix();

}

void carOnRoad2()
{
    glPushMatrix();
    glRotatef(30,0,1,0);

    glPushMatrix();
    glTranslatef(-415.1+82.5, .3, 166.1-2400+car2z);
    glRotatef(90,0,1,0);
    glScalef(.5,.5,.5);
    car(234,146,49,28,165,134);
    glPopMatrix();
    glPopMatrix();

}


void carOnRoad3()
{

    glPushMatrix();
    glRotatef(30,0,1,0);

    glPushMatrix();
    glTranslatef(-415.1+82.5-22, .3, 166.1-1650+car3z);
    glRotatef(90,0,1,0);
    glScalef(.5,.5,.5);
    car(164,32,242,28,165,134);
    glPopMatrix();
    glPopMatrix();

}


void carOnRoad4()
{

    glPushMatrix();
    glRotatef(30,0,1,0);

    glPushMatrix();
    glTranslatef(-415.1+82.5-22, .3, 166.1-1650+car4z);
    glRotatef(90,0,1,0);
    glScalef(.5,.5,.5);
    car(241,241,5,0,241,241);
    glPopMatrix();
    glPopMatrix();

}


void carOnRoad5()
{

    glPushMatrix();
    glRotatef(30,0,1,0);

    glPushMatrix();
    glTranslatef(-415.1+82.5-22, .3, 166.1-1650+car5z);
    glRotatef(90,0,1,0);
    glScalef(.5,.5,.5);
    car(207,59,60,20,199,220);
    glPopMatrix();
    glPopMatrix();

}


void drawAllcar()
{


    glPushMatrix();
    glRotatef(30,0,1,0);
    glTranslatef((-415.1+82.5+carx), .3, (166.1-1650+carz));
    glRotatef(carTheta, 0,1,0);
    glTranslatef(-(-415.1+82.5+carx), .3, -(166.1-1650+carz));
    glRotatef(-30,0,1,0);
    carOnRoad();
    glPopMatrix();

    glPushMatrix();
    carOnRoad2();
    glPopMatrix();


    glPushMatrix();
    carOnRoad3();
    glPopMatrix();


    glPushMatrix();
    carOnRoad4();
    glPopMatrix();


    glPushMatrix();
    carOnRoad5();
    glPopMatrix();


}

void drawAllTree()
{

    glPushMatrix();
    glTranslatef(-279.401, 5.5, 272.801);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279.401-42.9, 5.5, 272.801-71.5);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();
//
//
    glPushMatrix();
    glTranslatef(-279.401+45, 5.5, 272.801+77);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-279.401-88, 5.5, 272.801-146);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();
//
//
//
    glPushMatrix();
    glTranslatef(-279.401+76.9999, 5.5, 272.801+130.9);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();
//
//
//
    glPushMatrix();
    glTranslatef(-279.401+76.9999+38.5, 5.5, 272.801+130.9+68.2);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-279.401+76.9999+38.5+31.9, 5.5, 272.801+130.9+68.2+57.2);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-279.401-130.9, 5.5, 272.801-214.5);
    glRotatef(treeTheta, 0,0,1);
    xtree();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-297.001,0,35.2);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-297.001+39.6,0,35.2-28.6);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-297.001+39.6 -28.6,0,35.2-28.6+90.1999);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-297.001+39.6+41.8,0,35.2-28.6+0);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-297.001+39.6+ 1.1,0,35.2-28.6+42.9);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(271.701,0,0);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(271.701-12.1,0,71.5);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(271.701-14.3,0,0+124.3);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(271.701-2.2,0,0+146.3);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(271.701-31.9,0,0+23.1);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,-172.7);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(100,0,-172.7);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-100,0,-172.7);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-50,0,-400.7);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(50,0,-400.7);
    glScalef(1.5,2,1.5);
    tree();
    glPopMatrix();

}

void sign(){

    glPushMatrix();
    glScalef(2,2,2);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.2,0);
    glScalef(1.6,1.6,1.6);
    drawcube(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,4.4,0);
    glScalef(1,1,1);
    drawcube(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,35.2,0);
    glScalef(1,60,1);
    cylinder(255,255,255);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,65,0);
    glRotatef(-90,1,0,0);
    glScalef(1,1,1);
    glutSolidCone(1.5,2.5,100,100);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,62.7, 15.4);
    glRotatef(90,1,0,0);
    glScalef(.7,30,.7);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,57.6, 7.7);
    glScalef(.4,10,.4);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,57.6, 25.7);
    glScalef(.4,10,.4);
    cylinder(255,255,255);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,62.7, 29.7);
//    glRotatef(0,1,0,0);
    glScalef(1,1,1);
    glutSolidCone(1.5,2.5,100,100);
    glPopMatrix();


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(.1,42.9 ,16.5);
    glRotatef(90,0,1,0);
    glScalef(15, -10, .5);
    glBindTexture(GL_TEXTURE_2D,43);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-.1,42.9 ,16.5);
    glRotatef(90,0,1,0);
    glScalef(-15, 10, .5);
    glBindTexture(GL_TEXTURE_2D,43);
    drawcube(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void draw_all()
{

    glPushMatrix();
    glTranslatef(-75-80, 0, 50);
    glRotatef(40, 0,1,0);
    drawBuilding();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(75+80,0,50);
    glRotatef(-40, 0,1,0);
    glScalef(-1,1,1);
    drawBuilding();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(209, -4, 120);
    glRotatef(50, 0,1,0);
    glScalef(3,3,3);
    trash();
    glTranslatef(8,0,0);
    trash();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(-228.8, -10, 124.3);
    glRotatef(40,0,1,0);
    glScalef(1.4,1.4,1.4);
    draw_counter();
    glPopMatrix();


    glPushMatrix();
        glTranslatef(ttx,tty,ttz);

         glScalef(.3,.3,.3);
         drawcube(255,255,255);
         glPopMatrix();

//




    glPushMatrix();
    glTranslatef(0,-4.7-3.4,0);
    glScalef(1,1,0.5);
    lovers_Den();
    glPopMatrix();
//
////
//
//
//
    glPushMatrix();
    glTranslatef(-64-23,-8.5, 353+15.5);
    glRotatef(30,0,1,0);
//    glScalef(.7,.7,.7);
    PetrolPump();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(ttx,tty,ttz);
    glScalef(2,.7,2);
    cylinder(255,54.7,255);
    glPopMatrix();
//
////
////
    glPushMatrix();
    glTranslatef(-375-50,-9.6,-50);
    glRotatef(30,0,1,0);
    roads();
    glPopMatrix();
//
//
    glPushMatrix();
    glRotatef(30,0,1,0);
    sideRoad();
    glPopMatrix();
////
////
    glPushMatrix();
    glTranslatef(-332+137.5,5.5,25+261.801);
    glRotatef(-60,0,1,0);
    boundary();
    glPopMatrix();

//
//

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(300+sunx,suny,-800);
    glScalef(4,4,4);
    glBindTexture(GL_TEXTURE_2D,t);
    sphere2(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glRotatef(nightTheta,0,0,1);
    glRotatef(skyTheta, 0,1,0);
    glRotatef(90,0,0,1);
    glScalef(100,100,100);
    glBindTexture(GL_TEXTURE_2D,t2);
    sphere2(255,255,255);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//
//
//
//
////
    glPushMatrix();
    glTranslatef(-110+215.6, -9.9, 414.701+3.3);
    glRotatef(30,0,1,0);
    parkingLot();
    glPopMatrix();
////
////


    glPushMatrix();
    drawAllTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-122.1, -8.8, 386.101);
    glRotatef(-60,0,1,0);
    sign();
    glPopMatrix();


    glPushMatrix();

    drawAllcar();
    glPopMatrix();


}

void river()
{
    glPushMatrix();
    glScalef(4,4,200);
    drawcube(0,0,255);
    glPopMatrix();

}
int state = 1;
void display(void)
{


    // Count the FPS
    static int frame = 0;
    static int time = 0;
    static int timebase = 0;
//	char s[30]{};
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000)
    {
        std::string fps = "FPS: " + std::to_string(frame * 1000.0 / (time - timebase));
        std::string title = "Project" + std::string(" - ") + fps;
        glutSetWindowTitle(title.c_str());
        //sprintf(s, "FPS:%4.2f", frame * 1000.0 / (time - timebase));
        timebase = time;
        frame = 0;
    }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
//    glFrustum(-10, 10, -10, 10, 4, 200);
    gluPerspective(60,1,5,20000);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upx, upy, upz);
    glViewport(0,0, windowHeight, windowWidth);
    glScalef(scale_x, scale_y, scale_z);
    glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta,axis_x, axis_y, axis_z );
    glRotatef( beta,axis_x, axis_y, axis_z );



    glPushMatrix();
//    river();
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

    light(300+sunx,suny,-800,GL_LIGHT0, light_0_on, true, sr, sg,sb);
    light(0.0,30,0, GL_LIGHT1,light_1_on, false);
    light(-86.8999, 14.3, 368.501, GL_LIGHT2,light_2_on, true, 1,.3,.3);
    light(-206.8,13.2,107.8, GL_LIGHT3,light_3_on, true);
//    -206.8 13.2 107.8

    keyFunc();
    glFlush();
    glutSwapBuffers();
}






void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'l':
        keyState[key] = true;
        break;
    case 'j':
        keyState[key] = true;
        break;
    case 'i':
        keyState[key] = true;
        break;
    case 'k':
        keyState[key] = true;
        break;
    case 'o':
        keyState[key] = true;
        break;
    case 'u':
        keyState[key] = true;
        break;

    case '[':
        keyState[key] = true;
        break;

    case ']':
        keyState[key] = true;
        break;
    case 's':
        keyState[key] = true;
        break;
    case 'S':
        keyState[key] = true;
        break;
    case 'w':
        keyState[key] = true;
        break;
    case 'W':
        keyState[key] = true;
        break;

    case 'd':
        keyState[key] = true;
        break;
    case 'D':
        keyState[key] = true;
        break;
    case 'A':
        keyState[key] = true;
        break;
    case 'a':
        keyState[key] = true;
        break;

    case 'q':
        bRotate = !bRotate;
        uRotate = false;
        tRotate = false;
        stateqP = 0;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;
    case 'Q':
        bRotate = !bRotate;
        uRotate = false;
        tRotate = false;
        stateqP = 1;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 'r':
        uRotate = !uRotate;
        bRotate = false;
        tRotate = false;
        staterP = 0;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        tRotate = false;
        staterP = 1;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        glutPostRedisplay();
        break;

    case 'e':
        tRotate = !tRotate;
        uRotate = false;
        bRotate = false;
        stateeP = 0;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        glutPostRedisplay();
        break;
    case 'E':
        tRotate = !tRotate;
        uRotate = false;
        bRotate = false;
        stateeP = 1;
        axis_x=0.0;
        axis_y=0.0;
        axis_z=1.0;
        glutPostRedisplay();
        break;



    case '%':
        activate_roll = !activate_roll;
        keyState[key] = true;
        break;
    case '^':
        activate_pitch = !activate_pitch;
        keyState[key] = true;
        break;
    case '&':
        activate_yaw = !activate_yaw;
        keyState[key] = true;
        break;
    case 'z':
    case 'Z':
        keyState[key] = true;
        break;
    case 'c':
    case 'C':
        keyState[key] = true;
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
      case '@':
        light_3_on = !light_3_on;
//        std::cout<<light_3_on<<std::endl;
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
        doorOpen = true;
        doorClose = false;
        break;
    case 'N':
        doorOpen = false;
        doorClose = true;
        break;
    case 'm':
        dRotate = !dRotate;
        dRotate2 = false;
        break;
    case 'M':
        dRotate2 = !dRotate2;
        dRotate = false;
        break;
    case 'g':
        lidOpen = true;
        lidClose = false;
        break;
    case 'G':
        lidOpen = false;
        lidClose = true;
        break;
    case 'p':
        mPlay = true;
        mPause = false;
        PlaySound(TEXT("E:\\Gx\\abc\\Project\\asset\\song\\song.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
    case 'P':
        mPlay = false;
        mPause = true;
        PlaySound(0,0,0);
        break;

    case 'x':
        night = !night;
        break;

    case 'v':
        skyRotate = true;
        break;
    case 'V':
        skyRotate = false;
        break;

    case 'b':
        carMove = !carMove;
        break;

    case 'y':
        treeMove = !treeMove;
        break;

    case '?':
        init();
        break;
    case '/':
        init2();
        break;


    case '\'':
//        tty -= 0.1;
        tty -= 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case '"':
//        tty += 0.1;
        tty += 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case ';':
//        ttx -= 0.1;
        ttx -= 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case ':':
//        ttx += 0.1;
        ttx += 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;

    case '\\':
//        ttz -= 0.1;
        ttz -= 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case '|':
//        ttz += 0.1;
        ttz += 1.1;
        std::cout<<"Starting Point "<<ttx<<" "<<tty<<" "<<ttz<<" \n";
        break;
    case 27:	// Escape key
        exit(1);
    }
}

void myKeyboardFunc2( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'l':
        keyState[key] = false;
        break;
    case 'j':
        keyState[key] = false;
        break;
    case 'i':
        keyState[key] = false;

        break;
    case 'k':
        keyState[key] = false;
        break;
    case 'o':
        keyState[key] = false;
        break;
    case 'u':
        keyState[key] = false;
        break;

    case 'q':
    case 'Q':
        keyState[key] = false;
        break;

    case 'r':
    case 'R':
        keyState[key] = false;
        break;

    case 't':
    case 'T':
        keyState[key] = false;
        break;

    case '[':
        keyState[key] = false;
        break;

    case ']':
        keyState[key] = false;
        break;
    case 's':
        keyState[key] = false;
        break;
    case 'S':
        keyState[key] = false;
        break;
    case 'w':
        keyState[key] = false;
        break;
    case 'W':
        keyState[key] = false;
        break;
    case 'd':
        keyState[key] = false;
        break;
    case 'D':
        keyState[key] = false;
        break;
    case 'A':
        keyState[key] = false;
        break;
    case 'a':
        keyState[key] = false;
        break;

    case 'z':
    case 'Z':

        keyState[key] = false;
        break;
    case 'c':
    case 'C':

        keyState[key] = false;
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
        theta += .5*pow(-1, stateqP);
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
        std::cout<<theta<<std::endl;

    }

    if (uRotate == true)
    {
        alpha += .5*pow(-1, staterP);
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);

    }

    if (tRotate == true)
    {
        beta += .5*pow(-1, stateeP);
        if(beta > 360.0)
            beta -= 360.0*floor(beta/360.0);

    }
    if(dRotate == true)
    {

        if(door_theta>-120)
        {
            door_theta-=1.0;

        }

    }
    if(dRotate2==true)
    {
        if(door_theta<0)
        {
            door_theta+=1.0;
        }
    }

    if(lidOpen == true)
    {
        if(lidTheta>-90)
        {
            lidTheta-=1.0;
        }
    }
    if(lidClose == true)
    {
        if(lidTheta<0)
        {
            lidTheta+=1.0;
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

    if(doorOpen == true)
    {
        if(doorDistz>-.7) doorDistz-=.05;

        if(doorDistz<-.69)
        {

            if(doorDistx1>-8.2) doorDistx1-=.05;

            if(doorDistx2<8.2) doorDistx2+=.05;
        }
    }

    if(doorClose == true)
    {


        if(doorDistx1<0) doorDistx1+=.05;

        if(doorDistx2>0) doorDistx2-=.05;
        if(doorDistx1>-.01)
        {
            if(doorDistz<0) doorDistz+=.05;
        }

    }


    if(mPlay==true)
    {
        if(pinTheta<90)
        {
            pinTheta++;
        }
        if(pinTheta==90)
        {
            diskTheta++;
            if(diskTheta>=360)
            {
                diskTheta=0;
            }
        }
    }
    if(mPause == true)
    {
        if(pinTheta>0)
        {
            pinTheta--;
        }
    }

    if(skyRotate == true)
    {

        if(night==false)
        {
            if(sunx>-500)
            {
                if(suny<500)
                {
                    sunx-=2;
                    suny+=2;
                }
            }
            else if(suny>0)
            {
                sunx-=2;
                if(sunx==-750) t2=42;
                suny-=2;
            }
            if(suny==0)
            {
                night = true;
                t = 38;
                t2 = 41;
                sunx=0;
                suny=0;
                sr = .7;
                sg = .7;
                sb = .2;
            }
//
        }
        if(night==true){
             if(sunx>-500)
            {
                if(suny<500)
                {
                    sunx-=2;
                    suny+=2;
                }
            }
            else if(suny>0)
            {
                sunx-=2;
                suny-=2;
            }
            if(suny==0)
            {
                night = false;
                t = 40;
                t2 = 9;
                sunx=0;
                suny=0;
                sr = 1;
                sg = 1;
                sb = 1;
            }
        }

        if(skyTheta<360)
        {
            skyTheta++;
        }
        else
        {
            skyTheta=0.0;
        }
    }

//    if(night == true)
//    {
//        if(nightTheta<180)
//        {
//            nightTheta++;
//        }
//        else
//        {
//            nightTheta=0.0;
//        }
//    }

    if(carMove == true)
    {
        if(carz<1675)
        {
            var = 0.0;
            carz += 3;
//

        }
        else if(carz>=1675 && carz<1708)
        {
            if(carTheta<90)
            {
                carTheta++;
                carz+=.35;
                carx+=.35;
//                    std::cout<<carz<<std::endl;
            }
        }
        else if(carz>=1708 && carz<1728.3)
        {
            if(carx<140)
            {
                if(var<100)
                {
                    if(carx>70 && carx<75)
                    {
                        var++;
                    }
                    else carx++;
                }
                else carx++;

            }
            else if(carx>=140 && carx<165)
            {
                if(carTheta>0)
                {
                    carTheta-=2;
                    carx+=.45;
                    carz+=.45;
                }
            }
            //160.4 1728.4

        }


        else if(carz>=1728.3 && carz<1800)
        {
            carz++;
        }
        else if(carz>=1800 && carz<=1816)
        {
            if(carTheta>-90)
            {
                carTheta-=2;
                carx-=.45;
                carz+=.35;
            }
//            std::cout<<carx<<" "<<carz<<std::endl;
        }

        else if(carz>1816)
        {
            if(carx>20)
            {
                carx--;
            }
            else
            {
                if(carTheta<0)
                {
                    carTheta+=2;
                    carx-=.45;
                    carz+=.45;
                }
                else
                {
                    if(carz>=3200)
                    {
                        carz=0;
                    }
                    carz+=3;
                }
            }
        }

        if(car2z<3200)
        {
            car2z+=3;
        }
        else car2z=0;

        if(car3z>0)
        {
            car3z-=3;
        }
        else car3z=3200;


        if(car4z>0)
        {
            car4z-=3;
        }
        else car4z=3200;

        if(car5z>0)
        {
            car5z-=3;
        }
        else car5z=3200;


    }

    if(treeMove==true)
    {
        if(var2==0)
        {
            if(treeTheta<5)
            {
                treeTheta+=.2;
                if(treeTheta>=5) var2 = 1;
                if(leafTheta<25)
                {
                    leafTheta+=1;
                }
            }
        }
        else
        {
            if(treeTheta>-.1)
            {
                treeTheta-=.2;
            }
            if(treeTheta<=0) var2=0;
            if(leafTheta>0)
            {
                leafTheta-=1;
            }
        }

    }

    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Motel");

    std::cout << glGetString(GL_RENDERER) << std::endl;


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\wallTilesB.bmp"); //texture 1
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\wood.bmp"); //texture 2
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\xtree.bmp"); //texture 3
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\bark.bmp"); //texture 4
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\windowFrame.bmp"); //texture 5
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\sky2.bmp"); //texture 6
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\road2.bmp"); //texture 7
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\road.bmp"); //texture 8
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\sky.bmp"); //texture 9
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\bed.bmp"); //texture 10
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\mattress.bmp"); //texture 11
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\blanket.bmp"); //texture 12
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\pillow.bmp"); //texture 13
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\wood4.bmp"); //texture 14
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\windowFrame.bmp"); //texture 15
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\door.bmp"); //texture 16
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\corridorFloor.bmp"); //texture 17
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\pillar.bmp"); //texture 18
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\wall2.bmp"); //texture 19
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\stair.bmp"); //texture 20
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\pillar2.bmp"); //texture 21
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\trash2.bmp"); //texture 22
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\trashlid.bmp"); //texture 23
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\cushion.bmp"); //texture 24
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\pc.bmp"); //texture 25
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\clock.bmp"); //texture 26
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\list.bmp"); //texture 27
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\keyholder.bmp"); //texture 28
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\wall.bmp"); //texture 29
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\glass.bmp"); //texture 30
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\leaf2.bmp"); //texture 31
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\walls2.bmp"); //texture 32
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\ts2.bmp"); //texture 33
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\meter.bmp"); //texture 34
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\meter2.bmp"); //texture 35
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\iron.bmp"); //texture 36
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\iron2.bmp"); //texture 37
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\moon2.bmp"); //texture 38
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\pl.bmp"); //texture 39
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\sun2.bmp"); //texture 40
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\night2.bmp"); //texture 41
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\eve.bmp"); //texture 42
    LoadTexture("E:\\GX\\abc\\Project\\asset\\img\\logo.bmp"); //texture 43


    glutKeyboardFunc(myKeyboardFunc);
    glutKeyboardUpFunc(myKeyboardFunc2);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
