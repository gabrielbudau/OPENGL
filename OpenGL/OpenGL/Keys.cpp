#include "Keys.h"

bool* keyStates = new bool[256];
bool* keySpecialStates = new bool[256];

void keyOperations(void) {
	if (keyStates['a']) {
		// If the 'a' key has been pressed
		// Perform 'a' key operations
	}
}
void keySpecialOperations(void){
	if (keySpecialStates[GLUT_KEY_LEFT]) {
		// If the left arrow key has been pressed
		// Perform left arrow key operations
	}
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
	switch (key)
	{
	default:
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
	switch (key)
	{
	default:
		break;
	}
}

void keySpecial(int key, int x, int y) {
	keySpecialStates[key] = true;
}

void keySpecialUp(int key, int x, int y) {
	keySpecialStates[key] = false;
}