#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <ctype.h>
#include <time.h>
#include "header.h"



// initialize the values requried
void myinit() {
	// background
	glClearColor(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, BACKGROUND_A);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,SCREEN_X,0.0,SCREEN_Y);


// creates color of cube and outline color
	int i;
	for(i = 0; i < 15; i++) {
		queue[i].r = 0;
		queue[i].g = 0.25;
		queue[i].b = 0.75;
		queue[i].rl = 1;
		queue[i].gl = 0;
		queue[i].bl = 0;
	}

	float step = DIST/MAX;
	queue[0].x1 = OFFSET_X;
	queue[0].x2 = queue[0].x1+step;

	for(i = 1; i <= 15; i++) {
		queue[i].x1 = queue[i-1].x1+step;
		queue[i].x2 = queue[i].x1+step;
	}

}
//function to display details

void title()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	drawstring(200.0,450.0,"VIVEKANANDA INSTITUTE OF TECHNOLOGY",3);
	drawstring(200.0,448.0,"________________________________________",3); 
    drawstring(188.0,400.0,"COMPUTER GRAPHICS LAB WITH MINI PROJECT",5);
	drawstring(188.0,393.0,"-----------------------------------------",5);
    drawstring(275.0,350,"SINGLY LINKED LIST",0);
	drawstring(275.0,343,"-----------------",0);
    drawstring(150.0,300.0,"HARSHITHA H N",0);                                              
	drawstring(450.0,300.0,"JYOTHI NAYARI",0);
    drawstring(150.0,275.0,"1VK17CS018",0);                                                     
	drawstring(450.0,275.0,"1VK17CS022",0);
	drawstring(225.0,175.0,"GUIDED BY:   Mr.SURESH KUMAR S",5);
	drawstring(225.0,150.0,"                         Asst Prof of CSE",5);
	   
	drawstring(100.0,100.0,"",3);
    drawstring(225.0,100.0,"(Click Right Mouse Button For Options)",1);
    glFlush();
}


//display function ends here
//function to draw a square
void square(int x1, int y1, int x2, int y2) {
	glBegin(GL_POLYGON);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
	glEnd();
}





//function to draw the outline the square
void drawOutline(int x1, int y1, int x2, int y2) {
	int temp;
	if(x1 < x2) {
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if(y1 < y2) {
		temp = y1;
		y1 = y2;
		y2 = temp;
	}
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
	glEnd();
}





//function to draw a string to the output screen
void drawString(const char *str, double x=0, double y=0, double size=5.0) {
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(size,size,4.0);
	glColor3f(1, 0, 0);
	int itemCt = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	}
	glPopMatrix();
}






//5th function
//function to draw the queue arrow anywhere requried
void drawArrow(int x1, const char* s) {
	glBegin(GL_LINES);
		glVertex2f(x1, 3*SCREEN_Y/4);
		glVertex2f(x1, 3*SCREEN_Y/4-ARROW_LENGTH);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex2f(x1, 3*SCREEN_Y/4-ARROW_LENGTH);
		glVertex2f(x1-ARROW_LENGTH/4, 3*SCREEN_Y/4-ARROW_LENGTH+ARROW_LENGTH/4);
		glVertex2f(x1+ARROW_LENGTH/4, 3*SCREEN_Y/4-ARROW_LENGTH+ARROW_LENGTH/4);
	glEnd();
	if(strcmp(s, "BACK"))
		drawString(s, x1-ARROW_LENGTH/3, 3*SCREEN_Y/4+ARROW_LENGTH/2, 1.0/(2*FONT_RATIO));
	else
		drawString(s, x1-ARROW_LENGTH/3, 3*SCREEN_Y/4+ARROW_LENGTH/4, 1.0/(2*FONT_RATIO));
}
//6th function to display 
//function to display
void display_t()
{
	strcpy(displayString, enter_str);
	strcat(displayString, blinking);

	drawString(displayString, ENTER_POSITION_X, ENTER_POSITION_Y,1.0/(FONT_RATIO));
	drawArrow(queue[f].x1+OFFSET_X/2, "FRONT");
	drawArrow(queue[b].x1+OFFSET_X/2, "BACK");
	if(enqORdq == ENQUEUE)
		drawString("LAST OPERATION: ENQUEUE", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	else if(enqORdq == DEQUEUE1)
		drawString("LAST OPERATION: DEQUEUE ", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));
	else
		drawString("LAST OPERATION: NO OPERATION YET", OPERATION_POSITION_X, OPERATION_POSITION_Y+50, 1.0/(FONT_RATIO));

	//message
	if(message == EMPTY) {
		drawString("QUEUE EMPTY!", OPERATION_POSITION_X+80, OPERATION_POSITION_Y, 1.0/(FONT_RATIO));
		
	}
	else if(message == FULL) {
		drawString("QUEUE FULL!", OPERATION_POSITION_X+80, OPERATION_POSITION_Y, 1.0/(FONT_RATIO));
	}

	//instructions
	drawString("Instructions:", OPERATION_POSITION_X-280, OPERATION_POSITION_Y+60, 1.0/(1.5*FONT_RATIO));
	drawString("Press I or i to enqueue/Insert element", OPERATION_POSITION_X-280, OPERATION_POSITION_Y+40, 1.0/(2*FONT_RATIO));
	drawString("and F or f to dequeue/Delete element.", OPERATION_POSITION_X-280, OPERATION_POSITION_Y-20, 1.0/(2*FONT_RATIO));
	drawString("Press E or e to Exit.", OPERATION_POSITION_X-280, OPERATION_POSITION_Y-40, 1.0/(2*FONT_RATIO));
	glFlush();
}





//6th function
//function to display all things to the screen
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if(k==0)
	{
		title();
	}
	else
	{
		
	

	
	
	for(int i = 0; i < b; i++) {
		glColor3f(queue[i].r,queue[i].g,queue[i].b);
		square(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
		glColor3f(queue[i].rl,queue[i].gl,queue[i].bl);
		drawOutline(queue[i].x1, SCREEN_Y/2, queue[i].x2, SCREEN_Y/2+YD);
		if(queue[i].r != 1.0 || queue[i].b != 1.0 || queue[i].g != 1.0) {
			double ln = strlen(queue[i].num);
			double width = queue[i].x2-queue[i].x1;
			double step = width/(ln+1);
			double step_y = YD/4;
			drawString(queue[i].num, queue[i].x1+step, SCREEN_Y/2+step_y, 1.0/FONT_RATIO);
		}
	display_t();

	}
}




//7th function
//adding datavalue from the back end of the queue
void Enqueue(char *s) {
	int len = strlen(s);
	int i;
	if(b < MAX) {
		len = strlen(s);
		for(i = 0; i < len-1 && s[i] == '0'; i++);
		strcpy(queue[b].num, s+i);

		queue[f].r = 0;
		queue[f].g = 0.25;
		queue[f].b = 0.75;

		queue[f].rl = 1;
		queue[f].gl = 0;
		queue[f].bl = 0;

		b++;
		enqORdq = ENQUEUE;
		message = NO_MESSAGE;
	}
	if(b == MAX)
		message = FULL;
}













// removing datavalue form the queue
void Dequeue(void) {
	if(b <= 0 || b <= f) {
		message = EMPTY;
		return;
	}

	queue[f].r = BACKGROUND_R;
	queue[f].g = BACKGROUND_G;
	queue[f].b = BACKGROUND_B;

	queue[f].rl = BACKGROUND_R;
	queue[f].gl = BACKGROUND_G;
	queue[f].bl = BACKGROUND_B;

	f++;
	enqORdq = DEQUEUE1;

	if(b <= f) {
		message = EMPTY;
	}
	if(b >= MAX)
		message = FULL;
}







//11th function
//to check which is greater of two values
int max(int a, int b) {
	return a?(a>b):b;
}








//12th function
//funtion to get input from the user by keyboard
void mykey(unsigned char key, int x, int y) {

	int len = strlen(enter_str);
	if((key == 'F' || key == 'f') && (cnt_of_chars == 0))
		Dequeue();
   if((key=='E' || key == 'e')&& (cnt_of_chars == 0))
		exit(0);
	else if(isdigit(key) && strlen(enter_str) <= 28) {
		enter_str[len+1] = '\0';
		enter_str[len] = key;
		cnt_of_chars++;
	}
	else if(key == '\b' && len > start_of_num) {
		enter_str[len -1] = '\0';
		cnt_of_chars--;
	}
	else if(key=='i' || key=='I') {
		char newint[4];
		strncpy(newint, enter_str+start_of_num, 3);
		if(newint[0]) {
			Enqueue(newint);
			enter_str[start_of_num] = '\0';
		}
		cnt_of_chars = 0;
	}
	else if(key=='o' || key=='O'){
		char newint[4];
		strncpy(newint, enter_str+start_of_num, 3);
		if(newint[0]) {
			Enqueue(newint);
			enter_str[start_of_num] = '\0';
		}
		cnt_of_chars = 0;
	}
	glutPostRedisplay();
}







//main funtion 
int  main(int argc,char **argv) {
	char number[1000];
	int i, j, len;
	char c;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_X,SCREEN_Y);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Queue Simulation");
	glutDisplayFunc(title);
	glutKeyboardFunc(mykey);

	strcpy(enter_str, "Enter Element to Queue: ");
	start_of_num = strlen("Enter Element to Queue: ");
	jump:
	printf("\n\n\n");
	printf("------------------------------------\n");
	printf("Simulation of  Queue in OpenGL\n");
	printf("------------------------------------\n\n");
	printf("Enter the number of elements in the deQueue\n(Not greater than 15 and not lesser than 3):\n");
	scanf("%d", &MAX);

	while(MAX > 15 || MAX < 3) {
		printf("ERROR: Invalid value! \nEnter again: ");
		scanf("%d", &MAX);
	}
	printf("\n\nVALUE ACCEPTED! Program Running...\n");

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_X,SCREEN_Y);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Queue Simulation");
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);

	myinit();
	glutMainLoop();
	return 0;
}
