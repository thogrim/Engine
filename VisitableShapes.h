////////////////////////////////////////////////////////////
//
//	Reimplemented basic sfml shapes to allow applying 
//	Visitor pattern
//	
//	These shapes provide the same functionality as sfml
//	shapes(sf::RectangleShape, sf::CircleShape, 
//	sf::ConvexShape). They also implement accept() method
//	used for visitors, and clone() method so you can
//	copy them if you store them dynamically as pointer
//	to VisitableShape
//
////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include "ShapeVisitors/ShapeVisitor.h"


class VisitableShape : public sf::Shape{
public:
	VisitableShape();
	virtual ~VisitableShape();
	virtual unsigned int getPointCount() const = 0;
	virtual sf::Vector2f getPoint(unsigned int index) const = 0;
	virtual void accept(ShapeVisitor& v, const sf::Vector2f& position) const = 0;
	virtual VisitableShape* clone() = 0;
};

class VisitableCircleShape : public VisitableShape{
public:
	explicit VisitableCircleShape(float radius = 0, unsigned int pointCount = 30);
	~VisitableCircleShape();
	void setRadius(float radius);
	float getRadius() const;
	void setPointCount(unsigned int count);
	virtual unsigned int getPointCount() const override;
	virtual sf::Vector2f getPoint(unsigned int index) const override;
	void accept(ShapeVisitor& v, const sf::Vector2f& position) const;
	virtual VisitableShape* clone();
private:
	float radius_;
	unsigned int pointCount_;
};

class VisitableRectangleShape : public VisitableShape{
public:
	explicit VisitableRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0));
	~VisitableRectangleShape();
	void setSize(const sf::Vector2f& size);
	const sf::Vector2f& getSize() const;
	virtual unsigned int getPointCount() const override;
	virtual sf::Vector2f getPoint(unsigned int index) const override;
	void accept(ShapeVisitor& v, const sf::Vector2f& position) const;
	virtual VisitableShape* clone();
private:
	sf::Vector2f size_;
};

class VisitableConvexShape : public VisitableShape{
public:
	explicit VisitableConvexShape(unsigned int pointCount = 0);
	~VisitableConvexShape();
	void setPointCount(unsigned int count);
	virtual unsigned int getPointCount() const override;
	void setPoint(unsigned int index, const sf::Vector2f& point);
	virtual sf::Vector2f getPoint(unsigned int index) const override;
	void accept(ShapeVisitor& v, const sf::Vector2f& position) const;
	virtual VisitableShape* clone();
private:
	std::vector<sf::Vector2f> points_;
};