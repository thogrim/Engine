#pragma once

#include "../../VisitableShapes.h"
#include "../../PlayerSight.h"

struct CollisionComponent{
	CollisionComponent(VisitableShape* shape, sf::Transformable& transform)
		:shape_(shape),
		transform_(transform),
		playerSight_(PlayerSight::NONE){
		shape_->setFillColor(sf::Color(255,0,255,128));
	}
	CollisionComponent(const CollisionComponent& cc)
		:shape_(cc.shape_->clone()),
		transform_(cc.transform_),
		playerSight_(cc.playerSight_){
		shape_->setFillColor(sf::Color(255, 0, 255, 128));
	}
	~CollisionComponent(){
		delete shape_;
	}
	VisitableShape* shape_;
	sf::Transformable& transform_;
	PlayerSight playerSight_;
};