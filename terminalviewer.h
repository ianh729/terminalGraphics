#ifndef TERMINALVIEWER_H
#define TERMINALVIEWER_H

#define SCREEN_HEIGHT (25)
#define SCREEN_WIDTH (50)

#define K1 (25)

#define PI (3.14159265)
#define THETASPACING (PI/2)

// vertex data type
typedef struct vertices {
	float x;
	float y;
	float z;
} Vertex;

void output(void);
void newCircle(float x, float y, float z, float radius);
void newCircleVertex(Vertex center, float radius);

#endif