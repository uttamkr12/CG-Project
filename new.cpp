#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define RADIUS 0.025

#define RATIO (4./3.)

int cheat;
bool show[20][30];
float x_brick[50][50];
float y_brick[50][50];
int score=0;
int start=0;
string co,info;
int level_flag=1;
int launch_flag=0;
int lc[][2]={{0,0},{8,4},{10,6}};
float paddle_x = 0;
float paddle_y = -0.8;
float paddle_speed = 0;
const float PaddleSpeedFactor = 2.5;

bool phit_center = false, phit_corner = false;
bool game_over = false;

float speed_x = 0.;
float speed_y = 0.;

float x_pos = 0,y_pos = -0.75;
int lives  = 3;

float T_last_frame = 0.;
int flags=0;
void set_xy();
void output(string c,double x,double y,float r,float g,float b, void* font)
{
        int len,i;
        glColor3f(r,g,b);
        glRasterPos2d(x,y);
        len = c.length();
        for(i=0; i<len; i++)
        {
                glutBitmapCharacter(font, c[i]);
        }
}


void mainpage()
{
        glClearColor(0., 0., 0., 0.);
        glClear(GL_COLOR_BUFFER_BIT);
        char mp1[]="BALL GAME";
        char mp2[]="MANGALORE INSTITUTE OF TECHNOLOGY AND ENGINEERING";
        char mp3[]="BY:";
        char mp4[]=" Uttam (4MT17CS114)";
        char mp5[]="Sakshi(4MT17CS091)";
        char mp6[]="GUIDES:";
        char mp7[]=" Ms. SUNITHA N.V ";
        char mp8[]=" Mrs. JEEVITHA SAMPATH";
        char ctrl0[]="PRESS s TO START";
        output(mp2,-1, 0.8, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp1, -0.3,0.6, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp3, -1.2, 0.35, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp4,-1.2,0.2,1.0,1.0,1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp5, -1.2, 0.1, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp6, 0.3,0.35, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp7, 0.3, 0.2, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(mp8, 0.3, 0.1, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
        output(ctrl0, -0.5, -0.6, 1.0, 1.0, 1.0,GLUT_BITMAP_HELVETICA_18);
}

void endpage()
{
        glClearColor(0., 0., 0., 0.);
        glClear(GL_COLOR_BUFFER_BIT);
        string end_msg="Game Over",msg="Thank you for playing";
        output(end_msg,0,0.6,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24);
        output("Score :",-0.1,0.35,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24);
        output(co,0.3,0.35,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24);
        output(msg,-0.4,0.1,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24);

}

void draw_bricks()
{
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_QUADS);
        for(int a = 0; a < lc[level_flag][0]; a++)
        {
                for(int b = 0; b < lc[level_flag][1]; b++)
                {
                        if(show[b][a] == 1)
                        {
                                glVertex2f(x_brick[b][a],y_brick[b][a]);
                                glVertex2f(x_brick[b][a],y_brick[b][a] - 0.10);
                                glVertex2f(x_brick[b][a]+0.2,y_brick[b][a] - 0.10);
                                glVertex2f(x_brick[b][a]+0.2,y_brick[b][a]);
                        }
                }
        }
        glEnd();
}

void ball_draw()
{
    
        if(launch_flag==0)
        {
                x_pos=paddle_x;
                y_pos=-0.75;
        }
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x_pos,y_pos);
        for (float angle = 0; angle < (10); angle+=0.01)
        {
                glVertex2f((x_pos + sin(angle) * RADIUS), (y_pos + (cos(angle)) * RADIUS));
        }
        glEnd();
}

bool brick_hit()
{
        bool hit = false;
        int flag = 1;
        int temp_flag=0,i,j;
        int v[1][2];
        v[0][0]=lc[level_flag][0];
        v[0][1]=lc[level_flag][1];
        for(int a = 0; a < v[0][0]; a++)
        {
                for(int b =0; b < v[0][1]; b++)
                {
                        if(x_pos >= x_brick[b][a] && x_pos <= x_brick[b][a] + 0.2)
                        {
                                if(y_pos <= y_brick[b][a] && y_pos >= y_brick[b][a] - 0.1)
                                {
                                        if(show[b][a] == 1)
                                        {
                                                show[b][a] = 0;
                                                flag = 0;
                                                hit = true;
                                                score++;
                                                co=to_string(score);
                                                break;
                                        }
                                }
                        }
                }
                for(i=0; i<v[0][0]; i++)
                {
                        for(j =0; j < v[0][1]; j++)
                        {
                                if(show[j][i]==1)
                                {
                                        temp_flag=1;
                                }
                        }
                }
                if(temp_flag==0 && start<level_flag)
                {sudo 
                        start++;
                }
                if(start==level_flag)
                {
                        level_flag+=1;
                        launch_flag=0;
                        if(level_flag<3)
                                set_xy();

                }
                if(level_flag>2)
                        flags=2;
                // printf("%d\t%d\n",start,level_flag );
                temp_flag=0;
                if(flag == 0)
                        break;
        }
        return hit;
}

bool crashed()
{
        if(y_pos < paddle_y - 0.05)
        {
                launch_flag=0;
                if(cheat==1)
                {
                        level_flag=0;
                        flags=2;
                }
                return true;
        }

        return false;
}

void paddle_hit()
{
        phit_corner = false;
        phit_center = false;
        if(x_pos <= paddle_x + 0.13 && x_pos >= paddle_x - 0.13)
        {
                if(y_pos <= paddle_y)
                {
                        phit_center = true;
                }
        }
        else if( (x_pos >= paddle_x + 0.13 && x_pos <= paddle_x + 0.2) ||
                 (x_pos <= paddle_x - 0.13 && x_pos >= paddle_x - 0.2))
        {
                if(y_pos <= paddle_y)
                {
                        phit_corner = true;
                }
        }
}

void paddle_move(float dT)
{

        if(paddle_x < RATIO && paddle_x > -RATIO)
                paddle_x += paddle_speed * PaddleSpeedFactor * dT;

        if( paddle_x > 0.95) {
                paddle_x = 0.95;
                paddle_speed = 0.;
        }

        if( paddle_x < -0.95) {
                paddle_x = -0.95;
                paddle_speed = 0.;
        }

        paddle_speed *= (1. - 0.05);
        if( fabs(paddle_speed) < 0.01 )
                paddle_speed = 0.;
}

void ball_move(float dT)
{
        x_pos += speed_x * dT;
        y_pos += speed_y * dT;

        if( brick_hit() ) {
                speed_y *= -1;
        }

        if( x_pos >= (RATIO-RADIUS) || x_pos <= (-RATIO+RADIUS ) )
        {
                speed_x *= -1;
        }

        if( y_pos >= (1.-RADIUS) )
        {
                speed_y = -1;
        }

        paddle_hit();
        if(phit_center)
        {
                speed_y = 1;
        }
        if(phit_corner)
        {
                speed_x *= -1;
                speed_y = 1;
        }
}

void paddle_draw()
{
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);
        glVertex2f(paddle_x - 0.2, paddle_y);
        glVertex2f(paddle_x + 0.2, paddle_y);
        glVertex2f(paddle_x + 0.2, paddle_y - 0.05);
        glVertex2f(paddle_x - 0.2, paddle_y - 0.05);
        glEnd();
}

void step_game()
{
        if(flags==1)
        {
                paddle_move(T_last_frame);
                ball_move(T_last_frame);

                if(crashed())
                {
                        speed_x = 0;
                        speed_y = 0;
                        x_pos = 0;
                        y_pos = -0.7;
                        paddle_speed = 0;
                        paddle_x = 0;
                }

                // glutPostRedisplay();
        }
}

void launch_ball()
{
        speed_y = 1.;
        speed_x = 1.;
        launch_flag=1;
}

void user_input(unsigned char key, int x, int y)
{
        if (key=='s')
                flags=1;
        else if(key == 13 && flags==1)
                launch_ball();
}

void ArrowKeys(int key, int x, int y)
{
        if(key==GLUT_KEY_LEFT)
                paddle_speed = -1.;

        if(key==GLUT_KEY_RIGHT)
                paddle_speed = +1.;
}

void set_xy()
{
        float ac=0;
        int i;
        for(int a = 0; a < lc[level_flag][1]; a++)
        {
                for(int b = 0; b < lc[level_flag][0]; b++)
                {
                        show[a][b] = 1;
                }
        }
        int c = 0;
        for(i=0; i<=lc[level_flag][0]/2; i++)
                ac-=0.17;
        for(; c <= 15; ac+=0.21)
        {

                for(int b = 0; b <=lc[level_flag][1]; b++)
                {
                        x_brick[b][c] = ac;

                }
                c++;
        }
        int d = 0;
        for(float s = 0.99; d <= 10; s-=0.11)
        {
                for(int r = 0; r < lc[level_flag][0]; r++)
                {
                        y_brick[d][r] = s;
                }
                d++;
        }
}

void display()
{
        const int win_width  = glutGet(GLUT_WINDOW_WIDTH);
        const int win_height = glutGet(GLUT_WINDOW_HEIGHT);
        const float win_aspect = (float)win_width / (float)win_height;

        glViewport(0, 0, win_width, win_height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(win_aspect > RATIO) {
                glOrtho(-win_aspect, win_aspect, -1., 1., -1., 1.);
        } else {
                glOrtho(-RATIO, RATIO, -RATIO/win_aspect, RATIO/win_aspect, -1., 1.);
        }

        glMatrixMode(GL_MODELVIEW);

        glClearColor(0., 0., 1., 1);
        glClear(GL_COLOR_BUFFER_BIT);
        if(flags==0)
                mainpage();

        if (flags==1 )
        {
                glBegin(GL_QUADS);
                glColor3f(1,1,1);
                glVertex2f(-RATIO, -1);
                glVertex2f(RATIO, -1);
                glVertex2f(RATIO, 1);
                glVertex2f(-RATIO, 1);
                glEnd();

                draw_bricks();
                paddle_draw();
                info="Level"+to_string(level_flag);
                output(info,0,0,0,0,0,GLUT_BITMAP_TIMES_ROMAN_24);
                output(co, 1.1, 0.9, 0, 0, 0,GLUT_BITMAP_TIMES_ROMAN_24);
                ball_draw();
        }

        if(flags==2)
        {
                endpage();
        }
        glutSwapBuffers();
        glutPostRedisplay();
        
        T_last_frame = 1./60.;
}

void menu(int id)
{
        switch (id) {
        case 1: cheat=0;
                break;
        case 2: cheat=1;
                break;
        case 3: exit(0);
        }
        printf("%d\n",cheat );
        // glutPostRedisplay();
}

int main(int argc, char **argv)
{
        set_xy();

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

        glutInitWindowPosition(0,0);
        glutInitWindowSize(800, 600);

        glutCreateWindow("C_G project");
        glutDisplayFunc(display);

        glutKeyboardFunc(user_input);
        glutSpecialFunc(ArrowKeys);
        glutIdleFunc(step_game);
        glutCreateMenu(menu);
        glutAddMenuEntry("Easy", 1);
        glutAddMenuEntry("Hard", 2);
        glutAddMenuEntry("Quit", 3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
        glutMainLoop();

        glutMainLoop();

        return 0;
}
