#include <stdio.h>
#include <math.h>
#include <string.h>

#define X_BOUND (80) // max and min value of x and y
#define Y_BOUND (25)
#define SCREEN_WIDTH (2*X_BOUND+1)
#define SCREEN_HEIGHT (2*Y_BOUND+1) // +1 to make pixel (0,0) symmetrical

#define K1 (25)
#define NEARZ (5)
#define FARZ (500)

#define YZSLOPE ((float) (Y_BOUND + 1) / (float) K1) // top edge of frustum
#define XZSLOPE ((float) (X_BOUND + 1) / (float) K1) // right edge of frustum

#define THETASPACING (0.1)
#define PHISPACING (0.05)

#define PI (3.14159265)
#define SQUARED(x) (x*x)

// vertex data type
typedef struct Vector3 {
	float x;
	float y;
	float z;
} Vector3;

const char fullShades[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const char abbreviatedShades[] = " .:-=+*#%@";
char screen[SCREEN_WIDTH][SCREEN_HEIGHT];
float zbuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
Vector3 light;

void setScreen(int x, int y, char c);
void output(void);
void render(Vector3 *vertex, Vector3 *normal);
int inBounds(int xp, int yp);
float dot(Vector3 *v1, Vector3 *v2);
float norm(Vector3 *vect);
void normalize(Vector3 *vect);
int inFrustum(float x, float y, float z);
void newCircle(float x, float y, float z, float radius);
void newCircleVertex(Vector3 center, float radius);

int main(int argc, char *argv[]) {
	light = (Vector3) {.x = 0, .y = 0, .z = 1};
	normalize(&light);
	setScreen(-X_BOUND,-Y_BOUND,'$');
	setScreen(X_BOUND,-Y_BOUND,'$');
	setScreen(-X_BOUND,Y_BOUND,'$');
	setScreen(X_BOUND,Y_BOUND,'$');
	newCircle(0, 0, 100, 90);
	output();
}

void setScreen(int x, int y, char c) {
	screen[x+X_BOUND][y+Y_BOUND] = c;
}

float getZbuffer(int x, int y) {
	return zbuffer[x+X_BOUND][y+Y_BOUND];
}

void setZbuffer(int x, int y, float val) {
	zbuffer[x+X_BOUND][y+Y_BOUND] = val;
}

void output() {
	for (int r = SCREEN_HEIGHT - 1; r >= 0; r--) {
		for (int c = 0; c < SCREEN_WIDTH; c++) {
			printf("%c", screen[c][r]);
		}
		if (r) {
			printf("\n");
		} 
	}
}

void render(Vector3 *vertex, Vector3 *normal) {
	normalize(normal);
	float x=vertex->x, y=vertex->y, z=vertex->z;
	(void) normal;
	// check if in viewing frustum
	if (inFrustum(x,y,z)) {
		int xp = (int) ((K1*x)/z);
		int yp = (int) ((K1*y)/z);
		float bufferval = 1/z;
		if (bufferval > getZbuffer(x,y)) {
			setZbuffer(xp,yp,bufferval);

			float luminance = dot(&light, normal);
			if (luminance > 0) {
				char point = abbreviatedShades[(int) (luminance * strlen(abbreviatedShades))];
				setScreen(xp,yp,point);
			}
			// setScreen(xp,yp,'@');
		}
	}
}

float dot(Vector3 *v1, Vector3 *v2) {
	return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

float norm(Vector3 *vect) {
	return sqrt(SQUARED(vect->x) + SQUARED(vect->y) + SQUARED(vect->z));
}

void normalize(Vector3 *vect) {
	float normal = norm(vect);
	vect->x /= normal;
	vect->y /= normal;
	vect->z /= normal;
}

int inFrustum(float x, float y, float z) {
	return (fabs(y / z) <= YZSLOPE && fabs(x / z) <= XZSLOPE) && (z <= FARZ && z >= NEARZ);
}

// draws circle with given radius and center x, y, z coords
void newCircle(float x, float y, float z, float radius) {
	for (float phi = 0.0; phi < PI; phi+=THETASPACING) {
		float zn = radius*cos(phi);
		float incRadius = radius*sin(phi); // radius that gets incremented
		for (float theta = 0.0; theta < 2 * PI; theta+=PHISPACING) {
			float xn = incRadius*cos(theta);
			float yn = incRadius*sin(theta);
			Vector3 vertex = {.x = xn + x, .y = yn + y, .z = zn + z};
			Vector3 normal = {.x = xn, .y = yn, .z = zn};
			render(&vertex, &normal);
		}
	}
}

void newCircleVertex(Vector3 center, float radius) {
	newCircle(center.x, center.y, center.z, radius);
}

int inBounds(int xp, int yp) {
	return ((xp <= X_BOUND) && xp >= (-X_BOUND)) && ((yp <= Y_BOUND) && (yp >= -Y_BOUND));
}