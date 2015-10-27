////////////////////////////////////////////////////////////
//
//	Interface for Shape Visitors
//
///////////////////////////////////////////////////////////

#pragma once

#include <SFML/System/Vector2.hpp>

class VisitableCircleShape;
class VisitableRectangleShape;
class VisitableConvexShape;

class ShapeVisitor{
public:
	virtual void visit(const VisitableCircleShape&, const sf::Vector2f& position) = 0;
	virtual void visit(const VisitableRectangleShape&, const sf::Vector2f& position) = 0;
	virtual void visit(const VisitableConvexShape&, const sf::Vector2f& position) = 0;
};