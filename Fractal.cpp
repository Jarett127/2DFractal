#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <math.h>
#include <iostream>
#include <dos.h>

using namespace sf;

//window size
const int WIN_X = 900;
const int WIN_Y = 900;

//initial branch position
const float BRANCH_X = (float)WIN_X / 2;
const float BRANCH_Y = 0;

//initial length of branch
const float LENGTH = 400;

//minimumn length of branch
const float MIN_LENGTH = 1;

//decrease factor for lines
const float DECREASE_FACT = 2.0f / 3;

//total degrees in triangle besides right angle
const int DEGREES = 90;

//color of branches
const Color color = Color::Cyan;

//delay time variables
const Time FREEZE_TIME = milliseconds(2000);
const Time DEFAULT_TIME = milliseconds(20);

//angle...serves as parameter in branch function...initialized value is starting value
int angle = 360;

//create window
RenderWindow window(VideoMode(WIN_X, WIN_Y), "Fractal One");

//declare drawBranch method
void drawBranch(float xPos, float yPos, float rot, float length);


int main() {

	//keep window open until otherwise noted
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			//close window if exit pressed
			if (event.type == Event::Closed) {
				window.close();
			}
		}	

		//display branch and update angle for animation
		while (angle >= 15) {
			window.clear();
			drawBranch(BRANCH_X, BRANCH_Y, DEGREES, LENGTH);
			window.display();
			angle--;
			if ((angle + 1) % 45 != 0)
				sleep(DEFAULT_TIME);
			else
				sleep(FREEZE_TIME);
		}
	}


	return 0;
}


//draws whole tree through recursive algorithim
void drawBranch(float xPos, float yPos, float rot, float length) {

	//make sure branch length is greater than min
	if (length < MIN_LENGTH) {
		return;
	}
	else {
		//decrease size of line for drawing
		float currentLength = length * DECREASE_FACT;

		//determine end point values
		float endX = xPos + currentLength * cos(rot * M_PI / 180.0);
		float endY = yPos + currentLength * sin(rot * M_PI / 180.0);

		//set verticies of lines
		Vertex line[] = {
			Vertex(Vector2f(xPos, yPos), color),
			Vertex(Vector2f(endX, endY), color)
		};

		//render lines
		window.draw(line, 2, Lines);

		//continue to draw branches going both directions
		drawBranch(endX, endY, rot - angle , currentLength);
		drawBranch(endX, endY, rot + angle, currentLength);
	}

}



