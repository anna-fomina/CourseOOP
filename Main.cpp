#include <iostream>
#include "Shapes.h"
#include "ShapeFactory.h"

int main() {
	Container<Shape*> shapes;
	for (int i = 0; i < 100; ++i) {
		shapes.pushFront(ShapeFactory::makeRandomShape());
	}
	std::cout << "ShapesCount: " << Shape::getCount() << std::endl;

	std::cout << "Shapes:" << std::endl;
	shapes.forEach(
		[](Shape * const& shape){
			std::cout << shape->print() << std::endl;
		}
	);

	shapes.forEach(
		[](Shape * const& shape) {
			delete shape;
		}
	);

	std::cout << "ShapesCount: " << Shape::getCount() << std::endl;

	return 0;
}