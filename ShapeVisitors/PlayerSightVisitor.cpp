#include "PlayerSightVisitor.h"

void PlayerSightVisitor::visit(const VisitableCircleShape& circ, const sf::Vector2f& position){
	//TODO
}

void PlayerSightVisitor::visit(const VisitableRectangleShape& rect, const sf::Vector2f& position){
	if (playerPosition_.x < rect.getPoint(1).x + position.x &&
		playerShape_.getPoint(1).x + playerPosition_.x > position.x){
		if (playerShape_.getPoint(0).y + playerPosition_.y >= rect.getPoint(2).y + position.y){
			sight_ = PlayerSight::ABOVE;
		}
		else if (playerShape_.getPoint(2).y + playerPosition_.y <= position.y){
			sight_ = PlayerSight::BELOW;
		}
	}
	else if (playerShape_.getPoint(0).y + playerPosition_.y<rect.getPoint(2).y + position.y &&
		playerShape_.getPoint(2).y + playerPosition_.y>rect.getPoint(0).y + position.y){
		if (playerShape_.getPoint(1).x + playerPosition_.x <= rect.getPoint(0).x + position.x){
			sight_ = PlayerSight::RIGHT;
		}
		else if (playerShape_.getPoint(0).x + playerPosition_.x >= rect.getPoint(1).x + position.x){
			sight_ = PlayerSight::LEFT;
		}
	}
}

void PlayerSightVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){
	//TODO
}