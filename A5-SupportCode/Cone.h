#ifndef COHE_H
#define CONE_H

#include "Shape.h"
#define RADIUS 0.5

#define NORMAL_Y 0.447213595499958f

class Cone : public Shape {
public:
	Cone() {};
	~Cone() {};

	void draw() {

		drawBody();

		glPushMatrix();
		glTranslatef(0, -0.5, 0);
		drawCap();
		glPopMatrix();
	};

	void drawNormal() {
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

		double radiusSqr = RADIUS*RADIUS;
		double a = ray[0] * ray[0] + ray[2] * ray[2] - (radiusSqr*(ray[1] * ray[1]));
		double b = 2 * eyePoint[0] * ray[0] + 2 * eyePoint[2] * ray[2] + radiusSqr*ray[1] - RADIUS*eyePoint[1] * ray[1];
		double c = eyePoint[0] * eyePoint[0] + eyePoint[2] * eyePoint[2] + radiusSqr*eyePoint[1] - radiusSqr*eyePoint[1] * eyePoint[1] - radiusSqr*radiusSqr;
		double t = MIN_ISECT_DISTANCE;
		//Point isect;

		double det = b*b - 4 * a*c;
		if (det < 0) {
			t = -1;
		}
		else {
			double t1 = (-b - sqrt(det)) / (2 * a);
			double t2 = (-b + sqrt(det)) / (2 * a);

			double isectY2 = eyePoint[1] + t2 * ray[1];

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
			if ((tmpP[0] * tmpP[0] + tmpP[2] * tmpP[2]) < radiusSqr) {
				if (((t1 > 0) && (t < 0)) || ((t1 > 0) && (t1 < t))) {
					t = t1;
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

		if (IN_RANGE(normalVector[1], -0.5)) {
			normalVector[0] = 0; normalVector[1] = -1; normalVector[2] = 0;
		}
		else if ((normalVector[0] == 0) && (normalVector[2] == 0)){
			normalVector[0] = 0; normalVector[1] = 1; normalVector[2] = 0;
		}
		else {
			normalVector[0] = 2 * normalVector[0];
			normalVector[1] = RADIUS * (RADIUS - normalVector[1]);
			normalVector[2] = 2 * normalVector[2];
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

		float radius = 0.5;
		float radius_delta = 0.5 / (float)m_segmentsY;

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_segmentsY; i++) {
			x = radius;
			z = 0;
			float x_next = x - radius_delta;
			float z_next = 0.0;
			for (int j = 0; j < m_segmentsX; j++) {
				float newx = x*cos(angle) - z*sin(angle);
				float newz = x*sin(angle) + z*cos(angle);

				float newx_next = x_next*cos(angle) - z_next*sin(angle);
				float newz_next = x_next*sin(angle) + z_next*cos(angle);

				normalizeNormal(x, NORMAL_Y, z);
				glVertex3f(x, y, z);  
				normalizeNormal(newx, NORMAL_Y, newz);
				glVertex3f(newx, y, newz); 
				normalizeNormal(newx_next, NORMAL_Y, newz_next);
				glVertex3f(newx_next, y + height, newz_next); 

				normalizeNormal(newx_next, NORMAL_Y, newz_next);
				glVertex3f(newx_next, y + height, newz_next);  
				normalizeNormal(x_next, NORMAL_Y, z_next);
				glVertex3f(x_next, y + height, z_next); 
				normalizeNormal(x, NORMAL_Y, z);
				glVertex3f(x, y, z); 

				x = newx;
				z = newz;
				x_next = newx_next;
				z_next = newz_next;
			}
			radius = radius - radius_delta;
			y = y + height;
		}
		glEnd();
	};

	void drawCap() {
		float x = 0.5;
		float z = 0.0;
		float angle = 2 * PI / (float)m_segmentsX;
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
	};

	void drawBodyNormal() {
		float x = 0.5;
		float z = 0.0;
		float y = -0.5;
		float angle = 2 * PI / (float)m_segmentsX;
		float height = 1.0 / (float)m_segmentsY;

		float radius = 0.5;
		float radius_delta = 0.5 / (float)m_segmentsY;

		glBegin(GL_LINES);
		for (int i = 0; i < m_segmentsY; i++) {
			x = radius;
			z = 0;
			float x_next = x - radius_delta;
			float z_next = 0.0;
			for (int j = 0; j < m_segmentsX; j++) {
				float newx = x*cos(angle) - z*sin(angle);
				float newz = x*sin(angle) + z*cos(angle);

				float newx_next = x_next*cos(angle) - z_next*sin(angle);
				float newz_next = x_next*sin(angle) + z_next*cos(angle);

				Point p (x, y, z);
				Vector normal (x, NORMAL_Y, z);
				normal.normalize();
				Point dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());

				
				p = Point (newx, y, newz);
				normal = Vector(newx, NORMAL_Y, newz);
				normal.normalize();
				dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());


				p = Point (newx_next, y + height, newz_next);
				normal = Vector(newx_next, NORMAL_Y, newz_next);
				normal.normalize();
				dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());



				p = Point (newx_next, y + height, newz_next);
				normal = Vector(newx_next, NORMAL_Y, newz_next);
				normal.normalize();
				dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());


				p = Point (x_next, y + height, z_next);
				normal = Vector(x_next, NORMAL_Y, z_next);
				normal.normalize();
				dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());


				p = Point (x, y, z);
				normal = Vector (x, NORMAL_Y, z);
				normal.normalize();
				dest = p + normal*0.1;
				glVertex3dv(p.unpack());
				glVertex3dv(dest.unpack());

				x = newx;
				z = newz;
				x_next = newx_next;
				z_next = newz_next;
			}
			radius = radius - radius_delta;
			y = y + height;
		}
		glEnd();
	};

};

#endif