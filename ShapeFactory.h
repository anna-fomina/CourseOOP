#pragma once
#include "Shapes.h"

class ShapeFactory {
public:
	static Shape * makeRandomShape() {
		switch (rand() % SHAPETYPESCOUNT) {
			case 0:
				return makePoint();
			case 1:
				return makeCircle();
			case 2:
				return makeRect();
			case 3:
				return makeSquare();
			case 4:
				return makePolyline();
			case 5:
				return makePolygon();
			default:
				return nullptr;
			}
	}

	static Point * makePoint()	{
		return new Point(randomDouble(-MAXRAND, MAXRAND), randomDouble(-MAXRAND, MAXRAND));
	}

	static Circle * makeCircle() {
		Point * center = makePoint();
		Circle * circle = new Circle(*center, randomDouble(-MAXRAND, MAXRAND));
		delete center;
		return circle;
	}

	static Rect * makeRect() {
		Point * point1 = makePoint();
		Point * point2 = makePoint();
		Rect * rect = new Rect(*point1, *point2);
		delete point1;
		delete point2;
		return rect;
	}

	static Square * makeSquare() {
		Point * point = makePoint();
		Square * square = new Square(*point, randomDouble(-MAXRAND, MAXRAND));
		delete point;
		return square;
	}

	static Polyline * makePolyline() {
		Polyline * polyline = new Polyline();
		for (int i = 0, pointCount = 1 + rand() % MAXPOINTS; i < pointCount; ++i) {
			Point * point = makePoint();
			polyline->addPoint(*point);
			delete point;
		}
		return polyline;
	}

	static Polygon* makePolygon() {
		Polygon * polygon = new Polygon();
		for (int i = 0, pointCount = 1 + rand() % MAXPOINTS; i < pointCount + 3; ++i) {
			Point* point = makePoint();
			polygon->addPoint(*point);
			delete point;
		}
		return polygon;
	}

private:
	static double randomDouble(double min, double max) {
		double random = (double)rand() / RAND_MAX;
		return min + random * (max - min);
	}

	static unsigned int const MAXPOINTS = 16;
	static double constexpr MAXRAND = 64;
	static unsigned int const SHAPETYPESCOUNT = 6;

};