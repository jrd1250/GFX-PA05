#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

#define RADIUS 0.5

class Cylinder : public Shape {
public:
	Cylinder() {};
	~Cylinder() {};

	void draw() {
		glPushMatrix();
		glTranslatef(0, 0.5, 0);
		drawCap();
		glPopMatrix();

		drawBody();

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		drawCap();
		glPopMatrix();
	};

	void drawNormal() {
		//glPushMatrix();
		//glTranslatef(0, 0.5, 0);
		//drawCap();
		//glPopMatrix();

		drawBodyNormal();

		//glPushMatrix();
		//glTranslatef(0, -0.5, 0);
		//drawCap();
		//glPopMatrix();
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double t = MIN_ISECT_DISTANCE;
		double a = ray[0] * ray[0] + ray[2] * ray[2];
		double b = 2 * (eyePoint[0] * ray[0] + eyePoint[2] * ray[2]);
		double c = eyePoint[0] * eyePoint[0] + eyePoint[2] * eyePoint[2] - RADIUS * RADIUS;
		//Point isect;

		double det = b*b - 4 * a*c;
		if (det < 0) {
			t = -1;
		}
		else {
			double t1 = (-b - sqrt(det)) / (2 * a);
			double t2 = (-b + sqrt(det)) / (2 * a);

			if (t1 > 0) {
				double isectY1 = eyePoint[1] + t1 * ray[1];
				if (!((isectY1 > -0.5) && (isectY1 < 0.5))) {
					t1 = -1;
				}
			}
			if (t2 > 0) {
				double isectY2 = eyePoint[1] + t2 * ray[1];
				if (!((isectY2 > -0.5) && (isectY2 < 0.5))) {
					t2 = -1;
				}
			}

			if ((t1 > 0) && (t2 > 0))
				t1 < t2 ? (t = t1) : (t = t2);
			else if (t1 < 0)
				t = t2;
			else if (t2 < 0)
				t = t1;
			else
				t = -1;
		}

		if (eyePoint[1] * ray[1] < 0) {
			double t1 = (-RADIUS - eyePoint[1]) / ray[1];
			Point tmpP = eyePoint + t1 * ray;
			if ((tmpP[0] * tmpP[0] + tmpP[2] * tmpP[2]) < RADIUS * RADIUS) {
				if (((t1 > 0) && (t < 0)) || ((t1 > 0) && (t1 < t))) {
					t = t1;
				}
			}
			double t2 = (RADIUS - eyePoint[1]) / ray[1];
			tmpP = eyePoint + t2 * ray;
			if ((tmpP[0] * tmpP[0] + tmpP[2] * tmpP[2]) < RADIUS * RADIUS) {
				if (((t2 > 0) && (t < 0)) || ((t2 > 0) && (t2 < t))) {
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

		if (IN_RANGE(normalVector[1], 0.5)) {
			normalVector[0] = 0; normalVector[1] = 1; normalVector[2] = 0;
		}
		else if (IN_RANGE(normalVector[1], -0.5)) {
			normalVector[0] = 0; normalVector[1] = -1; normalVector[2] = 0;
		}
		else {
			normalVector[1] = 0;
		}

		return normalVector;
	}


private:
	void drawBody() {
		float x = 0.5;
		float z = 0.0;
		float y = -0.5;
		float angle = 2 * PI / (float)m_segmentsX;
		float height = 1.0 / (float)m_segmentsY;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsY; i++) {
			for (int j = 0; j < m_segmentsX; j++) {
				float newx = x*cos(angle) - z*sin(angle);
				float newz = x*sin(angle) + z*cos(angle);

				normalizeNormal(x, 0, z);
				glVertex3f(x, y, z); 
				normalizeNormal(newx, 0, newz);
				glVertex3f(newx, y, newz);
				normalizeNormal(newx, 0, newz);
				glVertex3f(newx, y + height, newz);

				normalizeNormal(newx, 0, newz);
				glVertex3f(newx, y + height, newz);
				normalizeNormal(x, 0, z);
				glVertex3f(x, y + height, z);
				normalizeNormal(x, 0, z);
				glVertex3f(x, y, z);

				x = newx;
				z = newz;
			}
			y = y + height;
		}
		glEnd();
	};

	void drawCap() {
		float x = 0.5;
		float z = 0.0;
		float angle = 2*PI / (float)m_segmentsX;
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsX; i++) {
			float newx = x*cos(angle) - z*sin(angle);
			float newz = x*sin(angle) + z*cos(angle);

			glNormal3f(0, -1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(x, 0, z);
			glVertex3f(newx, 0, newz);

			x = newx;
			z = newz;
		}
		glEnd();
	}

	void drawBodyNormal() {
		float x = 0.5;
		float z = 0.0;
		float y = -0.5;
		float angle = 2 * PI / (float)m_segmentsX;
		float height = 1.0 / (float)m_segmentsY;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsY; i++) {
			for (int j = 0; j < m_segmentsX; j++) {
				float newx = x*cos(angle) - z*sin(angle);
				float newz = x*sin(angle) + z*cos(angle);

				glVertex3f(x, y, z); glVertex3f(1.1*x, y, 1.1*z);
				glVertex3f(newx, y, newz); glVertex3f(1.1*newx, y, 1.1*newz); 
				glVertex3f(newx, y + height, newz); glVertex3f(1.1*newx, (y + height), 1.1*newz);

				glVertex3f(newx, y + height, newz); glVertex3f(1.1*newx, (y + height), 1.1*newz);
				glVertex3f(x, y + height, z); glVertex3f(1.1*x, (y + height), 1.1*z);
				glVertex3f(x, y, z); glVertex3f(1.1*x, y, 1.1*z);

				x = newx;
				z = newz;
			}
			y = y + height;
		}
		glEnd();
	};};

#endif