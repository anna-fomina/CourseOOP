#pragma once
#define _USE_MATH_DEFINES
#include "Base.h"
#include <math.h>
#include "Container.h"

class Shape : public Printable {
public:
	Shape()	{
		++count;
	}

	Shape(Shape const& shape) {
		++count;
	}

	virtual ~Shape() {
		--count;
	}

	static size_t getCount() {
		return count;
	}

private:
	static size_t count;
};

size_t Shape::count = 0;

class Point : public Shape, public Named {
public:
	Point(double x, double y) : Named("Point"), x(x), y(y) {}
	std::string print() const {
		return Named::print() + " (" + std::to_string(x) + "," + std::to_string(y) + ")";
	}
	static double distance(const Point& point1, const Point& point2);
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
private:
	double x;
	double y;
};

double Point::distance(const Point& point1, const Point& point2) {
	return sqrt(pow(point1.getX() - point2.getX(), 2) + pow(point1.getY() - point2.getY(), 2));
}


class Circle : public Shape, public Named {
public:
	Circle(const Point& center, double radius) : Named("Circle"), center(center), radius(radius) {}
	std::string print() const {
		return Named::print() + ": "
			+ "center: " + center.print()
			+ ", radius: " + std::to_string(radius)
			+ ", area: " + std::to_string(getArea())
			;
	}
	double getArea() const {
		return radius * radius * M_PI;
	}
private:
	Point center;
	double radius;
};

class Rect : public Shape, public Named {
public:
	Rect(const Point& point1, const Point& point2) : Named("Rect"), point1(point1), point2(point2) {}
	std::string print() const {
		return Named::print() + ": "
			+ "point1: " + point1.print()
			+ ", point2: " + point2.print()
			+ ", perimeter: " + std::to_string(getPerimeter())
			+ ", area: " + std::to_string(getArea())
			;
	}
	double getPerimeter() const {
		return 2 * (getSideX() + getSideY());
	}
	double getArea() const {
		return getSideX() * getSideY();
	}
	double getSideX() const {
		return fabs(point1.getX() - point2.getX());
	}
	double getSideY() const {
		return fabs(point1.getY() - point2.getY());
	}
private:
	Point point1;
	Point point2;
};
/*
	
*/
class Square : public Shape, public Named {
public:
	Square(const Point& point, double side) : Named("Square"), point(point), side(side) {}
	std::string print() const {
		return Named::print() + ": "
			+ "point: " + point.print()
			+ ", side: " + std::to_string(side)
			+ ", perimeter: " + std::to_string(getPerimeter())
			+ ", area: " + std::to_string(getArea())
			;
	}
	double getPerimeter() const {
		return 4 * side;
	}
	double getArea() const {
		return side * side;
	}
private:
	Point point;
	double side;
};

class Polyline : public Shape, virtual public Named {
public:
	Polyline() : Named("Polyline"), points(Container<Point>()) {}
	Polyline(const Container<Point>& points) : Named("Polyline"), points(points)
	{}
	void addPoint(const Point& point) {
		points.pushBack(point);
	}
	virtual double getLength() const {
		double length = 0;
		Point prevPoint = points.getFront();
		points.forEach(
			[&length, &prevPoint](const Point& nextPoint) {
				length += Point::distance(prevPoint, nextPoint);
				prevPoint = nextPoint;
			}
		);
		return length;
	}
	std::string print() const {
		return Named::print() + ": "
			+ " number of points: " + std::to_string(points.getSize())
			+ ", length: " + std::to_string(getLength())
		;
	}
protected:
	Container<Point> points;
};

class Polygon : public Polyline, virtual public Named {
public:
	Polygon() : Named("Polygon"), Polyline() {}
	Polygon(const Container<Point>& points) : Named("Polygon"), Polyline(points) {}
	double getLength() const {
		return Polyline::getLength() + Point::distance(points.getFront(), points.getBack());
	}
	std::string print() const {
		return Named::print() + ": "
			+ " number of points: " + std::to_string(points.getSize())
			+ ", perimeter: " + std::to_string(getLength())
			;
	}
};