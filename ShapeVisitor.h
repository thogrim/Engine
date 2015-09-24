/**********************************
	Interface for Shape Visitor
**********************************/

#pragma once

class VisitableCircleShape;
class VisitableRectangleShape;
class VisitableConvexShape;

class ShapeVisitor{
public:
	virtual void visit(const VisitableCircleShape&) = 0;
	virtual void visit(const VisitableRectangleShape&) = 0;
	virtual void visit(const VisitableConvexShape&) = 0;
};