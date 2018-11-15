#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"
#include "Algebra.h"

class Torus : public Shape {
public:
	Torus() {};
	~Torus() {};

	void draw() {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		drawBody();
		glPopMatrix();
	};

	void drawNormal() {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		drawBodyNormal();
		glPopMatrix();
	};
private:

	void drawBody() {

		float radius = 0.15;
		float radiusRing = 0.5;
		float angle_delta = 2 * PI / (float)m_segmentsX;
		float angleRing_delta = 2 * PI / (float)m_segmentsY;

		glBegin(GL_TRIANGLES);
		float angleRing = 0;
		for (int i = 0; i < m_segmentsY; i++) {
			float angle = 0;
			for (int j = 0; j < m_segmentsX; j++) {
				Point origin(0, 0, 0);
				Point p (radius, 0, 0);
				Point pt = rotZ_mat(angle) * p;
				Point newPt = rotZ_mat(angle + angle_delta)*p;

				Matrix transform1 = rotY_mat(angleRing) * trans_mat(Vector(radiusRing - radius, 0, 0));

				Point origin_ring = transform1 * origin;
				Point pt_ring =  transform1 * pt;
				Point newPt_ring = transform1 * newPt;

				Matrix transform2 = rotY_mat(angleRing + angleRing_delta) * trans_mat(Vector(radiusRing - radius, 0, 0));

				Point origin_ring_next = transform2 * origin;
				Point pt_ring_next =  transform2 * pt;
				Point newPt_ring_next = transform2  * newPt;

				normalizeNormal(pt_ring - origin_ring);
				glVertex3dv(pt_ring.unpack()); 
				normalizeNormal(newPt_ring - origin_ring);
				glVertex3dv(newPt_ring.unpack());
				normalizeNormal(newPt_ring_next - origin_ring_next);
				glVertex3dv(newPt_ring_next.unpack());

				normalizeNormal(newPt_ring_next - origin_ring_next);
				glVertex3dv(newPt_ring_next.unpack());
				normalizeNormal(pt_ring_next - origin_ring_next);
				glVertex3dv(pt_ring_next.unpack());
				normalizeNormal(pt_ring - origin_ring);
				glVertex3dv(pt_ring.unpack());

				angle = angle + angle_delta;
			}
			angleRing = angleRing + angleRing_delta;
		}
		glEnd();
	};

	void drawBodyNormal() {

		float radius = 0.15;
		float radiusRing = 0.5;
		float angle_delta = 2 * PI / (float)m_segmentsX;
		float angleRing_delta = 2 * PI / (float)m_segmentsY;

		glBegin(GL_LINES);
		float angleRing = 0;
		for (int i = 0; i < m_segmentsY; i++) {
			float angle = 0;
			for (int j = 0; j < m_segmentsX; j++) {
				Point origin(0, 0, 0);
				Point p (radius, 0, 0);
				Point pt = rotZ_mat(angle) * p;
				Point newPt = rotZ_mat(angle + angle_delta)*p;

				Matrix transform1 = rotY_mat(angleRing) * trans_mat(Vector(radiusRing - radius, 0, 0));

				Point origin_ring = transform1 * origin;
				Point pt_ring =  transform1 * pt;
				Point newPt_ring = transform1 * newPt;

				Matrix transform2 = rotY_mat(angleRing + angleRing_delta) * trans_mat(Vector(radiusRing - radius, 0, 0));

				Point origin_ring_next = transform2 * origin;
				Point pt_ring_next =  transform2 * pt;
				Point newPt_ring_next = transform2  * newPt;

				Vector v = pt_ring - origin_ring;
				v.normalize();
				glVertex3dv(pt_ring.unpack()); glVertex3dv((pt_ring+v*0.1).unpack()); 
				v = newPt_ring - origin_ring;
				v.normalize();
				glVertex3dv(newPt_ring.unpack()); glVertex3dv((newPt_ring+v*0.1).unpack()); 
				v = newPt_ring_next - origin_ring_next;
				v.normalize();
				glVertex3dv(newPt_ring_next.unpack()); glVertex3dv((newPt_ring_next+v*0.1).unpack()); 

				v = (newPt_ring_next - origin_ring_next);
				v.normalize();
				glVertex3dv(newPt_ring_next.unpack()); glVertex3dv((newPt_ring_next+v*0.1).unpack()); 
				v = (pt_ring_next - origin_ring_next);
				v.normalize();
				glVertex3dv(pt_ring_next.unpack()); glVertex3dv((pt_ring_next+v*0.1).unpack()); 
				v = (pt_ring - origin_ring);
				v.normalize();
				glVertex3dv(pt_ring.unpack()); glVertex3dv((pt_ring+v*0.1).unpack()); 

				angle = angle + angle_delta;
			}
			angleRing = angleRing + angleRing_delta;
		}
		glEnd();
	};
};

#endif