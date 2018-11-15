#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#define RADIUS 0.5

class Sphere : public Shape {
public:
	Sphere() {};
	~Sphere() {};

	void draw() {
		glPushMatrix();
		drawBody();
		glPopMatrix();
	};

	void drawNormal() {
		glPushMatrix();
		drawBodyNormal();
		glPopMatrix();
	};

	double Intersect(Point eyePointP, Vector rayV, Matrix transformMatrix) {
		Matrix inverseTransform = invert(transformMatrix);
		Point eyePoint = inverseTransform * eyePointP;
		Vector ray = inverseTransform * rayV;

		double t = MIN_ISECT_DISTANCE;
		double a = ray[0] * ray[0] + ray[1] * ray[1] + ray[2] * ray[2];
		double b = 2 * (ray[0] * eyePoint[0] + ray[1] * eyePoint[1] + ray[2] * eyePoint[2]);
		double c = eyePoint[0] * eyePoint[0] + eyePoint[1] * eyePoint[1] + eyePoint[2] * eyePoint[2] - RADIUS * RADIUS;

		double det = b*b - 4 * a*c;
		if (det < 0) {
			return -1;
		}

		double t1 = (-b - sqrt(det)) / (2 * a);
		double t2 = (-b + sqrt(det)) / (2 * a);

		if ((t1 > 0) && (t2 > 0))
			t1 < t2 ? (t = t1) : (t = t2);
		else if (t1 < 0)
			t = t2;
		else if (t2 < 0)
			t = t1;
		else
			return -1;

		return t;
	}

	Vector findIsectNormal(Point eyePoint, Vector ray, double dist) {
		Point tmpP = eyePoint + dist * ray;
		Vector normalVector(tmpP[0], tmpP[1], tmpP[2]);
		return normalVector;
	}

private:
	void drawBody() {
		float radius = 0.5;
		float angle = 0;
		float angleH = -PI/(float)2.0;

		float angle_delta = 2.0 * PI / (float)m_segmentsX;
		float angleH_delta = PI / (float)m_segmentsY;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsY; i++) {
			angle = 0;
			for (int j = 0; j < m_segmentsX; j++) {
				float x = radius * cos(angleH) * cos(angle);
				float z = radius * cos(angleH) * sin(angle);
				float y = radius * sin(angleH);

				float newx = radius * cos(angleH) * cos(angle + angle_delta);
				float newz = radius * cos(angleH) * sin(angle + angle_delta);
				float newy = radius * sin(angleH);

				float x_next = radius * cos(angleH + angleH_delta) * cos(angle);
				float z_next = radius * cos(angleH + angleH_delta) * sin(angle);
				float y_next = radius * sin(angleH + angleH_delta);

				float newx_next = radius * cos(angleH + angleH_delta) * cos(angle + angle_delta);
				float newz_next = radius * cos(angleH + angleH_delta) * sin(angle + angle_delta);
				float newy_next = radius * sin(angleH + angleH_delta);

				glNormal3f(x, y, z);
				glVertex3f(x, y, z);
				glNormal3f(newx, newy, newz);
				glVertex3f(newx, newy, newz);
				glNormal3f(newx_next, newy_next, newz_next);
				glVertex3f(newx_next, newy_next, newz_next);

				glNormal3f(newx_next, newy_next, newz_next);
				glVertex3f(newx_next, newy_next, newz_next);
				glNormal3f(x_next, y_next, z_next);
				glVertex3f(x_next, y_next, z_next);
				glNormal3f(x, y, z);
				glVertex3f(x, y, z);

				angle = angle + angle_delta;
			}
			angleH = angleH + angleH_delta;
		}
		glEnd();
	};


	void drawBodyNormal() {
		float radius = 0.5;
		float angle = 0;
		float angleH = -PI/(float)2.0;

		float angle_delta = 2.0 * PI / (float)m_segmentsX;
		float angleH_delta = PI / (float)m_segmentsY;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsY; i++) {
			angle = 0;
			for (int j = 0; j < m_segmentsX; j++) {
				float x = radius * cos(angleH) * cos(angle);
				float z = radius * cos(angleH) * sin(angle);
				float y = radius * sin(angleH);

				float newx = radius * cos(angleH) * cos(angle + angle_delta);
				float newz = radius * cos(angleH) * sin(angle + angle_delta);
				float newy = radius * sin(angleH);

				float x_next = radius * cos(angleH + angleH_delta) * cos(angle);
				float z_next = radius * cos(angleH + angleH_delta) * sin(angle);
				float y_next = radius * sin(angleH + angleH_delta);

				float newx_next = radius * cos(angleH + angleH_delta) * cos(angle + angle_delta);
				float newz_next = radius * cos(angleH + angleH_delta) * sin(angle + angle_delta);
				float newy_next = radius * sin(angleH + angleH_delta);

				glVertex3f(x, y, z); glVertex3f(1.1*x, 1.1*y, 1.1*z);
				glVertex3f(newx, newy, newz); glVertex3f(1.1*newx, 1.1*newy, 1.1*newz);
				glVertex3f(newx_next, newy_next, newz_next); glVertex3f(1.1*newx_next, 1.1*newy_next, 1.1*newz_next);

				glVertex3f(newx_next, newy_next, newz_next); glVertex3f(1.1*newx_next, 1.1*newy_next, 1.1*newz_next);
				glVertex3f(x_next, y_next, z_next); glVertex3f(1.1*x_next, 1.1*y_next, 1.1*z_next);
				glVertex3f(x, y, z); glVertex3f(1.1*x, 1.1*y, 1.1*z);

				angle = angle + angle_delta;
			}
			angleH = angleH + angleH_delta;
		}
		glEnd();
	};
};

#endif