#pragma once

class Shape;
class Circle;
class Box;
class Plane;

class CollisionFunctions
{
	bool CollideShapes(Shape* shape1, Shape* shape2);

	bool CollideCircleWithCircle(Circle* shape1, Circle* shape2);
	bool CollideCircleWithBox(Circle* shape1, Box* shape2);
	bool CollideCircleWithPlane(Circle* shape1, Plane* shape2);
};