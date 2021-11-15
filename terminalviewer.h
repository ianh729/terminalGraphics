#ifndef TERMINALVIEWER_H
#define TERMINALVIEWER_H

#define X_BOUND (25) // max and min value of x and y
#define Y_BOUND (13)
#define SCREEN_WIDTH (2*X_BOUND+1)
#define SCREEN_HEIGHT (2*Y_BOUND+1) // +1 to make pixel (0,0) symmetrical

#define K1 (25)

#define PI (3.14159265)
#define THETASPACING (0.1)

// vertex data type
typedef struct vertices {
	float x;
	float y;
	float z;
} Vertex;

void screenSet(int x, int y, char c);
void output(void);
void render(int xp, int yp, float z);
void newCircle(float x, float y, float z, float radius);
void newCircleVertex(Vertex center, float radius);

#endif