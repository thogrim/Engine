#include "VisitableShapes.h"

/********************
	VisitableShape
********************/

VisitableShape::VisitableShape()
	:sf::Shape(){
	//update();
}

VisitableShape::~VisitableShape(){
}

/**************************
	VisitableCircleShape
**************************/

VisitableCircleShape::VisitableCircleShape(float radius, unsigned int pointCount)
	:VisitableShape(),
	radius_(radius),
	pointCount_(pointCount){
	update();
}

VisitableCircleShape::~VisitableCircleShape(){
}

void VisitableCircleShape::setRadius(float radius){
	radius_ = radius;
	update();
}

float VisitableCircleShape::getRadius() const{
	return radius_;
}

void VisitableCircleShape::setPointCount(unsigned int pointCount) {
	assert(pointCount > 2);
	pointCount_ = pointCount;
	update();
}

unsigned int VisitableCircleShape::getPointCount() const{
	return pointCount_;
}

sf::Vector2f VisitableCircleShape::getPoint(unsigned int index) const{
	assert(index < pointCount_);
	static const float pi = 3.141592654f;
	float angle = index * 2 * pi / pointCount_ - pi / 2;
	float x = std::cos(angle) * radius_;
	float y = std::sin(angle) * radius_;
	return sf::Vector2f(radius_+x,radius_+y);
}

void VisitableCircleShape::accept(ShapeVisitor& v, const sf::Vector2f& position) const{
	v.visit(*this, position);
}

VisitableShape* VisitableCircleShape::clone(){
	return new VisitableCircleShape(*this);
}

/*****************************
	VisitableRectangleShape
*****************************/

VisitableRectangleShape::VisitableRectangleShape(const sf::Vector2f& size)
	:VisitableShape(),
	size_(size){
	update();
}

VisitableRectangleShape::~VisitableRectangleShape(){
}

void VisitableRectangleShape::setSize(const sf::Vector2f& size){
	size_ = size;
	update();
}

const sf::Vector2f& VisitableRectangleShape::getSize() const{
	return size_;
}

unsigned int VisitableRectangleShape::getPointCount() const{
	return 4;
}

sf::Vector2f VisitableRectangleShape::getPoint(unsigned int index) const{
	assert(index < 4);
	if (index == 0)
		return sf::Vector2f(0.f, 0.f);
	else if (index == 1)
		return sf::Vector2f(size_.x, 0.f);
	else if (index == 2)
		return size_;
	else if (index == 3)
		return sf::Vector2f(0.f, size_.y);
	//else
	//	return sf::Vector2f();
}

void VisitableRectangleShape::accept(ShapeVisitor& v, const sf::Vector2f& position) const{
	v.visit(*this, position);
}

VisitableShape* VisitableRectangleShape::clone(){
	return new VisitableRectangleShape(*this);
}

/**************************
	VisitableConvexShape
**************************/

VisitableConvexShape::VisitableConvexShape(unsigned int pointCount)
	:VisitableShape(),
	points_(pointCount, sf::Vector2f()){
	update();
}

VisitableConvexShape::~VisitableConvexShape(){
}

void VisitableConvexShape::setPointCount(unsigned int count){
	assert(count > 2);
	points_.reserve(count);
	update();
}

unsigned int VisitableConvexShape::getPointCount() const{
	return points_.capacity();
}

void VisitableConvexShape::setPoint(unsigned int index, const sf::Vector2f& point){
	assert(index < points_.capacity());
	points_[index] = point;
	update();
}

sf::Vector2f VisitableConvexShape::getPoint(unsigned int index) const{
	assert(index < points_.capacity());
	return points_[index];
}

void VisitableConvexShape::accept(ShapeVisitor& v, const sf::Vector2f& position) const{
	v.visit(*this, position);
}

VisitableShape* VisitableConvexShape::clone(){
	return new VisitableConvexShape(*this);
}