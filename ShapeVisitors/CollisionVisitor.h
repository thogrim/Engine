////////////////////////////////////////////////////////////
//
//	Collision Visitor used for collision detection
//
////////////////////////////////////////////////////////////
#include "ShapeVisitor.h"

struct CircleShapeVisitor : public ShapeVisitor{
	CircleShapeVisitor(const VisitableCircleShape& circle, const sf::Vector2f& position)
		:circle_(circle),
		position_(position),
		collisionExists_(false){
	}
	void visit(const VisitableCircleShape& circ, const sf::Vector2f& position);
	void visit(const VisitableRectangleShape& rect, const sf::Vector2f& position);
	void visit(const VisitableConvexShape& conv, const sf::Vector2f& position);

	const VisitableCircleShape& circle_;
	const sf::Vector2f& position_;
	bool collisionExists_;
};

struct RectangleShapeVisitor : public ShapeVisitor{
	RectangleShapeVisitor(const VisitableRectangleShape& rectangle, const sf::Vector2f& position)
		:rectangle_(rectangle),
		position_(position),
		collisionExists_(false){
	}
	void visit(const VisitableCircleShape& circ, const sf::Vector2f& position);
	void visit(const VisitableRectangleShape& rect, const sf::Vector2f& position);
	void visit(const VisitableConvexShape& conv, const sf::Vector2f& position);

	const VisitableRectangleShape& rectangle_;
	const sf::Vector2f& position_;
	bool collisionExists_;
};

struct ConvexShapeVisitor : public ShapeVisitor{
	ConvexShapeVisitor(const VisitableConvexShape& convex, const sf::Vector2f& position)
		:convex_(convex),
		position_(position),
		collisionExists_(false){
	}
	void visit(const VisitableCircleShape& circ, const sf::Vector2f& position);
	void visit(const VisitableRectangleShape& rect, const sf::Vector2f& position);
	void visit(const VisitableConvexShape& conv, const sf::Vector2f& position);

	const VisitableConvexShape& convex_;
	const sf::Vector2f& position_;
	bool collisionExists_;
};

class VisitableShape;

struct CollisionVisitor: public ShapeVisitor{
public:
	CollisionVisitor(const VisitableShape& shape, const sf::Vector2f& position)
		:shape_(shape),
		position_(position),
		collisionExists_(false){
	}

	void visit(const VisitableCircleShape& circ, const sf::Vector2f& position);
	void visit(const VisitableRectangleShape& rect, const sf::Vector2f& position);
	void visit(const VisitableConvexShape& conv, const sf::Vector2f& position);

	const VisitableShape& shape_;
	const sf::Vector2f& position_;
	bool collisionExists_;
};