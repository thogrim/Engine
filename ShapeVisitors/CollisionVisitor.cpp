#include "CollisionVisitor.h"
#include "../MathUtils.h"
#include "../VisitableShapes.h"

void CircleShapeVisitor::visit(const VisitableCircleShape& circ, const sf::Vector2f& position){
	sf::Vector2f center1(position_ + sf::Vector2f(circle_.getRadius(), circle_.getRadius()));
	sf::Vector2f center2(position + sf::Vector2f(circ.getRadius(), circ.getRadius()));
	if (Math::distance(center1, center2) < circ.getRadius() + circle_.getRadius())
		collisionExists_ = true;
}

void CircleShapeVisitor::visit(const VisitableRectangleShape& rect, const sf::Vector2f& position){

}

void CircleShapeVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){

}

void RectangleShapeVisitor::visit(const VisitableCircleShape& circ, const sf::Vector2f& position){

}

void RectangleShapeVisitor::visit(const VisitableRectangleShape& rect, const sf::Vector2f& position){
	//checks point containing, not intersection
	//for (unsigned int i = 0; i < rectangle_.getPointCount(); ++i){
	//	if (rect.getPoint(0).x + position.x < rectangle_.getPoint(i).x + position_.x &&
	//		rect.getPoint(1).x + position.x > rectangle_.getPoint(i).x + position_.x &&
	//		rect.getPoint(0).y + position.y < rectangle_.getPoint(i).y + position_.y &&
	//		rect.getPoint(2).y + position.y > rectangle_.getPoint(i).y + position_.y){
	//		collisionExists_ = true;
	//		break;
	//	}
	//}

	//checks intersection
	if (rect.getPoint(0).x + position.x < rectangle_.getPoint(1).x + position_.x &&
		rect.getPoint(1).x + position.x > rectangle_.getPoint(0).x + position_.x &&
		rect.getPoint(0).y + position.y < rectangle_.getPoint(2).y + position_.y &&
		rect.getPoint(2).y + position.y > rectangle_.getPoint(0).y + position_.y)
		collisionExists_ = true;
}

void RectangleShapeVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){

}

void ConvexShapeVisitor::visit(const VisitableCircleShape& circ, const sf::Vector2f& position){

}

void ConvexShapeVisitor::visit(const VisitableRectangleShape& rect, const sf::Vector2f& position){

}

void ConvexShapeVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){

}

void CollisionVisitor::visit(const VisitableCircleShape& circ, const sf::Vector2f& position){
	CircleShapeVisitor circVisitor(circ, position);
	shape_.accept(circVisitor, position_);
	collisionExists_ = circVisitor.collisionExists_;
}

void CollisionVisitor::visit(const VisitableRectangleShape& rect, const sf::Vector2f& position){
	RectangleShapeVisitor rectVisitor(rect, position);
	shape_.accept(rectVisitor, position_);
	collisionExists_ = rectVisitor.collisionExists_;
}

void CollisionVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){
	ConvexShapeVisitor convVisitor(conv, position);
	shape_.accept(convVisitor, position_);
	collisionExists_ = convVisitor.collisionExists_;
}