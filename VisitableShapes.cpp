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

inline void VisitableCircleShape::setRadius(float radius){
	radius_ = radius;
	update();
}

inline float VisitableCircleShape::getRadius() const{
	return radius_;
}

inline void VisitableCircleShape::setPointCount(unsigned int pointCount) {
	assert(pointCount > 2);
	pointCount_ = pointCount;
	update();
}

inline unsigned int VisitableCircleShape::getPointCount() const{
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

inline void VisitableCircleShape::accept(ShapeVisitor& v){
	v.visit(*this);
}

inline VisitableShape* VisitableCircleShape::clone(){
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

inline void VisitableRectangleShape::setSize(const sf::Vector2f& size){
	size_ = size;
	update();
}

inline const sf::Vector2f& VisitableRectangleShape::getSize() const{
	return size_;
}

inline unsigned int VisitableRectangleShape::getPointCount() const{
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

inline void VisitableRectangleShape::accept(ShapeVisitor& v){
	v.visit(*this);
}

inline VisitableShape* VisitableRectangleShape::clone(){
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

inline void VisitableConvexShape::setPointCount(unsigned int count){
	assert(count > 2);
	points_.reserve(count);
	update();
}

inline unsigned int VisitableConvexShape::getPointCount() const{
	return points_.capacity();
}

inline void VisitableConvexShape::setPoint(unsigned int index, const sf::Vector2f& point){
	assert(index < points_.capacity());
	points_[index] = point;
	update();
}

inline sf::Vector2f VisitableConvexShape::getPoint(unsigned int index) const{
	assert(index < points_.capacity());
	return points_[index];
}

inline void VisitableConvexShape::accept(ShapeVisitor& v){
	v.visit(*this);
}

inline VisitableShape* VisitableConvexShape::clone(){
	return new VisitableConvexShape(*this);
}