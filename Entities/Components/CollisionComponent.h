#pragma once

#include "../../VisitableShapes.h"

struct CollisionComponent{
	CollisionComponent(VisitableShape* shape, sf::Transformable& transform)
		:shape_(shape),
		transform_(transform){
		shape_->setOutlineColor(sf::Color::Magenta);
		shape_->setOutlineThickness(-2.f);
		shape_->setFillColor(sf::Color::Transparent);
	}
	CollisionComponent(const CollisionComponent& cc)
		:shape_(cc.shape_->clone()),
		transform_(cc.transform_){
		shape_->setOutlineColor(sf::Color::Magenta);
		shape_->setOutlineThickness(-2.f);
		shape_->setFillColor(sf::Color::Transparent);
	}
	~CollisionComponent(){
		delete shape_;
	}
	VisitableShape* shape_;
	sf::Transformable& transform_;
};