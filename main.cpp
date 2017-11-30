//
//  main.cpp
//  project2
//
//  Created by Jamil Jalal on 10/12/17.
//  Copyright © 2017 Jamil Jalal. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>


GLint vert[100][2];
GLint points[100][2];
GLint vect[100][2];
GLdouble magn[100];

int width=400,height=600,n=0,s=0,k=0,t=0, type = GL_LINE_STRIP,v;double pi=3.14;
bool antialiasing=false, flag=true, polygon=false,color=false;
void changeColor(bool color);
int point(int,int);

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(n==1 && (type==GL_LINE_STRIP || type==GL_LINE_LOOP)){
        glBegin(GL_POINTS);
        glVertex2iv(vert[0]);
        glEnd();
    }
    glBegin(type);
    glColor3f(1, 1, 0);
    for(int i=0;i<n;i++){
        glVertex2iv(vert[i]);
    }
    glEnd();
    if(polygon){
        glBegin(GL_POINTS);
        for(int i=0;i<t;i++){
            glVertex2iv(points[i]);
            switch (point(points[k][0],points[k][1])) {
                case true:
                    glColor3f(0, 1, 0);
                    break;
                case false:
                    glColor3f(1, 0, 0);
                    
                default:
                    break;
            }
          /*  if(point(points[k][0],points[k][1])==true){
                glColor3f(0, 1, 0);
            }else{
            glColor3f(1, 0, 0);
            }*/
            
        }
        glEnd();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key,int x, int y){
    switch(key){
        case 'a': antialiasing = !antialiasing;
            if(antialiasing){
                glEnable(GL_BLEND);
                glEnable(GL_LINE_SMOOTH);
            }else{
                glDisable(GL_BLEND);
                glDisable(GL_LINE_SMOOTH);
            }
            break;
        case 'c': type=GL_LINE_LOOP; flag=false;polygon=true;break;
        case 'l': type=GL_LINE_STRIP; break;
        case 'r': n=0;t=0;type=GL_LINE_STRIP;flag=true;polygon=false;break;
        case 'v': type=GL_POINTS; break;
    }
    glutPostRedisplay();
}

int point(int x, int y){
    double theta=0;
    double magnitude=0;
    double dotProd=0;
    double a=0;
    double b=0;
    double c=0;
    double d=0;
    double e=0;
    for(int i=0;i<=v;i++){
        d=vert[i][0];e=vert[i][1];
        vect[i][0]=vert[i][0]-x;
        vect[i][1]=vert[i][1]-y;
        a=(vert[i][0]-x);
        b=(vert[i][1]-y);
        a=pow(a,2);
        b=pow(b,2);
        c=sqrt(a+b);
        magn[i]=c;
    }
    vect[v+1][0]=vect[0][0];
    vect[v+1][1]=vect[0][1];
    magn[v+1]=magn[0];
    for(int i=0;i<=v;i++){
        dotProd=(vect[i][0]*vect[i+1][0])+(vect[i][1]*vect[i+1][1]);
        magnitude=magn[i]*magn[i+1];
        theta += acos((dotProd/magnitude));
    }
    
    if(theta>=2*pi){
        return true;
    }
    else{
        return false;
    }
}

void changeColor(bool color){
    if(color==true){
        glColor3f(0, 1, 0);
    }else{
        glColor3f(1, 0, 0);
    }
}

void mouse(int button, int state, int x, int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            changeColor(color);
            if(state ==GLUT_DOWN){
                if(flag){
                    v=n++;
                    vert[v][0]=x;
                    vert[v][1]=height-1-y;
                    //rubberbanding=true;
                    glutPostRedisplay();
                }
                if(polygon){
                    color=false;
                    k=t++;
                    points[k][0]=x;
                    points[k][1]=height-1-y;
                    glutPostRedisplay();
                }
            }else
                break;
        case GLUT_RIGHT_BUTTON:
            
            break;
    }
}

int main(int argc, char** argv) {
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("project3");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width,0,height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    
}
