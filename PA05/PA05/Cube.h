#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

#define SIDELENGTH 0.5

class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	void draw() {
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, 0.5);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef(90, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, -0.5);
			glRotatef(180, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.5, 0.0, 0.0);
			glRotatef(270, 0, 1, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0.5, 0.0);
			glRotatef(270, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(90, 1, 0, 0);
			drawCubeFace();
		}
		glPopMatrix();
	};


	void drawNormal() {
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, 0.5);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef(90, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, 0.0, -0.5);
			glRotatef(180, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(-0.5, 0.0, 0.0);
			glRotatef(270, 0, 1, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0, 0.5, 0.0);
			glRotatef(270, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
		glPushMatrix(); {
			glTranslatef(0.0, -0.5, 0.0);
			glRotatef(90, 1, 0, 0);
			drawCubeFaceNormal();
		}
		glPopMatrix();
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double t = MIN_ISECT_DISTANCE;
		Point tmpP;//isect;

		if (eyePoint[1] * ray[1] < 0) {
			double t1 = (-SIDELENGTH - eyePoint[1]) / ray[1];
			tmpP = eyePoint + t1 * ray;
			if ((tmpP[0] >= -SIDELENGTH) && (tmpP[0] <= SIDELENGTH) && (tmpP[2] >= -SIDELENGTH) && (tmpP[2] <= SIDELENGTH)) {
				if ((t1 > 0) && (t1 < t)) {
					t = t1;
				}
			}

			double t2 = (SIDELENGTH - eyePoint[1]) / ray[1];
			tmpP = eyePoint + t2 * ray;
			if ((tmpP[0] >= -SIDELENGTH) && (tmpP[0] <= SIDELENGTH) && (tmpP[2] >= -SIDELENGTH) && (tmpP[2] <= SIDELENGTH)) {
				if ((t2 > 0) && (t2 < t)) {
					t = t2;
				}
			}
		}

		if (eyePoint[0] * ray[0] < 0) {
			double t1 = (-SIDELENGTH - eyePoint[0]) / ray[0];
			tmpP = eyePoint + t1 * ray;
			if ((tmpP[1] >= -SIDELENGTH) && (tmpP[1] <= SIDELENGTH) && (tmpP[2] >= -SIDELENGTH) && (tmpP[2] <= SIDELENGTH)) {
				if ((t1 > 0) && (t1 < t)) {
					t = t1;
				}
			}

			double t2 = (SIDELENGTH - eyePoint[0]) / ray[0];
			tmpP = eyePoint + t2 * ray;
			if ((tmpP[1] >= -SIDELENGTH) && (tmpP[1] <= SIDELENGTH) && (tmpP[2] >= -SIDELENGTH) && (tmpP[2] <= SIDELENGTH)) {
				if ((t2 > 0) && (t2 < t)) {
					t = t2;
				}
			}
		}

		if (eyePoint[2] * ray[2] < 0) {
			double t1 = (-SIDELENGTH - eyePoint[2]) / ray[2];
			tmpP = eyePoint + t1 * ray;
			if ((tmpP[1] >= -SIDELENGTH) && (tmpP[1] <= SIDELENGTH) && (tmpP[0] >= -SIDELENGTH) && (tmpP[0] <= SIDELENGTH)) {
				if ((t1 > 0) && (t1 < t)) {
					t = t1;
				}
			}
			double t2 = (SIDELENGTH - eyePoint[2]) / ray[2];
			tmpP = eyePoint + t2 * ray;
			if ((tmpP[1] >= -SIDELENGTH) && (tmpP[1] <= SIDELENGTH) && (tmpP[0] >= -SIDELENGTH) && (tmpP[0] <= SIDELENGTH)) {
				if ((t2 > 0) && (t2 < t)) {
					t = t2;
				}
			}
		}

		//isect = eyePoint + t * ray;
		if (IN_RANGE(t, MIN_ISECT_DISTANCE))
			return -1;
		else
			return t;
	}

	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
		Point tmpP = eyePoint + (dist * ray);
		Vector normalVector(tmpP[0], tmpP[1], tmpP[2]);

		if (IN_RANGE(normalVector[0], 0.5)) {
			normalVector[0] = 1; normalVector[1] = 0; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[0], -0.5)) {
			normalVector[0] = -1; normalVector[1] = 0; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[1], 0.5)) {
			normalVector[0] = 0; normalVector[1] = 1; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[1], -0.5)) {
			normalVector[0] = 0; normalVector[1] = -1; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[2], 0.5)) {
			normalVector[0] = 0; normalVector[1] = 0; normalVector[2] = 1;
		}
		else if (IN_RANGE(normalVector[2], -0.5)) {
			normalVector[0] = 0; normalVector[1] = 0; normalVector[2] = -1;
		}
		else {
			//printf ("something is wrong here in cube normalVector\n");
			//printf ("%lf, %lf, %lf\n", x_cord, y_cord, z_cord);
			//printf ("t: %lf\n", t);
		}

		return normalVector;
	}

private:
	void drawCubeFace() {
		float width = 1.0f / (float)m_segmentsX;
		float height = 1.0f / (float)m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			float xcoord = startX + (i*width);
			for (int j = 0; j < m_segmentsY; j++) {
				float ycoord = startY + (j*height);
				glNormal3f(0, 0, 1);
				glVertex3d(xcoord, ycoord, 0);
				glVertex3d(xcoord + width, ycoord, 0);
				glVertex3d(xcoord + width, ycoord + height, 0);

				glNormal3f(0, 0, 1);
				glVertex3d(xcoord + width, ycoord + height, 0);
				glVertex3d(xcoord, ycoord + height, 0);
				glVertex3d(xcoord, ycoord, 0);
			}
		}
		glEnd();
	}

	void drawCubeFaceNormal() {
		float width = 1.0f / (float)m_segmentsX;
		float height = 1.0f / (float)m_segmentsY;
		float startX = -0.5f;
		float startY = -0.5f;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsX; i++) {
			float xcoord = startX + (i*width);
			for (int j = 0; j < m_segmentsY; j++) {
				float ycoord = startY + (j*height);
				glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1); 
				glVertex3d(xcoord + width, ycoord, 0); glVertex3d(xcoord + width, ycoord, 0.1);
				glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);

				glVertex3d(xcoord + width, ycoord + height, 0); glVertex3d(xcoord + width, ycoord + height, 0.1);
				glVertex3d(xcoord, ycoord + height, 0); glVertex3d(xcoord, ycoord + height, 0.1); 
				glVertex3d(xcoord, ycoord, 0); glVertex3d(xcoord, ycoord, 0.1);
			}
		}
		glEnd();
	}
};

#endif