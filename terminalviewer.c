#include "terminalviewer.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

const char fullShades[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
const char abbreviatedShades[] = " .:-=+*#%@";
char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
float zbuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

int main(int argc, char *argv[]) {
	screen[0][0] = '@';
	screen[24][49] = '@';
	newCircle(12, 24, 50, 10);
	output();
}

void output() {
	for (int r = 0; r < SCREEN_HEIGHT; r++) {
		for (int c = 0; c < SCREEN_WIDTH; c++) {
			/*zbuffer[r][c] == 0 ? printf(" ") : printf("%c", screen[r][c]);*/
			printf("%c", screen[r][c]);
		}
		if (r != SCREEN_HEIGHT - 1) {
			printf("\n");
		}
	}
}

// draws circle with given radius and center x, y, z coords
void newCircle(float x, float y, float z, float radius) {
	for (int theta = 0; theta < 2 * PI; theta+=THETASPACING) {
		int xn = radius*cos(theta) + x;
		int yn = radius*sin(theta) + y;
		// render: calculate x', y'
		int xp = (int) ((K1*xn)/z);
		int yp = (int) ((K1*yn)/z);
		screen[xp][yp] = '@';
	}
}

void newCircleVertex(Vertex center, float radius) {
	newCircle(center.x, center.y, center.z, radius);
}