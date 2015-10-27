#include "PlayerCollisionVisitor.h"
#include "../VisitableShapes.h"

void PlayerCollisionVisitor::visit(const VisitableCircleShape& entityCirc, const sf::Vector2f& entityPos){
	//TODO
}

void PlayerCollisionVisitor::visit(const VisitableRectangleShape& entityRect, const sf::Vector2f& entityPos){
	sf::Vector2f playerPos(player_.getPosition());
	sf::Vector2f playerSize(player_.getShape().getLocalBounds().width, player_.getShape().getLocalBounds().height);
	switch (sight_){

	case PlayerSight::ABOVE:
		if (playerPos.y < entityRect.getPoint(2).y + entityPos.y)
			player_.setPosition(playerPos.x, entityRect.getPoint(2).y + entityPos.y);
		break;

	case PlayerSight::RIGHT:
		if (playerPos.x + playerSize.x > entityPos.x)
			player_.setPosition(entityPos.x - playerSize.x, playerPos.y);
		break;

	case PlayerSight::BELOW:
		if (playerPos.y + playerSize.y > entityPos.y)
			player_.setPosition(playerPos.x, entityPos.y - playerSize.y);
		break;

	case PlayerSight::LEFT:
		if (playerPos.x < entityRect.getPoint(1).x + entityPos.x)
			player_.setPosition(entityRect.getPoint(1).x + entityPos.x, playerPos.y);
		break;
	}
}

void PlayerCollisionVisitor::visit(const VisitableConvexShape& conv, const sf::Vector2f& position){
	//TODO
}